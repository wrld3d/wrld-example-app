#!/bin/sh

echo
echo "Compile android project step..."
echo

pathToProjectDir=$1
shouldKeepLibs=$2

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

if [ -z "$shouldKeepLibs" ]; then
        echo
        echo "Error: shouldKeepLibs must be provided"
        echo
        exit 1
fi

script_dir=`dirname $0`
. ./$script_dir/is_windows.sh
is_windows=$(is_windows)

pushd $pathToProjectDir

if [ shouldKeepLibs == 0 ] ; then
	rm -rf "./libs"
fi

rm -rf "./obj"
rm -rf "./bin"

if [ "$is_windows" == true ]; then
    cmd "/C ndk-build.cmd"
else
    ndk-build
fi 

resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE ANDROID PROJECT SUCCEEDED"
else
  echo "COMPILE ANDROID PROJECT FAILED"
fi

popd
exit $resultcode
