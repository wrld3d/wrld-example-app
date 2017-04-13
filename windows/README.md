<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# Getting Started on Windows

![WRLD](http://cdn2.eegeo.com/wp-content/uploads/2016/03/readme-banner.jpg)

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/wrld3d/wrld-example-app).

## Requirements

- [Microsoft Visual Studio 2015](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)
- [CMake](https://cmake.org/) (>= 3.1.1)
- [Git for Windows (MinGW shell)](https://git-for-windows.github.io/)

## Setup

1.  Open a Git Bash (MinGW) terminal for the following commands.
2.  In the root of the repo, run the command `./update.platform.sh -p windows` to download the latest WRLD Windows SDK.
	*	We recommend you run this step frequently to keep your SDK version up to date.
3.  In the `windows` directory, run `mkdir build` to create a build directory.
4.  In the `windows/build` directory, run `cmake -G "Visual Studio 14 Win64" ..` to generate a project file.
5.  Open the `ExampleApp.sln` project file in Visual Studio.
6.  Right-click the ExampleAppWPF project and select `Set as StartUp Project`.
7.  Run the application.
8.  If you want to build from the command line, you can run `./build.sh -p windows` from the root of the repository.

## HTML Views

1. Go to the 'user_data' section of your poi in the Poi Tool.
2. Enter the html url you want to use using the following data field: `"custom_view":"https://www.myurl.com"`
3. Make sure your url starts with `https://` or `http://`
4. You can optionally edit the height of your web view in piexels with the data field `"custom_view_height":int`
4. In order to render the web view using IE 11, run regedit.exe from your start menu.
5. Create a new DWORD value in :HKEY_LOCAL_MACHINE (or HKEY_CURRENT_USER) > SOFTWARE > Microsoft > Internet Explorer > Main > FeatureControl > FEATURE_BROWSER_EMULATION
6. Call it (appName).exe, for windows example app it will be ExampleAppWPF.exe
7. Set the Decimal data to 11000. Other IE rendering mode values can be found [here](https://msdn.microsoft.com/library/ee330730(v=vs.85).aspx)
