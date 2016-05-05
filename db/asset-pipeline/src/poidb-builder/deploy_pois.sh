#!/bin/sh

function check_arg() {
  arg_value_as_string=$1
  arg_name=$2
 
  if [ -z "${arg_value_as_string}" ]; then
    echo "Error: ${arg_name} must be provided"
    echo 
    echo "Usage format: ./deploy_pois.sh src_xls_filename poi_service_url eegeo_dev_auth_token cdn_url s3_access_key s3_access_secret build_number"
    echo "Usage example: ./deploy_pois.sh assets/ldc-pois.xls https://poi.eegeo.com/v1/poisets/20 DH1l2F4WyqXxFwhF http://cdn3.eegeo.com MY_S3_KEY MY_S3_SECRET 1"
    exit 1
  fi
}

src_xls_filename=$1 
poi_service_url=$2 
eegeo_dev_auth_token=$3 
cdn_url=$4 
s3_access_key=$5 
s3_access_secret=$6 
build_number=$7

check_arg "${src_xls_filename}" "src_xls_filename"
check_arg "${poi_service_url}" "poi_service_url"
check_arg "${eegeo_dev_auth_token}" "eegeo_dev_auth_token"
check_arg "${cdn_url}" "cdn_url"
check_arg "${s3_access_key}" "s3_access_key"
check_arg "${s3_access_secret}" "s3_access_secret"
check_arg "${build_number}" "build_number"

asset_build_dir=./build

# build poi db (mostly a redundant step, but contains image conditioning functionality)
./build_poi_db.sh $src_xls_filename $asset_build_dir/poidb.db $build_number

if [ $? -ne 0 ]; then
  echo "Failed to build poi db"
  exit 1
fi

# upload image assets to s3 bucket so that the image urls in the pois are valid
./deploy_assets.sh $asset_build_dir $s3_access_key $s3_access_secret

if [ $? -ne 0 ]; then
  echo "Failed to upload assets to s3"
  exit 1
fi

# export xls sheet pois to eegeo poi service
python export_to_poi_service.py -i $src_xls_filename \
	-u $poi_service_url \
	-k $eegeo_dev_auth_token \
	-c "${cdn_url}/assets/v${build_number}" \
	-v

if [ $? -ne 0 ]; then
  echo "Failed to export to poi service"
  exit 1
fi

echo "Successfully build assets and deployed to poi service"
