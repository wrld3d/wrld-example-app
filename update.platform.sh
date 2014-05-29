#!/bin/sh

platformVersion=$1

if [ -z "$platformVersion" ]; then
    echo "\nError: Target platform must be provided.\n\nValid platform choices:\n\t- ios\n\t- android\n"
    exit 1
fi

if [ $platformVersion == ios ]; then
    echo "Updating iOS platform..."
    rm -rf ./ios/Include
	curl http://s3.amazonaws.com/eegeo-static/sdk.package.tar.gz > ./sdk.package.ios.tar.gz
	tar -zxvf ./sdk.package.ios.tar.gz
	rm -f ./sdk.package.ios.tar.gz
	value=`cat ./sdk.package/version.txt`
	echo "Platform version --> $value"
	mv ./sdk.package/ ./ios/Include
elif [ $platformVersion == android ]; then
    echo "Updating Android platform..."
    rm -rf ./android/libs
	curl http://s3.amazonaws.com/eegeo-static/sdk.package.android.tar.gz > ./sdk.package.android.tar.gz
	tar -zxvf ./sdk.package.android.tar.gz
	rm -f ./sdk.package.android.tar.gz
	value=`cat ./sdk.package.android/version.txt`
	echo "Platform version --> $value"
	mv ./sdk.package.android/ ./android/libs
else
    echo "Error: Target platform must be 'ios' or 'android'"
    exit 1
fi