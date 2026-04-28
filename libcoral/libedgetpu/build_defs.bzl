"""Utilities for darwinn."""

def darwinn_port_defines():
    """Generates a list of port defines suitable for the build.

    Returns:
      List of defines.
    """
    return select({
        "//libcoral/:darwinn_portable": ["DARWINN_PORT_DEFAULT"],
        "//libcoral/:darwinn_firmware": ["DARWINN_PORT_FIRMWARE"],
        "//libcoral/conditions:default": ["DARWINN_PORT_GOOGLE3"],
    })
