<a href="http://www.wrld3d.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2017/04/WRLD_Blue.png" align="right" height="80px" />
</a>

# Getting Started on Android

![WRLD](http://cdn2.eegeo.com/wp-content/uploads/2017/04/screenselection01.png)


* [Requirements](#requirements)
* [Android Studio Setup](#setup)
* [Automated build scripts](#automated-build-scripts)
* [Troubleshooting](#troubleshooting)

## Requirements

- [Android Studio](https://developer.android.com/studio/index.html).

## Setup

First, download the appropriate WRLD Android SDK by running the following command in the root of the repository:

*   `./update.platform.sh -p android -v NNNN` where NNNN is the build number of the WRLD platform SDK. If omitted, the most recent WRLD platform SDK will be used.

### Setting up and building the project

1. Open Android Studio and if prompted about a missing SDK, (minimally) install the `SDK` and `SDK Platform`.
2. Select `Open an existing Android Studio project`
3. Navigate to the [swallow-app/android](https://github.com/wrld3d/swallow-app/tree/master/android) directory and hit `Ok`.
4. If prompted to generate a gradle wrapper, select `Ok`.
5. For local debugging, open the `Build Variants` pane using the button on the lower-left side, and from the `Build Variant` dropdown, ensure `normalDebug` is selected.

To build a local release build, define `versionCode` and `versionName` in [build.gradle](https://github.com/wrld3d/swallow-app/blob/master/android/build.gradle#L46) and run the `assembleRelease` gradle task. 

## Automated build scripts

This repository includes build scripts for automated builds.  Note that Android Studio must still be installed.
To build from the command line at the root of this repository:
1. `./update.platform.sh -p android -v $WRLD_SDK_BUILD`
2. `./build-scripts/encrypt_config.sh -p android -e $ENVIRONMENT -j $CONFIG_PASSWORD` 
3. `./build-scripts/android/create_apk_file_gradle.step.sh ./android/ $VERSION_CODE $VERSION_STRING `
where the parameters are :

Parameter | Description
----------|------------
WRLD_SDK_BUILD | Build number of the WRLD platform SDK
ENVIRONMENT | One of `staging`, `production`, or `release` 
CONFIG_PASSWORD | Password used to derive encryption key
VERSION_CODE | Android version code, see [android docs](https://developer.android.com/studio/publish/versioning)
VERSION_STRING | Version name, see [android docs](https://developer.android.com/studio/publish/versioning)

The WRLD build machine runs `./build-scripts/android/teamcity.android.sh`, which additionally pushes the build to HockeyApp.


## Troubleshooting

If gradle project configuration fails, Android Studio may prompt with either of the following:

1. NDK not configured: Select `Install NDK and sync project`, accept the license agreement and continue.
2. Failed to find CMake: Select `Install CMake and sync project`.

After this project configuration should succeed.

Alternatively, if a `Gradle 'android' project refresh failed` prompt is not displayed, select `File > Settings`.

1. Select the list item `Appearance & Behavior > System Settings > Android SDK`
2. Click the `SDK Tools` and check the following:
    * Android SDK Built-Tools,
    * CMake,
    * LLDB,
    * Android SDK Platform-Tools,
    * Android SDK Tools, and
    * NDK.

If an error persists, you may try deleting the directory `%APPDATA%/../Local/Android` on Windows or `~/Library/Android` on OSX.  This should force Android Studio to prompt for a re-install of the SDK and tools.
