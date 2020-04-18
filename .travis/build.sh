#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2019 Alexander Kurbatov

mkdir build && cd build

if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then
  cmake ../ -G "Visual Studio 16 2019"
  cmake --build . --config ${BUILD_CONFIGURATION}
else
  cmake -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION ../
  VERBOSE=1 cmake --build .
fi

cd ../
