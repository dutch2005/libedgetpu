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
    default_visibility = ["//src/visibility:public"],
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
        "//src/port:integral_types",
        "//src/port:logging",
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
        "//src/api:allocated_buffer",
        "//src/api:buffer",
        "//src/port",
    ],
)

cc_library(
    name = "device_buffer",
    srcs = ["device_buffer.cc"],
    hdrs = ["device_buffer.h"],
    deps = [
        "//src/port",
    ],
)

cc_library(
    name = "executable_util",
    srcs = ["executable_util.cc"],
    hdrs = ["executable_util.h"],
    deps = [
        "//src/api:buffer",
        "//src/executable:executable_fbs",
        "//src/port",
    ],
)

# Driver Factory.
cc_library(
    name = "driver_factory",
    srcs = ["driver_factory.cc"] + select({
        "//src:windows": ["driver_factory_windows.cc"],
        "//src:darwin": ["driver_factory_darwin.cc"],
        "//conditions:default": ["driver_factory_default.cc"],
    }),
    hdrs = [
        "driver_factory.h",
    ],
    deps = [
        ":driver",
        "//src/api:chip",
        "//src/api:driver",
        "//src/api:driver_factory",
        "//src/api:driver_options_fbs",
        "//src/api:driver_options_helper",
        "//src/driver/config",
        "//src/driver/kernel:gasket_ioctl",
        "//src/port",
        "//src/port:fileio",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
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
        "//src/api:buffer",
        "//src/api:chip",
        "//src/api:driver",
        "//src/api:package_reference",
        "//src/api:request",
        "//src/api:telemeter_interface",
        "//src/api:timing",
        "//src/executable:executable_fbs",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
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
        "//src/api:buffer",
        "//src/executable:executable_fbs",
        "//src/port",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "run_controller",
    srcs = ["run_controller.cc"],
    hdrs = ["run_controller.h"],
    deps = [
        ":hardware_structures",
        "//src/driver/config",
        "//src/driver/config:register_constants",
        "//src/driver/registers",
        "//src/port",
    ],
)

cc_library(
    name = "scalar_core_controller",
    srcs = ["scalar_core_controller.cc"],
    hdrs = ["scalar_core_controller.h"],
    deps = [
        "//src/driver/config",
        "//src/driver/interrupt:interrupt_controller",
        "//src/driver/registers",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
    ],
)

cc_library(
    name = "hardware_structures",
    hdrs = ["hardware_structures.h"],
    deps = [
        "//src/port:integral_types",
        "//src/port:macros",
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
        "//src/api:buffer",
        "//src/api:chip",
        "//src/api:driver",
        "//src/api:execution_context_interface",
        "//src/api:package_reference",
        "//src/api:request",
        "//src/api:telemeter_interface",
        "//src/driver/memory:dma_direction",
        "//src/driver_shared/time_stamper",
        "//src/executable:executable_fbs",
        "//src/port",
        "//src/port:blocking_counter",
        "//src/port:shared_mutex",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "default_telemeter",
    hdrs = ["default_telemeter.h"],
    deps = [
        "//src/api:telemeter_interface",
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
        "//src/api:allocated_buffer",
        "//src/api:buffer",
        "//src/api:watchdog",
        "//src/driver/config",
        "//src/driver/config:register_constants",
        "//src/driver/interrupt:interrupt_controller_interface",
        "//src/driver/interrupt:interrupt_handler",
        "//src/driver/interrupt:top_level_interrupt_manager",
        "//src/driver/memory:address_space",
        "//src/driver/memory:address_utilities",
        "//src/driver/memory:dma_direction",
        "//src/driver/memory:dram_allocator",
        "//src/driver/memory:mmu_mapper",
        "//src/driver/mmio:host_queue",
        "//src/driver/registers",
        "//src/driver_shared/time_stamper",
        "//src/driver_shared/time_stamper:driver_time_stamper",
        "//src/executable:executable_fbs",
        "//src/port",
        "//src/port:fileio",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "dma_info",
    srcs = ["dma_info.cc"],
    hdrs = ["dma_info.h"],
    deps = [
        ":device_buffer",
        "//src/port",
    ],
)

cc_library(
    name = "device_buffer_mapper",
    srcs = ["device_buffer_mapper.cc"],
    hdrs = ["device_buffer_mapper.h"],
    deps = [
        ":device_buffer",
        ":hardware_structures",
        "//src/api:buffer",
        "//src/driver/memory:address_space",
        "//src/driver/memory:address_utilities",
        "//src/driver/memory:dma_direction",
        "//src/port",
        "//src/port:tracing",
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
        "//src/driver/memory:address_utilities",
        "//src/executable:executable_fbs",
        "//src/port",
    ],
)

cc_library(
    name = "dma_scheduler",
    hdrs = ["dma_scheduler.h"],
    deps = [
        ":dma_info",
        ":tpu_request",
        "//src/api:driver",
        "//src/port",
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
        "//src/api:driver",
        "//src/api:watchdog",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
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
        "//src/api:driver",
        "//src/api:package_reference",
        "//src/api:timing",
        "//src/api:watchdog",
        "//src/driver_shared/time_stamper",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
    ],
)

cc_library(
    name = "dma_chunker",
    srcs = ["dma_chunker.cc"],
    hdrs = ["dma_chunker.h"],
    deps = [
        ":device_buffer",
        "//src/port",
    ],
)

cc_library(
    name = "top_level_handler",
    hdrs = ["top_level_handler.h"],
    deps = ["//src/port"],
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
        "//src/api:buffer",
        "//src/api:chip",
        "//src/api:driver_options_fbs",
        "//src/api:execution_context_interface",
        "//src/api:layer_information",
        "//src/api:package_reference",
        "//src/api:runtime_version",
        "//src/driver/memory:dram_allocator",
        "//src/executable:executable_fbs",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "package_verifier",
    srcs = ["package_verifier.cc"],
    hdrs = ["package_verifier.h"],
    deps = [
        "//src/executable:executable_fbs",
        "//src/port",
    ],
)

cc_library(
    name = "tpu_request",
    hdrs = ["tpu_request.h"],
    deps = [
        ":dma_info",
        ":package_registry",
        "//src/api:buffer",
        "//src/api:request",
        "//src/port",
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
        "//src/api:allocated_buffer",
        "//src/api:buffer",
        "//src/driver/memory:address_space",
        "//src/driver/memory:dram_allocator",
        "//src/executable:executable_fbs",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "request",
    srcs = ["request.cc"],
    hdrs = ["request.h"],
    deps = [
        ":tpu_request",
        "//src/api:request",
        "//src/driver_shared/time_stamper",
        "//src/driver_shared/time_stamper:driver_time_stamper_factory",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)

filegroup(
    name = "linker_script",
    srcs = ["libdarwinn_driver.lds"],
)
