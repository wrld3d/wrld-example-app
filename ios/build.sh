#!/bin/sh

usage() { echo "Usage: $0 -p ios [-c]"; echo "  -p -> platform, ios or android (required)"; echo "  -c -> cpp11 support"; 1>&2; exit 1; }

projectPath=$(pwd)/./
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
   targetName="ExampleAppCpp11"
else
   targetName="ExampleApp"
fi

(cd $projectPath && xcodebuild -target $targetName -arch "i386" -sdk "iphonesimulator")
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE XCODE PROJECT SUCCEEDED"
else
  echo "COMPILE XCODE PROJECT FAILED"
fi
echo

exit $resultcode
