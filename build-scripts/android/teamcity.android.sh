#!/bin/sh

versionCode=$1
versionName=$2
buildUrl=$3
githubUrl=$4
pathToProjectDir=${5}
hockeyAppIdentifier=${6:-62a47548d62a577300d5949f3f858683}
environment=${7:staging}
config_password=$8

if [[ ( $environment != 'staging' ) && ( $environment != 'production' ) && ( $environment != 'release' ) ]]; then
  echo "invalid environment '$environment'. Must be one of [staging|production|release]"
  exit 1
fi

sh build-scripts/encrypt_config.sh -p android -e $environment -j $config_password

sh "./build-scripts/android/create_apk_file_gradle.step.sh" $pathToProjectDir  $versionCode $versionName 
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
