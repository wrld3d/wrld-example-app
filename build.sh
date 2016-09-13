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
    echo "Building iOS examples..."
    rm -rf "./ios/Include/eegeo"
    rm -rf "./ios/build"
    ./update.platform.sh $allArguments

    if [ $? -ne 0 ] ; then
        exit $?
    fi    
    
    pushd ios
    ./build.sh $allArguments
    resultcode=$?
    popd
elif [ $p == "android" ]; then
    echo "Building Android examples..."
    rm -rf "./android/libs/eegeo"
    rm -rf "./android/obj"
    rm -rf "./android/bin"
    ./update.platform.sh $allArguments

    if [ $? -ne 0 ] ; then
        exit $?
    fi
    
    pushd android
    ./build.sh $allArguments
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
