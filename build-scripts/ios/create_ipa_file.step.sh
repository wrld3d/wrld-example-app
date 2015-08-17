#!/bin/sh

echo
echo "Create .ipa file step..."
echo

appname=$1
pathToProjectDir=$2

if [ -z "$appname" ]; then
        echo
        echo "Error: appname must be provided"
        echo
        exit 1
fi

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

# Go to project path.
apppath=$pathToProjectDir"/build/Release-iphoneos/"
cd $apppath

# Folder name where the .app will be inserted.
foldername="Payload";
if [ -d $foldername ]
  then
    rm -R $foldername
  fi

outputname="Streaming_Test.ipa";

mkdir $foldername
cp -R -f $appname $foldername/$appname

# Zip the folder and rename the file created with the file output name.
zip -r $outputname $foldername
resultcode=$?

# Finally, delete the temporary folder previously created.
#rm -R $foldername

# Output the result of the operation.
echo
if [ $resultcode = 0 ] ; then
  echo "CREATE IPA FILE SUCCEEDED"
else
  echo "CREATE IPA FILE FAILED"
fi
echo

exit $resultcode
