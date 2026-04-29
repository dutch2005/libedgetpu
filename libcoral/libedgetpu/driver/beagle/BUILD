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
#  Beagle Specific functionality.

package(default_visibility = ["//libcoral/visibility:public_target"])

# Google Owned Code
licenses(["unencumbered"])

BEAGLE_USB_DRIVER_DEPS = [
    ":beagle_top_level_handler",
    ":beagle_top_level_interrupt_manager",
    "@com_google_absl//absl/strings",
    "//libcoral/api:chip",
    "//libcoral/api:driver",
    "//libcoral/api:driver_options_fbs",
    "//libcoral/driver:allocator",
    "//libcoral/driver:driver_factory",
    "//libcoral/driver:package_registry",
    "//libcoral/driver:package_verifier",
    "//libcoral/driver:run_controller",
    "//libcoral/driver:scalar_core_controller",
    "//libcoral/driver/config/beagle:beagle_chip_config",
    "//libcoral/driver/interrupt:grouped_interrupt_controller",
    "//libcoral/driver/interrupt:interrupt_controller",
    "//libcoral/driver/interrupt:interrupt_controller_interface",
    "//libcoral/driver/memory:null_dram_allocator",
    "//libcoral/driver_shared/time_stamper:driver_time_stamper",
    "//libcoral/driver/usb:usb_device_interface",
    "//libcoral/driver/usb:usb_driver",
    "//libcoral/driver/usb:usb_ml_commands",
    "//libcoral/driver/usb:usb_registers",
    "//libcoral/port",
    "//libcoral/port:tracing",
]

# Provides Beagle USB Driver for internal (=no_external_release) usage.
# libUSB is statically linked in this version.
cc_library(
    name = "beagle_usb_driver_provider_no_external_release",
    srcs = ["beagle_usb_driver_provider.cc"],
    deps = BEAGLE_USB_DRIVER_DEPS + [
        "//libcoral/driver/usb:local_usb_device_no_external_release",
    ],
    alwayslink = 1,
)

# Provides Beagle USB Driver.
# libUSB is dynamically linked in this version.
cc_library(
    name = "beagle_usb_driver_provider",
    srcs = ["beagle_usb_driver_provider.cc"],
    deps = BEAGLE_USB_DRIVER_DEPS + [
        "//libcoral/driver/usb:local_usb_device",
    ],
    alwayslink = 1,
)

BEAGLE_PCI_DRIVER_PROVIDER_DEPS = [
    ":beagle_kernel_top_level_handler",
    "//libcoral/api:chip",
    "//libcoral/api:driver",
    "//libcoral/driver:allocator",
    "//libcoral/driver:driver_factory",
    "//libcoral/driver:hardware_structures",
    "//libcoral/driver:mmio_driver",
    "//libcoral/driver:package_registry",
    "//libcoral/driver:package_verifier",
    "//libcoral/driver:run_controller",
    "//libcoral/driver:scalar_core_controller",
    "//libcoral/driver/config",
    "//libcoral/driver/config/beagle:beagle_chip_config",
    "//libcoral/driver/interrupt:dummy_interrupt_controller",
    "//libcoral/driver/interrupt:grouped_interrupt_controller",
    "//libcoral/driver/interrupt:interrupt_handler",
    "//libcoral/driver/interrupt:top_level_interrupt_manager",
    "//libcoral/driver/kernel:kernel_coherent_allocator",
    "//libcoral/driver/kernel:kernel_event_handler",
    "//libcoral/driver/kernel:kernel_interrupt_handler",
    "//libcoral/driver/kernel:kernel_mmu_mapper",
    "//libcoral/driver/kernel:kernel_registers",
    "//libcoral/driver/kernel:kernel_wire_interrupt_handler",
    "//libcoral/driver/memory:dual_address_space",
    "//libcoral/driver/memory:null_dram_allocator",
    "//libcoral/driver/mmio:host_queue",
    "//libcoral/driver_shared/time_stamper:driver_time_stamper",
    "//libcoral/port",
    "//libcoral/port:fileio",
]

cc_library(
    name = "beagle_pci_driver_provider",
    srcs = ["beagle_pci_driver_provider.cc"],
    hdrs = ["beagle_pci_driver_provider.h"],
    deps = BEAGLE_PCI_DRIVER_PROVIDER_DEPS,
)

# Provides Beagle PCI Driver for Linux.
cc_library(
    name = "beagle_pci_driver_provider_linux",
    srcs = ["beagle_pci_driver_provider_linux.cc"],
    deps = BEAGLE_PCI_DRIVER_PROVIDER_DEPS + [
        "//libcoral/driver/beagle:beagle_pci_driver_provider",
        "//libcoral/driver/kernel/linux:kernel_coherent_allocator_linux",
        "//libcoral/driver/kernel/linux:kernel_event_handler_linux",
        "//libcoral/driver/kernel/linux:kernel_registers_linux",
    ],
    alwayslink = 1,
)

# Provides Beagle PCI Driver for Windows.
cc_library(
    name = "beagle_pci_driver_provider_windows",
    srcs = ["beagle_pci_driver_provider_windows.cc"],
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = BEAGLE_PCI_DRIVER_PROVIDER_DEPS + [
        "//libcoral/driver/beagle:beagle_pci_driver_provider",
        "//libcoral/driver/kernel/windows:kernel_coherent_allocator_windows",
        "//libcoral/driver/kernel/windows:kernel_event_handler_windows",
        "//libcoral/driver/kernel/windows:kernel_registers_windows",
    ],
    alwayslink = 1,
)

