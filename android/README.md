<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# Getting Started on Android

![eeGeo](http://cdn2.eegeo.com/wp-content/uploads/2016/03/readme-banner.jpg)

* [Requirements](#requirements)
* [Setup](#setup)
    * [Setting up the Android SDK](#setting-up-the-android-sdk)
    * [Setting up Eclipse](#setting-up-eclipse)
    * [Setting up the project](#setting-up-the-project)
* [Optional Steps](#optional-steps)
    * [Build for debugging](#build-for-debugging)
    * [Speeding up build times](#speeding-up-build-times)
* [Troubleshooting](#troubleshooting)
    * [Eclipse hangs adding native support](#eclipse-hangs-adding-native-support)

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/eegeo/eegeo-example-app).

## Requirements

- [Eclipse IDE for Java Developers](https://eclipse.org/downloads/)   
- [Android SDK Tools](http://developer.android.com/sdk/index.html#Other) (24.4.1 or higher)
- [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) (r11c or Higher)

## Setup

First, download the latest eeGeo Android SDK by running the following command in the root of the repository:

*   `./update.platform.sh -p android`
    *   We recommend you run this step frequently to keep your SDK version up to date.

The following steps will guide you through installing and setting up the Android SDK, and Eclipse. If you already have these installed and setup, you can skip to [here](#setting-up-the-project).

### Setting up the Android SDK

1.  Open Android's SDK Manager, which was installed with the Android SDK Tools
2.  Install the Android SDK Build-tools (23.0.2)
3.  Install the Android SDK Platfrorm-tools (23.1)
4.  Install the SDK platform for the API version to be developed (Min API 24)

### Setting up Eclipse

1.  Open Eclipse and select `Help > Install New Software`
2.  Select `Add` in the top-right corner.
3.  In the Add Repository dialog that appears, enter "ADT Plugin" for the Name, and enter `https://dl-ssl.google.com/android/eclipse/` for the Location.
4.  Click `OK`.
5.  In the Available Software dialog, select the checkbox next to "Developer Tools" and click `Next`.
6.  You'll see a lit of the tools to be downloaded. Click `Next` again.
7.  Read and accept the license agreements, then click `Finish`.
8.  Once the installation is complete, restart Eclipse.

### Setting up the project

1.  In Eclipse, go to `File > Switch Workspace > Other...`
2.  Select an empty folder to use as a Workspace
3.  Go to `Eclipse > Preferences` on OSX, `Window > Preferences` on Windows.
4.  Find `NDK Location` under `Android > NDK` and set it to wherever you installed the NDK to.
5.  Right-click on the Package Explorer sidebar and choose `Import...`
6.  Select `Android > Existing Android Code Into Workspace`
7.  Select the `android` folder in the Example App and click `Finish`
8.  Right click the project, and select `Android Tools > Add Native Support...`
9.  Add the cross-platform source by right-clicking the `jni` folder and selecting `New > Folder`.
10. Click `Advanced` and select the `Linked to alternate location` radio button. 
11. Click `Browse..` and select the [src](https://github.com/eegeo/eegeo-example-app/tree/master/src) directory. 
12. To speed up compile times, see [this section below](#speeding-up-build-times) for compiling with multiple threads.
13. To run the project, right-click it and select `Run As > Android Application`

After selecting an Android device from the dialog, the app should then run as normal.

## Optional Steps

### Build for debugging

If you wish to attach a debugger, you will need to build the app in debug mode. You can do this by supplying the `NDK_DEBUG` option to the ndk-build command. This is done as follows:

-   Right-click the project and select **Properties**
-   Under **C/C\+\+ Build**, uncheck "Use default build command".
-   In the "Build command" field, add the `NDK_DEBUG` option: `ndk-build NDK_DEBUG=1`

See the [NDK documentation](http://developer.android.com/ndk/guides/ndk-build.html#dvr) for more details on the `NDK_DEBUG` option and how it interacts with the `android:debuggable` option in the Android manifest.

### Speeding up build times

1.  Compiling on multiple threads:

    - Right-click the project and select `Properties`
    - Under C/C\+\+ Build, uncheck "Use default build command".
    - In the "Build command" field, add the option `-jN`, where N is the number of threads to use.
    - For example: `ndk-build -j4` to use 4 threads
    
2.  Reducing the number of architectures:
    
    -   By default, the project is compiled for three different architectures: **armeabi**, **armeabi-v7a**, and **arm64-v8a**.
    -   If you do not need all of these, or you wish to quickly test on a single architecture, you can remove some of them from [Application.mk](/android/jni/Application.mk#L4).
    -   For example: `APP_ABI := armeabi`

## Troubleshooting

### Eclipse hangs adding native support  

Some developers have experienced a deadlock when adding native support to the project. The IDE hangs, and the project is left in a corrupted and unrecoverable state. The following steps mitigate this issue:

- Destroy the corrupted Eclipse workspace by deleting the metadata Eclipse creates in android directory. The metadata are:
    - .classpath file
    - .project file
    - .cproject file
    - .settings directory
- Create the workspace again as described in [Setting up the project](#setting-up-the-project)
- Delete the contents of [Android.mk](/android/jni/Android.mk#L4).
- Add native support to the project
- Revert the change to Android.mk
