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

#include "api/buffer.h"

#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace platforms {
namespace darwinn {
namespace {

TEST(BufferTest, WrappedBuffer) {
  std::vector<unsigned char> data = {1, 2, 3, 4, 5};
  Buffer buffer(data.data(), data.size());

  EXPECT_TRUE(buffer.IsValid());
  EXPECT_TRUE(buffer.IsPtrType());
  EXPECT_FALSE(buffer.FileDescriptorBacked());
  EXPECT_FALSE(buffer.IsDramType());
  EXPECT_EQ(buffer.size_bytes(), 5);
  EXPECT_EQ(buffer.ptr(), data.data());
}

TEST(BufferTest, AllocatedBuffer) {
  bool freed = false;
  auto* ptr = new unsigned char[10];
  auto free_callback = [&freed](void* p) {
    delete[] static_cast<unsigned char*>(p);
    freed = true;
  };

  {
    auto allocated = std::make_shared<AllocatedBuffer>(ptr, 10, free_callback);
    Buffer buffer(allocated);
    EXPECT_TRUE(buffer.IsValid());
    EXPECT_TRUE(buffer.IsPtrType());
    EXPECT_TRUE(buffer.IsManagedType());
    EXPECT_EQ(buffer.ptr(), ptr);
    EXPECT_EQ(buffer.size_bytes(), 10);
  }
  EXPECT_TRUE(freed);
}

TEST(BufferTest, Slice) {
  std::vector<unsigned char> data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  Buffer buffer(data.data(), data.size());

  Buffer slice = buffer.Slice(2, 4);
  EXPECT_EQ(slice.size_bytes(), 4);
  EXPECT_EQ(slice.ptr(), data.data() + 2);
}

TEST(BufferTest, Move) {
  std::vector<unsigned char> data = {1, 2, 3};
  Buffer b1(data.data(), data.size());
  Buffer b2 = std::move(b1);

  EXPECT_FALSE(b1.IsValid());
  EXPECT_TRUE(b2.IsValid());
  EXPECT_EQ(b2.size_bytes(), 3);
  EXPECT_EQ(b2.ptr(), data.data());
}

}  // namespace
}  // namespace darwinn
}  // namespace platforms
