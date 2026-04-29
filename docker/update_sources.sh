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

# For Ubuntu 24.04 (noble) and later
if [ -f "/etc/apt/sources.list.d/ubuntu.sources" ]; then
    # Disable the default sources - we will rewrite them
    mv /etc/apt/sources.list.d/ubuntu.sources /etc/apt/sources.list.d/ubuntu.sources.bak
    
    # Add amd64 sources
    cat <<EOT > /etc/apt/sources.list.d/amd64.sources
Types: deb
URIs: http://archive.ubuntu.com/ubuntu/ http://security.ubuntu.com/ubuntu/
Suites: ${UBUNTU_CODENAME} ${UBUNTU_CODENAME}-updates ${UBUNTU_CODENAME}-security ${UBUNTU_CODENAME}-backports
Components: main universe restricted multiverse
Architectures: amd64
EOT

    # Add arm64 and armhf sources
    cat <<EOT > /etc/apt/sources.list.d/ports.sources
Types: deb
URIs: http://ports.ubuntu.com/ubuntu-ports
Suites: ${UBUNTU_CODENAME} ${UBUNTU_CODENAME}-updates ${UBUNTU_CODENAME}-security
Components: main universe restricted multiverse
Architectures: arm64 armhf
EOT
else
    # Legacy format for older Ubuntu
    sed -i "s/deb\ /deb \[arch=amd64\]\ /g" /etc/apt/sources.list
    cat <<EOT >> /etc/apt/sources.list
deb [arch=arm64,armhf] http://ports.ubuntu.com/ubuntu-ports ${UBUNTU_CODENAME} main universe restricted multiverse
deb [arch=arm64,armhf] http://ports.ubuntu.com/ubuntu-ports ${UBUNTU_CODENAME}-updates main universe restricted multiverse
deb [arch=arm64,armhf] http://ports.ubuntu.com/ubuntu-ports ${UBUNTU_CODENAME}-security main universe restricted multiverse
EOT
fi