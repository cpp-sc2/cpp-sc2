#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2020 Alexander Kurbatov

if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then
  choco install visualstudio2019community
  choco install visualstudio2019-workload-nativedesktop
fi

