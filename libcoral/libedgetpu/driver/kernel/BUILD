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

package(default_visibility = ["//libcoral/visibility:public"])

licenses(["notice"])

cc_library(
    name = "kernel_mmu_mapper",
    srcs = ["kernel_mmu_mapper.cc"],
    hdrs = ["kernel_mmu_mapper.h"],
    deps = [
        ":gasket_ioctl",
        "//libcoral/driver:hardware_structures",
        "//libcoral/driver/memory:dma_direction",
        "//libcoral/driver/memory:mmu_mapper",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "kernel_event",
    hdrs = ["kernel_event.h"],
    deps = [
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "kernel_event_handler",
    srcs = ["kernel_event_handler.cc"],
    hdrs = ["kernel_event_handler.h"],
    deps = [
        ":gasket_ioctl",
        "//libcoral/driver/kernel:kernel_event",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "kernel_interrupt_handler",
    srcs = ["kernel_interrupt_handler.cc"],
    hdrs = ["kernel_interrupt_handler.h"],
    deps = [
        "//libcoral/driver/interrupt:interrupt_handler",
        "//libcoral/driver/kernel:kernel_event_handler",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "kernel_wire_interrupt_handler",
    srcs = ["kernel_wire_interrupt_handler.cc"],
    hdrs = ["kernel_wire_interrupt_handler.h"],
    deps = [
        "//libcoral/driver/config",
        "//libcoral/driver/interrupt:interrupt_handler",
        "//libcoral/driver/interrupt:wire_interrupt_handler",
        "//libcoral/driver/kernel:kernel_event_handler",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "kernel_coherent_allocator",
    srcs = ["kernel_coherent_allocator.cc"],
    hdrs = ["kernel_coherent_allocator.h"],
    deps = [
        ":gasket_ioctl",
        "//libcoral/driver:hardware_structures",
        "//libcoral/driver/mmio:coherent_allocator",
        "//libcoral/port",
        "//libcoral/port:fileio",
    ],
)

cc_library(
    name = "kernel_registers",
    srcs = ["kernel_registers.cc"],
    hdrs = ["kernel_registers.h"],
    deps = [
        ":gasket_ioctl",
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "gasket_ioctl",
    hdrs = [
        "common_gasket_ioctl.inc",
        "gasket_ioctl.h",
    ],
    deps = ["//libcoral/driver/kernel/windows:gasket_ioctl_windows"],
)
