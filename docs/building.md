# Build instructions

> :construction: This project requires a compiler with C++20 support.

<!-- markdown-toc start - Don't edit this section. Run M-x markdown-toc-refresh-toc -->
**Table of Contents**

- [Build instructions](#build-instructions)
    - [Windows](#windows)
    - [macOS](#macos)
    - [Linux](#linux)
    - [Compilation options](#compilation-options)
        - [Game client version](#game-client-version)
    - [Troubleshooting](#troubleshooting)
        - [Build freezes (Linux or macOS)](#build-freezes-linux-or-macos)
    - [WSL2 Support](#wsl2-support)
        - [Requirements](#requirements)
        - [Building](#building)
        - [Downstream Projects](#downstream-projects)

<!-- markdown-toc end -->

## Windows

For building for Windows under WSL2, see [WSL2 Support](#wsl2-support).

### Prerequisites

1. Install **[CMake](https://cmake.org/download/)**.

2. Download and install **[Visual Studio 2022](https://www.techspot.com/downloads/7493-visual-studio-2022.html)**.

    - 2022 is recommended for stability; 2017 is the minimum. 

    - Select **Desktop development with C++** workload and default optional settings.

### Step 1: Clone

- Open **Visual Studio**, select `continue without code`, and open the PowerShell **terminal** (`` CTRL+` ``)
- Navigate to where you want to save your bot:
```bat
cd C:\YOUR_FOLDER_PATH
```

#### Option A: Clone the official repo directly:

```bat
git clone --recursive https://github.com/cpp-sc2/cpp-sc2
```

#### Option B: If you made your own fork, use your fork's URL instead:

```bat
git clone --recursive https://github.com/YOUR_USERNAME/YOUR_REPO_NAME
```

### Step 2: Generate Project Files

#### Enter the working directory:

```bat
cd cpp-sc2
```

#### Run CMake to create the build files for your version of Visual Studio:

```bat
cmake -B build -G "Visual Studio 17 2022"
```

<details>
<summary>For other Visual Studio versions:</summary>
<br>
Replace the generator string in the command above with your version:

<br><code>`"Visual Studio 15 2017"`</code>
<br><code>`"Visual Studio 16 2019"`</code>
<br><code>`"Visual Studio 18 2026"`</code>

</details>

### Step 3: cmake

```bat
cmake --build build --config RelWithDebInfo
```

<details>
<summary>RelWithDebInfo?</summary>
<br><code>RelWithDebInfo</code> is a blend of the Release and Debug configurations:
<br><br>- <b>Debug</b> is not useful for bot development due to massive performance costs.
<br><br>- <b>Release</b> is what your bot will be built as when you submit to the ladder.
<br><br>- <b>RelWithDebInfo</b> is nearly as fast as Release, and if your client crashes, you get readable debugging output rather than Release's cryptic memory addresses.
</details>

### Step 4: Build Solution

#### Open the solution file in Visual Studio:

```bat
start build\cpp-sc2.sln
```

###### If you're using Visual Studio 2026: `.slnx`

#### Change Visual Studio CMake Configuration to `RelWithDebInfo`

<details>
<summary>Visual Studio 2022</summary>
<br>- On the toolbar at the top, find the <b>Configuration</b> dropdown that reads <code>x64-Debug</code>.
<br>- Click the down-arrow and select <code>Manage Configurations</code>.
<br>- Click the <span style="color: green;font-size: 1.4em;"><b>+</b></span> button to add a new configuration (you will create two).
<br>- Select <code>x64-Release</code>, rename it to <code>x64-RelWithDebInfo</code>, and confirm that the configuration type is <code>RelWithDebInfo</code>.
<br>- Click the <span style="color: green;font-size: 1.4em;"><b>+</b></span> button again, select <code>x64-Release</code>, and change this configuration type to <code>Release</code>.
<br>- Save the changes with <code>CTRL+S</code>.
<br>- Close the <code>CMakeSettings.json</code> tab.
<br>- Select the <code>x64-RelWithDebInfo</code> configuration from the dropdown.
<br>- Open the <b>Build</b> menu on the top toolbar and select <b>Rebuild All</b> (<code>CTRL+ALT+F7</code>).
</details>

<details>
<summary>Visual Studio 2026</summary>
<br>- On the toolbar at the top, find the <b>Solution Configurations</b> dropdown that reads <code>Debug</code>.
<br>- Click the down-arrow and select <code>RelWithDebInfo</code>.
<br>- Open the <b>Build</b> menu on the top toolbar and select <b>Rebuild Solution</b> (<code>CTRL+ALT+F7</code>).
</details>

## macOS

### Prerequisites

1. Install [CMake](https://cmake.org/download/).

2. Install XCode.

3. Install XCode command-line tools.

### Step 1: Clone

   ```bash
   git clone https://github.com/cpp-sc2/cpp-sc2
   ```

### Step 2. Enter the working directory.

   ```bash
   cd cpp-sc2
   ```

### Step 3. Create makefiles.

   ```bash
   cmake -B build
   ```

### Step 4. Build the project.

   ```bash
   cmake --build build --parallel $(nproc)
   ```

## Linux

### Prerequisites

1. Install [CMake](https://cmake.org/download/).

2. Install `gcc-c++`.

3. Install the `make` utility.

### Step 1. Clone

   ```bash
   git clone https://github.com/cpp-sc2/cpp-sc2
   ```

### Step 2. Create makefiles.

#### Enter the working directory.

   ```bash
   cd cpp-sc2
   ```

#### Create makefiles.

   ```bash
   cmake -B build
   ```

### Step 3. Build the project.

   ``` bash
   cmake --build build --parallel $(nproc)
   ```

## Compilation options

### Game client version

By default, the API assumes the latest version of the game client. The assumed version can be found in cmake's output, e.g.:
```bash
$ cmake ../ | grep 'SC2 version'
Target SC2 version: 5.0.5
...
```

However, sometimes one may need to compile with an older version of the game, e.g. to play with a Linux build which is
always behind the Windows version. It is possible by specifying the game version manually, e.g.:
```bash
$ cmake -DSC2_VERSION=4.10.0 ../
```

## Troubleshooting

### Build freezes (Linux or macOS)

If project compilation freezes, decrease nproc to 1 or more, e.g.:

``` bash
$ cmake --build build --parallel $(nproc --ignore=1)
```

## WSL2 Support

Thanks to interoperability between the [Windows and Linux file systems](https://docs.microsoft.com/en-us/windows/wsl/filesystems) in WSL2, it is possible to cross compile `cpp-sc2` under WSL2 for Windows and launch the executables from the WSL2 context using the Windows Starcraft II installation. Current implementation may not support custom installs of Starcraft II (e.g. to an external hard drive).

This documentation assumes the user is familiar with WSL2 setup. For a more detailed walkthrough of using WSL2 for the first time, see the [Microsoft documentation on installing Linux on Windows with WSL](https://docs.microsoft.com/en-us/windows/wsl/install)

### Requirements

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

### Building

To cross compile, enable the `WSL2_CROSS_COMPILING` option either in the project root `CMakeLists.txt` or by passing the option from the command line:

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

### Downstream Projects

When including `cpp-sc2` as a dependency (whether as a git submodule, or using CMake's `FetchContent`), the toolchain file for WSL2 cross compilation must be specified *prior* to the first CMake `project` declaration. The [BlankBot](https://github.com/cpp-sc2/blank-bot) repository provides the framework for incorporating WSL2 cross compilation, but for other projects looking to use the interface:

1. Copy the `cpp-sc2` toolchain file [cmake/toolchain/x86-64-w64-mingw32.cmake](https://github.com/cpp-sc2/cpp-sc2/blob/master/cmake/toolchain/x86-64-w64-mingw32.cmake). This can be kept in-project as with `cpp-sc2` and `BlankBot`, or the path provided at CMake configuration time from the command line.

2. Set `CMAKE_TOOLCHAIN_FILE` as the path to the toolchain file, and the `WSL2_CROSS_COMPILE` option to `ON` when cross compiling:

```bash
$ cmake -B build \
    -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain/file \
    -DWSL2_CROSS_COMPILE=ON
```
