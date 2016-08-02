#!/bin/sh

version=$1
buildUrl=$2
githubUrl=$3
pathToProjectDir=${4}
pathToReleaseKey=${5:-./release-key.keystore}
hockeyAppIdentifier=${6:-62a47548d62a577300d5949f3f858683}
shouldKeepLibs=${7:-1}
apiVersion=$8

#poke the version in the manifest
manifest=$pathToProjectDir/AndroidManifest.xml
cp $pathToProjectDir/AndroidManifest.xml $manifest.bak
python "./build-scripts/android/poke_manifest_version.py" $manifest 1 $version > $manifest.poked

if [ $? -ne 0 ] ; then
  cp $manifest.bak $manifest
  exit 1
fi

cp $manifest.poked $manifest

sh "./build-scripts/android/compile_android.step.sh" $pathToProjectDir $shouldKeepLibs

if [ $? -ne 0 ] ; then
  git checkout $file_to_poke
  exit 1
fi

git checkout $file_to_poke

sh "./build-scripts/android/create_apk_file.step.sh" $pathToProjectDir $pathToReleaseKey $apiVersion
if [ $? -ne 0 ] ; then
  exit 1
fi

sh "./build-scripts/android/commit_to_hockeyapp.step.sh" $pathToProjectDir $buildUrl $githubUrl $hockeyAppIdentifier
if [ $? -ne 0 ] ; then
  exit 1
fi

cp $manifest.bak $manifest
rm $manifest.xml.bak
rm $manifest.poked

echo
echo "BUILD SUCCEEDED"
echo
