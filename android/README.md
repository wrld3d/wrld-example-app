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


## Requirements

## Requirements

* [Android Studio](https://developer.android.com/studio/archive) (3.0+ tested)
* Gradle: (4.4, set within the `Project` tab of the `Project Structure` window inside Android Studio)
* Android Plugin for Gradle: (3.1.1, set within [build.gradle](https://github.com/wrld3d/swallow-app/blob/master/android/build.gradle))
* [Android SDK Tools](https://developer.android.com/studio/releases/sdk-tools): (25.2.3.1 or later)
* [Android NDK](https://developer.android.com/ndk/downloads/older_releases): (11c or later)
- [Senion SDK](https://senion.com/)

## Building

1. Download the latest WRLD Android SDK by running `./update.platform.sh -p android` in the root directory of this repository. We recommend you run this step frequently to keep your SDK version up to date.
2. Copy your Senion SDK JAR file into your local checkout directory of [wrld-example-app/android/libs](https://github.com/wrld3d/wrld-example-app/tree/master/android/libs).
3. To create a debug build for Android run:

  `./android/build.sh`


See `./android/build.sh --help` for further build options.

## Building interactively in Android Studio

1. Open Android Studio and if prompted about a missing SDK, (minimally) install the `SDK` and `SDK Platform`.
2. Select `Open an existing Android Studio project`
3. Navigate to your local checkout directory of [wrld-example-app/android](https://github.com/wrld3d/wrld-example-app/tree/master/android) and select `Ok`.
4. When prompted to generate a gradle wrapper, select `Ok`.
5. Once project configuration completes, Open the `Build Variants` pane using the button on the lower-left side, and from the `Build Variant` dropdown, ensure `normalDebug` is selected.

## Speeding up build times

By default, the project builds a native library targeting multiple architectures. If you do not need all of these, or you wish to quickly test on a single architecture, you can remove some of them from [build.gradle](/android/build.gradle#L63).
    -   For example: `abiFilters "armeabi-v7a"`

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

If an error persists, you may try deleting the directory `%APPDATA%/../Local/Android` on Windows or `~/Library/Android` on macOS. This should force Android Studio to prompt for a re-install of the SDK and tools.
