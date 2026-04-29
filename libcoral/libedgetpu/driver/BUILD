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
#  Portable DarwiNN driver implementation.

package(
    default_visibility = ["//libcoral/visibility:public_target"],
)

licenses(["notice"])

exports_files(["libdarwinn_driver.lds"])

# Utility functions.
cc_library(
    name = "util",
    hdrs = [
        "bitfield.h",
    ],
    deps = [
        "//libcoral/port:integral_types",
        "//libcoral/port:logging",
    ],
)

cc_library(
    name = "allocator",
    srcs = [
        "aligned_allocator.cc",
        "allocator.cc",
    ],
    hdrs = [
        "aligned_allocator.h",
        "allocator.h",
    ],
    deps = [
        "//libcoral/api:allocated_buffer",
        "//libcoral/api:buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "device_buffer",
    srcs = ["device_buffer.cc"],
    hdrs = ["device_buffer.h"],
    deps = [
        "//libcoral/port",
    ],
)

cc_library(
    name = "executable_util",
    srcs = ["executable_util.cc"],
    hdrs = ["executable_util.h"],
    deps = [
        "//libcoral/api:buffer",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
    ],
)

# Driver Factory.
cc_library(
    name = "driver_factory",
    srcs = ["driver_factory.cc"] + select({
        "//libcoral/:windows": ["driver_factory_windows.cc"],
        "//libcoral/:darwin": ["driver_factory_darwin.cc"],
        "//libcoral/conditions:default": ["driver_factory_default.cc"],
    }),
    hdrs = [
        "driver_factory.h",
    ],
    deps = [
        ":driver",
        "//libcoral/api:chip",
        "//libcoral/api:driver",
        "//libcoral/api:driver_factory",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/api:driver_options_helper",
        "//libcoral/driver/config",
        "//libcoral/driver/kernel:gasket_ioctl",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "driver_helper",
    srcs = ["driver_helper.cc"],
    hdrs = ["driver_helper.h"],
    deps = [
        ":executable_util",
        ":package_registry",
        ":test_vector",
        "//libcoral/api:buffer",
        "//libcoral/api:chip",
        "//libcoral/api:driver",
        "//libcoral/api:package_reference",
        "//libcoral/api:request",
        "//libcoral/api:telemeter_interface",
        "//libcoral/api:timing",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "instruction_buffers",
    srcs = ["instruction_buffers.cc"],
    hdrs = ["instruction_buffers.h"],
    deps = [
        ":allocator",
        ":device_buffer_mapper",
        ":executable_util",
        "//libcoral/api:buffer",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "run_controller",
    srcs = ["run_controller.cc"],
    hdrs = ["run_controller.h"],
    deps = [
        ":hardware_structures",
        "//libcoral/driver/config",
        "//libcoral/driver/config:register_constants",
        "//libcoral/driver/registers",
        "//libcoral/port",
    ],
)

cc_library(
    name = "scalar_core_controller",
    srcs = ["scalar_core_controller.cc"],
    hdrs = ["scalar_core_controller.h"],
    deps = [
        "//libcoral/driver/config",
        "//libcoral/driver/interrupt:interrupt_controller",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "hardware_structures",
    hdrs = ["hardware_structures.h"],
    deps = [
        "//libcoral/port:integral_types",
        "//libcoral/port:macros",
    ],
)

cc_library(
    name = "driver",
    srcs = ["driver.cc"],
    hdrs = ["driver.h"],
    deps = [
        ":default_telemeter",
        ":device_buffer_mapper",
        ":package_registry",
        ":request",
        ":tpu_request",
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/api:buffer",
        "//libcoral/api:chip",
        "//libcoral/api:driver",
        "//libcoral/api:execution_context_interface",
        "//libcoral/api:package_reference",
        "//libcoral/api:request",
        "//libcoral/api:telemeter_interface",
        "//libcoral/driver/memory:dma_direction",
        "//libcoral/driver_shared/time_stamper",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
        "//libcoral/port:blocking_counter",
        "//libcoral/port:shared_mutex",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "default_telemeter",
    hdrs = ["default_telemeter.h"],
    deps = [
        "//libcoral/api:telemeter_interface",
    ],
)

cc_library(
    name = "mmio_driver",
    srcs = ["mmio_driver.cc"],
    hdrs = ["mmio_driver.h"],
    deps = [
        ":allocator",
        ":device_buffer",
        ":device_buffer_mapper",
        ":dma_info_extractor",
        ":driver",
        ":hardware_structures",
        ":package_registry",
        ":real_time_dma_scheduler",
        ":run_controller",
        ":scalar_core_controller",
        ":single_tpu_request",
        ":top_level_handler",
        ":tpu_request",
        "//libcoral/api:allocated_buffer",
        "//libcoral/api:buffer",
        "//libcoral/api:watchdog",
        "//libcoral/driver/config",
        "//libcoral/driver/config:register_constants",
        "//libcoral/driver/interrupt:interrupt_controller_interface",
        "//libcoral/driver/interrupt:interrupt_handler",
        "//libcoral/driver/interrupt:top_level_interrupt_manager",
        "//libcoral/driver/memory:address_space",
        "//libcoral/driver/memory:address_utilities",
        "//libcoral/driver/memory:dma_direction",
        "//libcoral/driver/memory:dram_allocator",
        "//libcoral/driver/memory:mmu_mapper",
        "//libcoral/driver/mmio:host_queue",
        "//libcoral/driver/registers",
        "//libcoral/driver_shared/time_stamper",
        "//libcoral/driver_shared/time_stamper:driver_time_stamper",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "dma_info",
    srcs = ["dma_info.cc"],
    hdrs = ["dma_info.h"],
    deps = [
        ":device_buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "device_buffer_mapper",
    srcs = ["device_buffer_mapper.cc"],
    hdrs = ["device_buffer_mapper.h"],
    deps = [
        ":device_buffer",
        ":hardware_structures",
        "//libcoral/api:buffer",
        "//libcoral/driver/memory:address_space",
        "//libcoral/driver/memory:address_utilities",
        "//libcoral/driver/memory:dma_direction",
        "//libcoral/port",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "dma_info_extractor",
    srcs = ["dma_info_extractor.cc"],
    hdrs = ["dma_info_extractor.h"],
    deps = [
        ":device_buffer_mapper",
        ":dma_info",
        ":package_registry",
        "//libcoral/driver/memory:address_utilities",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
    ],
)

cc_library(
    name = "dma_scheduler",
    hdrs = ["dma_scheduler.h"],
    deps = [
        ":dma_info",
        ":tpu_request",
        "//libcoral/api:driver",
        "//libcoral/port",
    ],
)

cc_library(
    name = "single_queue_dma_scheduler",
    srcs = ["single_queue_dma_scheduler.cc"],
    hdrs = ["single_queue_dma_scheduler.h"],
    deps = [
        ":dma_info",
        ":dma_scheduler",
        ":tpu_request",
        "//libcoral/api:driver",
        "//libcoral/api:watchdog",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "real_time_dma_scheduler",
    srcs = ["real_time_dma_scheduler.cc"],
    hdrs = ["real_time_dma_scheduler.h"],
    deps = [
        ":dma_info",
        ":dma_scheduler",
        ":package_registry",
        ":single_queue_dma_scheduler",
        ":tpu_request",
        "@com_google_absl//absl/strings:str_format",
        "//libcoral/api:driver",
        "//libcoral/api:package_reference",
        "//libcoral/api:timing",
        "//libcoral/api:watchdog",
        "//libcoral/driver_shared/time_stamper",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

cc_library(
    name = "dma_chunker",
    srcs = ["dma_chunker.cc"],
    hdrs = ["dma_chunker.h"],
    deps = [
        ":device_buffer",
        "//libcoral/port",
    ],
)

cc_library(
    name = "top_level_handler",
    hdrs = ["top_level_handler.h"],
    deps = ["//libcoral/port"],
)

cc_library(
    name = "package_registry",
    srcs = ["package_registry.cc"],
    hdrs = ["package_registry.h"],
    deps = [
        ":allocator",
        ":device_buffer_mapper",
        ":instruction_buffers",
        ":package_verifier",
        "//libcoral/api:buffer",
        "//libcoral/api:chip",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/api:execution_context_interface",
        "//libcoral/api:layer_information",
        "//libcoral/api:package_reference",
        "//libcoral/api:runtime_version",
        "//libcoral/driver/memory:dram_allocator",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "package_verifier",
    srcs = ["package_verifier.cc"],
    hdrs = ["package_verifier.h"],
    deps = [
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
    ],
)

cc_library(
    name = "tpu_request",
    hdrs = ["tpu_request.h"],
    deps = [
        ":dma_info",
        ":package_registry",
        "//libcoral/api:buffer",
        "//libcoral/api:request",
        "//libcoral/port",
    ],
)

cc_library(
    name = "single_tpu_request",
    srcs = ["single_tpu_request.cc"],
    hdrs = ["single_tpu_request.h"],
    deps = [
        ":allocator",
        ":device_buffer",
        ":device_buffer_mapper",
        ":dma_info",
        ":dma_info_extractor",
        ":executable_util",
        ":hardware_structures",
        ":instruction_buffers",
        ":package_registry",
        ":request",
        ":tpu_request",
        "//libcoral/api:allocated_buffer",
        "//libcoral/api:buffer",
        "//libcoral/driver/memory:address_space",
        "//libcoral/driver/memory:dram_allocator",
        "//libcoral/executable:executable_fbs",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

cc_library(
    name = "request",
    srcs = ["request.cc"],
    hdrs = ["request.h"],
    deps = [
        ":tpu_request",
        "//libcoral/api:request",
        "//libcoral/driver_shared/time_stamper",
        "//libcoral/driver_shared/time_stamper:driver_time_stamper_factory",
        "//libcoral/port",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
        "//libcoral/port:tracing",
    ],
)

filegroup(
    name = "linker_script",
    srcs = ["libdarwinn_driver.lds"],
)
