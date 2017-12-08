#!/bin/sh

usage() { echo "Usage: $0 -e <ENVIRONMENT> -f <CONFIG_FOLDER> -p <CONFIG_PASSWORD>" ; }

while getopts "e:f:p:" o; do
    case "${o}" in
	e) 
            environment=${OPTARG}
            ;;
	f)
            config_folder=${OPTARG}
       
            ;;
    p)
            config_password=${OPTARG}
       
            ;;
   *)
            usage
            ;;
    esac
done

if [ ! -z "${config_password}" ]; then
	secret_key=$((python "./build-scripts/generate_key.py" ${config_password}) 2>&1)
    sed_pattern="s#project_swallow_config.json#encrypted_config.json#g;s#APP_CONFIG_SECRET_HERE#${secret_key}#g"
else
	sed_pattern="s#project_swallow_config.json#encrypted_config.json#g"
fi

if [ $environment == 'production' ]; then
	src_config_file=project_swallow_production_config.json
else
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