#!/bin/sh

allArguments=$@

usage() { echo "Usage: $0 -p android|ios";
    echo "  -p -> platform, ios or android (required)";
    echo "  -e -> environment for deployment (staging or production)"
    echo "  -j -> password used to derive configuration file encryption key";
    1>&2;
    exit 1;
}

while getopts "p:e:j:" o; do
    case "${o}" in
        p)
            platform=${OPTARG}
            if [ "$platform" != "ios" ]; then
               if [ "$platform" != "android" ]; then
                 usage
               fi
            fi
            ;;
        e)
            environment=${OPTARG}
            ;;
        j)
            config_password=${OPTARG}
            ;;
        *)
            usage
            ;;
    esac
done

shift $((OPTIND-1))

if [ -z "${platform}" ]; then
    usage
fi

if [ $platform == "ios" ]; then
    echo "Building iOS examples..."
    rm -rf "./ios/Include/eegeo"
    rm -rf "./ios/build"

    ./update.platform.sh -p ios

    if [ $? -ne 0 ] ; then
        exit $?
    fi

    pushd ios
    ./build.sh $allArguments
    resultcode=$?
    popd
elif [ $platform == "android" ]; then
    echo "Building Android examples..."
    rm -rf "./android/libs/eegeo"
    rm -rf "./android/obj"
    rm -rf "./android/bin"
    ./update.platform.sh -p android

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
