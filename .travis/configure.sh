#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2019 Alexander Kurbato

# On Windows, configures path to VS2019 to give cmake a hint where to search it.
# On Linux, configures to use recent C++ compiler + linker instead of default.

echo "Configuring for ${BUILD_CONFIGURATION}"

if [[ "$TRAVIS_OS_NAME" == "windows" ]]; then
  export VS160COMNTOOLS="/c/Program Files (x86)/Microsoft Visual Studio/2019/Community/Common7/Tools"
elif [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
  export GCCVER='9'
  export CXX_COMPILER=g++-${GCCVER} C_COMPILER=gcc-${GCCVER}
  export AR=gcc-ar-${GCCVER} RANLIB=gcc-ranlib-${GCCVER} NM=gcc-nm-${GCCVER}
  export CC=${C_COMPILER} CXX=${CXX_COMPILER}
fi
