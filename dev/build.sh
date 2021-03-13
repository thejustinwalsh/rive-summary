#!/bin/bash

OPTION=$1

pushd $(dirname $0) &>/dev/null
./premake5 --file=../build/premake5.lua gmake2

if [ "$OPTION" = "release" ]; then
    make -C ../lib/rive-cpp/build config=release -j7
    make -C ../build config=release -j7
else
    make -C ../lib/rive-cpp/build -j7
    make -C ../build -j7
fi

popd &>/dev/null
