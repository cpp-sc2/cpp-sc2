# Build instructions

## Prerequisites

For building for Windows under WSL2, see [WSL2 Support](#wsl2-support).

1. Download and install [CMake](https://cmake.org/download/).

2. A compiler with C++14 support.

3. Windows: Download and install Visual Studio ([2017](https://www.visualstudio.com/downloads/) or newer).

4. Linux: Install 'gcc-c++'.

5. Linux: Install the 'make' utility.

6. OS X: Install XCode.

7. OS X: Install XCode command-line tools.

## Windows (Visual Studio)
```bat
:: Clone the project.
$ git clone git@github.com:cpp-sc2/cpp-sc2.git

:: Enter the working directory.
$ cd cpp-sc2

:: Create Visual Studio project files.
:: E.g. for Visual Studio 2022:
$ cmake -B build -G "Visual Studio 17 2022"

:: Build the project using Visual Studio.
$ start build\cpp-sc2.sln
```

## Windows (cmdline)
```bat
:: Clone the project.
$ git clone git@github.com:cpp-sc2/cpp-sc2.git

:: Enter the working directory.
$ cd cpp-sc2

:: Configure the project.
$ cmake -B build

:: Build the project.
$ cmake --build build --parallel
```

## Mac (Xcode)
```bash
# Clone the project.
$ git clone git@github.com:cpp-sc2/cpp-sc2.git

# Enter the working directory.
$ cd cpp-sc2

# Create Xcode project files.
$ cmake -B build -G Xcode

# Build the project using Xcode.
$ open build/cpp-sc2.xcodeproj
```

## Mac (cmdline)
```bash
# Clone the project.
$ git clone git@github.com:cpp-sc2/cpp-sc2.git

# Enter the working directory.
$ cd cpp-sc2

# Create makefiles.
$ cmake -B build

# Build the project.
$ cmake --build build --parallel
```

## Linux (cmdline)
```bash
# Clone the project.
$ git clone git@github.com:cpp-sc2/cpp-sc2.git

# Enter the working directory.
$ cd cpp-sc2

# Create makefiles.
$ cmake -B build

# Build the project.
$ cmake --build build --parallel
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
# From the command line
$ cmake -B build \
    -DCMAKE_TOOLCHAIN_FILE=/path/to/toolchain/file \
    -DWSL2_CROSS_COMPILE=ON
```
