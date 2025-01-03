# Changelog

All notable changes to this project will be documented in this file.


## Unreleased

### <!-- 0 -->🚀 Features

- Rebase to the latest proto ([3dcf423](3dcf42398e65c9a0127a4d8d3c10ee966044d803))
- Rebase to the latest proto ([8aeb890](8aeb8907a2e0b317a0a4616ef57e894daf00d76d))
- Support 5.0.10 typeids ([a215b98](a215b98fcd34adc7a963e964f056adf1b7f56d09))
- Allow ActionImp::UnitCommand to use sc2::Tag ([8957d4a](8957d4a1ab335cb0b597c7d8016cdc029e4d96f4)) by @Nickrader
- Rebase to the latest proto ([59ca978](59ca978508a354c4090cf465e0a07988094dc016))
- Rebase to the latest proto ([5e31856](5e318565cef915ab3bb6650eba7c91c761da7bc4))
- Rebase to the latest proto ([7c63478](7c634781a68fe8f7cd973c92c0d185814ebdbed1)) by @Nickrader
- Rebase to the latest proto ([20ae48b](20ae48b9b60d8a5a37a7803b5b4e0002aa4964d8))
- Support 5.0.12 typeids ([f4e8761](f4e8761ee6346c95aa0253d458df241631a4e778))
- Switch to C++17 ([a306e7f](a306e7f2f203e7da55332a46d1a89d5c664c3abc))
- Update SDL to support latest OS X ([23c2efb](23c2efb11f1454f587ad07c3ccd62b2e683581df))
- Support 5.0.14 typeids ([4cf34ba](4cf34badfdb3f8718d7c0489d7541f57d1ff100d))

### <!-- 1 -->🐛 Bug Fixes

- Remove dummy typeids from units, abilities and buffs ([868a9cc](868a9cc5f7cb7887444b3cb8296440c9048e502d))
- Restore ZERG_PARASITICBOMBDUMMY ([480bc9c](480bc9c0fc126c5b5024a0cc142edeaf45041b4d))
- Sdl fetchcontent case sensitive fix ([22747b8](22747b8bf14b3ea3b8b8510dde5c87093e36da58)) by @jrtknauer
- Mingw wsl2 header normalization ([9df2e25](9df2e25f60f67f1242eb5a0833b56424e9738332)) by @jrtknauer
- Mark roach warren as building ([506e0d0](506e0d0d5cc4efa746eb38cd9ff95aa0005fd456))
- Revert changes in civetweb because of broken Windows ([e6f9b76](e6f9b763901d37ae31c5ebf61d227efc83d49c4a))
- Bad image rendering in Linux ([e8f3db9](e8f3db9c15a82b947aa092c9085c1a77e85e299a))
- Update WSL2 proto assets, #143 ([8bc55a9](8bc55a936417107d9200ebd80ed7c565633bbb9e))
- Downgrade Civetweb to v1.15, #133 ([04c44d9](04c44d95bc218f11363bf57f19de131049f8ed07))
- Apply civetweb patches only once, #148 ([117405e](117405e99210e7e1cca9999b528f235549b0ad34))

### <!-- 3 -->🚜 Refactor

- Fix compilation warnings ([fd269b3](fd269b300055215de9e53670cb64c6a3a514b1b9))
- Submodule remains ([6673dc5](6673dc5d8bd69ad9436214a59f8180a8f38f6409))
- Print error reason of SC2 connection failure, #133 ([6f14eb5](6f14eb5232952584f6f845dbb55be171de7aaa66))
- (sc2_connection) Improve connection establish logic ([b63225b](b63225b7130db7e53a81c1798959462d424d0575))
- Unify headers and sources ([53eaf51](53eaf518142f4597577d3ab3bf3850f9c4f1f7e7))
- Integrate clang-tidy ([68e42b9](68e42b9f563804f4c71a084d5d76612e02da0cb9))
- Fix some of warnings reported by clang-tidy ([4df80c7](4df80c7e2fd31739076a82e9de8eed6323033b2e))
- (clang-tidy) Disable boost checks ([6d05f16](6d05f166f8ba05abf4d31ba0ba04ec6bcd683a15))

