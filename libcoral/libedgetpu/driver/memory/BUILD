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
#  Memory management related functionality.

package(default_visibility = ["//libcoral/visibility:public"])

licenses(["notice"])

cc_library(
    name = "address_utilities",
    hdrs = ["address_utilities.h"],
    deps = [
        "//libcoral/driver:hardware_structures",
        "//libcoral/port",
    ],
)

cc_library(
    name = "mmu_mapper",
    srcs = ["mmu_mapper.cc"],
    hdrs = ["mmu_mapper.h"],
    deps = [
        ":address_utilities",
        "//libcoral/api:buffer",
        "//libcoral/driver:device_buffer",
        "//libcoral/driver/memory:dma_direction",
        "//libcoral/port",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "address_space",
    hdrs = ["address_space.h"],
    deps = [
        ":dma_direction",
        "//libcoral/api:buffer",
        "//libcoral/driver:device_buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "mmio_address_space",
    srcs = ["mmio_address_space.cc"],
    hdrs = ["mmio_address_space.h"],
    deps = [
        ":address_space",
        ":address_utilities",
        ":dma_direction",
        ":mmu_mapper",
        "//libcoral/api:buffer",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "buddy_address_space",
    srcs = ["buddy_address_space.cc"],
    hdrs = ["buddy_address_space.h"],
    deps = [
        ":address_utilities",
        ":buddy_allocator",
        ":dma_direction",
        ":mmio_address_space",
        ":mmu_mapper",
        "//libcoral/api:buffer",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "address_space_allocator",
    hdrs = ["address_space_allocator.h"],
    deps = ["//libcoral/port"],
)

cc_library(
    name = "buddy_allocator",
    srcs = ["buddy_allocator.cc"],
    hdrs = ["buddy_allocator.h"],
    deps = [
        ":address_space_allocator",
        ":address_utilities",
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "fake_mmu_mapper",
    srcs = ["fake_mmu_mapper.cc"],
    hdrs = ["fake_mmu_mapper.h"],
    deps = [
        ":address_utilities",
        ":dma_direction",
        ":mmu_mapper",
        "//libcoral/driver:hardware_structures",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "dma_direction",
    hdrs = ["dma_direction.h"],
    deps = [
    ],
)

cc_library(
    name = "nop_address_space",
    srcs = ["nop_address_space.cc"],
    hdrs = ["nop_address_space.h"],
    deps = [
        ":address_space",
        ":dma_direction",
        "//libcoral/api:buffer",
        "//libcoral/driver:device_buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "dual_address_space",
    srcs = ["dual_address_space.cc"],
    hdrs = ["dual_address_space.h"],
    deps = [
        ":address_space",
        ":buddy_address_space",
        ":mmu_mapper",
        "//libcoral/driver:hardware_structures",
        "//libcoral/driver/config",
        "//libcoral/port",
    ],
)

cc_library(
    name = "dram_allocator",
    hdrs = ["dram_allocator.h"],
    deps = [
        "//libcoral/api:dram_buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "null_dram_allocator",
    hdrs = ["null_dram_allocator.h"],
    deps = [
        ":dram_allocator",
        "//libcoral/api:dram_buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "fake_dram_allocator",
    srcs = ["fake_dram_allocator.cc"],
    hdrs = ["fake_dram_allocator.h"],
    deps = [
        ":dram_allocator",
        "//libcoral/api:dram_buffer",
        "//libcoral/port",
    ],
)
