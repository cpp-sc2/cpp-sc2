#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2019 Alexander Kurbatov

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    sudo add-apt-repository -y ppa:ubuntu-toolchain-r/test # For C++14
    sudo apt-get -qq update
fi
