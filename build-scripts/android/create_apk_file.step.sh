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

script_dir=`dirname $0`
. ./$script_dir/is_windows.sh
is_windows=$(is_windows)

pushd $pathToProjectDir

apiVersion=${4:-23}

droid_cmd_to_execute="android update project --path . --name NativeActivity --target android-$apiVersion"

if [ "$is_windows" == true ]; then
    cmd "/c ${droid_cmd_to_execute}"
else
    ${droid_cmd_to_execute}
fi

ant release
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

#ant has created an unsigned release apk so we must sign it (and verify the signing)
mv bin/NativeActivity-release-unsigned.apk bin/NativeActivityRelease.apk

jarsigner -verbose -sigalg SHA1withRSA -digestalg SHA1 -keystore $pathToReleaseKey -storepass 123456 bin/NativeActivityRelease.apk alias_name
verify="$(jarsigner -verify bin/NativeActivityRelease.apk)"

# Did the jar sign succeed?
resultcode=$?
echo
if [ $resultcode = 0 ] && [[ "$verify" == "jar verified."* ]] ; then
  echo "JAR SIGN SUCCEEDED"
else
  echo "JAR SIGN FAILED"
  exit $resultcode
fi
echo

rm -f bin/NativeActivity.apk
zipalign -v 4 bin/NativeActivityRelease.apk bin/NativeActivity.apk

popd
exit $resultcode
