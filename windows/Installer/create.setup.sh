#!/bin/sh

pushd windows/Installer

echo
echo Creating windows installer
echo

applicationOutputDirectory=../ExampleApp/ExampleAppWPF/bin/Release
version=$1
certPassword=$2
timestampUrl=$3

if [ -z "$version" ]; then
        echo
        echo "Error: version must be provided (i.e. create.setup.sh 1.0.15)"
        echo
        exit 1
fi

if [ -z "$certPassword" ]; then
        echo
        echo "Error: Certificate password for signing the installer must be provided"
        echo
        exit 1
fi


if [ -z "$timestampUrl" ]; then
        echo
        echo "Error: Timestamp url must be provided for signing the installer (eg. http://timestamp.digicert.com)"
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

candle.exe Product.wxs -o ./deploy/Product.wixobj -dVersion="$version" -ext WixUtilExtension 

if [ $? = 0 ] ; then
  echo "Installer compilation step success"
else
  echo "Installer compilation step FAILED!"
  exit 1
fi

light.exe ./deploy/Product.wixobj -o ./deploy/Swallow.msi -ext WixUtilExtension 

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

echo "Signing installer..."
echo "Extracting bootstrapper..."
echo
rm ./deploy/engine.exe
insignia -ib "./deploy/Swallow Installer.exe" -o "./deploy/engine.exe"

if [ $? = 0 ] ; then
  echo "Bootstrapper extracted!"
else
  echo "Bootstrapper extraction failed!"
  exit 1
fi

echo
echo "Signing Bootstrapper"
echo

signToolPath=/c/Program\ Files\ \(x86\)/Windows\ Kits/8.1/bin/x86/SignTool.exe

"$signToolPath" sign -f ../Certificates/certificate.pfx -p $certPassword -t $timestampUrl deploy/engine.exe

if [ $? = 0 ] ; then
  echo "Bootstrapper Signing success!"
else
  echo "Bootstrapper Signing failed!"
  exit 1
fi

echo
echo "Reattach Bootstrapper"
echo
insignia -ab "./deploy/engine.exe" "./deploy/Swallow Installer.exe" -o "./deploy/Swallow Installer.exe"

if [ $? = 0 ] ; then
  echo "Bootstrapper Reattach success!"
else
  echo "Bootstrapper Reattach failed!"
  exit 1
fi

echo
echo "Sign package"
echo

"$signToolPath" sign -f ../Certificates/certificate.pfx -p $certPassword -t $timestampUrl "./deploy/Swallow Installer.exe"

if [ $? = 0 ] ; then
  echo "Package sign success!"
else
  echo "Package sign failed!"
  exit 1
fi

popd

exit 0

