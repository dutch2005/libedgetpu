// Copyright 2026 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
12: // limitations under the License.
13: 
14: #include "api/watchdog.h"
15: 
16: #include <atomic>
17: #include <chrono>
18: #include <condition_variable>
19: #include <mutex>
20: #include <thread>
21: #include <vector>
22: 
23: #include <gmock/gmock.h>
24: #include <gtest/gtest.h>
25: 
26: #include "port/ptr_util.h"
27: #include "port/statusor.h"
28: #include "port/timer.h"
29: 
30: namespace platforms {
31: namespace darwinn {
32: namespace api {
33: namespace {
34: 
35: // A high-fidelity fake timer that allows manual stepping of time.
36: // This is essential for testing timeout logic deterministically.
37: class ManualTimer : public Timer {
38:  public:
39:   ManualTimer() = default;
40:   ~ManualTimer() override {
41:     {
42:       std::lock_guard<std::mutex> lock(mutex_);
43:       destroyed_ = true;
44:     }
45:     cv_.notify_all();
46:   }
47: 
48:   Status Set(int64 nanos) override {
49:     {
50:       std::lock_guard<std::mutex> lock(mutex_);
51:       timeout_nanos_ = nanos;
52:       signaled_ = false;
53:     }
54:     cv_.notify_all();
55:     return OkStatus();
56:   }
57: 
58:   StatusOr<uint64> Wait() override {
59:     std::unique_lock<std::mutex> lock(mutex_);
60:     cv_.wait(lock, [this] { return timeout_nanos_ >= 0 || destroyed_; });
61:     
62:     if (destroyed_) {
63:       return 1; // Wake up to exit
64:     }
65: 
66:     if (timeout_nanos_ == 0) {
67:       // Deactivated. Block until re-set or destroyed.
68:       cv_.wait(lock, [this] { return timeout_nanos_ > 0 || destroyed_; });
69:       if (destroyed_) return 1;
70:     }
71: 
72:     // Wait for an explicit manual trigger/signal.
73:     cv_.wait(lock, [this] { return signaled_ || destroyed_; });
74:     
75:     if (destroyed_) {
76:       return 1;
77:     }
78: 
79:     signaled_ = false;
80:     return 1; // One expiration
81:   }
82: 
83:   // Manually trigger the timer expiration.
84:   void Trigger() {
85:     {
86:       std::lock_guard<std::mutex> lock(mutex_);
87:       signaled_ = true;
88:     }
89:     cv_.notify_all();
90:   }
91: 
92:  private:
93:   std::mutex mutex_;
94:   std::condition_variable cv_;
95:   int64 timeout_nanos_{-1};
96:   bool signaled_{false};
97:   bool destroyed_{false};
98: };
99: 
100: TEST(TimerFdWatchdogTest, BasicActivation) {
101:   auto* manual_timer = new ManualTimer();
102:   std::atomic<int64> expired_id{-1};
103:   auto expire_cb = [&expired_id](int64 id) {
104:     expired_id = id;
105:   };
106: 
107:   {
108:     TimerFdWatchdog watchdog(1000000, expire_cb, std::unique_ptr<Timer>(manual_timer));
109:     auto id_or = watchdog.Activate();
110:     ASSERT_TRUE(id_or.ok());
111:     int64 activation_id = id_or.ValueOrDie();
112:     
113:     manual_timer->Trigger();
114:     
115:     // Wait for callback (with timeout to avoid hanging)
116:     for (int i = 0; i < 100 && expired_id == -1; ++i) {
117:       std::this_thread::sleep_for(std::chrono::milliseconds(10));
118:     }
119:     
120:     EXPECT_EQ(expired_id, activation_id);
121:   }
122: }
123: 
124: TEST(TimerFdWatchdogTest, SignalResetsTimer) {
125:   auto* manual_timer = new ManualTimer();
126:   std::atomic<int> expire_count{0};
127:   auto expire_cb = [&expire_count](int64 id) {
128:     expire_count++;
129:   };
130: 
131:   {
132:     TimerFdWatchdog watchdog(1000000, expire_cb, std::unique_ptr<Timer>(manual_timer));
133:     ASSERT_TRUE(watchdog.Activate().ok());
134:     
135:     // Signal should reset the timer (internally calling Set(timeout_ns_))
136:     ASSERT_TRUE(watchdog.Signal().ok());
137:     
138:     // Deactivate should stop it
139:     ASSERT_TRUE(watchdog.Deactivate().ok());
140:   }
141:   EXPECT_EQ(expire_count, 0);
142: }
143: 
144: TEST(CascadeWatchdogTest, MultiLevelExpiration) {
145:   std::atomic<int> level1_count{0};
146:   std::atomic<int> level2_count{0};
147:   
148:   std::vector<CascadeWatchdog::Config> configs = {
149:     {[&level1_count](int64 id) { level1_count++; }, 1000},
150:     {[&level2_count](int64 id) { level2_count++; }, 1000},
151:   };
152: 
153:   // We need to capture the manual timers to trigger them
154:   std::vector<ManualTimer*> timers;
155:   auto maker = [&timers](int64 timeout, Watchdog::Expire expire) {
156:     auto* t = new ManualTimer();
157:     timers.push_back(t);
158:     return gtl::MakeUnique<TimerFdWatchdog>(timeout, std::move(expire), std::unique_ptr<Timer>(t));
159:   };
160: 
161:   {
162:     class TestCascadeWatchdog : public CascadeWatchdog {
163:      public:
164:       TestCascadeWatchdog(const std::vector<Config>& configs, WatchdogMaker maker)
165:           : CascadeWatchdog(configs, std::move(maker)) {}
166:     };
167: 
168:     TestCascadeWatchdog cascade(configs, maker);
169:     ASSERT_TRUE(cascade.Activate().ok());
170:     
171:     ASSERT_EQ(timers.size(), 2);
172:     
173:     // Trigger first level
174:     timers[0]->Trigger();
175:     
176:     // Wait for level 1
177:     for (int i = 0; i < 100 && level1_count == 0; ++i) {
178:       std::this_thread::sleep_for(std::chrono::milliseconds(10));
179:     }
180:     EXPECT_EQ(level1_count, 1);
181:     EXPECT_EQ(level2_count, 0);
182:     
183:     // Trigger second level
184:     timers[1]->Trigger();
185:     
186:     // Wait for level 2
187:     for (int i = 0; i < 100 && level2_count == 0; ++i) {
188:       std::this_thread::sleep_for(std::chrono::milliseconds(10));
189:     }
190:     EXPECT_EQ(level2_count, 1);
191:   }
192: }
193: 
194: TEST(NoopWatchdogTest, Basic) {
195:   NoopWatchdog watchdog;
196:   EXPECT_TRUE(watchdog.Activate().ok());
197:   EXPECT_TRUE(watchdog.Signal().ok());
198:   EXPECT_TRUE(watchdog.Deactivate().ok());
199:   EXPECT_TRUE(watchdog.UpdateTimeout(1000).ok());
200: }
201: 
202: }  // namespace
203: }  // namespace api
204: }  // namespace darwinn
205: }  // namespace platforms
