#!/bin/sh

usage() { echo "Usage: $0 -p android"; echo "  -p -> platform, ios or android (required)"; 1>&2; exit 1; }

projectPath=$(pwd)/./
ndkbuild_arguments=""

while getopts "p:" o; do
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

# running on msys (basically the git provided shell we use on windows)
if [ "$OSTYPE" == "msys" ]; then
    cpu_count=$NUMBER_OF_PROCESSORS        
    cmd "/C ndk-build.cmd -j${cpu_count}${ndkbuild_arguments}"
else
    cpu_count=$(sysctl -n hw.ncpu)
    echo "compile_android.step.sh (osx): cpu count: ${cpu_count}"
    ndk-build -j$cpu_count$ndkbuild_arguments
fi

resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE ANDROID PROJECT SUCCEEDED"
else
  echo "COMPILE ANDROID PROJECT FAILED"
fi


exit $resultcode
