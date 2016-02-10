#!/bin/sh

echo
echo "Compile xcode project step..."
echo

targetName=$1
productName=$2
productVersion=$3
pathToProjectDir=$4

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

# Compile the xcode project.
(cd $pathToProjectDir && xcodebuild -target $targetName -configuration Release ONLY_ACTIVE_ARCH='NO' PRODUCT_NAME=$productName PRODUCT_VERSION=$productVersion)
resultcode=$?

# Output the result of the operation.
echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE XCODE PROJECT SUCCEEDED"
else
  echo "COMPILE XCODE PROJECT FAILED"
fi
echo

exit $resultcode