### <!-- 4 -->👷 Build

- Msvc runtime library abstraction ([7e07179](7e071793b92caf56424f28d8c8d8dd4e10284533)) by @jrtknauer
- Removed unnecessary cmake policy settings ([d97cfe5](d97cfe5154c2b47bf3e83302475081a4d0ffc74d)) by @jrtknauer
- Cmake project restructure ([f1cba80](f1cba808cc584cc1f1f641b6447cacedde21e629)) by @jrtknauer
- Disable ipv6-parse ([9a475f8](9a475f8203967cc1326eaf38d5171d0f4f78b2b3)) by @jrtknauer
- Cmake dependency approach refactor ([477c79f](477c79f9f5dc78677ef9d3e63089243a9908c316)) by @jrtknauer
- Switch ladder CI to Ubuntu 20.04 ([3a8e89e](3a8e89e50f480b552f29f69ccc6c3335ae57a29b))
- Wsl2 cross compilation for windows ([7cfccf1](7cfccf119bf8c26f0e7dbed222adf4fb7d872563)) by @jrtknauer
- Wsl2 downstream project support ([4d9e7fe](4d9e7fed1ec9572a20cb631a70cf449a00e0cc27)) by @jrtknauer
- Cmake policy setting for protos download ([0032d69](0032d69b852ef9616d1a8f4a7281deeaf56b0872)) by @jrtknauer
- Use FetchContent to patch civetweb ([e4cd069](e4cd069fb2d4fadcb11fa2260fe9846e0c95d654))
- Fix compilation under latest OS X ([5bc693e](5bc693e61945f99354fda448b83694421d3e3023))

### <!-- 5 -->📚 Documentation

- Specify discord channel for questions regarding the API ([aefd931](aefd931ab0a4fa75c6b94b5ad7573b0af64dcbd5))
- Fix typo in CODE_OF_CONDUCT ([16a35ab](16a35ab75fad4254fa58a2bea8178432c1e2b771))
- Update supporters links ([87fd044](87fd0442aff2f989f870689565c1398ad95e5b14))
- Update maps link ([0b6682f](0b6682f5b9c990c3314f75db9e8c03a4e8f65a11))
- Pin the oldest Visual Studio version ([0794d9a](0794d9a0ce5cfd6c8140af8b5022b54759967f80))
- Wsl2 cross compilation support ([6709720](670972075050fe905f9cef8ec8f377a7ae01342b)) by @jrtknauer
- Wsl2 downstream project support ([ca7b7ae](ca7b7aeac386f605b6611802e0339ef5ba017554)) by @jrtknauer
- Minor readme changes ([b6dc5c4](b6dc5c4b02dd08b0e2dbeeef511b28e22b2b7970)) by @jrtknauer
- Claim that we support VS 2022, #130 ([e47e9e2](e47e9e2f8fdc2658cfd7ee2633064b56bb3fe7c9))
- Remove --recursive option from build instructions ([43bc2f7](43bc2f7830a0fd2e89b5467d99f78f499e70c3d5))
- Add valuable hints to documentation of some classes ([9ed3155](9ed3155f9417eab4b1e6e391f40d38fafc90871d))
- Add getting started video ([e227d28](e227d2883414aea6bd482c1901891e89aae227af))
- Remove link to Patreon ([c1befdd](c1befdd17132e0f4cf8d9f262723c4d9969076ed))
- Update copyright year ([8eb698e](8eb698e8cc4d05b0455bbc4a52c82f9c443c51c4))
- Add Discord badge to README ([a2792fe](a2792febde07e008269adea303934153782889a1))
- Update linux and macOS build instructions, #142 ([e4e7baf](e4e7bafca81d5266da811370bf44503729a0fd41))
- Refine build instructions ([998ca3b](998ca3b1d40013ebb774120787daade8f5f227ea))
- Refresh Discord invitation link ([a69b8b0](a69b8b08adf8d0e4fbde9c4479839b9a958b6bfe))

