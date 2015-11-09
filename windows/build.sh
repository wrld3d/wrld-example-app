#!/bin/sh

usage() { echo "Usage: $0 -p windows -k <APIKEY>"; echo "  -p -> platform, windows (required)"; echo "  -k -> the Eegeo API key to use for the app"; 1>&2; exit 1; }

projectPath=$(pwd)/./

while getopts "p:k:" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "windows" ]; then
               usage
            fi
            ;;
    	k)
            k=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ -z "${p}" ]; then
    usage
fi

if [ -z "${k}" ]; then
    usage
fi

sed -i "s/std::string\s*ApiKey\s*=\s*\"[^\"]*\"/std::string ApiKey = \"$k\"/g" src/ApiKey.h

if [ ! -f windows/nuget.exe ]; then
	curl -o windows/nuget.exe https://api.nuget.org/downloads/nuget.exe
fi
cmd //C windows\\build.bat
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE WINDOWS PROJECT SUCCEEDED"
else
  echo "COMPILE WINDOWS PROJECT FAILED"
fi

exit $resultcode
