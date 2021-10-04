# Build instructions

## Prerequisites
1. Download and install [CMake](https://cmake.org/download/).

2. A compiler with C++14 support.

3. If you are already cloned the repository, make sure a recursive clone of the project is done to download all submodules.
If you already cloned the repository without specifying `--recursive` you can initialize and checkout
the required submodules with the following git command:
```bash
$ git submodule update --init --recursive
```

4. Windows: Download and install Visual Studio ([2019](https://www.visualstudio.com/downloads/) or older).

5. Linux: Install 'gcc-c++'.

6. Linux: Install the 'make' utility.

7. OS X: Install XCode.

8. OS X: Install XCode command-line tools.

## Windows (Visual Studio)
```bat
:: Clone the project.
$ git clone --recursive git@github.com:cpp-sc2/cpp-sc2.git

:: Enter the working directory.
$ cd cpp-sc2

:: Create Visual Studio project files.
:: For Visual Studio 2019.
$ cmake -B build -G "Visual Studio 16 2019"
:: For Visual Studio 2017.
$ cmake -B build -G "Visual Studio 15 2017 Win64"

:: Build the project using Visual Studio.
$ start build\cpp-sc2.sln
```

## Windows (cmdline)
```bat
:: Clone the project.
$ git clone --recursive git@github.com:cpp-sc2/cpp-sc2.git

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
$ git clone --recursive git@github.com:cpp-sc2/cpp-sc2.git

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
$ git clone --recursive git@github.com:cpp-sc2/cpp-sc2.git

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
$ git clone --recursive git@github.com:cpp-sc2/cpp-sc2.git

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
