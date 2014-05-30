#!/bin/sh

platformVersion=$1

if [ -z "$platformVersion" ]; then
        echo "\nError: Target platform must be provided.\n\nValid platform choices:\n\t- ios\n\t- android\n"
        exit 1
fi

if [ $platformVersion == ios ]; then
    echo "Building iOS examples..."
    rm -rf "./ios/Include"
    rm -rf "./ios/build"
    ./update.platform.sh ios
    pushd ios
    ./build.sh
    if [ $? = 1 ] ; then
        popd
        exit 1
    fi
    popd
elif [ $platformVersion == android ]; then
    echo "Building Android examples..."
    rm -rf "./android/libs"
    rm -rf "./android/obj"
    rm -rf "./android/bin"
    ./update.platform.sh android
    pushd android
    ./build.sh
    if [ $? = 1 ] ; then
        popd
        exit 1
    fi
    popd
else
    echo "Error: Build platform must be 'ios' or 'android'"
    exit 1
fi