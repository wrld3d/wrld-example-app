#!/bin/sh

script_name=${0##*/}
base_dir=$(dirname "$0")


clean_build=0
release_build=0
version_code=1
version_name="1.0"
application_id="com.wrld.exampleapp"


usage()
{
    echo -e "Usage\n\n${script_name} [options]\n" >&2
    echo -e "Options\n" >&2
    echo -e "-c,--clean\t\t\tPerform clean task prior to build." >&2
    echo -e "-r,--release\t\t\tCreate Release build (default is Debug)." >&2
    echo -e "-h,--help\t\t\tDisplay this usage message." >&2
    echo -e "--version-code\t\t\tVersion code of app, default ${version_code}." >&2
    echo -e "--version-name\t\t\tVersion name of app, default ${version_name}." >&2
    echo -e "--application-id\t\tBundle identifier of app, default ${application_id}." >&2
    echo -e "--external-signing\t\tRelative path to external apk signing credentials, default no signing." >&2
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
        -h|--help)
        shift
        usage
        exit 0
        ;;
        --version-code)
        version_code="$2"
        shift
        shift
        ;;
        --version-name)
        version_name="$2"
        shift
        shift
        ;;
        --application-id)
        application_id="$2"
        shift
        shift
        ;;
        --external-signing)
        external_signing="$2"
        shift
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


pushd $base_dir

    if [ ${clean_build} -ne 0 ] ; then
        echo "Performing clean" >&2
        ./gradlew :clean
        resultcode=$?
        if [ ${resultcode} -ne 0 ] ; then
            echo "Error performing gradle build" >&2
            exit ${resultcode}
        fi
        
    fi
    
    if [ ${release_build} -ne 0 ] ; then
        build_task=":assembleNormalRelease"
    else
        build_task=":assembleNormalDebug"
    fi
    
    gradle_arguments="-PversionCode=${version_code} -PversionName=${version_name} -PapplicationId=${application_id}"
    
    if [ -n "$external_signing" ]; then
        gradle_arguments="${gradle_arguments} -Pexternal.signing=${external_signing}"
    fi

    ./gradlew ${gradle_arguments} ${build_task}
    resultcode=$?

    if [ ${resultcode} -ne 0 ] ; then
        echo "Error performing gradle build" >&2
        exit ${resultcode}
    fi
popd

trap : 0
echo -e "\n$0 SUCCEEDED\n" >&2


exit 0
