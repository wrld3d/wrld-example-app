#!/bin/sh

usage() { echo "Usage: $0 -p ios"; echo "  -p -> platform, ios or android (required)"; 1>&2; exit 1; }

projectPath=$(pwd)/XcodeBuild/
rm -rf $projectPath
mkdir $projectPath

targetName="INVALID"

while getopts "p:f:t:" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "ios" ]; then
               usage
            fi
            ;;
        f)
            cmakeRootDir=${OPTARG}
            ;;
        t)
            xcodeTarget=${OPTARG}
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

if [ -z "${cmakeRootDir}" ]; then
    cmakeRootDir=".."
fi

if [ -z "${xcodeTarget}" ]; then
    xcodeTarget="ExampleApp"
fi

(cd $projectPath && cmake -G Xcode $cmakeRootDir)
resultcode=$?
if [ $resultcode -ne 0 ]; then
    echo "FAILED TO GENERATE PROJECT"
    
    exit $resultcode
fi

(cd $projectPath && xcodebuild -target $xcodeTarget -arch "i386" -sdk "iphonesimulator")
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE XCODE PROJECT SUCCEEDED"
else
  echo "COMPILE XCODE PROJECT FAILED"
fi
echo

exit $resultcode
