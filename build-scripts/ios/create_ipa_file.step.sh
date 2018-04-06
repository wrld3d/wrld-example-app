#!/bin/sh

echo
echo "Create .ipa file step..."
echo

appname=$1
pathToProjectDir=$2
archivePath=$3
ipaName=$4
provisioningProfile=$5

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

if [ -z "$archivePath" ]; then
        echo
        echo "Error: archivePath must be provided (eg. ./Appname.xcarchive)"
        echo
        exit 1
fi

if [ -z "$ipaName" ]; then
    echo
    echo "Error: ipaName must be provided (eg. Appname)"
    echo
exit 1
fi

if [ -z "$provisioningProfile" ]; then
    echo
    echo "Error: provisioningProfile must be provided and should match installed enterprise distribution provisioning Profile"
    echo
    exit 1
fi

# Delete old ipa if exists
if [ -e "$pathToProjectDir/$ipaName.ipa" ]; then
    echo "Removing existing ipa at: $pathToProjectDir/$ipaName.ipa"
    rm "$pathToProjectDir/$ipaName.ipa"

    if [ $? -ne 0 ]; then
        echo "Failed to remove existing IPA."
        exit 1
    fi
fi

# Export ipa re-signed with enterprise provisioningProfile
# TODO: This method is depricated - should use an exportOptionsPlist but currently that option doesn't work (see http://github.com/fastlane/gym/issues/89 for more info)
(cd $pathToProjectDir && xcodeBuild -exportArchive -exportFormat ipa -exportProvisioningProfile "$provisioningProfile" -archivePath "$archivePath" -exportPath "$ipaName")
if [ $? -ne 0 ]; then
    echo "Failed to export IPA."
    exit 1
fi

exit 0
