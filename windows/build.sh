#!/bin/sh

usage()
{ 
	echo "Usage: $0 [-n <PRODUCT_NAME> -e <ENVIRONMENT> -v <FILE_VERSION> -i <INFORMATIONAL_VERSION>] -p <CONFIG_PASSWORD>]"; 
	echo "  -n -> the product name of the app"; 
    echo "  -e -> environment for deployment (staging or production)"
	echo "  -v -> file version of executable"; 
	echo "  -i -> informational version of executable"; 
	echo "  -p -> password used to derive configuration file encryption key"; 
	1>&2; 
	exit 1; 
}

projectPath=$(pwd)/windows/WinBuild/
rm -rf $projectPath
mkdir $projectPath

while getopts "n:e:v:i:p:" o; do
    case "${o}" in
    	n)
            productName=${OPTARG}
            ;;
        e) 
            environment=${OPTARG}
            ;;
    	v)
            fileVersion=${OPTARG}
            ;;
    	i)
            informationalVersion=${OPTARG}
            ;;
		p)
			config_password=${OPTARG}
			;;
		*)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

if [ ! -z "${productName}" ]; then
    sed -i "s/string\s*ProductName\s*=\s*@\"[^\"]*\"/string ProductName = @\"$productName\"/g" windows/ExampleApp/ExampleAppWPF/Properties/VersionInfo.cs
	sed -i "s/\s*Title\s*=\s*\"[^\"]*\"/        Title=\"$productName\"/g" windows/ExampleApp/ExampleAppWPF/MainWindow.xaml
	
fi

if [ ! -z "${fileVersion}" ]; then
    sed -i "s/string\s*FileVersion\s*=\s*@\"[^\"]*\"/string FileVersion = @\"$fileVersion\"/g" windows/ExampleApp/ExampleAppWPF/Properties/VersionInfo.cs
fi

if [ ! -z "${informationalVersion}" ]; then
    sed -i "s/string\s*InformationalFileVersion\s*=\s*@\"[^\"]*\"/string InformationalFileVersion = @\"$informationalVersion\"/g" windows/ExampleApp/ExampleAppWPF/Properties/VersionInfo.cs
fi

if [[ ( $environment != 'production' ) && ( $environment != 'staging' ) ]]; then
    echo "invalid environment '$environment'. Must be one of [staging|production]"
    exit 1
fi



if [ ! -z "${config_password}" ]; then
	secret_key=$((python "./build-scripts/generate_key.py" ${config_password}) 2>&1)
    sed_pattern="s#project_swallow_config.json#encrypted_config.json#g;s#APP_CONFIG_SECRET_HERE#${secret_key}#g"
elif [ $environment == 'production' ]; then
	sed_pattern="s#project_swallow_config.json#project_swallow_production_config.json#g"
else
	sed_pattern="s#project_swallow_config.json#project_swallow_config.json#g"
fi


config_folder=windows/Resources/ApplicationConfigs

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

temp_config_folder=

if [ ! -z "${secret_key}" ]; then

	temp_config_folder=temp_config
	rm -vr ${temp_config_folder}/
	mv -v ${config_folder}/ ${temp_config_folder}/
	mkdir ${config_folder}/
	
	dest_config_file=encrypted_config.json

	python "./build-scripts/encrypt_config.py" -i ${temp_config_folder}/${src_config_file} -o ${config_folder}/${dest_config_file} -s ${secret_key}	

	if [ $? -ne 0 ] ; then
		echo "Failed to encrypt config file"  >&2
		exit 1
	fi

fi

if [ ! -f windows/nuget.exe ]; then
	curl -o windows/nuget.exe https://api.nuget.org/downloads/nuget.exe
fi

pushd $projectPath
cmake -G "Visual Studio 14 Win64" ..
popd

cmd //C windows\\build.bat
resultcode=$?

if [ $resultcode = 0 ] ; then
	echo "COMPILE WINDOWS PROJECT SUCCEEDED" >&2
else
	echo "COMPILE WINDOWS PROJECT FAILED" >&2
fi

if [ ! -z ${temp_config_folder} ]; then	

	rm -vr ${config_folder}/
	mv -fv ${temp_config_folder}/ ${config_folder}/
	
	if [ $? -ne 0 ] ; then
		echo "failed to restore config folder" >&2
		exit 1
	fi
	
	rm -rf ${temp_config_folder}

fi

exit $resultcode
