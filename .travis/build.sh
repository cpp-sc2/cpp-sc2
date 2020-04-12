#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2019 Alexander Kurbatov

echo "Configuring for ${BUILD_CONFIGURATION}"

if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then
  export VS160COMNTOOLS="/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/Tools"

  cmake ../ -G "Visual Studio 16 2019"
  cmake --build . --config ${BUILD_CONFIGURATION}
else
  cmake -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION ../
  VERBOSE=1 cmake --build .
fi
