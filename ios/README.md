<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# eeGeo Example App

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/eegeo/mobile-example-app).

## Getting Started on iOS

### Requirements

- [Xcode](https://developer.apple.com/xcode/) (7.2 tested)
- [CMake](https://cmake.org/) (3.1.1  or higher)

### Setup

1.  In the root of the repo, run the command `./update.platform -p ios` to download the latest eeGeo iOS SDK.
2.  In the `ios` directory, run `mkdir build` to create a build directory.
3.  In the `ios/build` directory, run `cmake -G Xcode ..` to generate a project file.
4.  Open the `ExampleApp.xcodeproj` project file in Xcode and run the application.
5.  If you want to build from the command line, you can run `./build.sh -p ios` from the root of the repository.

### C++03 Builds

By default, the above steps generate a project using C\+\+11. To build versions of the application which are C\+\+03 only, follow these steps:

1.  In the root of the repo, run the command `./update.platform -p ios -c` to download the latest C\+\+03 version of the eeGeo iOS SDK.
2.  In the `ios` directory, run `mkdir build` to create a build directory.
3.  In the `ios/build` directory, run `cmake -G Xcode -DCOMPILE_CPP_03=1 ..` to generate a project file.
4.  Open the `ExampleApp.xcodeproj` project file in Xcode and run the application.
5.  To build from the command line, you can run `./build.sh -p ios -c` from the root of the repository.