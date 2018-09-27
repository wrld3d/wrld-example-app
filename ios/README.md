<a href="http://www.wrld3d.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2017/04/WRLD_Blue.png"  align="right" height="80px" />
</a>

# Getting Started on iOS

![WRLD](http://cdn2.eegeo.com/wp-content/uploads/2017/04/screenselection01.png)

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/wrld3d/wrld-example-app).

## Requirements

- [Xcode](https://developer.apple.com/xcode/) (9.3 tested)
- [CMake](https://cmake.org/) (3.2.0  or higher)
- [Senion SDK](https://senion.com/)
- For building and running on an iOS device, an Apple Developer Team ID from your [Apple Developer Account](https://developer.apple.com/account/#/membership/)

## Setup

1.  In the root of the repo, run the command `./update.platform.sh -p ios` to download the latest WRLD iOS SDK.
	*	We recommend you run this step frequently to keep your SDK version up to date.
2.  Copy your Senion SDK framework file into the [wrld-example-app/ios/Include/SenionLab/](https://github.com/wrld3d/wrld-example-app/tree/master/ios/Include/SenionLab) directory
3.  In the `ios` directory, run `mkdir build` to create a build directory.
4.  In the `ios/build` directory, run cmake to generate an Xcode project, also specifying your Apple Development Team id: `cmake -DDEVELOPMENT_TEAM=<YOUR_APPLE_DEVELOPMENT_TEAM_ID> -G Xcode ..`.
5.  Open the `ExampleApp.xcodeproj` project file in Xcode.
6.  Build and run the ExampleApp target.

## Building from the command line

There is a script included in the repo to build the app from the command line. You may wish to do this, for example, if you want to have the app building on a Continuous Integration system.

To build from the command line, you will need to install the Xcode Command Line Tools by running the command: `xcode-select --install`

Then run `./build.sh -p ios` from the root of this repository to build the project.

## Troubleshooting

When building the app for deployment to physical iOS devices, the app needs codesigning with your iOS development certificate.

In some cases, multiple certificates with name prefix 'iPhone Developer' may be present in your login keychain, which creates ambiguity over which identity to use when signing embedded frameworks. A cmake option has been added that attempts to resolve such ambiguities. To enable, pass `-DRESOLVE_CODE_SIGN_IDENTITY=ON` as a cmake argument, i.e. `cmake -DDEVELOPMENT_TEAM=<YOUR_APPLE_DEVELOPMENT_TEAM_ID> -DRESOLVE_CODE_SIGN_IDENTITY=ON -G Xcode ..`.

