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

#include "api/allocated_buffer.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace platforms {
namespace darwinn {
namespace {

TEST(AllocatedBufferTest, Basic) {
  bool freed = false;
  unsigned char* ptr = new unsigned char[10];
  auto free_callback = [&freed](void* p) {
    delete[] static_cast<unsigned char*>(p);
    freed = true;
  };

  {
    AllocatedBuffer buffer(ptr, 10, free_callback);
    EXPECT_EQ(buffer.ptr(), ptr);
    EXPECT_EQ(buffer.size_bytes(), 10);
    EXPECT_FALSE(freed);
  }

  EXPECT_TRUE(freed);
}

}  // namespace
}  // namespace darwinn
}  // namespace platforms