### <!-- 9 -->💼 Other

- Setup clang-format in pre-commit hooks and CI, #52 ([fdde354](fdde3542fb658f34ad97119d9c49f003b31b08f7))
- Reformat the sources, #52 ([2c125f8](2c125f802b62833a2e3a42fe432938ede5d51fac))
- Reformat the code with newer clang-format from pre-commit hooks ([c08fef3](c08fef3e812807e0297bba2f2c409b07b9ef1dad))
- Improve README.md markdown style ([e0dc678](e0dc678ac3300f1aa6ca645d8d93435c42c9fd68))


## 1.4.1 - 2022-01-08

[bfc8359](bfc83597c28f94864f639ec87d37a86c7d15538a)...[a4e1883](a4e188360e1f1686896c6b2b5dfcd8fac8221395)

### <!-- 0 -->🚀 Features

- Rebase to the latest proto ([dc67545](dc67545b574a0956a6759c4f098e00c76dd76506))
- Read path to game client from SC2PATH, #107 ([f1f65aa](f1f65aa0e33d0391e1ce3b3e2bc0960bb057e3de))

### <!-- 1 -->🐛 Bug Fixes

- Fix typo ([c031314](c0313149fe6afeb59d17c6417fad64e47dcd978b))
- Missing DebugIgnoreGas ([2eb60b9](2eb60b962a10358bbf662dbef11826a7ba57915d)) by @Nickrader
- Extend error reporting when searching SC2 executable ([26284b6](26284b6c7b61abf19fab7b94a65b068352ab49e3))

### <!-- 2 -->⚡ Performance

- Speed up creation of Point objects ([02fe908](02fe90836450ccb64523fe25aa15d95dd3d74460))

### <!-- 3 -->🚜 Refactor

- Use default destructors ([cac2237](cac223700971b55e02643318e4d4276de56c749d))

### <!-- 4 -->👷 Build

- Don't try to commit docs if no changes, #109 ([7906e37](7906e3796dce97ae9400700b768ecd5339c9ec02))

### <!-- 5 -->📚 Documentation

- Correct clone URLs ([6200ee0](6200ee03dcce1fae17174a760f9cc3969e40e17b))
- Add missing v1.4.0 to the changelog ([3c1fc5d](3c1fc5da475de28a74663cade40faa3d424f8ac0))


## 1.4.0 - 2021-10-07

[57b6e05](57b6e05c7933d4e26a5bc0e02ea0e9bc107ffa57)...[bfc8359](bfc83597c28f94864f639ec87d37a86c7d15538a)

### <!-- 0 -->🚀 Features

- Update Civetweb to v1.13 ([538383e](538383e15c220dffd693144168fced6cdaf6aa16))
- Support sc2::Unit::is_hallucination, #84 ([5617655](5617655cb450861607608cb8720682111a726821))
- Switch to 5.0.3 IDs, #78 ([bae3d5e](bae3d5e49d0963fd1d7ea059da91bc5ca4e6025b))
- Update the s2client-proto submodule ([5be7be2](5be7be2a02dc58296dcc7151951ae4d72b899975))
- Support different SC2 versions, #77 ([4a423a3](4a423a3dcbd7b268c8fc2d9225a1073faacff3cf))
- Rebase to the latest proto ([144b783](144b7835f45278f21165c37c45f8bf6040f4a173))
- Support 4.10.0 typeids, #77 ([775bcad](775bcad32871be86d3c9edffe84bdb944964384f))
- Introduce IsBuilding filter, #87 ([16d4468](16d4468826d96ec7fffeb3d996c30e27be75e46b))
- Introduce sc2::Unit::is_building, #87 ([ca4339b](ca4339b86599ceec4f358725eaadd972305b1a43))
- Update the SDL submodule ([df661b2](df661b2ee3f167d3617255e30c67be7a8db4ec55))
- Introduce IsWorker filter, #92 ([b4190a8](b4190a8ff587418e017df7f8c865a228f9d74c93))
- Introduce sc2::Unit::IsBuildFinished ([08f93f3](08f93f32d3b3fbe2082d02113d1ff844a4dd8c2b))
- Rebase to the latest proto ([fcea655](fcea655298d162b3e01e863b993d57de7c001010))

