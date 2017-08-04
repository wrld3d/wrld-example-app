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

cd ${0%/*}/src

python meetingroom-status-update.py --poi_service_url $poiServiceURL --dev_auth_token $devAuthToken