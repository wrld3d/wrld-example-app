#!/bin/sh

pushd windows/Installer

echo
echo Creating windows installer
echo

applicationOutputDirectory=../ExampleApp/ExampleAppWPF/bin/Release
version=$1

if [ -z "$version" ]; then
        echo
        echo "Error: version must be provided (i.e. create.setup.sh 1.0.15)"
        echo
        exit 1
fi

# Check if exists and if it doesn't bail and inform them to build project first.
if [ ! -d "$applicationOutputDirectory" -o ! -e "$applicationOutputDirectory/ProjectSwallow.exe" ]; then
	echo "ExampleApp has not been built. Please ensure a Release build of ExampleAppWPF has been built first"
	exit 1
fi

rm -rd "./payload"
rm -rd "./deploy"
mkdir payload
cp -R $applicationOutputDirectory/*.dll "./payload" 
cp -R $applicationOutputDirectory/*.exe "./payload"
mkdir payload/Resources
cp -R "$applicationOutputDirectory/Resources" "./payload"

echo "Data copied from project output"
echo "Creating Basic Installer..."

candle.exe Product.wxs -o ./deploy/Product.wixobj -dVersion="$version"

if [ $? = 0 ] ; then
  echo "Installer compilation step success"
else
  echo "Installer compilation step FAILED!"
  exit 1
fi

light.exe ./deploy/Product.wixobj -o ./deploy/Swallow.msi

if [ $? = 0 ] ; then
  echo "Installer linker step success"
else
  echo "Installer linker step FAILED!"
  exit 1
fi

echo
echo "Basic installer created"
echo "Creating bundle..."
echo

candle.exe -ext WixBalExtension -ext WixUtilExtension -ext WixNetFxExtension Bundle.wxs -o ./deploy/Bundle.wixobj -dSwallowMsiLocation="./deploy/Swallow.msi" -dVersion="$version"

if [ $? = 0 ] ; then
  echo "Main Bundle compilation step success"
else
  echo "Main Bundle compilation step FAILED!"
  exit 1
fi

light.exe -ext WixBalExtension -ext WixUtilExtension -ext WixNetFxExtension ./deploy/Bundle.wixobj -o "./deploy/Swallow Installer.exe"

if [ $? = 0 ] ; then
  echo "Main Bundle linker step success"
else
  echo "Main Bundle linker step FAILED!"
  exit 1
fi

echo
echo "Bundle installer for V$version created!"
echo
popd

exit 0