### <!-- 1 -->🐛 Bug Fixes

- Abort game on unexpected cmdline options ([86f1823](86f18230ade5c9f8f3f0f978938746669ae7db9c))
- Make '-e, --executable' optional ([794a1ff](794a1fffeacefb416616f4e86bea0847a39ad7b0))
- Don't mix runtime environments on Windows ([3c030f6](3c030f6bb89d46239806909766ca8fa4ae0ce526))
- Broken linking with SDL2-static on Windows ([2a88b08](2a88b0811d894e232e5857f0e35eeb96912298ec))
- Broken build on Windows with disabled renderer ([a319382](a319382048bf29fa31d03f41ff2d51ed0218214e))
- Throw when we can't connect to client ([085e588](085e5886150dd565f6c2d1d7ed62383364e6310c))

### <!-- 3 -->🚜 Refactor

- Fix protobuf warnings ([baff1c9](baff1c956b4ab84d7625b66cb57bd625ea13800a))
- Get rid of random_shuffle ([2ebc82b](2ebc82bfc36af5c18c076a1d485fc3b138c73e08))
- Reduce verbocity in examples ([fbe3c9c](fbe3c9c3444267ee56b5e0cfaf204f26f546fa33))
- Move IsVisible to sc2_unit_filters ([40ae46b](40ae46b27fb5ea25c22a76d89f95b4cbd70fd47f))
- Move other filters to sc2_unit_filets, #82 ([509786d](509786dbcd225437841957a9e7d9ba2e2b9492b1))
- Unify CI tasks, #93 ([2980fe2](2980fe2d117b12ad5917b02121da4763cb691eda))

### <!-- 4 -->👷 Build

- Check branch name instead of custom env... ([d803698](d80369888ba0b9559cc38856e5a36633ffb241a6))
- Fix typo in docs publishing script ([d93c43f](d93c43f23faa398d656a9ade0840fb0dca4ed6e7))
- Fix docs publishing ([2e9f0ae](2e9f0aeda9da737ed2b1c0551fdad91a8007d5cb))
- Make sc2renderer conditional, #90 ([cbc2a87](cbc2a87d41b7dcd9a7d9ddc0c9e04757f0f74387))
- Switch CI to Github Actions, #93 ([de3bf26](de3bf26839fe25bdd7dcd81d2df1b6308cb4776e))
- Generate docs using github actions, #93 ([caf956e](caf956e76642a93bf173d646c5b607e68dcc4ffe))
- Fix docs publishing after testing, #93 ([7ee508f](7ee508f12a8303f3152f70349c5320dd57fc045f))

### <!-- 5 -->📚 Documentation

- Added #include <sc2api/sc2_unit_filters.h> to docs/tutorial3.md ([3d3fcbb](3d3fcbbebffdfec590255bc62f5531d3a6904374)) by @Nickrader
- Link CommandCenter with cpp-sc2, #70 ([df5f943](df5f9434b2502b0078935bbfabf67079a70184d5))
- Link the Contributing guide ([0b2f642](0b2f64277e3cfede8f059703ce4c6564110a1f2e))
- Add link to blank bot ([2c792a5](2c792a5ca6e58c6e9659151fc62589c5acaea90f))
- Update the CONTRIBUTING guide ([ca237c4](ca237c48849ffe0b7cdfa1c0f924ff87d8eff3ad))
- Describe when it's better to use IsWorker ([4042ecb](4042ecbadd575e2bba8195484b837098058e7f62))
- Add info about linter ([9a45b28](9a45b288ee4e4becd6d6f3a7a6a16c7e21761609))
- Add code of conduct, #14 ([dcf43b3](dcf43b3c251a79850ac848dcafe19ea75276edbc))
- Simplify build instructions ([56fb22e](56fb22e1011d108803d39e7ca7422a6814b65c0e))
- Use GitHub Actions badge, #93 ([c295c56](c295c562ecdd3bbd773b53d7311116c6e34c3cf5))

