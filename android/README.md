<a href="http://www.wrld3d.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2017/04/WRLD_Blue.png" align="right" height="80px" />
</a>

# Getting Started on Android

![WRLD](http://cdn2.eegeo.com/wp-content/uploads/2017/04/screenselection01.png)


Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/wrld3d/wrld-example-app).

* [Requirements](#requirements)
* [Android Studio Setup](#setup)
* [Speeding up build times](#speeding-up-build-times)
* [Troubleshooting](#troubleshooting)

[Instructions for Eclipse development](#eclipse-project-setup-legacy) are included for transition support. The recommended development environment for Android is now Android Studio.  

## Requirements

- [Android Studio](https://developer.android.com/studio/).
- [Senion SDK](https://senion.com/)

## Setup

First, download the latest WRLD Android SDK by running the following command in the root of the repository:

*   `./update.platform.sh -p android`
    *   We recommend you run this step frequently to keep your SDK version up to date.

### Setting up the project

1. Open Android Studio and if prompted about a missing SDK, (minimally) install the `SDK` and `SDK Platform`.
2. Select `Open an existing Android Studio project`
3. Navigate to the [wrld-example-app/android](https://github.com/wrld3d/wrld-example-app/tree/master/android) directory and hit `Ok`.
4. When prompted to generate a gradle wrapper, select `Ok`.
5. Once project configuration completes, Open the `Build Variants` pane using the button on the lower-left side, and from the `Build Variant` dropdown, ensure `normalDebug` is selected.
6. Copy your Senion SDK JAR file into the [wrld-example-app/android/libs](https://github.com/wrld3d/wrld-example-app/tree/master/android/libs) directory

## Speeding up build times

By default, the project is compiled for three different architectures: **armeabi**, **armeabi-v7a**, and **arm64-v8a**.
If you do not need all of these, or you wish to quickly test on a single architecture, you can remove some of them from [build.gradle](/android/build.gradle#L63).
    -   For example: `abiFilters "armeabi"`

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
