#!/bin/sh

usage()
{ 
	echo "Usage: $0 -p windows -k <APIKEY> [-n <PRODUCT_NAME> -v <FILE_VERSION> -i <INFORMATIONAL_VERSION>]"; 
	echo "  -p -> platform, windows (required)"; 
	echo "  -k -> the Eegeo API key to use for the app (required)"; 
	echo "  -n -> the product name of the app"; 
	echo "  -v -> file version of executable"; 
	echo "  -i -> informational version of executable"; 
	1>&2; 
	exit 1; 
}

projectPath=$(pwd)/windows/WinBuild/
rm -rf $projectPath
mkdir $projectPath

while getopts "p:k:n:v:i:" o; do
    case "${o}" in
        p)
            p=${OPTARG}
            if [ "$p" != "windows" ]; then
               usage
            fi
            ;;
    	k)
            k=${OPTARG}
            ;;
    	n)
            productName=${OPTARG}
            ;;
    	v)
            fileVersion=${OPTARG}
            ;;
    	i)
            informationalVersion=${OPTARG}
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

if [ -z "${k}" ]; then
    usage
fi

sed -i "s/std::string\s*ApiKey\s*=\s*\"[^\"]*\"/std::string ApiKey = \"$k\"/g" src/ApiKey.h



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

if [ ! -f windows/nuget.exe ]; then
	curl -o windows/nuget.exe https://api.nuget.org/downloads/nuget.exe
fi

pushd $projectPath
cmake -G "Visual Studio 14 Win64" ..
popd

cmd //C windows\\build.bat
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE WINDOWS PROJECT SUCCEEDED"
else
  echo "COMPILE WINDOWS PROJECT FAILED"
fi

exit $resultcode
