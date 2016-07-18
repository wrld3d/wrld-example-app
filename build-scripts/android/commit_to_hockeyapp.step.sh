#!/bin/sh

pathToProjectDir=$1

if [ -z "$pathToProjectDir" ]; then
        echo
        echo "Error: pathToProjectDir must be provided"
        echo
        exit 1
fi

buildUrl=$2

if [ -z "$buildUrl" ]; then
        echo
        echo "Error: buildUrl must be provided"
        echo
        exit 1
fi

sourceControlUrl=$3

if [ -z "$sourceControlUrl" ]; then
        echo
        echo "Error: sourceControlUrl must be provided"
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

echo
echo "Commit .apk file to hockeyapp step..."
echo


# API_TOKEN, from https://rink.hockeyapp.net/manage/auth_tokens
apitoken='b93a76258d944864816b7f89a4bd83b6'

# Full path where the app file is located.
filepath=$pathToProjectDir/bin/NativeActivity.apk

script_dir=`dirname $0`
. ./$script_dir/is_windows.sh
is_windows=$(is_windows)


if [ "$is_windows" == true ]; then
	echo "Converting unix-style path to windows format."
	echo "Original: "$filepath
    # when running on windows, we need to translate the unix-style path to a windows path or curl will reject it.    		
	# Note: mingw actually does convert paths, but doesn't account for all formats (e.g. some/path)
	# http://www.mingw.org/wiki/Posix_path_conversion	
	
	# http://stackoverflow.com/a/21188136	
	get_abs_filename() {
		# $1 : relative filename
		echo "$(cd "$(dirname "$1")" && pwd)/$(basename "$1")"
	}

	# first, convert to a full unix-style path /c/some/path/dude.txt
	filepath=$(get_abs_filename $filepath)	
	
	# secondly, transform it into a c:\some\path\dude.txt
	# http://stackoverflow.com/a/13701495/83891
    filepath=$(echo $filepath | sed 's/^\///' | sed 's/\//\\/g' | sed 's/^./\0:/')
	echo "Modified: "$filepath
fi

# Release notes for the build.
notes="Build uploaded automatically from teamcity ($buildUrl) from commit: $sourceControlUrl"

# Path of the commit log.
commitlog=$pathToProjectDir/"commit_result.log"

# Execute the commit.
resultcode=$(curl --write-out %{http_code} --output "$commitlog" \
  -F status="2" \
  -F notify="1" \
  -F tags="engineering,qa" \
  -F notes="$notes" \
  -F notes_type="0" \
  -F ipa="@$filepath" \
  -F build_server_url="$buildUrl" \
  -F repository_url="$sourceControlUrl" \
  -H "X-HockeyAppToken: $apitoken" \
  https://rink.hockeyapp.net/api/2/apps/$hockeyAppIdentifier/app_versions/upload)

# Output the result of the operation.
echo
if [ $resultcode = 201 ] ; then
  echo "COMMIT APK FILE SUCCEEDED"
  echo
  exit 0
else
  echo "COMMIT APK FILE FAILED"
  echo
  exit 1
fi
