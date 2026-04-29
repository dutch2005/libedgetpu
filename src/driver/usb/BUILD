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
# USB driver specific functionality.

package(default_visibility = ["//src/visibility:public"])

licenses(["notice"])

cc_library(
    name = "usb_device_interface",
    hdrs = ["usb_device_interface.h"],
    deps = ["//src/port"],
)

LIBUSB_OPTIONS_SRC = select({
    "//src:windows": ["libusb_options_windows.cc"],
    "//conditions:default": ["libusb_options_default.cc"],
})

cc_library(
    name = "libusb_options",
    srcs = LIBUSB_OPTIONS_SRC,
    hdrs = ["libusb_options.h"],
    deps = ["//src/port"] + select({
        "//src:windows": ["@libusb//:headers"],
        "//conditions:default": ["@libusb//:headers"],
    }),
)

cc_library(
    name = "libusb_options_no_external_release",
    srcs = LIBUSB_OPTIONS_SRC,
    hdrs = ["libusb_options.h"],
    deps = [
        "//src/port",
        "//src/third_party/libusb",  # statically linked
    ],
)

# libUSB is dynamically linked in this version.
cc_library(
    name = "local_usb_device",
    srcs = ["local_usb_device.cc"],
    hdrs = ["local_usb_device.h"],
    deps = [
        ":libusb_options",
        ":usb_device_interface",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ] + select({
        "//src:windows": ["@libusb//:headers"],
        "//conditions:default": ["@libusb//:headers"],
    }),
)

# libUSB is statically linked in this version.
cc_library(
    name = "local_usb_device_no_external_release",
    srcs = ["local_usb_device.cc"],
    hdrs = ["local_usb_device.h"],
    deps = [
        ":libusb_options_no_external_release",
        ":usb_device_interface",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
        "//src/third_party/libusb",
    ],
)

cc_library(
    name = "usb_standard_commands",
    srcs = ["usb_standard_commands.cc"],
    hdrs = ["usb_standard_commands.h"],
    deps = [
        ":usb_device_interface",
        "//src/port",
        "//src/port:std_mutex_lock",
    ],
)

cc_library(
    name = "usb_dfu_commands",
    srcs = ["usb_dfu_commands.cc"],
    hdrs = ["usb_dfu_commands.h"],
    deps = [
        ":usb_device_interface",
        ":usb_standard_commands",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
    ],
)

genrule(
    name = "usb_latest_firmware",
    srcs = [
        "apex_latest_single_ep.bin",
        "apex_latest_multi_ep.bin",
    ],
    outs = [
        "usb_latest_firmware.h",
    ],
    cmd = """
        echo "namespace {" > $(location usb_latest_firmware.h)
        for FILE in $(SRCS); do
          FILENAME=$${FILE##*/}
          FILEBASE=$${FILENAME%.*}
          echo "const unsigned char ""$$FILEBASE"" [] = {" >> $(location usb_latest_firmware.h)
          xxd -i < "$$FILE" >> $(location usb_latest_firmware.h)
          echo "};" >> $(location usb_latest_firmware.h)
          echo "constexpr unsigned int ""$$FILEBASE""_len = sizeof(""$$FILEBASE"")/sizeof(unsigned char);" >> $(location usb_latest_firmware.h)
          echo "" >> $(location usb_latest_firmware.h)
        done
        echo "} // namespace" >> $(location usb_latest_firmware.h)
    """,
)

cc_library(
    name = "usb_ml_commands",
    srcs = ["usb_ml_commands.cc"],
    hdrs = ["usb_ml_commands.h"],
    deps = [
        ":usb_device_interface",
        ":usb_standard_commands",
        "//src/port",
        "//src/port:std_mutex_lock",
    ],
)

cc_library(
    name = "usb_registers",
    srcs = ["usb_registers.cc"],
    hdrs = ["usb_registers.h"],
    deps = [
        ":usb_ml_commands",
        "//src/driver/registers",
        "//src/port",
    ],
)

cc_library(
    name = "usb_dfu_util",
    srcs = ["usb_dfu_util.cc"],
    hdrs = ["usb_dfu_util.h"],
    deps = [
        ":usb_device_interface",
        ":usb_dfu_commands",
        "//src/port",
        "//src/port:tracing",
    ],
)

cc_library(
    name = "usb_io_request",
    srcs = ["usb_io_request.cc"],
    hdrs = ["usb_io_request.h"],
    deps = [
        ":usb_ml_commands",
        "//src/driver:device_buffer",
        "//src/driver:dma_chunker",
        "//src/driver:dma_info",
        "//src/port",
    ],
)

cc_library(
    name = "usb_driver",
    srcs = [
        "usb_driver.cc",
        ":usb_latest_firmware",
    ],
    hdrs = ["usb_driver.h"],
    deps = [
        ":usb_device_interface",
        ":usb_dfu_commands",
        ":usb_dfu_util",
        ":usb_io_request",
        ":usb_ml_commands",
        ":usb_registers",
        "//src/api:buffer",
        "//src/api:watchdog",
        "//src/driver",
        "//src/driver:allocator",
        "//src/driver:device_buffer",
        "//src/driver:device_buffer_mapper",
        "//src/driver:dma_chunker",
        "//src/driver:dma_info",
        "//src/driver:dma_info_extractor",
        "//src/driver:hardware_structures",
        "//src/driver:package_registry",
        "//src/driver:request",
        "//src/driver:run_controller",
        "//src/driver:single_queue_dma_scheduler",
        "//src/driver:single_tpu_request",
        "//src/driver:top_level_handler",
        "//src/driver:tpu_request",
        "//src/driver/config",
        "//src/driver/interrupt:interrupt_controller_interface",
        "//src/driver/interrupt:top_level_interrupt_manager",
        "//src/driver/memory:address_utilities",
        "//src/driver/memory:dma_direction",
        "//src/driver/memory:dram_allocator",
        "//src/driver/memory:nop_address_space",
        "//src/driver/registers",
        "//src/driver_shared/time_stamper",
        "//src/port",
        "//src/port:std_mutex_lock",
        "//src/port:thread_annotations",
        "//src/port:tracing",
    ],
)
