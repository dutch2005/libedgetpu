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
#  Interrupt functionality.

package(default_visibility = ["//src/visibility:public_target"])

licenses(["notice"])

cc_library(
    name = "interrupt_handler",
    hdrs = ["interrupt_handler.h"],
    deps = ["//src/port"],
)

cc_library(
    name = "wire_interrupt_handler",
    srcs = ["wire_interrupt_handler.cc"],
    hdrs = ["wire_interrupt_handler.h"],
    deps = [
        ":interrupt_handler",
        "//src/driver/config",
        "//src/driver/registers",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "interrupt_controller_interface",
    hdrs = ["interrupt_controller_interface.h"],
    deps = [
        "//src/driver/config:register_constants",
        "//src/port",
    ],
)

cc_library(
    name = "dummy_interrupt_controller",
    hdrs = ["dummy_interrupt_controller.h"],
    deps = [
        ":interrupt_controller_interface",
        "//src/port",
    ],
)

cc_library(
    name = "interrupt_controller",
    srcs = ["interrupt_controller.cc"],
    hdrs = ["interrupt_controller.h"],
    deps = [
        ":interrupt_controller_interface",
        "//src/driver/config",
        "//src/driver/config:register_constants",
        "//src/driver/registers",
        "//src/port",
    ],
)

cc_library(
    name = "grouped_interrupt_controller",
    srcs = ["grouped_interrupt_controller.cc"],
    hdrs = ["grouped_interrupt_controller.h"],
    deps = [
        ":interrupt_controller",
        ":interrupt_controller_interface",
        "//src/port",
    ],
)

cc_library(
    name = "top_level_interrupt_manager",
    srcs = ["top_level_interrupt_manager.cc"],
    hdrs = ["top_level_interrupt_manager.h"],
    deps = [
        ":interrupt_controller_interface",
        "//src/port",
    ],
)
