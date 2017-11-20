#!/bin/bash

feedScript=$1
if [ -z "$feedScript" ]; then
        echo
        echo "Error: feedScript must be provided"
        echo
        exit 1
fi

poiServiceURLA=$2
if [ -z "$poiServiceURLA" ]; then
        echo
        echo "Error: poiServiceURLA must be provided"
        echo
        exit 1
fi

poiServiceURLB=$3
if [ -z "$poiServiceURLB" ]; then
        echo
        echo "Error: poiServiceURLB must be provided"
        echo
        exit 1
fi

soapServiceURL=$4
if [ -z "$soapServiceURL" ]; then
        echo
        echo "Error: soapServiceURL must be provided"
        echo
        exit 1
fi

devAuthToken=$5
if [ -z "$devAuthToken" ]; then
        echo
        echo "Error: devAuthToken must be provided"
        echo
        exit 1
fi

appSecret=$6
if [ -z "$appSecret" ]; then
        echo
        echo "Error: appSecret must be provided"
        echo
        exit 1
fi

publicAppId=$7
if [ -z "$publicAppId" ]; then
        echo
        echo "Error: publicAppId must be provided"
        echo
        exit 1
fi

privateAppId=$8
if [ -z "$privateAppId" ]; then
        echo
        echo "Error: privateAppId must be provided"
        echo
        exit 1
fi

regionCode=$9
if [ -z "$regionCode" ]; then
        echo
        echo "Error: regionCode must be provided"
        echo
        exit 1
fi

debugData=${10}
if [ -z "$debugData" ]; then
        echo
        echo "Error: debugData must be provided"
        echo
        exit 1
fi

cdnBaseURL=${11}
if [ -z "$cdnBaseURL" ]; then
        echo
        echo "Error: cdnBaseURL must be provided"
        echo
        exit 1
fi

cd ${0%/*}/src

python $feedScript --soap_service_wsdl_url $soapServiceURL --poi_service_a_base_path $poiServiceURLA --poi_service_b_base_path $poiServiceURLB --wrld_dev_auth_token $devAuthToken --hmac_secret $appSecret --public_app_id $publicAppId --private_app_id $privateAppId --region_code $regionCode --debug $debugData --cdn_base_url $cdnBaseURL