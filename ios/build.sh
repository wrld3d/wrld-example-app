#!/bin/sh

usage() { echo "Usage: $0 -p ios";
    echo "  -p -> platform, ios ";
    echo "  -e -> environment for deployment (staging or production)"
    echo "  -j -> password used to derive configuration file encryption key";
    1>&2;
    exit 1;
}

projectPath=$(pwd)/XcodeBuild/
rm -rf $projectPath
mkdir $projectPath

targetName="INVALID"

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


pushd ..
    sh build-scripts/encrypt_config.sh -p $platform -e $environment -j $config_password
popd


(cd $projectPath && cmake -G Xcode ..)



resultcode=$?
if [ $resultcode -ne 0 ]; then
    echo "FAILED TO GENERATE PROJECT"    
    exit $resultcode
fi

(cd $projectPath && python ../embed_frameworks.py)

resultcode=$?
if [ $resultcode -ne 0 ]; then
    echo "FAILED TO EMBED SENION FRAMEWORK IN PROJECT"
    exit $resultcode
fi

#(cd $projectPath && xcodebuild -target ProjectSwallowApp -arch "i386" -sdk "iphonesimulator")
#resultcode=$?

#echo
#if [ $resultcode = 0 ] ; then
#  echo "COMPILE XCODE PROJECT SUCCEEDED"
#else
#  echo "COMPILE XCODE PROJECT FAILED"
#fi
#echo

exit $resultcode