### <!-- 7 -->🧪 Tests

- Switch Linux CI to Ubuntu 20.04 ([61071cc](61071cceeea89d26a46d5d0291d8fa64c4c56fec))
- Refine CI ([d340c98](d340c98722a679b6549cf000061c7961da0c6019))

### <!-- 9 -->💼 Other

- Test BuildBarracksTechLabDifferentPointE failed ([c0b9869](c0b9869dcaf2715c04eb563d3f11026b2fbf839d)) by @Nickrader


## 1.3.1 - 2020-06-10

[f21f6fa](f21f6fa2d2f9c5c085d022be678d19daebfecdec)...[57b6e05](57b6e05c7933d4e26a5bc0e02ea0e9bc107ffa57)

### <!-- 1 -->🐛 Bug Fixes

- Fix CI build could be not marked as failed ([ef2f0b9](ef2f0b94c27f8ce82ad106d6eab9ecb75c420e29))
- Fix links in README ([2ed52f2](2ed52f2beb388bc807914a283370b284e83b031d))

### <!-- 4 -->👷 Build

- Use xcode11.4 in CI ([dde3c34](dde3c343e6d8169473175e8e9fea22b67d05d507))
- Use all available CPUs in CI build, #65 ([84e23d3](84e23d3f67771cb723a5f16bdb80dba83933f4e6))
- Don't source scripts in CI ([84b79d9](84b79d984df20c42d9ecc11d61f0e05c60d1ba6b))
- Compile with clang on OS X ([3ee8a41](3ee8a4168593dbd3a5de378b2a81a8cba39caf33))
- Refine CI routine ([823d9fd](823d9fde3a4c91bad1f904e993a6cfd9819a2016))

### <!-- 5 -->📚 Documentation

- Improve build instructions, #65 ([8963c9c](8963c9c0bbb83ce07284a4733a18ca8d223421f8))
- Introduce CONTRIBUTING guide, #42 ([f1f3055](f1f305502af8b9390a29c843d0161b328b47fe2d))
- Add Patreon link, #66 ([186fa76](186fa760385c9ea272082c67eba0052fe5aa2b9c))
- Add GitHub issue template, #67 ([7d691de](7d691de71516d08d9357b627d42d3d09c3174145))

### <!-- 9 -->💼 Other

- Fix scripts style and shellcheck warnings ([afdfb36](afdfb368e82a780ae9b30692d4206daff440cd42))


## 1.3.0 - 2020-05-15

[1f69424](1f69424e69043f8b3fd101fa7853504795653aef)...[f21f6fa](f21f6fa2d2f9c5c085d022be678d19daebfecdec)

### <!-- 0 -->🚀 Features

