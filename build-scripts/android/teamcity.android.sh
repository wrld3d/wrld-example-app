#!/bin/sh

versionName=$1
buildUrl=$2
githubUrl=$3
pathToProjectDir=${4}
hockeyAppIdentifier=${5:-62a47548d62a577300d5949f3f858683}
environment=${6:staging}
config_password=$7

if [[ ( $environment != 'production' ) && ( $environment != 'staging' ) ]]; then
  echo "invalid environment '$environment'. Must be one of [staging|production]"
  exit 1
fi

sh build-scripts/encrypt_config.sh -p android -e $environment -j $config_password

sh "./build-scripts/android/create_apk_file_gradle.step.sh" $pathToProjectDir  1 $versionName 
if [ $? -ne 0 ] ; then
  exit 1
fi

sh "./build-scripts/android/commit_to_hockeyapp.step.sh" $pathToProjectDir $buildUrl $githubUrl $hockeyAppIdentifier
if [ $? -ne 0 ] ; then
  exit 1
fi

echo
echo "BUILD SUCCEEDED"
echo
