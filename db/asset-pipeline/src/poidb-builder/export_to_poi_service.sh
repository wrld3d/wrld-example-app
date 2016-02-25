#!/bin/sh

srcXlsFilename=$1
if [ -z "$srcXlsFilename" ]; then
        echo
        echo "Error: srcXlsFilename must be provided"
        echo
        exit 1
fi

destPoiServiceUrl=$2
if [ -z "$destPoiServiceUrl" ]; then
        echo
        echo "Error: destPoiServiceUrl must be provided"
        echo
        exit 1
fi

eegeoDevAuthToken=$3
if [ -z "$eegeoDevAuthToken" ]; then
        echo
        echo "Error: eegeoDevAuthToken must be provided"
        echo
        exit 1
fi

build_number=$4
if [ -z "$build_number" ]; then
        echo
        echo "Error: build_number must be provided"
        echo
        exit 1
fi

python export_to_poi_service.py -i $srcXlsFilename -u $destPoiServiceUrl -k $eegeoDevAuthToken -v -c http://cdn1.eegeo.com/swallow-pois/assets/v$build_number
returnCode=$?
if [ $returnCode -ne 0 ]; then
	echo
	echo "Error: export_to_poi_service.py failed"
	echo
	exit 1
fi