#!/bin/sh

usage() { echo "Usage: $0 -f <PLATFORM> -e <ENVIRONMENT>  -j <CONFIG_PASSWORD>" ;
    echo "  -p -> platform, windows,ios or android (required)";
    echo "  -e -> environment for deployment (staging or production)"
    echo "  -j -> password used to derive configuration file encryption key";
    1>&2;
    exit 1;
}

while getopts "p:e:j:" o; do
    case "${o}" in
    p)
        platform=${OPTARG}
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


if [ $platform == "ios" ]; then
    config_folder=ios/Resources/ApplicationConfigs
elif [ $platform == "android" ]; then
    config_folder=android/assets/ApplicationConfigs
elif [ $platform == "windows" ]; then
    config_folder=windows/Resources/ApplicationConfigs
else
    usage
fi

if [ ! -z "${config_password}" ]; then
	secret_key=$((python "./build-scripts/generate_key.py" ${config_password}) 2>&1)
    sed_pattern="s#project_swallow_config.json#encrypted_config.json#g;s#APP_CONFIG_SECRET_HERE#${secret_key}#g"
else
    echo "no password"
	sed_pattern="s#project_swallow_config.json#encrypted_config.json#g"
fi

if [ $environment == 'production' ]; then
	src_config_file=project_swallow_production_config.json
else
    echo "not production"
	src_config_file=project_swallow_config.json
fi

apiKeyFile=./src/ApiKey.h
apiKeyFileTemp=./src/ApiKeyTemp.h

git checkout $apiKeyFile
sed -e ${sed_pattern} $apiKeyFile > $apiKeyFileTemp

if [ $? -ne 0 ] ; then
	echo "Failed to poke config file values into ApiKey file"  >&2
	exit 1
fi

mv $apiKeyFileTemp $apiKeyFile

if [ $platform == "ios" ]; then
    pushd ios/Resources
    sed -e 's#Resources/ApplicationConfigs/project_swallow_config.json#Resources/ApplicationConfigs/encrypted_config.json#' \
    -e 's#Resources/ApplicationConfigs/project_swallow_production_config.json##' CMakeLists.txt > CMakeListsTemp.txt

    mv CMakeListsTemp.txt CMakeLists.txt
    popd
fi

dest_config_file=encrypted_config.json
temp_config_folder=

if [ ! -z "${secret_key}" ]; then

	git checkout -- ${config_folder}
	temp_config_folder=config_bak
	rm -vr ${temp_config_folder}/
	mv -v ${config_folder}/ ${temp_config_folder}/
	mkdir ${config_folder}/
	
	python "./build-scripts/encrypt_config.py" -i ${temp_config_folder}/${src_config_file} -o ${config_folder}/${dest_config_file} -s ${secret_key}	

	if [ $? -ne 0 ] ; then
		echo "Failed to encrypt config file"  >&2
		exit 1
	fi
else
	cp -f ${config_folder}/${src_config_file} ${config_folder}/${dest_config_file}
fi

resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "ENCRYPTION SUCCEEDED"
else
  echo "ENCRYPTION FAILED"
fi

exit $resultcode