- Show invisible units when observing replays ([985f1ae](985f1ae8df5afdc2501615d6be5ab2403e741eeb))
- Allow to set player name, #13 ([7ab6688](7ab668873746931a372aaae6ea45badde454502a))
- Allow to retrieve player names, #13 ([6487f61](6487f61f7e7a05addd94ed73ef72a706f6079add))
- Allow to set and retrieve AI build, #45 ([87d10ce](87d10ce8bcee08ef02cc5b5032afc79e8cb931b5))
- Allow to get count of larva, #44 ([e205164](e2051646cb0a9ed38cbac76ff5bf586a912f1a0b))
- Add some missing types to ABILITY_ID, RESEARCH_ID and UPGRADE_ID enums ([2b7d04e](2b7d04e2fd7646e2a7f340b1b5fae06a65c65a8a)) by @mboedigh
- Add use_generalized_ability option when retrieving abilities using GetAbilitiesForUnit/s ([cc3b534](cc3b53489e5fcd38809b0b83cc6377da40ae4a38)) by @mboedigh
- Upgraded type enums for 4.11.3 ([2ae5519](2ae5519f6fa3c0954cf0d3c0d9d6e92effb81a8f))
- Added legacy typeenums for compatibility ([f27c954](f27c954b87f331d117f19246568036c114d26576))
- Allow retrieving specific ability ids with GetAbilitiesFromUnit(s) ([c024e34](c024e3454efd62467b756e5736ded87f169fb870)) by @mboedigh
- Add mineral and geyser filters, #24 ([7500a6e](7500a6e90a639dd9bce59973f66d4fdb178aa559))
- Add unit upgrades level, #54 ([93dedc6](93dedc61f114fd88d8ebbbca0afb35679280443e))
- Enable display of 'ghost' buildings, #23 ([74f24e1](74f24e125b972b1ca834dfb75622876928849c36))
- Include the amount of health and shield damage in OnUnitDamaged events ([3bd0469](3bd046938ac3e510655fb26ca8816e6872f36d85)) by @mboedigh
- Sync IDs with the latest sc2 ([4c20614](4c206148a3ff22f46d215c9b9d1859f8e479e39c))

### <!-- 1 -->🐛 Bug Fixes

- Broken deployment of the API docs ([b682b3e](b682b3e702b11ad28b96210c4798c7cda1309a59))
- == and != operators in Point2D and Point3D should be const functions to implement equal_to interface ([13ebbdf](13ebbdf479df6158b12c4a338914d494e00d6767)) by @mboedigh
- Report error if API can't load replay info ([215a310](215a310e4ca9dd3c825bdf8b7b65528a9689f0d4))
- Skip replay in case of any loading errors ([cc937a7](cc937a78ec044eea1246728c572fbe54c2a7cf14))
- GetGameLoop() returns wrong number on restart ([e94baa2](e94baa24897b7035f906a6b39e9fea02b2be31b4))
- Simultaneous 'Created' and 'Completed' events ([5530467](553046759347651be5fc22a55f0993caa5daae13))
- GetFoodWorkers() should return uint32_t ([11b8860](11b886055b8fe7eb0cb409efc578a850c64e5ef0)) by @mboedigh
- Issue where OnUnitDamage event was issued multiple times ([5e3f3fd](5e3f3fdd9fa3ca77ebbe71b48f19c2062139c105)) by @mboedigh
- Unit filters always returned 'true' ([8731e75](8731e75f5c88190dcf6290b53520f3f2bb5dd3a9))

### <!-- 2 -->⚡ Performance

- Mark newly constructed buildings as idle ([d73f633](d73f633662f7afd0fd4926c8d82b473412f98ca7))

### <!-- 3 -->🚜 Refactor

- Move logic from .travis.yaml to scripts ([34da289](34da289a52764bb3d7f5bc2421a1ea4b63eea201))

### <!-- 4 -->👷 Build

- Improve compilation under VS 2019 ([bed887a](bed887a262d76b44f7351043b5a6f4f80754f1dd))
- Validate windows builds against VS2019 ([7e21c71](7e21c71d770ec25d195afbf4744343f1c39350bc))
- Don't try to publish docs in dev branch ([b88aef2](b88aef2a2b2e0ef1be14be71081e2db3ebd2e03c))

### <!-- 5 -->📚 Documentation

- Set Windows build recommendations to VS 2019 ([6971da0](6971da07c837954c84b94ac47a91fbf968dbe087))
- Provide better Windows build instructions ([2e0a4d4](2e0a4d445df6dc013d3035c18495e2910c2d62c6))

### <!-- 7 -->🧪 Tests

- Add shortcut for determining map center ([8c35bf2](8c35bf2de3e204cc07a7155c8b1420b3cefeac31))

