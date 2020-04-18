#!/bin/bash
#
# The MIT License (MIT)
#
# Copyright (c) 2017-2019 Alexander Kurbatov

# Build documentation and copy it to website/ which is the folder
# we deploy to gh-pages
if [[ "$PUBLISH_DOCS" == "yes" && "$TRAVIS_OS_NAME" == "linux" && $BUILD_CONFIGURATION = "Debug" ]]; then
  mkdir -p docs/html
  doxygen 2>&1 > doxygen.log || cat doxygen.log
  mkdir website
  cp -r docs/html/* website/
fi
