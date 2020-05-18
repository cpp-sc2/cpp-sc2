#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2020 Alexander Kurbatov

set -ev

if [[ "${TRAVIS_OS_NAME}" == "windows" ]]; then
  choco install visualstudio2019community
  choco install visualstudio2019-workload-nativedesktop
elif [[ "${TRAVIS_OS_NAME}" == "linux" ]]; then
  sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test
  sudo apt-get -qq update

  sudo apt-get install -y doxygen
fi

