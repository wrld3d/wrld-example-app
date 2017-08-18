#!/bin/bash

poiServiceURL=$1
if [ -z "$poiServiceURL" ]; then
        echo
        echo "Error: poiServiceURL must be provided"
        echo
        exit 1
fi

devAuthToken=$2
if [ -z "$devAuthToken" ]; then
        echo
        echo "Error: devAuthToken must be provided"
        echo
        exit 1
fi

appSecret=$3
if [ -z "$appSecret" ]; then
        echo
        echo "Error: appSecret must be provided"
        echo
        exit 1
fi

appId=$4
if [ -z "$appId" ]; then
        echo
        echo "Error: appId must be provided"
        echo
        exit 1
fi

regionCode=$5
if [ -z "$regionCode" ]; then
        echo
        echo "Error: regionCode must be provided"
        echo
        exit 1
fi

debugData=$6
if [ -z "$debugData" ]; then
        echo
        echo "Error: debugData must be provided"
        echo
        exit 1
fi

cdnBaseURL=$7
if [ -z "$cdnBaseURL" ]; then
        echo
        echo "Error: cdnBaseURL must be provided"
        echo
        exit 1
fi

cd ${0%/*}/src

python meetingroom-update.py --poi_service_url $poiServiceURL --dev_auth_token $devAuthToken --app_secret $appSecret --app_id $appId --region_code $regionCode --debug_data $debugData --cdn_base_url $cdnBaseURL

./../meetingroom-status-update.sh $poiServiceURL $devAuthToken $appSecret $appId $regionCode $debugData