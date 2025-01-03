# Contributing

Hi, if you are reading this is because you pretty likely want to participate in
the development of this API and curious about how to start.

You are in `cpp-sc2` core project, but actually, we have more repositories you
can contribute to:

- **[codegen](https://github.com/cpp-sc2/codegen)** - type IDs code generation
  utility;
- **[commandcenter](https://github.com/cpp-sc2/commandcenter)** - original
  version of CommandCenter bot with integrated cpp-sc2;
- **[docker-sc2](https://github.com/cpp-sc2/docker-sc2)** - dockerized
  StarCraft II Linux client;
- **[scrubber](https://github.com/cpp-sc2/scrubber)** - scrubs type ids from
  a game client.
- **[blank-bot](https://github.com/cpp-sc2/blank-bot)** - starter bot for
  StarCraft II with integrated cpp-sc2.

## What can I do?

- [ ] Search for other issues tagged [with `good first issue` or `help wanted` tag](https://github.com/cpp-sc2/cpp-sc2/issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22).
- [ ] Suggest new features.
- [ ] Vote for existing issues (issues with highest number of reactions are
      likely to be fixed first).
- [ ] Fix `// FIXME:` comments in the code.
- [ ] Improve the documentation of the API.
- [ ] Add/Fix/Improve tutorials.
- [ ] Add/Fix/Improve new bot examples.
- [ ] Add/Fix/Improve tests.
- [ ] Add new bots examples.
- [ ] Support this project on [Boosty](https://boosty.to/cpp-sc2). Support of
      the project allows to make releases more often and implement nice new
      features for developers.

If you have any suggestions, feel free to message over
[Discord](https://discord.gg/YurYAgHRSw) (the `#cpp` channel).

## What should I know before the start?

This project follows a [Code of Conduct](CODE_OF_CONDUCT.md) in order to ensure
an open and welcoming environment.

### Coding Standard

We use the [Google C++ Style Guide][google-c++-style-guide] with some tweaks and
[`clang-format`](https://clang.llvm.org/docs/ClangFormat.html) to format
the code.

### Commit guidelines

We follow the semantic versioning approach, this is important so your PR will
appear on the Changelog 🎉 ! I guess you expect recognition and we will give it
to you.

The list of supported commit message prefixes:

- `feat` - a new feature or API improvements;
- `fix` - a bugfix;
- `perf` - performance improvements;
- `refactor` - code refactoring;
- `test` - functional or unit tests;
- `build` - build system improvements, also includes CI improvements;
- `docs` - documentation improvements;
- `chore` - routine task, e.g. create new release (doesn't appear in the
  changelog);
- `style` - fix code style, no functional changes.

## Work with documentation

To edit and generate the documentation yourself:

1. Download and install [Doxygen][doxygen].
1. Fork the repository and clone it locally.
1. Checkout the master branch
   `git checkout origin/master -b my-documentation-update`.
1. Make changes to the code documentation or docs/ files.
1. From the root of the project run: `doxygen Doxyfile`.
1. Review your documentation changes by opening docs/html/index.html in your
   browser.
1. Push your changes to your fork and send us a pull request.

## Before PR

- Keep the PR small as possible and one single topic for each.
- Write good commit message: describe what was the problem and why the changes
  required.
- Consider implementing a test.

[doxygen]: http://www.stack.nl/~dimitri/doxygen/download.html#srcbin
[google-c++-style-guide]: https://google.github.io/styleguide/cppguide.html
