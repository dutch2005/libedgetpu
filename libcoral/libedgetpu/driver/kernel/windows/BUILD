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
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/driver/kernel:kernel_event",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
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
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/driver/kernel:kernel_event",
        "//libcoral/driver/kernel:kernel_event_handler",
        "//libcoral/driver/kernel/windows:kernel_event_windows",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
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
        "//libcoral/driver:hardware_structures",
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/driver/kernel:kernel_coherent_allocator",
        "//libcoral/driver/mmio:coherent_allocator",
        "//libcoral/port",
        "//libcoral/port:fileio",
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
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/driver/kernel:kernel_registers",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "gasket_ioctl_windows",
    hdrs = ["windows_gasket_ioctl.inc"],
    deps = [
        "//libcoral/port",
    ],
)