### <!-- 9 -->💼 Other

- Correct style ([73dfa68](73dfa68b0eda767d1d83e3c2c07fc5628eb1481a))
- Correct indent ([b4e4e39](b4e4e39a60ad3bf632347d422bac2a50dc03926d))


## 1.2.0 - 2019-11-04

[b628ca9](b628ca955324a00cb18eeb7958dc08a35d1258bb)...[1f69424](1f69424e69043f8b3fd101fa7853504795653aef)

### <!-- 0 -->🚀 Features

- Support -d, --data_version parameter #20 ([d7d0168](d7d016865e70f1169ae3fa2e470ea87378a01e53))
- New coordinator setting allowing users to choose to reduce the number of generated actions ([37d1776](37d177682d5c3c980ed6a356f0a1830ffb4e7f89)) by @RaphaelRoyerRivard
- Support launch in full screen, #21 ([d610d2d](d610d2d27c0641517b8a69df06af26e6dcd37c7e))
- Use full screen for first player only, #21 ([9177574](9177574da7fd4ef8e62b3b9bfffc3107ab80f52f))
- Implement IsTownHall filter, #17 ([6f786a4](6f786a4c9064dc01e15c8c44928791a9af52d7b7))

### <!-- 1 -->🐛 Bug Fixes

- EXCLUDE of */build/* on travis excludes everything ([e17b553](e17b5539a0bf99c86a588f9c40761ac33002ca0b)) by @yanntm
- Fix compilation under VS2019 ([abd6bd7](abd6bd77b1497d6e26e88805fc0ca0728d5e2cf9))
- Always specify -displayMode value ([cf39856](cf398561020b1d329fc288c5d8fa8220230a73db))
- Correct player data fields return types, #16 ([cfed8b8](cfed8b8921c73c9a2fec980e0dea82f9281c00d4))
- Exit in child process instead of sleep, #22 ([9b10fc0](9b10fc0f21f3398848a152a2ed54b89538281438))

### <!-- 3 -->🚜 Refactor

- Discard these scripts replaced by code in the .travis file ([01e5d75](01e5d757c151a0e2986b477a054add0b7b214375)) by @yanntm
- Fix compilation warning in tests ([07f0dae](07f0dae0f6ab0a06fdc0c5f1a511aa81728743ed))
- Group unit filters in separate file, #19 ([6c87664](6c87664e6c7096c992a73c94c5caa1fc17a059e9))

### <!-- 4 -->👷 Build

- Updated travis build script + Doxygen generation and deployment ([41f9659](41f965983e288d9f9501dc42d65120d6d265eb77)) by @yanntm


## 1.1.0 - 2019-09-14

[d4cbc54](d4cbc54951a95849db0b37d4d00c24e278c7dbbb)...[b628ca9](b628ca955324a00cb18eeb7958dc08a35d1258bb)

### <!-- 0 -->🚀 Features

- Allow to change replay observing perspective ([8c3051e](8c3051e28e73afa054f6cfa3a2e120fb73120fac))
- Allow to retrieve cloaked enemy units ([789465d](789465dc646d9b02678a6bf5a5f8674586624a37))
- Expose shadows of moving burrowed units ([b1b7ed4](b1b7ed47aa638478ca76cf080311c3737babf3fa))

### <!-- 1 -->🐛 Bug Fixes

- Don't call TerminateProcess with zero pid ([a7c1a8c](a7c1a8ca5894f2d808e50c6df275949fab8f93a5))
- Avoid crash of replay observer on relaunch ([0f5b5fb](0f5b5fb282fb0b20c311b3b35f13b1cf3f6ab776))

### <!-- 3 -->🚜 Refactor

- Fix style ([71c785b](71c785b9eddb6060457b719c3484f86e26cb2920))
- Use pointer to pointer ([e366ba7](e366ba784aee803d5ef4bd0bb9e1c5a34084fd7e))
- Simplify IgnoreReplay ([8ef49bf](8ef49bf6e1fb1edbfee6ce60a29e592cf4db8c3e))

### <!-- 4 -->👷 Build

- Fix C4530 warnings generated by VS2017 ([a7a7ed6](a7a7ed6140d591d3129a468dadb7a8a761cc5736))

### <!-- 5 -->📚 Documentation

- Correct description of the Cloaked state ([a0520d3](a0520d3536285ab08f038fd3ca84cce4b504ac04))
- Correct commit hashes in changelog ([f501670](f5016703d6cb3da15fae9a8338d108fde0903936))


## 1.0.0 - 2019-08-28

### <!-- 5 -->📚 Documentation

- Correct README ([f7a2051](f7a205176f41d7bae27586d60502899907e9aa8b))
- Added missing link to tutorial ([a7c3372](a7c3372d1a14eba28816bdc6ab1bdcc760201dd7))
- Fix a typo ([2a33789](2a3378954490db81c334803e9e833d9b6b686f7e))
- Refine build instructions ([68a3643](68a3643faf7d1a2f6fd2133e470cdaea966f8d72))
- Correct link to github pages ([b4d3184](b4d3184d9b64ac209f7e6b5ab77e873505181fd3))
- Mention discord in README ([9755002](9755002c74da7f6f03cf0a5d4e3f758f62f37566))
- Add more platform-specific dependencies ([56c52af](56c52af33d29f347856a9bba7388cb4d377956a3))
- Add build instructions for nmake ([c131953](c1319539202267e9561cf8c8da6212374043fa6c))

### <!-- 7 -->🧪 Tests

- Fix TestUnitCommand ([4debe09](4debe09cfa25d27e1d0db3891c33bce0e1233569))

### <!-- 9 -->💼 Other

- Drop old civetweb submodule ([5243fe4](5243fe4e1b9fc1820572415ae1a899c564bf8711))
- Bring in new civetweb submodule ([1652187](16521872c5838e8007a03e7defa9c02ed8c5f7ae))
- Fix some compilation warnings ([a2c4501](a2c4501f5f6c7ef1ca566e8dbd21f1e6becf33a5))
- Extend DisplayType with Placeholder value ([dd73ec0](dd73ec0cfbe20c1b26b74b7081601fbd89a1cdb2))
- Fix chronoboost ([573960b](573960b404d9da46056d8ce0645c3d2dd311836c))
- Handle INVALID in all *ToName functions ([f0f0e9e](f0f0e9e9d342205dc896412b099ba6f901df4f9b))
- Add missing types to UnitTypeToName ([91311b3](91311b3610bf1456931d59b8c81906738d9d9e23))
- Fix MOVE and PATROL abilities ([bb8109a](bb8109af21a29b07baa0035eff09678fd5acc6eb))
- Fix type of minerals and vespene ([d2b29a9](d2b29a9588e4f15cf8dbf5ae1319e26d771390c2))
- Fix assertion in SampleImageData ([ba30bfa](ba30bfaf19d40a40649d2afba4e78e00c5c10971))
- Add cyclone lock on damage upgrade ([d67204a](d67204ad3d1b8ae71671bb26f3630fc7a6551bf2))
- Add 'rich' types of vespene extractors ([ab0f5bc](ab0f5bca9944371888a350ef143c8577532fe7a8))
- Extend Rect2DI functionality ([054a835](054a835eefa28d38b959734982163c48bcb9db8a))
- Add conversion of Point2D to Point2DI ([7791b6a](7791b6a907916a3fbd601ffdc9a7e670f183d5c6))
- Fix IsPlacable and IsPathable, #5 ([3b0100d](3b0100d9130cacd487eff7648b5060f796853850))
- Switch to the latest proto ([f3bd271](f3bd2713698bfc105629c504c3f2727ff99d9c98))
- Don't invert heights map coordinates... ([c2c38bf](c2c38bf69810c08e595080a7c7f9e3a00b1e4b1f))


<!-- generated by git-cliff -->
