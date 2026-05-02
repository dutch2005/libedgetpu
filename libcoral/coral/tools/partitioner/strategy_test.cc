/* Copyright 2026 Google LLC
 
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
 
    http://www.apache.org/licenses/LICENSE-2.0
 
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
 
#include "coral/tools/partitioner/strategy.h"
 
#include <vector>
 
#include "coral/tools/partitioner/utils.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "tensorflow/lite/schema/schema_generated.h"
 
namespace coral {
namespace {
 
using tflite::BuiltinOperator_ADD;
using tflite::BuiltinOptions_AddOptions;
 
// Helper to build a simple TFLite model with N Add operations in a chain.
std::vector<uint8_t> CreateSimpleChainModel(int num_ops) {
  flatbuffers::FlatBufferBuilder builder;
  
  std::vector<flatbuffers::Offset<tflite::Operator>> operators;
  std::vector<flatbuffers::Offset<tflite::Tensor>> tensors;
  
  // Create tensors. For N ops in a chain, we need N+1 tensors.
  for (int i = 0; i <= num_ops; ++i) {
    auto name = builder.CreateString("tensor_" + std::to_string(i));
    tensors.push_back(tflite::CreateTensorDirect(builder, /*shape=*/nullptr, tflite::TensorType_FLOAT32, 0, name));
  }
 
  // Create operators
  for (int i = 0; i < num_ops; ++i) {
    std::vector<int32_t> inputs = {i, i}; // Dummy inputs
    std::vector<int32_t> outputs = {i + 1};
    operators.push_back(tflite::CreateOperatorDirect(builder, 0, &inputs, &outputs));
  }
 
  auto subgraph = tflite::CreateSubGraphDirect(builder, &tensors, /*inputs=*/nullptr, /*outputs=*/nullptr, &operators, "main");
  std::vector<flatbuffers::Offset<tflite::SubGraph>> subgraphs = {subgraph};
  
  auto operator_code = tflite::CreateOperatorCode(builder, tflite::BuiltinOperator_ADD, 0);
  std::vector<flatbuffers::Offset<tflite::OperatorCode>> codes = {operator_code};
  
  auto model = tflite::CreateModelDirect(builder, 3, &codes, &subgraphs, "model");
  builder.Finish(model);
  
  auto* buf = builder.GetBufferPointer();
  return std::vector<uint8_t>(buf, buf + builder.GetSize());
}
 
TEST(StrategyTest, GetStrategyFromNumOps) {
  auto model_buf = CreateSimpleChainModel(4);
  const auto* model = tflite::GetModel(model_buf.data());
  
  // Partition 4 ops into 2 segments: [2, 2]
  std::vector<int> num_ops_per_segment = {2, 2};
  auto strategy = GetStrategyFromNumOps(model, num_ops_per_segment);
  
  ASSERT_EQ(strategy.size(), 2);
  
  // First segment should have ops 0, 1
  EXPECT_THAT(strategy[0].target_nodes, testing::UnorderedElementsAre(0, 1));
  // Second segment should have ops 2, 3
  EXPECT_THAT(strategy[1].target_nodes, testing::UnorderedElementsAre(2, 3));
}
 
TEST(StrategyTest, InvalidNumSegmentsFails) {
  auto model_buf = CreateSimpleChainModel(2);
  const auto* model = tflite::GetModel(model_buf.data());
  
  // num_segments must be > 1
  EXPECT_DEATH(GetStrategyFromNumOps(model, {2}), "num_segments must be >1");
}
 
}  // namespace
}  // namespace coral
