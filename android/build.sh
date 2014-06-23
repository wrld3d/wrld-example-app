#!/bin/sh

usage() { echo "Usage: $0 -p android [-c]"; echo "  -p -> platform, ios or android (required)"; echo "  -c -> cpp11 support"; 1>&2; exit 1; }

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
            c="cpp11"
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

if [ "$c" == "cpp11" ]; then
   ndkbuild_arguments="COMPILE_CPP_11=1"
fi

# running on msys (basically the git provided shell we use on windows)
if [ "$OSTYPE" == "msys" ]; then
    cmd "/C ndk-build.cmd" $ndkbuild_arguments
else
    ndk-build $ndkbuild_arguments
fi

resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE ANDROID PROJECT SUCCEEDED"
else
  echo "COMPILE ANDROID PROJECT FAILED"
fi


exit $resultcode
