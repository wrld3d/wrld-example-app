#!/bin/sh

rm -rf ./Include
curl http://s3.amazonaws.com/eegeo-static/sdk.package.tar.gz > ./sdk.package.tar.gz
tar -zxvf ./sdk.package.tar.gz
rm -f ./sdk.package.tar.gz
value=`cat ./sdk.package/version.txt`
echo "Platform version --> $value"
mv ./sdk.package/ ./Include