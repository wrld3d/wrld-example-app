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


if [ $environment == 'production' ]; then
	src_config_path=windows/Resources/ApplicationConfigs/project_swallow_production_config.json
else
	src_config_path=windows/Resources/ApplicationConfigs/project_swallow_config.json
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

if [ ! -z "${secret_key}" ]; then

	dest_config_path=windows/Resources/ApplicationConfigs/encrypted_config.json
	rm $dest_config_path

	python "./build-scripts/encrypt_config.py" -i ${src_config_path} -o ${dest_config_path} -s ${secret_key}

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

exit $resultcode
