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
#  Memory Mapped IO (ex: PCIe.)

package(default_visibility = ["//libcoral/visibility:public_target"])

licenses(["notice"])

cc_library(
    name = "coherent_allocator",
    srcs = ["coherent_allocator.cc"],
    hdrs = ["coherent_allocator.h"],
    deps = [
        "//libcoral/api:buffer",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "host_queue",
    hdrs = ["host_queue.h"],
    deps = [
        ":coherent_allocator",
        "//libcoral/api:buffer",
        "//libcoral/driver:device_buffer",
        "//libcoral/driver:hardware_structures",
        "//libcoral/driver/config",
        "//libcoral/driver/memory:address_space",
        "//libcoral/driver/memory:dma_direction",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)
