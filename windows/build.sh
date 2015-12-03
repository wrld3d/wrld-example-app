#!/bin/sh

usage()
{ 
	echo "Usage: $0 [-n <PRODUCT_NAME> -v <FILE_VERSION> -i <INFORMATIONAL_VERSION>]"; 
	echo "  -n -> the product name of the app"; 
	echo "  -v -> file version of executable"; 
	echo "  -i -> informational version of executable"; 
	1>&2; 
	exit 1; 
}

projectPath=$(pwd)/./

while getopts "n:v:i:" o; do
    case "${o}" in
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
cmd //C windows\\build.bat
resultcode=$?

echo
if [ $resultcode = 0 ] ; then
  echo "COMPILE WINDOWS PROJECT SUCCEEDED"
else
  echo "COMPILE WINDOWS PROJECT FAILED"
fi

exit $resultcode
