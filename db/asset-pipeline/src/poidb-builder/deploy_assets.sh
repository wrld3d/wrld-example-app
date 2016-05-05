#!/bin/sh

src_base_path=$1
s3cmd_access_key=$2
s3cmd_secret=$3

usage_example="usage format: deploy_assets.sh src_base_path s3cmd_access_key s3cmd_secret"
usage_example+="\nusage example: deploy_assets.sh . MY_S3_KEY MY_S3_SECRET"

if [ -z "$src_base_path" ]; then
  echo
  echo "Error: src_base_path must be provided"
  echo $usage_example
  exit 1
fi

if [ -z "$s3cmd_access_key" ]; then
  echo
  echo "Error: s3cmd_access_key must be provided"
  echo $usage_example
  exit 1
fi

if [ -z "$s3cmd_secret" ]; then
  echo 
  echo "Error: s3cmd_secret must be provided"
  echo $usage_example
  exit 1
fi

source_assets_dir="${src_base_path}/assets/"
s3_asset_dest_path="s3://ldc-assets/assets/"

echo 
echo "put assets from $source_assets_dir to $s3_asset_dest_path"
echo 

AWS_ACCESS_KEY_ID=$s3cmd_access_key; export AWS_ACCESS_KEY_ID
AWS_SECRET_ACCESS_KEY=$s3cmd_secret; export AWS_SECRET_ACCESS_KEY
AWS_DEFAULT_REGION=us-east-1; export AWS_DEFAULT_REGION

aws s3 cp ${source_assets_dir} ${s3_asset_dest_path} \
	--recursive \
	--exclude "*.xls" \
	--exclude "*.DS_Store" \
	--exclude "*.git" 

if [ $? -ne 0 ]; then
  echo "Failed to upload ${source_assets_dir} to ${s3_asset_dest_path}"
  exit 1
fi

echo "Successfully uploaded ${source_assets_dir} to ${s3_asset_dest_path}"
