#!/bin/sh

src_base_path=$1
s3cmd_access_key=$2
s3cmd_secret=$3

s3RootPath=s3://eegeo-static/swallow-pois

assets_relative_path="assets"
source_assets_dir=$src_base_path/$assets_relative_path

s3AssetsDestPath=$s3RootPath/

rm -f ./../../lib/s3ini_poked
cp ./../../lib/s3ini ./../../lib/s3ini_poked
sed -i.bak -e s/%S3_ACCESS_KEY%/$s3cmd_access_key/g -e s/%S3_SECRET_KEY%/$s3cmd_secret/g ./../../lib/s3ini_poked
rm -f ./../../lib/s3ini_poked.bak

echo 
echo "put assets from $source_assets_dir to $s3AssetsDestPath"
echo 

./../../lib/s3cmd-1.5.0-rc1/s3cmd --config ./../../lib/s3ini_poked put $source_assets_dir $s3AssetsDestPath --recursive --no-progress --acl-public --rexclude '\.git' --rexclude '\.DS_Store' --verbose 

#./../../lib/s3cmd-1.5.0-rc1/s3cmd --verbose --config ./../../lib/s3ini_poked info $s3DbDestPath

rm -f ./../../lib/s3ini_poked
