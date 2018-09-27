#!/bin/sh

script_name=${0##*/}
base_dir=$(dirname "$0")


readonly xcode_target="ExampleApp"

build_dir="XcodeBuild"
clean_build=0
release_build=0
archive=0
configure_only=0
simulator_build=0
pretty_print=0
build_version=1
product_name="$xcode_target"
product_version="$build_version"
development_team=""
resolve_codesign_identity=0

usage()
{
    echo -e "Usage\n\n${script_name} [options]\n" >&2
    echo -e "Options\n" >&2
    echo -e "-c,--clean\t\t\t\tDelete build directory prior to build." >&2
    echo -e "-r,--release\t\t\t\tCreate Release build (default is Debug, or RelWithDebInfo if --archive specified)." >&2
    echo -e "-a,--archive\t\t\t\tCreate archive." >&2
    echo -e "--configure-only\t\t\t\tConfigure only - generates xcproj via cmake, but does not build or archive." >&2
    echo -e "--build-dir\t\t\t\tBuild directory relative to this script in which xcproj will be created (default XcodeBuild)." >&2
    echo -e "--simulator\t\t\t\tCreate build for iphonesimulator targets (default is build for iphoneos)." >&2
    echo -e "--product-name <PRODUCT_NAME>\t\tPRODUCT_NAME of app, default ${product_name}." >&2
    echo -e "--product-version <tPRODUCT_VERSION>\t\tPRODUCT_VERSION of app, default ${product_version}." >&2
    echo -e "--build-version <tBUILD_VERSION>\t\tBUILD_VERSION of app, default ${build_version}." >&2
    echo -e "--development-team <DEVELOPMENT_TEAM>\tA valid Apple developer team id, for code signing and running on device." >&2
    echo -e "--resolve-codesign-identity\t\t\tAttempt to resolve ambiguous codesign identity matching TEAM_ID and 'iPhone Developer' (default OFF)." >&2
    echo -e "--pretty-print\t\t\t\tPretty-print xcodebuild output (requires xcpretty)." >&2
    echo -e "-h,--help\t\t\t\tDisplay this usage message." >&2
}


while [[ $# -gt 0 ]]
do
    option="$1"

    case $option in
        -c|--clean)
        clean_build=1
        shift
        ;;
        -r|--release)
        release_build=1
        shift
        ;;
        -a|--archive)
        archive=1
        shift
        ;;
        --simulator)
        simulator_build=1
        shift
        ;;
        --configure-only)
        configure_only=1
        shift
        ;;
        --pretty-print)
        pretty_print=1
        shift
        ;;
        -h|--help)
        shift
        usage
        exit 0
        ;;
        --build-dir)
        build_dir="$2"
        shift
        shift
        ;;
        --product-name)
        product_name="$2"
        shift
        shift
        ;;
        --product-version)
        product_version="$2"
        shift
        shift
        ;;
        --build-version)
        build_version="$2"
        shift
        shift
        ;;
        --development-team)
        development_team="$2"
        shift
        shift
        ;;
        --resolve-codesign-identity)
        resolve_codesign_identity=1
        shift
        ;;
        *)
        echo -e "Invalid argument: $1" >&2
        usage
        exit 1
        ;;
    esac
done



abort()
{
  echo "FAILED: $1 LINE $2" >&2
  exit 1
}

trap 'abort $0 $LINENO' 0

set -e

readonly project_path=$base_dir/$build_dir
echo "project_path is ${project_path}" >&2

if [ ${clean_build} -ne 0 ] ; then
    echo "Clean build specified, deleting $project_path" >&2
    rm -rf $project_path
fi

mkdir -p $project_path


pushd $project_path > /dev/null

    cmake_args=""

    if [ ${simulator_build} -ne 0 ] ; then
        cmake_args="${cmake_args} -DIOS_PLATFORM=SIMULATOR"
    fi

    if [ -n "${development_team}" ]; then
        cmake_args="${cmake_args} -DDEVELOPMENT_TEAM=${development_team}"
    fi

    if [ ${resolve_codesign_identity} -ne 0 ] ; then
        cmake_args="${cmake_args} -DRESOLVE_CODE_SIGN_IDENTITY=ON"
    fi

    cmake_args="${cmake_args} -G Xcode .."

    echo "Calling: cmake $cmake_args" >&2

    cmake $cmake_args

    if [ ${configure_only} -ne 0 ] ; then
        echo "configure-only specified, exiting." >&2
        exit 0
    fi

    if [ ${archive} -ne 0 ] ; then
        target_configuration="RelWithDebInfo"
    else
        if [ ${release_build} -ne 0 ] ; then
            target_configuration="Release"
        else
            target_configuration="Debug"
        fi
    fi

    xcodebuild_args=" \
-target $xcode_target \
-configuration $target_configuration \
PRODUCT_NAME=$product_name \
PRODUCT_VERSION=$product_version \
BUILD_VERSION=$build_version \
-allowProvisioningUpdates"

    if [ ${archive} -ne 0 ] ; then
        xcode_archive="${product_name}.xcarchive"
        echo "building archive $xcode_archive"
        xcodebuild_args="$xcodebuild_args ONLY_ACTIVE_ARCH=NO -archivePath $xcode_archive -scheme $xcode_target archive"
    else
        echo "performing non-archive build"
    fi

    echo "Calling: xcodebuild $xcodebuild_args" >&2

    if [ ${pretty_print} -ne 0 ] ; then
        xcodebuild $xcodebuild_args | tee xcodebuild.log | xcpretty && xcodebuild_result=${PIPESTATUS[0]}
        if [ $xcodebuild_result -ne 0 ] ; then 
            echo "xcodebuild failed with result $xcodebuild_result" >&2
            echo "Displaying last 100 lines of xcodebuild log $(pwd)/xcodebuild.log" >&2
            tail -n 100 xcodebuild.log >&2
            exit 1
        fi
    else
        xcodebuild $xcodebuild_args
    fi
    
    if [ ${archive} -ne 0 ] ; then
        mkdir -p "$xcode_target/"
        dsym_zip="$xcode_target/$product_name.dsym.zip"
        echo "zipping dSYM to: ${dsym_zip}" >&2
        zip -r "$dsym_zip" "./$xcode_archive/dSYMs/${product_name}.app.dSYM"
        rm -rf "./$xcode_archive/dSYMs/${product_name}.app.dSYM"
    fi

popd


trap : 0

echo "\n$0 SUCCEEDED\n" >&2


exit 0