#!/bin/sh

echo
echo "Commit .ipa file to hockeyapp step..."
echo

buildUrl=$1

if [ -z "$buildUrl" ]; then
        echo
        echo "Error: buildUrl must be provided"
        echo
        exit 1
fi

sourceControlUrl=$2

if [ -z "$sourceControlUrl" ]; then
        echo
        echo "Error: sourceControlUrl must be provided"
        echo
        exit 1
fi

pathToProjectDir=$3

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

hockeyAppIdentifier=$4

if [ -z "$hockeyAppIdentifier" ]; then
        echo
        echo "Error: hockeyAppIdentifier must be provided"
        echo
        exit 1
fi


# API_TOKEN, from https://rink.hockeyapp.net/manage/auth_tokens
apitoken='b93a76258d944864816b7f89a4bd83b6'

# Full path where the app file is located.
filepath=$pathToProjectDir"/build/Release-iphoneos/Streaming_Test.ipa"

# Release notes for the build.
notes="Build uploaded automatically from teamcity ($buildUrl) from commit: $sourceControlUrl"

# Path of the commit log.
commitlog=$pathToProjectDir/"commit_result.log"

# Execute the commit.
resultcode=$(curl --write-out %{http_code} --output "$commitlog" \
  -F status="2" \
  -F notify="0" \
  -F tags="engineering,qa" \
  -F notes="$notes" \
  -F notes_type="0" \
  -F ipa="@$filepath" \
  -F build_server_url="$buildUrl" \
  -F repository_url="$sourceControlUrl" \
  -H "X-HockeyAppToken: $apitoken" \
  https://rink.hockeyapp.net/api/2/apps/"$hockeyAppIdentifier"/app_versions/upload)

cat $commitlog

# Output the result of the operation.
#echo
if [ $resultcode = 201 ] ; then
  echo "COMMIT IPA FILE SUCCEEDED"
  echo
  exit 0
else
  echo "COMMIT IPA FILE FAILED"
  echo
  exit 1
fi
