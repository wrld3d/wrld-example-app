#!/bin/bash

usage() { echo "Usage: $0 -p android|ios [-c]"; echo "  -p -> platform, ios or android (required)"; echo "  -c -> cpp11 support"; 1>&2; exit 1; }

baseUrl="http://s3.amazonaws.com/eegeo-static/"
srcPackageName="INVALID"
destPackageName="./sdk.package.tar.gz"
includeDestination="INVALID"
sdkDestination="INVALID"

while getopts "p:c" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "ios" ]; then
               if [ "$p" != "android" ]; then
                 usage
               fi
            fi
            ;;
        c)
            c="cpp11"
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${p}" ]; then
    usage
fi

if [ "$p" == "ios" ]; then
   srcPackageName="sdk.package.ios"
   includeDestination="./ios/Include"
   sdkDestination="sdk.package"
elif [ "$p" == "android" ]; then
   srcPackageName="sdk.package.android"
   includeDestination="./android/libs"
   sdkDestination="sdk.package.android"
fi

if [ "$c" == "cpp11" ]; then
   srcPackageName="$srcPackageName.cpp11.tar.gz"
else
   srcPackageName="$srcPackageName.tar.gz"
fi

echo "Updating $p platform..."
rm -rf $includeDestination
curl $baseUrl$srcPackageName > ./$destPackageName
tar -zxvf $destPackageName
rm -f ./$destPackageName
platformVersion=`cat ./$sdkDestination/version.txt`
echo "Platform version --> $platformVersion"
mv ./$sdkDestination $includeDestination
