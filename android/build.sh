#!/bin/sh

rm -rf "./libs"
rm -rf "./obj"
rm -rf "./bin"

sh "update.platform.sh"

# running on msys (basically the git provided shell we use on windows)
if [ "$OSTYPE" == "msys" ]; then
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


exit $resultcode
