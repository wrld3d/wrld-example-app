<a href="http://www.wrld3d.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2017/04/WRLD_Blue.png"  align="right" height="80px" />
</a>

# Getting Started on iOS

![WRLD](http://cdn2.eegeo.com/wp-content/uploads/2017/04/screenselection01.png)

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/wrld3d/wrld-example-app).

## Requirements

- [Xcode](https://developer.apple.com/xcode/) (7.2 tested)
- [CMake](https://cmake.org/) (3.1.1  or higher)
- [Senion SDK](https://senion.com/)

## Setup

1.  In the root of the repo, run the command `./update.platform.sh -p ios` to download the latest WRLD iOS SDK.
	*	We recommend you run this step frequently to keep your SDK version up to date.
2.  Copy your Senion SDK framework file into the [wrld-example-app/ios/Include/SenionLab/](https://github.com/wrld3d/wrld-example-app/tree/master/ios/Include/SenionLab) directory
3.  In the `ios` directory, run `mkdir build` to create a build directory.
4.  In the `ios/build` directory, run `cmake -G Xcode ..` to generate a project file.
5.  Open the `ExampleApp.xcodeproj` project file in Xcode.
6.  Build and run the ExampleApp target.

## Building from the command line

There is a script included in the repo to build the app from the command line. You may wish to do this, for example, if you want to have the app building on a Continuous Integration system.

To build from the command line, you will need to install the Xcode Command Line Tools by running the command: `xcode-select --install`

Then run `./build.sh -p ios` from the root of this repository to build the project.