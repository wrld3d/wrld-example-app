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

pathToReleaseKey=$2

if [ -z "$pathToReleaseKey" ]; then
        echo
        echo "Error: pathToReleaseKey must be provided"
        echo
        exit 1
fi

versionCode=$3
if [ -z "$versionCode" ]; then
        echo
        echo "Error: versionCode must be provided"
        echo
        exit 1
fi

versionName=$4
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

apiVersion=${5:-23}

droid_cmd_to_execute="android update project --path . --name NativeActivity --target android-$apiVersion"

if [ "$is_windows" == true ]; then
    cmd "/c ${droid_cmd_to_execute}"
else
    ${droid_cmd_to_execute}
fi

./gradlew assembleRelease -PversionCode=$versionCode -PversionName=$versionName
resultcode=$?

# Output the result of the operation.
echo
if [ $resultcode = 0 ] ; then
  echo "CREATE APK FILE SUCCEEDED"
else
  echo "CREATE APK FILE FAILED"
  exit $resultcode
fi
echo

rm ./build.xml
rm ./proguard-project.txt

#gradle has created an unsigned release apk so we must sign it (and verify the signing)
mv build/outputs/apk/android-armv7a-release-unsigned.apk build/outputs/apk/NativeActivityRelease.apk

jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore $pathToReleaseKey -storepass 123456 build/outputs/apk/NativeActivityRelease.apk alias_name
verify="$(jarsigner -verify build/outputs/apk/NativeActivityRelease.apk)"

# Did the jar sign succeed?
resultcode=$?
echo
if [ $resultcode = 0 ] && [[ "$verify" == *"jar verified."* ]] ; then
  echo "JAR SIGN SUCCEEDED"
else
  echo "JAR SIGN FAILED"
  exit $resultcode
fi
echo

rm -f build/outputs/apk/NativeActivity.apk
zipalign -v 4 build/outputs/apk/NativeActivityRelease.apk build/outputs/apk/NativeActivity.apk

popd
exit $resultcode
