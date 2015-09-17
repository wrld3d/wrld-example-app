#!/bin/sh

srcXlsFilename=$1
if [ -z "$srcXlsFilename" ]; then
        echo
        echo "Error: srcXlsFilename must be provided"
        echo
        exit 1
fi

destDbFilename=$2
if [ -z "$destDbFilename" ]; then
        echo
        echo "Error: destDbFilename must be provided"
        echo
        exit 1
fi

build_number=$3
if [ -z "$build_number" ]; then
        echo
        echo "Error: destAssetsRelativePath must be provided"
        echo
        exit 1
fi


destAssetsRelativePath="$(printf "assets/v%d" $build_number)"

python build_poi_db.py -i $srcXlsFilename -o $destDbFilename -a $destAssetsRelativePath -v
returnCode=$?
if [ $returnCode -ne 0 ]; then
	echo
	echo "Error: build_poi_db.py failed"
	echo
	exit 1
fi