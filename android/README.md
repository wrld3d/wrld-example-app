<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# eeGeo Example App

Android builds of the [eeGeo Example App](https://github.com/eegeo/mobile-example-app) use the Android NDK and JNI to run native code on Android devices.

## Getting Started on Android

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/eegeo/mobile-example-app).

### Requirements

- [Eclipse IDE for Java Developers](https://eclipse.org/downloads/)   
- [Android SDK Tools](http://developer.android.com/sdk/index.html#Other) (24.4.1 or higher)
- [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) (r10e or higher)

### Setup

First, download the latest eeGeo Android SDK by running the following command in the root of the repository:

*   `./update.platform.sh -p android`
	*	We recommend you run this step frequently to keep your SDK version up to date.

The following steps will guide you through installing and setting up the Android SDK, and Eclipse. If you already have these installed and setup, you can skip to [here](#setting-up-the-project).

#### Setting up the Android SDK

1.  Open Android's SDK Manager, which was installed with the Android SDK Tools
2.  Install the Android SDK Build-tools (23.0.2)
3.  Install the Android SDK Platfrorm-tools (23.1)
4.  Install the SDK platform for the API version to be developed

#### Setting up Eclipse

1.  Open Eclipse and select `Help > Install New Software`
2.  Select `Add` in the top-right corner.
3.  In the Add Repository dialog that appears, enter "ADT Plugin" for the Name, and enter `https://dl-ssl.google.com/android/eclipse/` for the Location.
4.  Click `OK`.
5.  In the Available Software dialog, select the checkbox next to "Developer Tools" and click `Next`.
6.  You'll see a lit of the tools to be downloaded. Click `Next` again.
7.  Read and accept the license agreements, then click `Finish`.
8.  Once the installation is complete, restart Eclipse.

#### Setting up the project

1.  In Eclipse, go to `File > Switch Workspace > Other...`
2.  Select an empty folder to use as a Workspace
3.  Go to `Eclipse > Preferences`, find `NDK Location` under `Android > NDK` and set it to wherever you installed the NDK to.
4.  Right-click on the Package Explorer sidebar and choose `Import...`
5.  Select `Android > Existing Android Code Into Workspace`
6.  Select the `android` folder in the Example App and click `Finish`
7.  Right click the project, and select `Android Tools > Add Native Support...`
8.  To speed up compile times, see [this section below](#speeding-up-build-times) for compiling with multiple threads.
9.  To run the project, right-click it and select `Run As > Android Application`

#### C++03 Builds

By default, the above steps will build the project with C\+\+11. If you wish to build a C\+\+03 only version, follow these additional steps:

1.  Download the latest C\+\+03 version of the eeGeo Android SDK: `./update.platform.sh -p android -c`
2.  Right-click the project and select `Properties`
3.  Under C/C\+\+ Build, uncheck "Use default build command".
4.  Add `COMPILE_CPP_03=1` to the command in the "Build command" field.
5.  For example: `ndk-build COMPILE_CPP_03=1`
6.  Run the project as normal.

#### Debug & Release Builds

You can specify whether to build in debug mode or release mode by using the `NDK_DEBUG` option.

For example, to build in debug, follow the steps described [here](#c03-builds) to edit the ndk-build command, and replace it with the following:

-	`ndk-build NDK_DEBUG=1`

This will disable optimizations and generate debug symbols. See the [NDK documentation](http://developer.android.com/ndk/guides/ndk-build.html#dvr) for more details on the `NDK_DEBUG` option and how it interacts with the `android:debuggable` option in the Android manifest.

### Speeding up build times

1.  Compiling on multiple threads:

    - Right-click the project and select `Properties`
    - Under C/C\+\+ Build, uncheck "Use default build command".
    - In the "Build command" field, add the option `-jN`, where N is the number of threads to use.
    - For example: `ndk-build -j4` to use 4 threads
    
2.  Reducing the number of architectures:
    
    -   By default, the project is compiled for three different architectures: **armeabi**, **armeabi-v7a**, and **arm64-v8a**.
    -   If you do not need all of these, or you wish to quickly test on a single architecture, you can remove some of them from [this line in Application.mk](https://github.com/eegeo/mobile-example-app/blob/master/android/jni/Application.mk#L4).
    -   For example: `APP_ABI := armeabi`