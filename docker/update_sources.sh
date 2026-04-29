#!/bin/bash
# Copyright 2019 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
. /etc/os-release

[[ "${NAME}" == "Ubuntu" ]] || exit 0

SOURCES_FILE="/etc/apt/sources.list"
# Check for Ubuntu 24.04+ deb822 format
if [ -f "/etc/apt/sources.list.d/ubuntu.sources" ]; then
    SOURCES_FILE="/etc/apt/sources.list.d/ubuntu.sources"
    # For deb822, we need a different approach. For now, let's just append the ports
    cat <<EOT > /etc/apt/sources.list.d/ports.sources
Types: deb
URIs: http://ports.ubuntu.com/ubuntu-ports
Suites: ${UBUNTU_CODENAME} ${UBUNTU_CODENAME}-updates ${UBUNTU_CODENAME}-security
Components: main universe
Architectures: arm64 armhf
EOT
    # Limit existing sources to amd64
    sed -i "s/Architectures: /Architectures: amd64 /g" $SOURCES_FILE || true
else
    # Legacy format
    sed -i "s/deb\ /deb \[arch=amd64\]\ /g" $SOURCES_FILE
    cat <<EOT >> $SOURCES_FILE
deb [arch=arm64,armhf] http://ports.ubuntu.com/ubuntu-ports ${UBUNTU_CODENAME} main universe
deb [arch=arm64,armhf] http://ports.ubuntu.com/ubuntu-ports ${UBUNTU_CODENAME}-updates main universe
deb [arch=arm64,armhf] http://ports.ubuntu.com/ubuntu-ports ${UBUNTU_CODENAME}-security main universe
EOT
fi