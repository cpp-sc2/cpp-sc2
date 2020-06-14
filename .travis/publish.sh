#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2019 Alexander Kurbatov

# Build documentation and copy it to website/ which is the folder
# we deploy to gh-pages

set -ev

if [[ "${TRAVIS_BRANCH}" == "master" && "${TRAVIS_OS_NAME}" == "linux" && "${BUILD_CONFIGURATION}" == "Debug" ]]; then
  mkdir -p docs/html
  doxygen > doxygen.log 2>&1
  cat doxygen.log
  mkdir website
  cp -r docs/html/* website/
fi
