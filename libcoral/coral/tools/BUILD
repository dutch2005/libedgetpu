# Copyright 2019-2021 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

package(default_visibility = ["//libcoral/visibility:public"])

licenses(["notice"])

cc_library(
    name = "tflite_graph_util",
    srcs = ["tflite_graph_util.cc"],
    hdrs = ["tflite_graph_util.h"],
    deps = [
        "//libcoral/coral/learn:utils",
        "@com_google_absl//absl/algorithm:container",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@flatbuffers",
        "@glog",
        "@org_tensorflow//tensorflow/lite:framework",
        "@org_tensorflow//tensorflow/lite/c:common",
        "@org_tensorflow//tensorflow/lite/schema:schema_conversion_utils",
        "@org_tensorflow//tensorflow/lite/schema:schema_fbs",
        "@org_tensorflow//tensorflow/lite/schema:schema_utils",
    ],
)

cc_binary(
    name = "join_tflite_models",
    srcs = ["join_tflite_models.cc"],
    deps = [
        ":tflite_graph_util",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",
        "@flatbuffers",
        "@glog",
    ],
)

cc_binary(
    name = "append_recurrent_links",
    srcs = ["append_recurrent_links.cc"],
    deps = [
        ":tflite_graph_util",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",
        "@glog",
    ],
)

cc_library(
    name = "automl_video_object_tracking_utils",
    testonly = 1,
    srcs = ["automl_video_object_tracking_utils.cc"],
    hdrs = ["automl_video_object_tracking_utils.h"],
    deps = [
        "//libcoral/coral:tflite_utils",
        "@glog",
        "//src/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

cc_test(
    name = "automl_model_append_rnn_link_test",
    srcs = [
        "automl_model_append_rnn_link_test.cc",
    ],
    data = [
        "@test_data//automl_video_ondevice:images",
        "@test_data//automl_video_ondevice:models",
    ],
    linkstatic = 1,
    deps = [
        ":automl_video_object_tracking_utils",
        "//libcoral/coral:test_main_with_edgetpu",
        "//libcoral/coral:test_utils",
        "//libcoral/coral:tflite_utils",
        "//libcoral/coral/tools:tflite_graph_util",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_googletest//:gtest",
        "@glog",
        "//src/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

cc_binary(
    name = "automl_rnn_models_benchmark",
    testonly = 1,
    srcs = [
        "automl_rnn_models_benchmark.cc",
    ],
    data = [
        "@test_data//automl_video_ondevice:models",
    ],
    deps = [
        ":automl_video_object_tracking_utils",
        "//libcoral/coral:benchmark_main_with_edgetpu",
        "//libcoral/coral:test_utils",
        "//libcoral/coral:tflite_utils",
        "//libcoral/coral/tools:tflite_graph_util",
        "@com_github_google_benchmark//:benchmark",
        "@glog",
        "//src/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

cc_test(
    name = "tflite_graph_util_test",
    srcs = ["tflite_graph_util_test.cc"],
    data = [
        "@test_data//:images",
        "@test_data//:models",
        "@test_data//tools:models",
    ],
    linkstatic = 1,
    deps = [
        ":tflite_graph_util",
        "//libcoral/coral:test_main_with_edgetpu",
        "//libcoral/coral:test_utils",
        "//libcoral/coral:tflite_utils",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/strings:str_format",
        "@com_google_googletest//:gtest",
        "@flatbuffers",
        "@glog",
        "//src/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

cc_binary(
    name = "split_fc",
    srcs = ["split_fc.cc"],
    deps = [
        ":tflite_graph_util",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",
        "@glog",
    ],
)

cc_binary(
    name = "multiple_tpus_performance_analysis",
    testonly = 1,
    srcs = ["multiple_tpus_performance_analysis.cc"],
    data = [
        "@test_data//:images",
        "@test_data//:models",
    ],
    deps = [
        "//libcoral/coral:test_utils",
        "//libcoral/coral:tflite_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/status",
        "@com_google_absl//absl/types:span",
        "@glog",
        "//src/tflite/public:edgetpu",
        "//src/tflite/public:oss_edgetpu_direct_all",  # buildcleaner: keep
    ],
)

cc_library(
    name = "model_pipelining_benchmark_util",
    testonly = 1,
    srcs = ["model_pipelining_benchmark_util.cc"],
    hdrs = ["model_pipelining_benchmark_util.h"],
    deps = [
        "//libcoral/coral:error_reporter",
        "//libcoral/coral:test_utils",
        "//libcoral/coral:tflite_utils",
        "//libcoral/coral/pipeline:common",
        "//libcoral/coral/pipeline:pipelined_model_runner",
        "//libcoral/coral/pipeline:test_utils",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/strings",
        "@glog",
        "//src/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

cc_binary(
    name = "model_pipelining_performance_analysis",
    testonly = 1,
    srcs = ["model_pipelining_performance_analysis.cc"],
    deps = [
        ":model_pipelining_benchmark_util",
        "//libcoral/coral/pipeline:test_utils",
        "@com_google_absl//absl/container:node_hash_map",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@glog",
        "//src/tflite/public:oss_edgetpu_direct_all",  # buildcleaner: keep
    ],
)
