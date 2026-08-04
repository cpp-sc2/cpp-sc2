# cpp-sc2

[![GitHub](https://img.shields.io/github/license/cpp-sc2/cpp-sc2)](https://github.com/cpp-sc2/cpp-sc2/blob/master/LICENSE)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-green.svg)](https://isocpp.org/std/the-standard)
[![Build Status](https://github.com/cpp-sc2/cpp-sc2/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/cpp-sc2/cpp-sc2/actions/workflows/ci.yml)
[![Join the chat in Discord: https://discord.gg/YurYAgHRSw](https://img.shields.io/badge/Discord-Chat!-brightgreen.svg)](https://discord.gg/YurYAgHRSw)

The StarCraft II API provides access to in-game state observation and unit
control. The API is a wrapper around protobuf defined protocol over a websocket
connection.  

While it's possible to write directly to the protocol, this library provides
a C++ and class-based abstraction.

## Documentation

* [Getting Started with SC2 CPP Bot API](https://www.youtube.com/watch?v=Z7eX7YLPwc8).
* A [build guide](docs/building.md) and [tutorials](docs/tutorial1.md) are available to help you get started with your SC2 Bot.
* The API documentation can be found on our
  [GitHub pages site](https://cpp-sc2.github.io/cpp-sc2). The documentation is
  generated from code automatically, using [Doxygen](http://www.stack.nl/~dimitri/doxygen/)
* For example of usage of this API please refer to
  [CommandCenter](https://github.com/cpp-sc2/commandcenter),
  [Suvorov bot](https://github.com/alkurbatov/suvorov-bot) and
  the [examples](https://github.com/cpp-sc2/cpp-sc2/tree/master/examples) folder
  in this project.
* To start from scratch, please check this
  [boilerplate](https://github.com/cpp-sc2/blank-bot).

## Support

Have questions but don't want to create an issue? Join the unofficial
[Starcraft II AI](https://discordapp.com/invite/Emm5Ztz) Discord server. Questions about this
repository can be asked in the text channel [#cpp](https://discord.com/channels/350289306763657218/350289506068463618).  

Also, please consider to support this project on
[Boosty](https://boosty.to/cpp-sc2). Support of the project allows to make
releases more often and implement new features for developers.

## Building the project

This library uses [CMake](https://cmake.org/download/) with Ninja to generate project
files. It builds on most IDEs with little configuration needed.

It relies on the following contrib packages:

1. Civetweb
1. Protobuf
1. SDL (optional)

Follow the [build guide](docs/building.md) to help you through the process.

## Additional Maps

This repository only comes with a few maps for testing.
Additional maps can be found on the [AI Arena](https://aiarena.net/wiki/maps/) website.

## Contributing

Please, read the detailed [contributing guide][contributing-guide] before
creating pull-requests to the project. It can save you a lot of time.

[contributing-guide]: https://github.com/cpp-sc2/cpp-sc2/issues/9
