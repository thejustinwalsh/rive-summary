#!/bin/bash

PREMAKE="premake-5.0.0-alpha15-linux.tar.gz"

pushd $(dirname $0) &>/dev/null
if [ -f ./premake5 ]; then
    curl -L https://github.com/premake/premake-core/releases/download/v5.0.0-alpha15/premake-5.0.0-alpha15-macosx.tar.gz --output "$PREMAKE" --silent
    tar -xvf "$PREMAKE"
    rm "$PREMAKE"
fi
popd &>/dev/null
