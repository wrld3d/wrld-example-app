#!/bin/sh

usage() { echo "Usage: $0 -p android"; echo "  -p -> platform, ios or android (required)"; 1>&2; exit 1; }

projectPath=$(pwd)/./
ndkbuild_arguments=""

while getopts "p:c" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "android" ]; then
               usage
            fi
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

pushd app

gradle assembleRelease

resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE ANDROID PROJECT SUCCEEDED"
else
  echo "COMPILE ANDROID PROJECT FAILED"
fi

popd

exit $resultcode
