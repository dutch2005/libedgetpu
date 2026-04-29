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
# Kernel driver specific functionality.

package(default_visibility = ["//libcoral/visibility:public_target"])

licenses(["notice"])

cc_library(
    name = "kernel_event_linux",
    srcs = ["kernel_event_linux.cc"],
    hdrs = ["kernel_event_linux.h"],
    deps = [
        "//libcoral/driver/kernel:kernel_event",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "kernel_event_handler_linux",
    srcs = ["kernel_event_handler_linux.cc"],
    hdrs = ["kernel_event_handler_linux.h"],
    deps = [
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/driver/kernel:kernel_event",
        "//libcoral/driver/kernel:kernel_event_handler",
        "//libcoral/driver/kernel/linux:kernel_event_linux",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "kernel_coherent_allocator_linux",
    srcs = ["kernel_coherent_allocator_linux.cc"],
    hdrs = ["kernel_coherent_allocator_linux.h"],
    deps = [
        "//libcoral/driver:hardware_structures",
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/driver/kernel:kernel_coherent_allocator",
        "//libcoral/driver/mmio:coherent_allocator",
        "//libcoral/port",
        "//libcoral/port:fileio",
    ],
)

cc_library(
    name = "kernel_registers_linux",
    srcs = ["kernel_registers_linux.cc"],
    hdrs = ["kernel_registers_linux.h"],
    deps = [
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/driver/kernel:kernel_registers",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)
