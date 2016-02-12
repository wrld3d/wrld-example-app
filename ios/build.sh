#!/bin/sh

usage() { echo "Usage: $0 -p ios [-c]"; echo "  -p -> platform, ios or android (required)"; echo "  -c -> cpp03 support"; 1>&2; exit 1; }

projectPath=$(pwd)/XcodeBuild/
rm -rf $projectPath
mkdir $projectPath

targetName="INVALID"

while getopts "p:c" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "ios" ]; then
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

pushd $projectPath
if [ "$c" == "cpp03" ]; then
  cmake -G Xcode .. -DCOMPILE_CPP_03=1
else
  cmake -G Xcode ..
fi
popd

(cd $projectPath && xcodebuild -target ExampleApp -arch "i386" -sdk "iphonesimulator")
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE XCODE PROJECT SUCCEEDED"
else
  echo "COMPILE XCODE PROJECT FAILED"
fi
echo

exit $resultcode
