#!/bin/sh

echo
echo "Create .apk file step..."
echo

pathToProjectDir=$1

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

versionCode=$2
if [ -z "$versionCode" ]; then
        echo
        echo "Error: versionCode must be provided"
        echo
        exit 1
fi

versionName=$3
if [ -z "$versionName" ]; then
        echo
        echo "Error: versionName must be provided"
        echo
        exit 1
fi

script_dir=`dirname $0`
. ./$script_dir/is_windows.sh
is_windows=$(is_windows)

pushd $pathToProjectDir

./gradlew assembleRelease -PversionCode=$versionCode -PversionName=$versionName 
resultcode=$?

# Output the result of the operation.
echo
if [ $resultcode = 0 ] ; then
  echo "assembleRelease SUCCEEDED"
else
  echo "assembleRelease FAILED"
  exit $resultcode
fi
echo

mv build/outputs/apk/android-armv7a-release.apk build/outputs/apk/NativeActivity.apk

popd
exit $resultcode
