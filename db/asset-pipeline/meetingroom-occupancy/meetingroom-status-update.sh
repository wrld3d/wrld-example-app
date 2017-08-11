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

regionCode=$3
if [ -z "$regionCode" ]; then
        echo
        echo "Error: regionCode must be provided"
        echo
        exit 1
fi

cd ${0%/*}/src

if [ ! -f ../generated/MeetingRoomPoiData.json ]; then
        echo
        echo "meetingroom-update.py must be run first"
        echo
        exit 1
fi

python meetingroom-status-update.py --poi_service_url $poiServiceURL --dev_auth_token $devAuthToken --region_code $regionCode