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
// limitations under the License.

#include "driver/memory/mmu_mapper.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "api/buffer.h"
#include "driver/memory/address_utilities.h"
#include "port/status.h"

namespace platforms {
namespace darwinn {
namespace driver {
namespace {

using ::testing::_;
using ::testing::Return;

class MockMmuMapper : public MmuMapper {
 public:
  MOCK_METHOD(Status, Open, (int), (override));
  MOCK_METHOD(Status, Close, (), (override));
  MOCK_METHOD(Status, DoMap, (const void*, int, uint64, DmaDirection), (override));
  MOCK_METHOD(Status, DoUnmap, (const void*, int, uint64), (override));
};

TEST(MmuMapperTest, MapBuffer) {
  MockMmuMapper mapper;
  unsigned char data[4096] __attribute__((aligned(4096)));
  Buffer buffer(data, 4096);
  uint64 device_addr = 0x1000;

  EXPECT_CALL(mapper, DoMap(data, 1, device_addr, DmaDirection::kBidirectional))
      .WillOnce(Return(Status()));

  EXPECT_TRUE(mapper.Map(buffer, device_addr).ok());
}

TEST(MmuMapperTest, UnmapBuffer) {
  MockMmuMapper mapper;
  unsigned char data[4096] __attribute__((aligned(4096)));
  Buffer buffer(data, 4096);
  uint64 device_addr = 0x1000;

  EXPECT_CALL(mapper, DoUnmap(data, 1, device_addr))
      .WillOnce(Return(Status()));

  EXPECT_TRUE(mapper.Unmap(buffer, device_addr).ok());
}

}  // namespace
}  // namespace driver
}  // namespace darwinn
}  // namespace platforms
