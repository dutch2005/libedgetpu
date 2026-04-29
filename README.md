# PyCoral & LibEdgeTPU Modernized (C++23)

This repository contains the modernized source code for the Google Coral Edge TPU runtime driver (`libedgetpu`) and its Python bindings (`pycoral`).

> [!IMPORTANT]
> **Modernization Highlights (v2.0.0+):**
> - **C++23 Standard**: Core driver updated to C++23 for performance and stability.
> - **Statically Linked**: The `pycoral` wheels now statically link the `libedgetpu` driver, removing the need for separate runtime installation.
> - **Ubuntu 24.04 (Noble)**: Full support for the latest Ubuntu LTS.
> - **Hermetic Build**: Uses Bazel 6.5.0 with hermetic toolchains for Python (3.9-3.14).

## 🚀 Installation

### 1. Ubuntu PPA (Recommended)
Install the official pre-built packages for Ubuntu 24.04:
```bash
sudo add-apt-repository ppa:dutch2005/pycoral-modernized
sudo apt update
sudo apt install python3-pycoral
```

### 2. GitHub Packages (pip)
You can install the wheels directly from this repository:
```bash
pip install --extra-index-url https://maven.pkg.github.com/dutch2005/libedgetpu pycoral
```

### 3. Manual Download
Download `.deb` packages or `.whl` files directly from the [GitHub Releases](https://github.com/dutch2005/libedgetpu/releases) page.

## 🛠️ Building from Source

The project uses **Bazel 6.5.0** for all builds.

### Build Python Wheel
```bash
bazel build //pycoral:wheel
```
*Specify Python version with `TF_PYTHON_VERSION=3.12` env var.*

### Build Runtime Library (Shared Object)
```bash
bazel build //src:libedgetpu
```

### Local Docker Build
To replicate the CI environment locally:
```bash
docker build -t coral-builder -f docker/Dockerfile .
docker run --rm -v $(pwd):/workspace coral-builder bazel build //pycoral:wheel
```

## 📦 CI/CD Pipeline
The repository uses a fully automated GitHub Actions pipeline that triggers on tags (`v*`):
1. **Validates** the hermetic dependency graph.
2. **Builds** Python wheels for 3.9 through 3.14.
3. **Packages** source for Ubuntu Launchpad (PPA).
4. **Deploys** to GitHub Releases and GitHub Packages.

## ⚖️ License
[Apache License 2.0](LICENSE)

---
*Note: This is a modernized fork of the original Google Coral project, optimized for modern Linux distributions and simplified deployment.*
