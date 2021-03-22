Hi, if you are reading this is because you pretty likely want to participate in the development of this API and curious about how to start.

You are in **cpp-sc2** core project, but actually, we have more repositories you can contribute to:
- **[codegen](https://github.com/cpp-sc2/codegen)** - type IDs codegeneration utility;
- **[commandcenter](https://github.com/cpp-sc2/commandcenter)** - original version of CommandCenter bot with integrated cpp-sc2;
- **[docker-sc2](https://github.com/cpp-sc2/docker-sc2)** - dockerized StarCraft II Linux client;
- **[scrubber](https://github.com/cpp-sc2/scrubber)** - scrubs type ids from a game client.
- **[blank-bot](https://github.com/cpp-sc2/blank-bot)** - starter bot for StarCraft II with integrated cpp-sc2.

## What can I do?

- [ ] Search for other issues tagged [with `good first issue` or `help wanted` tag](https://github.com/cpp-sc2/cpp-sc2/issues?q=is%3Aissue+is%3Aopen+label%3A%22good+first+issue%22).
- [ ] Suggest new features.
- [ ] Vote for existing issues (issues with highest number of reactions are likely to be fixed first).
- [ ] Fix `// FIXME: ` comments in the code.
- [ ] Improve the documentation of the API.
- [ ] Add/Fix/Improve tutorials.
- [ ] Add/Fix/Improve new bot examples.
- [ ] Add/Fix/Improve tests.
- [ ] Add new bots examples.
- [ ] Help to test changes from the `dev` branch.
- [ ] Support this project on [Patreon](https://www.patreon.com/cppsc2) or just [buy me a coffee](https://www.buymeacoffee.com/alkurbatov).

If you have any suggestions, feel free to comment on this thread, or chat me over [Discord](https://discordapp.com/invite/Emm5Ztz) (the `#cpp` channel).

## What should I know before the start?

**The `master` branch is locked**
The `master` branch is considered stable thus all development happens in the `dev` branch. We merge changes from `dev` to `master` when it is time for release.

**Code guidelines**
We do our best to conform to [the Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) with the exception that we use four space tabs instead of two space tabs.

**Commit guidelines**
We follow the semantic versioning approach, this is important so your PR will appear on the Changelog 🎉 ! I guess you expect recognition and we will give it to you.
See [standard-version](https://github.com/conventional-changelog/standard-version#commit-message-convention-at-a-glance) for commit guidelines.

The list of supported commit message prefixes:

- `feat` - a new feature or API improvements;
- `fix` - a bugfix;
- `perf` - performance improvements;
- `refactor` - code refactoring;
- `test` - functional or unit tests;
- `build` - build system improvements,  also includes CI improvements;
- `docs` - documentation improvements;
- `chore` - routine task, e.g. create new release (doesn't appear in the changelog);
- `style` - fix code style, no functional changes (doesn't appear in the changelog.

## Before PR

* Keep the PR small as possible and one single topic for each.
* Write good commit message: describe what was the problem and why the changes required.
* Run Google style linter, see [.travis/lint.sh](.travis/lint.sh) for details.
* Consider implementing a test.
