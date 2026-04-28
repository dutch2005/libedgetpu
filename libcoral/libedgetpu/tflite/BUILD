# Copyright 2019 Google LLC
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
    name = "custom_op_wrapped_buffer",
    hdrs = ["custom_op_wrapped_buffer.h"],
    deps = [
        "//libcoral/api:chip",
    ],
)

cc_library(
    name = "custom_op_data",
    srcs = ["custom_op_data.cc"],
    hdrs = ["custom_op_data.h"],
    deps = [
        ":custom_op_wrapped_buffer",
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/api:chip",
        "//libcoral/port",
        "@flatbuffers",
    ],
)

cc_library(
    name = "custom_op",
    srcs = ["custom_op.cc"],
    hdrs = ["custom_op.h"],
    deps = [
        ":custom_op_data",
        "@com_google_absl//absl/strings",
        "//libcoral/api:layer_information",
        "//libcoral/driver:package_registry",
        "//libcoral/port",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:context",
    ],
)

cc_library(
    name = "custom_op_user_data_direct",
    srcs = ["custom_op_user_data_direct.cc"],
    hdrs = ["custom_op_user_data_direct.h"],
    deps = [
        ":custom_op",
        ":custom_op_data",
        "@com_google_absl//absl/container:flat_hash_map",
        "//libcoral/api:driver",
        "//libcoral/driver:package_registry",
        "//libcoral/port",
    ],
)

cc_library(
    name = "edgetpu_context_direct_header",
    hdrs = ["edgetpu_context_direct.h"],
    deps = [
        ":custom_op_data",
        ":custom_op_user_data_direct",
        "//libcoral/api:driver",
        "//libcoral/api:driver_factory",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/api:package_reference",
        "//libcoral/driver:driver_factory",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:context",
    ],
)

cc_library(
    name = "edgetpu_manager_direct_header",
    hdrs = ["edgetpu_manager_direct.h"],
    deps = [
        ":custom_op_data",
        ":custom_op_user_data_direct",
        ":edgetpu_context_direct_header",
        "//libcoral/api:driver",
        "//libcoral/api:driver_factory",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/api:package_reference",
        "//libcoral/driver:driver_factory",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:context",
    ],
)

cc_library(
    name = "edgetpu_context_direct",
    srcs = ["edgetpu_context_direct.cc"],
    hdrs = ["edgetpu_context_direct.h"],
    deps = [
        ":custom_op_user_data_direct",
        ":edgetpu_manager_direct_header",
        "@com_google_absl//absl/strings",
        "//libcoral/api:driver",
        "//libcoral/api:driver_factory",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/api:package_reference",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/tflite/public:edgetpu",
    ],
)

cc_library(
    name = "edgetpu_manager_direct",
    srcs = ["edgetpu_manager_direct.cc"],
    hdrs = ["edgetpu_manager_direct.h"],
    deps = [
        ":custom_op_data",
        ":custom_op_user_data_direct",
        ":edgetpu_context_direct",
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/api:driver",
        "//libcoral/api:driver_factory",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/api:package_reference",
        "//libcoral/api:runtime_version",
        "//libcoral/driver:driver_factory",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:context",
    ],
)

cc_library(
    name = "custom_op_direct",
    srcs = ["custom_op_direct.cc"],
    deps = [
        ":custom_op",
        ":custom_op_data",
        ":custom_op_user_data_direct",
        ":edgetpu_c",  # buildcleaner: keep
        ":edgetpu_context_direct",
        ":edgetpu_delegate_for_custom_op_tflite_plugin",  # buildcleaner: keep
        ":edgetpu_manager_direct",
        "//libcoral/api:driver",
        "//libcoral/port",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:context",
    ],
    alwayslink = 1,
)

cc_library(
    name = "tensor_data_controller",
    srcs = ["tensor_data_controller.cc"],
    hdrs = ["tensor_data_controller.h"],
    deps = [
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/port",
        "@flatbuffers",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

cc_library(
    name = "edgetpu_context_factory",
    srcs = ["edgetpu_context_factory.cc"],
    hdrs = ["edgetpu_context_factory.h"],
    deps = [
        ":edgetpu_context_direct",
        "//libcoral/port",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:framework",
    ],
)

# Set EXTRA_LOGGING to DUMMY to disable extra logging in text protobuf.
config_setting(
    name = "no_extra_logging",
    values = {"define": "EXTRA_LOGGING=DUMMY"},
)

cc_library(
    name = "edgetpu_delegate_for_custom_op",
    srcs = [
        "edgetpu_delegate_for_custom_op.cc",
    ],
    hdrs = ["edgetpu_delegate_for_custom_op.h"],
    deps = [
        "//libcoral/port",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:kernel_api",
        "@org_tensorflow//tensorflow/lite:util",
    ],
)

cc_library(
    name = "edgetpu_delegate_for_custom_op_tflite_plugin",
    srcs = [
        "edgetpu_delegate_for_custom_op_tflite_plugin.cc",
    ],
    deps = [
        ":edgetpu_delegate_for_custom_op",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/types:optional",
        "//libcoral/tflite/public:edgetpu",
        "@org_tensorflow//tensorflow/lite:kernel_api",
    ],
    alwayslink = 1,
)

cc_library(
    name = "edgetpu_c",
    srcs = [
        "edgetpu_c.cc",
    ],
    deps = [
        ":edgetpu_delegate_for_custom_op",
        "//libcoral/port",
        "//libcoral/tflite/public:edgetpu",
        "//libcoral/tflite/public:edgetpu_c",
    ],
    alwayslink = 1,
)
