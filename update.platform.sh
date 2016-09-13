#!/bin/bash

usage() { echo "Usage: $0 -p android|ios|windows [-c]"; echo "  -p -> platform, ios, android or windows (required)"; 1>&2; exit 1; }

baseUrl="http://s3.amazonaws.com/eegeo-static/"
srcPackageName="INVALID"
destPackageName="./sdk.package.tar.gz"
includeDestination="INVALID"
sdkDestination="INVALID"

while getopts "p:" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "ios" ]; then
               if [ "$p" != "android" ]; then
	          if [ "$p" != "windows" ]; then
                     usage
		  fi
               fi
            fi
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
   includeDestination="./ios/Include/eegeo"
   sdkDestination="sdk.package"
elif [ "$p" == "android" ]; then
   srcPackageName="sdk.package.android"
   includeDestination="./android/libs/eegeo"
   sdkDestination="sdk.package.android"
elif [ "$p" == "windows" ]; then
   srcPackageName="sdk.package.windows"
   includeDestination="./windows/libs/eegeo"
   sdkDestination="sdk.package.windows"

fi

if [ "$p" == "windows" ]; then
   srcPackageName="$srcPackageName.tar.gz"
else
   srcPackageName="$srcPackageName.cpp11.tar.gz"
fi

echo "Updating $p platform..."
rm -f ./$destPackageName
rm -rf $includeDestination
curl $baseUrl$srcPackageName > ./$destPackageName

statuscode=$?
if [ $statuscode -ne 0 ] ; then
    echo "Failed to download sdk package ${baseUrl}${srcPackageName}" >&2
    exit $statuscode
fi    

if [ ! -d `dirname "$includeDestination"` ]; then
    mkdir -p `dirname "$includeDestination"`
fi

tar -zxvf $destPackageName

if [ $? -ne 0 ] ; then
    echo "Failed to unzip sdk package ${destPackageName}"
    exit 1    
fi

rm -f ./$destPackageName
platformVersion=`cat ./$sdkDestination/version.txt`
echo "Platform version --> $platformVersion"
echo mv ./$sdkDestination $includeDestination
mv ./$sdkDestination $includeDestination
