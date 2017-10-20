<a href="http://www.wrld3d.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2017/04/WRLD_Blue.png"  align="right" height="80px" />
</a>

# Getting Started on Windows

![WRLD](http://cdn2.eegeo.com/wp-content/uploads/2017/04/screenselection01.png)

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

## Troubleshooting

### Touch Input recieves double input when interacting with virtual keyboard

With touch input enabled on some touchscreen devices, the virtual keyboard can be seen entering characters twice upon pressing.  This can be resolved by disabling the "Enable Press-and-hold for right clicking" feature in the Pen and Touch control panel:
1. Press the windows key.
2. type "pen and touch" and press enter.
3. In the window that appears, left-click the entry "Press and hold" and click "settings".
4. Uncheck "Enable press and hold for right-clicking".
5. Click OK on both windows to close them.


### System.Windows.Markup.XamlParseException and/or EEFileLoadException

When encountering this kind of exceptions: 
1. Open Apps & Features
2. Search for Microsoft Visual Studio Professional 2015 and select Modify
3. Select all features and apply update
4. Re-open and rebuild the solution