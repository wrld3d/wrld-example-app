cd windows
set VCTargetsPath=%PROGRAMFILES(X86)%\MSBuild\Microsoft.Cpp\v4.0\V140
set copyDestination=ExampleApp\ExampleAppWPF\bin\Release
nuget.exe restore WinBuild\ExampleApp.sln
"%VCTargetsPath%\..\..\..\14.0\Bin\msbuild" WinBuild\ExampleApp.sln /p:Configuration=Release /p:Platform=x64 /t:Clean
"%VCTargetsPath%\..\..\..\14.0\Bin\msbuild" WinBuild\ExampleApp.sln /p:Configuration=Release /p:Platform=x64 /target:ExampleAppWPF

if %ERRORLEVEL% NEQ 0 (
	echo "Compile failed."
	exit /b 1
)

if not exist "%copyDestination%\Resources" ( mkdir "%copyDestination%\Resources" )
xcopy /E /H /C /R /Q /Y "Resources" "%copyDestination%\Resources"
copy /Y "libs\eegeo\ANGLE\x64\Release\*.dll" "%copyDestination%"
copy /Y "libs\eegeo\openssl\x64\*.dll" "%copyDestination%"
copy /Y "libs\eegeo\pthread\x64\Release\*.dll" "%copyDestination%"
copy /Y "libs\eegeo\VS2012\x64\Release\*.dll" "%copyDestination%"
copy /Y "%PROGRAMFILES(X86)%\Microsoft Visual Studio 14.0\VC\bin\amd64\d3dcompiler_47.dll" "%copyDestination%"
copy /Y "%PROGRAMFILES(X86)%\Microsoft Visual Studio 14.0\Team Tools\Performance Tools\x64\msvcr120.dll" "%copyDestination%"

