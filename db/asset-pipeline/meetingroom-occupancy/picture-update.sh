#!/bin/bash

poiServiceURLA=$1
if [ -z "$poiServiceURLA" ]; then
        echo
        echo "Error: poiServiceURLA must be provided"
        echo
        exit 1
fi

poiServiceURLB=$2
if [ -z "$poiServiceURLB" ]; then
        echo
        echo "Error: poiServiceURLB must be provided"
        echo
        exit 1
fi

soapServiceURL=$3
if [ -z "$soapServiceURL" ]; then
        echo
        echo "Error: soapServiceURL must be provided"
        echo
        exit 1
fi

devAuthToken=$4
if [ -z "$devAuthToken" ]; then
        echo
        echo "Error: devAuthToken must be provided"
        echo
        exit 1
fi

appSecret=$5
if [ -z "$appSecret" ]; then
        echo
        echo "Error: appSecret must be provided"
        echo
        exit 1
fi

publicAppId=$6
if [ -z "$publicAppId" ]; then
        echo
        echo "Error: publicAppId must be provided"
        echo
        exit 1
fi

privateAppId=$7
if [ -z "$privateAppId" ]; then
        echo
        echo "Error: privateAppId must be provided"
        echo
        exit 1
fi

regionCode=$8
if [ -z "$regionCode" ]; then
        echo
        echo "Error: regionCode must be provided"
        echo
        exit 1
fi

debugData=$9
if [ -z "$debugData" ]; then
        echo
        echo "Error: debugData must be provided"
        echo
        exit 1
fi

cdnBaseURL=${10}
if [ -z "$cdnBaseURL" ]; then
        echo
        echo "Error: cdnBaseURL must be provided"
        echo
        exit 1
fi

scpHost=${11}
if [ -z "$scpHost" ]; then
        echo
        echo "Error: scpHost must be provided"
        echo
        exit 1
fi

scpUsername=${12}
if [ -z "$scpUsername" ]; then
        echo
        echo "Error: scpUsername must be provided"
        echo
        exit 1
fi

scpDestPath=${13}
if [ -z "$scpDestPath" ]; then
        echo
        echo "Error: scpDestPath must be provided"
        echo
        exit 1
fi

scpPrivateKeyPath=${14}
if [ -z "$scpPrivateKeyPath" ]; then
        echo
        echo "Error: scpPrivateKeyPath must be provided"
        echo
        exit 1
fi

ssh -l swallowadmin -i ~/.ssh/id_rsa.content londwayfweb01 'ls /var/www/html/employees/' > pictures-ls

cd ${0%/*}/src

python picture-update.py --soap_service_wsdl_url $soapServiceURL --poi_service_a_base_path $poiServiceURLA --poi_service_b_base_path $poiServiceURLB --wrld_dev_auth_token $devAuthToken --hmac_secret $appSecret --public_app_id $publicAppId --private_app_id $privateAppId --region_code $regionCode --debug $debugData --cdn_base_url $cdnBaseURL --scp_host $scpHost --scp_username $scpUsername --scp_dest_path "$scpDestPath" --scp_private_key_path $scpPrivateKeyPath