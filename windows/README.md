<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# eeGeo Example App

Windows builds of the [eeGeo Example App](https://github.com/eegeo/mobile-example-app) use WPF and C# for the native UI layer.

## Getting Started on Windows

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/eegeo/mobile-example-app).

### Requirements

- [Microsoft Visual Studio 2015](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)
- [CMake](https://cmake.org/) (>= 3.1.1)
- [Git for Windows](https://git-for-windows.github.io/)

### Setup

1.  Open a Git Bash terminal for the following commands.
2.  In the root of the repo, run the command `./update.platform -p windows` to download the latest eeGeo Windows SDK.
3.  In the `windows` directory, run `mkdir build` to create a build directory.
4.  In the `windows/build` directory, run `cmake -G "Visual Studio 14 Win64" ..` to generate a project file.
5.  Open the `ExampleApp.sln` project file in Visual Studio.
6.  Right-click the ExampleAppWPF project and select `Set as StartUp Project`.
7.  Run the application.
8.  If you want to build from the command line, you can run `./build.sh -p windows` from the root of the repository.

### C++03 Builds

By default, the above steps generate a project using C\+\+11. To build versions of the application which are C\+\+03 only, follow these steps:

1.  Open a Git Bash terminal for the following commands.
2.  In the root of the repo, run the command `./update.platform -p windows -c` to download the latest eeGeo Windows SDK.
3.  In the `windows` directory, run `mkdir build` to create a build directory.
4.  In the `windows/build` directory, run `cmake -G "Visual Studio 14 Win64" -DCOMPILE_CPP_03=1 ..` to generate a project file.
5.  Open the `ExampleApp.sln` project file in Visual Studio.
6.  Right-click the ExampleAppWPF project and select `Set as StartUp Project`.
7.  Run the application.