#!/bin/sh

echo
echo "Compile xcode project step..."
echo

targetName=$1
productName=$2
productVersion=$3
pathToProjectDir=$4
archivePath=$5


if [ -z "$targetName" ]; then
        echo
        echo "Error: targetName must be provided"
        echo
        exit 1
fi

if [ -z "$productName" ]; then
        echo
        echo "Error: productName must be provided"
        echo
        exit 1
fi

if [ -z "$productVersion" ]; then
        echo
        echo "Error: productVersion must be provided"
        echo
        exit 1
fi

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

if [ -z "$archivePath" ]; then
        echo
        echo "Error: archivePath must be provided (eg. ./Appname.xcarchive)"
        echo
exit 1
fi

# Manually inject schemes as xcodebuild archive needs them and cmake doesn't generate them
currentuser="$(whoami)"
schemeLocation=$pathToProjectDir/$targetName.xcodeproj/xcuserdata/$currentuser.xcuserdatad/xcschemes/
mkdir -p $schemeLocation
cp -R ./build-scripts/ios/schemes/. $schemeLocation
echo
if [ $? = 0 ] ; then
  echo "Successful injection of schemes into project at $pathToProjectDir/$targetName.xcodeproj"
else
  echo "Failed to inject schemes to $pathToProjectDir/$targetName.xcodeproj"
  exit $?
fi

# Archive the xcode project.
(cd $pathToProjectDir && xcodebuild archive -target $targetName -scheme "$targetName" -configuration Release -archivePath "$archivePath"  ONLY_ACTIVE_ARCH='NO' PRODUCT_NAME="$productName" PRODUCT_VERSION="$productVersion" CODE_SIGN_IDENTITY="iPhone Distribution: eeGeo Ltd")
resultcode=$?

# Output the result of the operation.
echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE XCODE PROJECT SUCCEEDED"
else
  echo "COMPILE XCODE PROJECT FAILED"
  exit $resultcode
fi
echo

exit $resultcode
