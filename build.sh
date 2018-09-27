#!/bin/sh

allArguments=$@

usage() { echo "Usage: $0 -p android|ios"; echo "  -p -> platform, ios or android (required)"; 1>&2; exit 1; }

while getopts "p:" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "ios" ]; then
               if [ "$p" != "android" ]; then
                 usage
               fi
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

if [ $p == "ios" ]; then
    echo "Building iOS example..."
    ./update.platform.sh $allArguments

    if [ $? -ne 0 ] ; then
        exit $?
    fi    
    
    pushd ios
    ./build.sh --clean --simulator
    resultcode=$?
    popd
elif [ $p == "android" ]; then
    echo "Building Android example..."
    ./update.platform.sh $allArguments

    if [ $? -ne 0 ] ; then
        exit $?
    fi
    
    pushd android
    ./build.sh
    resultcode=$?
    popd
fi

if [ $resultcode = 0 ] ; then
  echo "BUILD SUCCEEDED"
  exit 
else
  echo "BUILD FAILED"
fi

exit $resultcode
