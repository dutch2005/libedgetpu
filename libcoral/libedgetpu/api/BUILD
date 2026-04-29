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

# Description:
#   Darwinn API headers
load(
    "@flatbuffers//:build_defs.bzl",
    "flatbuffer_cc_library",
)

package(default_visibility = ["//libcoral/visibility:public_target"])

licenses(["notice"])

cc_library(
    name = "chip",
    hdrs = ["chip.h"],
    defines = select({
        "//libcoral/conditions:default": [],
    }),
)

cc_library(
    name = "tensor_util",
    srcs = ["tensor_util.cc"],
    hdrs = ["tensor_util.h"],
    deps = [
        "@com_google_absl//absl/types:optional",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
        "//libcoral/port:string_util",
    ],
)

cc_library(
    name = "layer_information",
    srcs = ["layer_information.cc"],
    hdrs = ["layer_information.h"],
    deps = [
        ":buffer",
        ":tensor_util",
        "@com_google_absl//absl/types:optional",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
    ],
)

cc_library(
    name = "request",
    hdrs = ["request.h"],
    deps = [
        ":buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "driver",
    hdrs = ["driver.h"],
    deps = [
        ":buffer",
        ":package_reference",
        ":request",
        ":timing",
        "//libcoral/api:telemeter_interface",
        "//libcoral/port",
    ],
)

cc_library(
    name = "driver_options_helper",
    srcs = ["driver_options_helper.cc"],
    hdrs = ["driver_options_helper.h"],
    deps = [
        ":driver",
        ":driver_options_fbs",
    ],
)

cc_library(
    name = "allocated_buffer",
    srcs = ["allocated_buffer.cc"],
    hdrs = ["allocated_buffer.h"],
    deps = ["//libcoral/port"],
)

cc_library(
    name = "dram_buffer",
    hdrs = ["dram_buffer.h"],
    deps = ["//libcoral/port"],
)

cc_library(
    name = "buffer",
    srcs = ["buffer.cc"],
    hdrs = ["buffer.h"],
    deps = [
        ":allocated_buffer",
        ":dram_buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "driver_factory",
    srcs = ["driver_factory.cc"],
    hdrs = ["driver_factory.h"],
    deps = [
        ":chip",
        ":driver",
        ":driver_options_fbs",
        "//libcoral/port",
    ],
)

cc_library(
    name = "package_reference",
    hdrs = ["package_reference.h"],
    deps = [
        ":execution_context_interface",
        ":layer_information",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
    ],
)

cc_library(
    name = "runtime_version",
    hdrs = ["runtime_version.h"],
)

flatbuffer_cc_library(
    name = "driver_options_fbs",
    srcs = ["driver_options.fbs"],
    flatc_args = [""],
)

cc_library(
    name = "timing",
    hdrs = ["timing.h"],
    deps = [
        "//libcoral/port",
    ],
)

cc_library(
    name = "watchdog",
    srcs = ["watchdog.cc"],
    hdrs = ["watchdog.h"],
    deps = [
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:timer",
    ],
)

cc_library(
    name = "telemeter_interface",
    hdrs = [
        "telemeter_interface.h",
    ],
    deps = [
        ":execution_context_interface",
    ],
)

cc_library(
    name = "execution_context_interface",
    hdrs = [
        "execution_context_interface.h",
    ],
)
