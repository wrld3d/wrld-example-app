#!/bin/bash

inputXlsPath=$1
if [ -z "$inputXlsPath" ]; then
        echo
        echo "Error: inputXlsPath must be provided"
        echo
        exit 1
fi

cd ${0%/*}/src

python meetingroom-mapping-update.py --input_xls_path $inputXlsPath