# Provides Beagle USB/PCI Driver for Linux. Used by an Android side script to
# populate dependencies for a unified Beagle provider in Beagle NNAPI HAL.
cc_library(
    name = "beagle_all_driver_provider_linux",
    srcs = [
        "beagle_pci_driver_provider.cc",
        "beagle_pci_driver_provider_linux.cc",
        "beagle_usb_driver_provider.cc",
    ],
    hdrs = ["beagle_pci_driver_provider.h"],
    deps = BEAGLE_PCI_DRIVER_PROVIDER_DEPS + [
        ":beagle_top_level_handler",
        ":beagle_top_level_interrupt_manager",
        "@com_google_absl//absl/strings",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/driver/interrupt:interrupt_controller",
        "//libcoral/driver/interrupt:interrupt_controller_interface",
        "//libcoral/driver/kernel/linux:kernel_coherent_allocator_linux",
        "//libcoral/driver/kernel/linux:kernel_event_handler_linux",
        "//libcoral/driver/kernel/linux:kernel_registers_linux",
        "//libcoral/driver/usb:local_usb_device",
        "//libcoral/driver/usb:usb_device_interface",
        "//libcoral/driver/usb:usb_driver",
        "//libcoral/driver/usb:usb_ml_commands",
        "//libcoral/driver/usb:usb_registers",
        "//libcoral/port:tracing",
    ],
    alwayslink = 1,
)

# Provides Beagle USB/PCI Driver for Windows.
cc_library(
    name = "beagle_all_driver_provider_windows",
    srcs = [
        "beagle_pci_driver_provider.cc",
        "beagle_pci_driver_provider_windows.cc",
        "beagle_usb_driver_provider.cc",
    ],
    hdrs = ["beagle_pci_driver_provider.h"],
    tags = [
        "manual",
        "nobuilder",
        "notap",
    ],
    deps = BEAGLE_PCI_DRIVER_PROVIDER_DEPS + [
        ":beagle_top_level_handler",
        ":beagle_top_level_interrupt_manager",
        "@com_google_absl//absl/strings",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/driver/interrupt:interrupt_controller",
        "//libcoral/driver/interrupt:interrupt_controller_interface",
        "//libcoral/driver/kernel/windows:kernel_coherent_allocator_windows",
        "//libcoral/driver/kernel/windows:kernel_event_handler_windows",
        "//libcoral/driver/kernel/windows:kernel_registers_windows",
        "//libcoral/driver/usb:local_usb_device",
        "//libcoral/driver/usb:usb_device_interface",
        "//libcoral/driver/usb:usb_driver",
        "//libcoral/driver/usb:usb_ml_commands",
        "//libcoral/driver/usb:usb_registers",
        "//libcoral/port:tracing",
    ],
    alwayslink = 1,
)

cc_library(
    name = "beagle_top_level_interrupt_manager",
    srcs = ["beagle_top_level_interrupt_manager.cc"],
    hdrs = ["beagle_top_level_interrupt_manager.h"],
    deps = [
        "//libcoral/driver/config",
        "//libcoral/driver/interrupt:interrupt_controller_interface",
        "//libcoral/driver/interrupt:top_level_interrupt_manager",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:fileio",
    ],
)

cc_library(
    name = "beagle_top_level_handler",
    srcs = ["beagle_top_level_handler.cc"],
    hdrs = ["beagle_top_level_handler.h"],
    deps = [
        "//libcoral/api:driver_options_fbs",
        "//libcoral/driver:top_level_handler",
        "//libcoral/driver/config",
        "//libcoral/driver/registers",
        "//libcoral/port",
        "//libcoral/port:fileio",
    ],
)

cc_library(
    name = "beagle_ioctl",
    hdrs = ["beagle_ioctl.h"],
    deps = ["//libcoral/driver/kernel:gasket_ioctl"],
)

cc_library(
    name = "beagle_kernel_top_level_handler",
    srcs = ["beagle_kernel_top_level_handler.cc"],
    hdrs = ["beagle_kernel_top_level_handler.h"],
    deps = [
        ":beagle_ioctl",
        "//libcoral/api:driver_options_fbs",
        "//libcoral/driver:top_level_handler",
        "//libcoral/port",
        "//libcoral/port:fileio",
        "//libcoral/port:std_mutex_lock",
        "//libcoral/port:thread_annotations",
    ],
)

# Standalone shared library that can be linked into a binary built elsewhere.
cc_binary(
    name = "libbeagle-usb.so",

    # Setting DT_SONAME for the result .so.
    # See b/72234056
    linkopts = [
        "-Wl,-soname,libbeagle-usb.so",
        "-Wl,--version-script=$(location //driver:libdarwinn_driver.lds)",
    ],
    linkshared = 1,
    linkstatic = 1,
    deps = [
        ":beagle_usb_driver_provider",
        "//libcoral/driver:libdarwinn_driver.lds",
    ],
)

# Standalone shared library that can be linked into a binary built elsewhere.
cc_binary(
    name = "libbeagle-pci.so",

    # Setting DT_SONAME for the result .so.
    # See b/72234056
    linkopts = [
        "-Wl,-soname,libbeagle-pci.so",
        "-Wl,--version-script=$(location //driver:libdarwinn_driver.lds)",
    ],
    linkshared = 1,
    linkstatic = 1,
    deps = [
        ":beagle_pci_driver_provider",
        "//libcoral/driver:libdarwinn_driver.lds",
    ],
)
