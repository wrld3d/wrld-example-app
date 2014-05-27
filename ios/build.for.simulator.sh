#!/bin/sh

sh "update.platform.sh ios"

projectpath=$(pwd)/./
targetName="ExampleApp"

(cd $projectpath && xcodebuild -target $targetName -arch "i386" -sdk "iphonesimulator")
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE XCODE PROJECT SUCCEEDED"
else
  echo "COMPILE XCODE PROJECT FAILED"
fi
echo

exit $resultcode

exit 0
