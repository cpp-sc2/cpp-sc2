# cpp-sc2

[![GitHub](https://img.shields.io/github/license/cpp-sc2/cpp-sc2)](https://github.com/cpp-sc2/cpp-sc2/blob/master/LICENSE)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-green.svg)](https://isocpp.org/std/the-standard)
[![Build Status](https://github.com/cpp-sc2/cpp-sc2/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/cpp-sc2/cpp-sc2/actions/workflows/ci.yml)
[![Join the chat in Discord: https://discord.gg/YurYAgHRSw](https://img.shields.io/badge/Discord-Chat!-brightgreen.svg)](https://discordapp.com/invite/Emm5Ztz)

The StarCraft II API provides access to in-game state observation and unit
control. The API is a wrapper around protobuf defined protocol over a websocket
connection.  
While it's possible to write directly to the protocol, this library provides
a C++ and class-based abstraction.

## Documentation

* [Getting Started with SC2 CPP Bot API](https://www.youtube.com/watch?v=Z7eX7YLPwc8).
* A detailed tutorial is located in [docs/tutorial1.md](docs/tutorial1.md).
* The API documentation can be found on our
  [github pages site](https://cpp-sc2.github.io/cpp-sc2). The documentation is
  generated from code automatically, using [Doxygen](http://www.stack.nl/~dimitri/doxygen/)
* For example of usage of this API please refer to
  [CommandCenter](https://github.com/cpp-sc2/commandcenter),
  [Suvorov bot](https://github.com/alkurbatov/suvorov-bot) and
  the [examples](https://github.com/cpp-sc2/cpp-sc2/tree/master/examples) folder
  in this project.
* To start from scratch, please check this
  [boilerplate](https://github.com/cpp-sc2/blank-bot).

## Precompiled Libraries

You can download precompiled libraries for Windows and OS X
[here](docs/precompiled_libs.md).

## Support

Have questions but don't want to create an issue? Join the unofficial
Starcraft II AI Discord server
([Invite Link](https://discordapp.com/invite/Emm5Ztz)). Questions about this
repository can be asked in the text channel `#cpp`.  
Also, please consider to support this project on
[Boosty](https://boosty.to/cpp-sc2). Support of the project allows to make
releases more often and implement new features for developers.

## Building the project

This library uses [CMake](https://cmake.org/download/) to generate project
files. It builds with [Visual Studio](https://www.visualstudio.com/downloads/)
on Windows and Makefiles on the other platforms. It relies on the following
contrib packages:

1. Civetweb
1. Protobuf
1. SDL (optional)

Follow the instructions for submodules and building in
[docs/building.md](docs/building.md).

## Work with documentation

To edit and generate the documentation yourself:

1. Download and install [Doxygen][doxygen].
1. Fork the repository and clone it locally.
1. Checkout the master branch
   `git checkout origin/master -b my-documentation-update`.
1. Make changes to the code documentation or docs/ files.
1. From the root of the project run: doxygen Doxyfile.
1. Review your documentation changes by opening docs/html/index.html in your
   browser.
1. Push your changes to your fork and send us a pull request.

## Contributing

This project follows a [Code of Conduct](CODE_OF_CONDUCT.md) in order to ensure
an open and welcoming environment.

Please, read the detailed [contributing guide][contributing-guide] before
creating pull-requests to the project. It can save you a lot of time.

## Coding Standard

We use the [Google C++ Style Guide][google-c++-style-guide] with some tweaks and
[`clang-format`](https://clang.llvm.org/docs/ClangFormat.html) to format
the code.

## Additional Downloads

### Maps

This repository only comes with a few maps for testing.
Additional maps can be found [here](https://aiarena.net/wiki/maps/).

[doxygen]: http://www.stack.nl/~dimitri/doxygen/download.html#srcbin
[contributing-guide]: https://github.com/cpp-sc2/cpp-sc2/issues/9
[google-c++-style-guide]: https://google.github.io/styleguide/cppguide.html
