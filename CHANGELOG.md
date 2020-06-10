# Changelog

All notable changes to this project will be documented in this file. See [standard-version](https://github.com/conventional-changelog/standard-version) for commit guidelines.

### [1.3.1](https://github.com/alkurbatov/cpp-sc2/compare/v1.3.0...v1.3.1) (2020-06-10)


### Bug Fixes

* Fix CI build could be not marked as failed ([ef2f0b9](https://github.com/alkurbatov/cpp-sc2/commit/ef2f0b94c27f8ce82ad106d6eab9ecb75c420e29))
* Fix links in README ([2ed52f2](https://github.com/alkurbatov/cpp-sc2/commit/2ed52f2beb388bc807914a283370b284e83b031d))


### Documentation

* Add GitHub issue template, [#67](https://github.com/alkurbatov/cpp-sc2/issues/67) ([7d691de](https://github.com/alkurbatov/cpp-sc2/commit/7d691de71516d08d9357b627d42d3d09c3174145))
* Add Patreon link, [#66](https://github.com/alkurbatov/cpp-sc2/issues/66) ([186fa76](https://github.com/alkurbatov/cpp-sc2/commit/186fa760385c9ea272082c67eba0052fe5aa2b9c))
* Improve build instructions, [#65](https://github.com/alkurbatov/cpp-sc2/issues/65) ([8963c9c](https://github.com/alkurbatov/cpp-sc2/commit/8963c9c0bbb83ce07284a4733a18ca8d223421f8))
* Introduce CONTRIBUTING guide, [#42](https://github.com/alkurbatov/cpp-sc2/issues/42) ([f1f3055](https://github.com/alkurbatov/cpp-sc2/commit/f1f305502af8b9390a29c843d0161b328b47fe2d))


### Build System

* Compile with clang on OS X ([3ee8a41](https://github.com/alkurbatov/cpp-sc2/commit/3ee8a4168593dbd3a5de378b2a81a8cba39caf33))
* Don't source scripts in CI ([84b79d9](https://github.com/alkurbatov/cpp-sc2/commit/84b79d984df20c42d9ecc11d61f0e05c60d1ba6b))
* Refine CI routine ([823d9fd](https://github.com/alkurbatov/cpp-sc2/commit/823d9fde3a4c91bad1f904e993a6cfd9819a2016))
* Use all available CPUs in CI build, [#65](https://github.com/alkurbatov/cpp-sc2/issues/65) ([84e23d3](https://github.com/alkurbatov/cpp-sc2/commit/84e23d3f67771cb723a5f16bdb80dba83933f4e6))
* Use xcode11.4 in CI ([dde3c34](https://github.com/alkurbatov/cpp-sc2/commit/dde3c343e6d8169473175e8e9fea22b67d05d507))

## [1.3.0](https://github.com/alkurbatov/cpp-sc2/compare/v1.2.0...v1.3.0) (2020-05-15)


### Features

* Add mineral and geyser filters, [#24](https://github.com/alkurbatov/cpp-sc2/issues/24) ([7500a6e](https://github.com/alkurbatov/cpp-sc2/commit/7500a6e90a639dd9bce59973f66d4fdb178aa559))
* Add some missing types to ABILITY_ID, RESEARCH_ID and UPGRADE_ID enums ([2b7d04e](https://github.com/alkurbatov/cpp-sc2/commit/2b7d04e2fd7646e2a7f340b1b5fae06a65c65a8a))
* Add unit upgrades level, [#54](https://github.com/alkurbatov/cpp-sc2/issues/54) ([93dedc6](https://github.com/alkurbatov/cpp-sc2/commit/93dedc61f114fd88d8ebbbca0afb35679280443e))
* add use_generalized_ability option when retrieving abilities using GetAbilitiesForUnit/s ([cc3b534](https://github.com/alkurbatov/cpp-sc2/commit/cc3b53489e5fcd38809b0b83cc6377da40ae4a38))
* Added legacy typeenums for compatibility ([f27c954](https://github.com/alkurbatov/cpp-sc2/commit/f27c954b87f331d117f19246568036c114d26576))
* Allow retrieving specific ability ids with GetAbilitiesFromUnit(s) ([c024e34](https://github.com/alkurbatov/cpp-sc2/commit/c024e3454efd62467b756e5736ded87f169fb870))
* Allow to retrieve player names, [#13](https://github.com/alkurbatov/cpp-sc2/issues/13) ([6487f61](https://github.com/alkurbatov/cpp-sc2/commit/6487f61f7e7a05addd94ed73ef72a706f6079add))
* Allow to set and retrieve AI build, [#45](https://github.com/alkurbatov/cpp-sc2/issues/45) ([87d10ce](https://github.com/alkurbatov/cpp-sc2/commit/87d10ce8bcee08ef02cc5b5032afc79e8cb931b5))
* Allow to set player name, [#13](https://github.com/alkurbatov/cpp-sc2/issues/13) ([7ab6688](https://github.com/alkurbatov/cpp-sc2/commit/7ab668873746931a372aaae6ea45badde454502a))
* Enable display of 'ghost' buildings, [#23](https://github.com/alkurbatov/cpp-sc2/issues/23) ([74f24e1](https://github.com/alkurbatov/cpp-sc2/commit/74f24e125b972b1ca834dfb75622876928849c36))
* Include the amount of health and shield damage in OnUnitDamaged events ([3bd0469](https://github.com/alkurbatov/cpp-sc2/commit/3bd046938ac3e510655fb26ca8816e6872f36d85))
* On Neutral Unit Created, [#33](https://github.com/alkurbatov/cpp-sc2/issues/33) ([2988bf3](https://github.com/alkurbatov/cpp-sc2/commit/2988bf3f8030431b46d2813003cefac6ae685e04))
* Show invisible units when observing replays ([985f1ae](https://github.com/alkurbatov/cpp-sc2/commit/985f1ae8df5afdc2501615d6be5ab2403e741eeb))
* Sync IDs with the latest sc2 ([4c20614](https://github.com/alkurbatov/cpp-sc2/commit/4c206148a3ff22f46d215c9b9d1859f8e479e39c))
* Upgraded type enums for 4.11.3 ([2ae5519](https://github.com/alkurbatov/cpp-sc2/commit/2ae5519f6fa3c0954cf0d3c0d9d6e92effb81a8f))
* **zerg:** Allow to get count of larva, [#44](https://github.com/alkurbatov/cpp-sc2/issues/44) ([e205164](https://github.com/alkurbatov/cpp-sc2/commit/e2051646cb0a9ed38cbac76ff5bf586a912f1a0b))


### Bug Fixes

* == and != operators in Point2D and Point3D should be const functions to implement equal_to interface ([13ebbdf](https://github.com/alkurbatov/cpp-sc2/commit/13ebbdf479df6158b12c4a338914d494e00d6767))
* Broken deployment of the API docs ([b682b3e](https://github.com/alkurbatov/cpp-sc2/commit/b682b3e702b11ad28b96210c4798c7cda1309a59))
* GetFoodWorkers() should return uint32_t ([11b8860](https://github.com/alkurbatov/cpp-sc2/commit/11b886055b8fe7eb0cb409efc578a850c64e5ef0))
* GetGameLoop() returns wrong number on restart ([e94baa2](https://github.com/alkurbatov/cpp-sc2/commit/e94baa24897b7035f906a6b39e9fea02b2be31b4))
* issue where OnUnitDamage event was issued multiple times ([5e3f3fd](https://github.com/alkurbatov/cpp-sc2/commit/5e3f3fdd9fa3ca77ebbe71b48f19c2062139c105))
* Report error if API can't load replay info ([215a310](https://github.com/alkurbatov/cpp-sc2/commit/215a310e4ca9dd3c825bdf8b7b65528a9689f0d4))
* Simultaneous 'Created' and 'Completed' events ([5530467](https://github.com/alkurbatov/cpp-sc2/commit/553046759347651be5fc22a55f0993caa5daae13))
* Skip replay in case of any loading errors ([cc937a7](https://github.com/alkurbatov/cpp-sc2/commit/cc937a78ec044eea1246728c572fbe54c2a7cf14))
* Unit filters always returned 'true' ([8731e75](https://github.com/alkurbatov/cpp-sc2/commit/8731e75f5c88190dcf6290b53520f3f2bb5dd3a9))


### Performance Improvements

* Mark newly constructed buildings as idle ([d73f633](https://github.com/alkurbatov/cpp-sc2/commit/d73f633662f7afd0fd4926c8d82b473412f98ca7))


### Build System

* Don't try to publish docs in dev branch ([b88aef2](https://github.com/alkurbatov/cpp-sc2/commit/b88aef2a2b2e0ef1be14be71081e2db3ebd2e03c))
* Improve compilation under VS 2019 ([bed887a](https://github.com/alkurbatov/cpp-sc2/commit/bed887a262d76b44f7351043b5a6f4f80754f1dd))
* Validate windows builds against VS2019 ([7e21c71](https://github.com/alkurbatov/cpp-sc2/commit/7e21c71d770ec25d195afbf4744343f1c39350bc))


### Refactoring

* Move logic from .travis.yaml to scripts ([34da289](https://github.com/alkurbatov/cpp-sc2/commit/34da289a52764bb3d7f5bc2421a1ea4b63eea201))


### Documentation

* Provide better Windows build instructions ([2e0a4d4](https://github.com/alkurbatov/cpp-sc2/commit/2e0a4d445df6dc013d3035c18495e2910c2d62c6))
* Set Windows build recommendations to VS 2019 ([6971da0](https://github.com/alkurbatov/cpp-sc2/commit/6971da07c837954c84b94ac47a91fbf968dbe087))

## [1.2.0](https://github.com/alkurbatov/cpp-sc2/compare/v1.1.0...v1.2.0) (2019-11-04)


### Features

* Implement IsTownHall filter, [#17](https://github.com/alkurbatov/cpp-sc2/issues/17) ([6f786a4](https://github.com/alkurbatov/cpp-sc2/commit/6f786a4c9064dc01e15c8c44928791a9af52d7b7))
* New coordinator setting allowing users to choose to reduce the number of generated actions ([37d1776](https://github.com/alkurbatov/cpp-sc2/commit/37d177682d5c3c980ed6a356f0a1830ffb4e7f89))
* Support -d, --data_version parameter [#20](https://github.com/alkurbatov/cpp-sc2/issues/20) ([d7d0168](https://github.com/alkurbatov/cpp-sc2/commit/d7d016865e70f1169ae3fa2e470ea87378a01e53))
* Support launch in full screen, [#21](https://github.com/alkurbatov/cpp-sc2/issues/21) ([d610d2d](https://github.com/alkurbatov/cpp-sc2/commit/d610d2d27c0641517b8a69df06af26e6dcd37c7e))
* Use full screen for first player only, [#21](https://github.com/alkurbatov/cpp-sc2/issues/21) ([9177574](https://github.com/alkurbatov/cpp-sc2/commit/9177574da7fd4ef8e62b3b9bfffc3107ab80f52f))


### Bug Fixes

* Always specify -displayMode value ([cf39856](https://github.com/alkurbatov/cpp-sc2/commit/cf398561020b1d329fc288c5d8fa8220230a73db))
* Correct player data fields return types, [#16](https://github.com/alkurbatov/cpp-sc2/issues/16) ([cfed8b8](https://github.com/alkurbatov/cpp-sc2/commit/cfed8b8921c73c9a2fec980e0dea82f9281c00d4))
* EXCLUDE of */build/* on travis excludes everything ([e17b553](https://github.com/alkurbatov/cpp-sc2/commit/e17b5539a0bf99c86a588f9c40761ac33002ca0b))
* Exit in child process instead of sleep, [#22](https://github.com/alkurbatov/cpp-sc2/issues/22) ([9b10fc0](https://github.com/alkurbatov/cpp-sc2/commit/9b10fc0f21f3398848a152a2ed54b89538281438))
* Fix compilation under VS2019 ([abd6bd7](https://github.com/alkurbatov/cpp-sc2/commit/abd6bd77b1497d6e26e88805fc0ca0728d5e2cf9))


### Refactoring

* discard these scripts replaced by code in the .travis file ([01e5d75](https://github.com/alkurbatov/cpp-sc2/commit/01e5d757c151a0e2986b477a054add0b7b214375))
* Fix compilation warning in tests ([07f0dae](https://github.com/alkurbatov/cpp-sc2/commit/07f0dae0f6ab0a06fdc0c5f1a511aa81728743ed))
* Group unit filters in separate file, [#19](https://github.com/alkurbatov/cpp-sc2/issues/19) ([6c87664](https://github.com/alkurbatov/cpp-sc2/commit/6c87664e6c7096c992a73c94c5caa1fc17a059e9))


### Build System

* Updated travis build script + Doxygen generation and deployment ([41f9659](https://github.com/alkurbatov/cpp-sc2/commit/41f965983e288d9f9501dc42d65120d6d265eb77))

## [1.1.0](https://github.com/alkurbatov/cpp-sc2/compare/v1.0.0...v1.1.0) (2019-09-14)


### Bug Fixes

* Avoid crash of replay observer on relaunch ([0f5b5fb](https://github.com/alkurbatov/cpp-sc2/commit/0f5b5fb))
* Don't call TerminateProcess with zero pid ([a7c1a8c](https://github.com/alkurbatov/cpp-sc2/commit/a7c1a8c))


### Build System

* Fix C4530 warnings generated by VS2017 ([a7a7ed6](https://github.com/alkurbatov/cpp-sc2/commit/a7a7ed6))


### Documentation

* Correct commit hashes in changelog ([f501670](https://github.com/alkurbatov/cpp-sc2/commit/f501670))
* Correct description of the Cloaked state ([a0520d3](https://github.com/alkurbatov/cpp-sc2/commit/a0520d3))


### Features

* Allow to change replay observing perspective ([8c3051e](https://github.com/alkurbatov/cpp-sc2/commit/8c3051e))
* Allow to retrieve cloaked enemy units ([789465d](https://github.com/alkurbatov/cpp-sc2/commit/789465d))
* Expose shadows of moving burrowed units ([b1b7ed4](https://github.com/alkurbatov/cpp-sc2/commit/b1b7ed4))


### Refactoring

* Fix style ([71c785b](https://github.com/alkurbatov/cpp-sc2/commit/71c785b))
* Simplify IgnoreReplay ([8ef49bf](https://github.com/alkurbatov/cpp-sc2/commit/8ef49bf))
* Use pointer to pointer ([e366ba7](https://github.com/alkurbatov/cpp-sc2/commit/e366ba7))

## 1.0.0 (2019-08-28)


### Bug Fixes

* Bring in new civetweb submodule ([1652187](https://github.com/alkurbatov/cpp-sc2/commit/1652187))
* Add missing types to UnitTypeToName ([91311b3](https://github.com/alkurbatov/cpp-sc2/commit/91311b3))
* Don't invert heights map coordinates... ([c2c38bf](https://github.com/alkurbatov/cpp-sc2/commit/c2c38bf))
* Fix assertion in SampleImageData ([ba30bfa](https://github.com/alkurbatov/cpp-sc2/commit/ba30bfa))
* Fix chronoboost ([573960b](https://github.com/alkurbatov/cpp-sc2/commit/573960b))
* Fix IsPlacable and IsPathable, [#5](https://github.com/alkurbatov/cpp-sc2/issues/5) ([3b0100d](https://github.com/alkurbatov/cpp-sc2/commit/3b0100d))
* Fix MOVE and PATROL abilities ([bb8109a](https://github.com/alkurbatov/cpp-sc2/commit/bb8109a))
* Fix some compilation warnings ([a2c4501](https://github.com/alkurbatov/cpp-sc2/commit/a2c4501))
* Fix type of minerals and vespene ([d2b29a9](https://github.com/alkurbatov/cpp-sc2/commit/d2b29a9))
* Fixed height map and visibility map ([8207f1c](https://github.com/alkurbatov/cpp-sc2/commit/8207f1c))
* Handle INVALID in all *ToName functions ([f0f0e9e](https://github.com/alkurbatov/cpp-sc2/commit/f0f0e9e))


### Build System

* Don't enforce WX on Windows ([f7af6d4](https://github.com/alkurbatov/cpp-sc2/commit/f7af6d4))
* Reimplement Travis CI ([4da5dab](https://github.com/alkurbatov/cpp-sc2/commit/4da5dab))


### Documentation

* Add build instructions for nmake ([c131953](https://github.com/alkurbatov/cpp-sc2/commit/c131953))
* Add more platform-specific dependencies ([56c52af](https://github.com/alkurbatov/cpp-sc2/commit/56c52af))
* Added missing link to tutorial ([a7c3372](https://github.com/alkurbatov/cpp-sc2/commit/a7c3372))
* Correct README ([f7a2051](https://github.com/alkurbatov/cpp-sc2/commit/f7a2051))
* Fix a typo ([2a33789](https://github.com/alkurbatov/cpp-sc2/commit/2a33789))
* Mention discord in README ([9755002](https://github.com/alkurbatov/cpp-sc2/commit/9755002))
* Refine build instructions ([68a3643](https://github.com/alkurbatov/cpp-sc2/commit/68a3643))


### Features

* Add 'rich' types of vespene extractors ([ab0f5bc](https://github.com/alkurbatov/cpp-sc2/commit/ab0f5bc))
* Add conversion of Point2D to Point2DI ([7791b6a](https://github.com/alkurbatov/cpp-sc2/commit/7791b6a))
* Add cyclone lock on damage upgrade ([d67204a](https://github.com/alkurbatov/cpp-sc2/commit/d67204a))
* Adjust CloakState parameters to the new proto ([b74166f](https://github.com/alkurbatov/cpp-sc2/commit/b74166f))
* Extend DisplayType with Placeholder value ([dd73ec0](https://github.com/alkurbatov/cpp-sc2/commit/dd73ec0))
* Extend Rect2DI functionality ([054a835](https://github.com/alkurbatov/cpp-sc2/commit/054a835))
* Switch to the latest proto ([f3bd271](https://github.com/alkurbatov/cpp-sc2/commit/f3bd271))


### Tests

* Fix TestUnitCommand ([4debe09](https://github.com/alkurbatov/cpp-sc2/commit/4debe09))
