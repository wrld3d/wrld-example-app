#!/bin/sh

usage() { echo "Usage: $0 -p android [-c]"; echo "  -p -> platform, ios or android (required)"; echo "  -c -> cpp03 support"; 1>&2; exit 1; }

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
        c)
            c="cpp03"
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

if [ "$c" != "cpp03" ]; then
    echo "Building for cpp11"
    # note the leading space. on windows, ndk-build.cmd seems to tokenise on spaces    
    ndkbuild_arguments=" COMPILE_CPP_11=1"
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
