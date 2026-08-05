# Build Instructions

> :construction: This project requires a compiler with C++20 support.

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Build Instructions](#build-instructions)
    - [Prerequisites](#prerequisites)
    - [Step 1: Clone Repository](#step-1-clone-repository)
    - [Step 2: CMake Generation](#step-2-cmake-generation)
    - [Step 3: Build Project](#step-3-build-project)
- [Compilation options](#compilation-options)
    - [Game client version](#game-client-version)
- [Troubleshooting](#troubleshooting)
    - [Build freezes](#build-freezes)
- [WSL2 Support](#wsl2-support)
    - [Requirements](#requirements)
    - [Building](#building)
    - [Downstream Projects](#downstream-projects)

<!-- markdown-toc end -->

> ℹ️ NOTE
>
> For building for Windows under WSL2, see [WSL2 Support](#wsl2-support).

## Prerequisites

> ℹ️ NOTE
>
> Commands that look like this:
> ```
> foo bar 
> ```
>
> Are to be entered in the OS command terminal:
>
> - Windows: **PowerShell**
> - macOS: **Terminal**
> - Linux: Your preferred shell (`Ctrl + Alt + T`)

<details name="prerequisites"><summary>Windows</summary>

### 1. [Install *Git*](https://git-scm.com/)

### 2. Install IDE

|                        | [<u>CLion</u>](https://www.jetbrains.com/clion/download/?section=windows) | [<u>Visual Studio</u>](https://visualstudio.microsoft.com/downloads/) | [<u>Qt Creator</u>](https://www.qt.io/development/download-qt-installer-oss) |
|:-----------------------|:--------------------------------------------------------------------------|:----------------------------------------------------------------------|:-----------------------------------------------------------------------------|
| **Setup Effort:**      | **Low** (Plug-and-play)                                                   | **Low-Medium**                                                        | **Low-Medium**                                                               |
| **Customizability:**   | High                                                                      | **Exceptional**                                                       | Moderate                                                                     |
| **Git Functionality:** | **Exceptional** (Native)                                                  | **Excellent** (Native)                                                | Good (Native)                                                                |
| **Resource Usage:**    | Heavy                                                                     | Heavy                                                                 | **Moderate**                                                                 |
| **CMake Support:**     | **Excellent** (Native)                                                    | **Excellent** (Native)                                                | Good (Native)                                                                |

</details>

<details name="prerequisites"><summary>macOS</summary>

### 1. Install *Xcode Command Line Tools*

```bash
xcode-select --install
```


> ℹ️ NOTE
> If using **CLion** IDE, skip to [Step 4](#4-install-ide).


### 2. [Install *Homebrew*](https://brew.sh/)

### 3. Install *CMake* and *Ninja*

```
brew install cmake ninja
```

### 4. Install IDE

Recommended IDE Comparison:

|                        | [<u>CLion</u>](https://www.jetbrains.com/clion/download/?section=mac) | [<u>Visual Studio Code</u>](https://code.visualstudio.com/Download) | [<u>Qt Creator</u>](https://www.qt.io/development/download-qt-installer-oss) |
|:-----------------------|:----------------------------------------------------------------------|:--------------------------------------------------------------------|:-----------------------------------------------------------------------------|
| **Setup Effort:**      | **Low** (Plug-and-play)                                               | Medium (Extension heavy setup)                                      | **Low-Medium**                                                               |
| **Customizability:**   | High                                                                  | **Exceptional**                                                     | Moderate                                                                     |
| **Git Functionality:** | **Exceptional** (Native)                                              | Good (**Excellent** with extensions)                                | Good (Native)                                                                |
| **Resource Usage:**    | Heavy                                                                 | **Lightweight**                                                     | Moderate                                                                     |
| **CMake Support:**     | **Excellent** (Native)                                                | **Excellent** (via Extension)                                       | Good (Native)                                                                |

</details>

<details name="prerequisites"><summary>Linux</summary>

### 1. Install Build Essential, CMake, Ninja, and Git

```
sudo apt install build-essential cmake ninja-build git
```

### 2. Ensure your favorite C++ CMake-capable IDE (or editor) is installed.

</details>

## Step 1: Clone Repository

### 1. Open the OS command terminal.

> ❗IMPORTANT
>
> Do not use the terminal within the IDE, it can confuse CMake's automated build process.

### 2. Navigate to the path where you want to save your bot:

<details name="step_1"><summary>Windows:</summary>

```
cd C:\YOUR\FOLDER\PATH
```

</details>

<details name="step_1"><summary>macOS/Linux:</summary>

```
cd /YOUR/FOLDER/PATH
```

</details>

### Option A: Clone the official repo directly:

```
git clone https://github.com/cpp-sc2/cpp-sc2
```

### Option B: If you made your own fork, use your fork's URL instead:

```
git clone https://github.com/YOUR_USERNAME/YOUR_REPO_NAME
```

## Step 2: CMake Generation

### 1. Open your IDE.

### 2. Select *Open Folder* from the menu.

### 3. Select the newly cloned folder:

<details name="step_2"><summary>Windows:</summary>

```
C:\YOUR\FOLDER\PATH\REPO_NAME
```

</details>

<details name="step_2"><summary>macOS/Linux:</summary>

```
/YOUR/FOLDER/PATH/REPO_NAME
```

</details>

> **CLion**: Use the **Enable profile** checkbox to enable all `x64` (Window) or `Unix` (macOS/Linux) build presets.

> **VS Code**: If using the *CMake Tools extension*, it will automatically prompt you to configure a kit (choose your default compiler like Clang or GCC).

The initial project build process will begin automatically.

Wait for **"CMake generation finished"** (or equivalent status) to proceed to the next step.

## Step 3: Build Project

1. On the top toolbar is a drop-down menu:

   change the setting from `Debug` to `RelWithDebInfo`.

> <details>
> <summary> 💡TIP: What is<code>RelWithDebInfo</code>?</summary>
> <br><code>RelWithDebInfo</code> is a blend of the <code>Release</code> and <code>Debug</code> CMake build types:
> <br><br> - <code>Debug</code> is designed for development and testing, but can cause issues for SC2 bot dev due to performance costs.
> <br><br> - <code>Release</code> is what your bot will be built as when you submit to the ladder.
> <br><br> - <code>RelWithDebInfo</code> is nearly as fast as Release, and if your client crashes, you get readable debugging output rather than Release's cryptic memory addresses. If the information it provides is not adequate, consider swapping to `Debug`.
> </details>

Open the <b>Build</b> menu on the top toolbar and choose the option for your IDE:

> CLion: **Rebuild Project**

> Visual Studio: **Rebuild Solution** (<code>Ctrl+Alt+F7</code>).

> Qt Creator: **Rebuild Project**.

> VS Code: Open the Command Palette (Ctrl+Shift+P / Cmd+Shift+P) and type CMake: Clean Rebuild.

A final build process will commence, taking a few minutes. When complete, proceed to the [next page](getting_started.md).

# Compilation options

## Game client version

By default, the API assumes the latest version of the game client. The assumed version can be found in cmake's output, e.g.:
```bash
$ cmake ../ | grep 'SC2 version'
Target SC2 version: 5.0.15
...
```

However, sometimes one may need to compile with an older version of the game, e.g. to play with a Linux build which is
always behind the Windows version. It is possible by specifying the game version manually, e.g.:
```bash
$ cmake -DSC2_VERSION=4.10.0 ../
```

# Troubleshooting

## Build freezes

If the final project build freezes (typically seen on underpowered machines), limit the parallel cores manually:

Replace `<preset-name>` with the identifier found in your `CMakePresets.json` (e.g., `x64-debug`).


<details name="build_freeze"><summary>Windows</summary>

```powershell
cmake --build --preset <preset-name> --parallel ($env:NUMBER_OF_PROCESSORS - 1)
```

</details>

<details name="build_freeze"><summary>macOS</summary>

```bash
cmake --build --preset <preset-name> --parallel $(( $(sysctl -n hw.logicalcpu) - 1 ))
```

</details>

<details name="build_freeze"><summary>Linux</summary>

```bash
cmake --build --preset <preset-name> --parallel $(nproc --ignore=1)
```

</details>

Or just drop the number of cores to 1:

```
cmake --build --preset <preset-name> --parallel 1
```

# WSL2 Support

Thanks to interoperability between the [Windows and Linux file systems](https://docs.microsoft.com/en-us/windows/wsl/filesystems) in WSL2, it is possible to cross compile `cpp-sc2` under WSL2 for Windows and launch the executables from the WSL2 context using the Windows Starcraft II installation. Current implementation may not support custom installations of Starcraft II (e.g. to an external hard drive).

This documentation assumes the user is familiar with WSL2 setup. For a more detailed walkthrough of using WSL2 for the first time, see the [Microsoft documentation on installing Linux on Windows with WSL](https://docs.microsoft.com/en-us/windows/wsl/install)

## Requirements

Cross compilation is facilitated through the toolchain file: `cmake/toolchain/x86-64-w64-mingw32.cmake`, which will require the installation of MinGW packages and POSIX configuration changes:

```bash
$ sudo apt install mingw-w64-x86-64-dev \
                g++-mingw-w64-x86-64 \
                gcc-mingw-w64-x86-64 \
                win-iconv-mingw-w64-dev

# Use POSIX threading model for MinGW
# Each command will return a prompt to select between three options:
#   x86_64-w64-mingw32-gxx-win32 auto-mode (this is the default install behavior)
#   x86_64-w64-mingw32-gxx-posix manual mode <---- Select this option
#   x86_64-w64-mingw32-gxx-win32 manual mode
#
# Select the -posix post-fixed alternative for both gcc and g++ MinGW compilers
# Alternatives can be changed at any time by re-running the commands
$ sudo update-alternatives --config x86_64-w64-mingw32-gcc
$ sudo update-alternatives --config x86_64-w64-mingw32-g++
```

## Building

To cross compile, enable the `WSL2_CROSS_COMPILE` option either in the project root `CMakeLists.txt` or by passing the option from the command line:

```bash
# Generate CMake configuration
$ cmake -B build -DWSL2_CROSS_COMPILE=ON

# Compile
$ cmake --build build -j

# Built executables can be run from the WSL2 context
$ ./build/bin/all_tests.exe
Running test: sc2::TestAbilityRemap
Launched SC2 (C:\Program Files (x86)\StarCraft II\Versions\Base87702\SC2_x64.exe), PID: 35288
Waiting for connection.
Connected to 127.0.0.1:8167
Waiting for the JoinGame response.
WaitJoinGame finished successfully.
...
```

## Downstream Projects

When including `cpp-sc2` as a dependency (whether as a git submodule, or using CMake's `FetchContent`), the toolchain file for WSL2 cross compilation must be specified *prior* to the first CMake `project` declaration. The [BlankBot](https://github.com/cpp-sc2/blank-bot) repository provides the framework for incorporating WSL2 cross compilation, but for other projects looking to use the interface:

1. Copy the `cpp-sc2` toolchain file [cmake/toolchain/x86-64-w64-mingw32.cmake](https://github.com/cpp-sc2/cpp-sc2/blob/master/cmake/toolchain/x86-64-w64-mingw32.cmake). This can be kept in-project as with `cpp-sc2` and `BlankBot`, or the path provided at CMake configuration time from the command line.

2. Set `CMAKE_TOOLCHAIN_FILE` as the path to the toolchain file, and the `WSL2_CROSS_COMPILE` option to `ON` when cross compiling:

```bash
$ cmake -B build \
    -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain/file \
    -DWSL2_CROSS_COMPILE=ON
```
