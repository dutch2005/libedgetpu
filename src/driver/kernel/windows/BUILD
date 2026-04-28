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

package(default_visibility = ["//src/visibility:public"])

licenses(["notice"])

cc_library(
    name = "kernel_event_windows",
    srcs = ["kernel_event_windows.cc"],
    hdrs = ["kernel_event_windows.h"],
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [
        ":gasket_ioctl_windows",
        "//src/driver/kernel:gasket_ioctl",
        "//src/driver/kernel:kernel_event",
        "//src/port",
        "//src/port:fileio",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "kernel_event_handler_windows",
    srcs = ["kernel_event_handler_windows.cc"],
    hdrs = ["kernel_event_handler_windows.h"],
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [
        ":gasket_ioctl_windows",
        "//src/driver/kernel:gasket_ioctl",
        "//src/driver/kernel:kernel_event",
        "//src/driver/kernel:kernel_event_handler",
        "//src/driver/kernel/windows:kernel_event_windows",
        "//src/port",
        "//src/port:fileio",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "kernel_coherent_allocator_windows",
    srcs = ["kernel_coherent_allocator_windows.cc"],
    hdrs = ["kernel_coherent_allocator_windows.h"],
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [
        ":gasket_ioctl_windows",
        "//src/driver:hardware_structures",
        "//src/driver/kernel:gasket_ioctl",
        "//src/driver/kernel:kernel_coherent_allocator",
        "//src/driver/mmio:coherent_allocator",
        "//src/port",
        "//src/port:fileio",
    ],
)

cc_library(
    name = "kernel_registers_windows",
    srcs = ["kernel_registers_windows.cc"],
    hdrs = ["kernel_registers_windows.h"],
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = [
        ":gasket_ioctl_windows",
        "@com_google_absl//absl/strings:str_format",
        "//src/driver/kernel:gasket_ioctl",
        "//src/driver/kernel:kernel_registers",
        "//src/driver/registers",
        "//src/port",
        "//src/port:fileio",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
    ],
)

cc_library(
    name = "gasket_ioctl_windows",
    hdrs = ["windows_gasket_ioctl.inc"],
    deps = [
        "//src/port",
    ],
)
