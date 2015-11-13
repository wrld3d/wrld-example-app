#!/bin/sh

projectPath=$(pwd)/./

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
