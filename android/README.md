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

* [Android Studio](https://developer.android.com/studio/archive) (3.1.1 or later)
* [Android NDK](https://developer.android.com/ndk/downloads/) (>= 17c)
* [Senion SDK](https://senion.com/)

## Obtaining and setting your WRLD API Key

1. Sign in to your WRLD account [here](https://www.wrld3d.com/).

2. Navigate to your [account page](https://accounts.wrld3d.com/users/sign_in?service=https%3A%2F%2Faccounts.wrld3d.com%2F%23apikeys).

3. Here you can copy the API key of your app, and create a new app if you don't already have one.

4. Paste your API key [here](https://github.com/wrld3d/wrld-example-app/blob/master/android/assets/ApplicationConfigs/standard_config.json#L3).

## Building

1. Download the latest WRLD Android SDK by running `./update.platform.sh -p android` in the root directory of this repository. We recommend you run this step frequently to keep your SDK version up to date.
2. Copy your Senion SDK JAR file into your local checkout directory of [wrld-example-app/android/libs](https://github.com/wrld3d/wrld-example-app/tree/master/android/libs).
3. Make sure your ANDROID_HOME and ANDROID_NDK_HOME are set to the correct paths. The default Android Studio installation paths on Windows are `\Users\username\AppData\Local\Android\sdk` and `\Users\username\AppData\Local\Android\sdk\ndk-bundle`.
On MacOS they are located at `/Users/<username>/Library/Android/sdk` and `/Users/<username>/Library/Android/sdk/ndk-bundle`.
4. Make sure your JAVA_HOME is set. Instructions for this can be found on the [oracle](https://docs.oracle.com/cd/E19182-01/821-0917/inst_jdk_javahome_t/index.html) website.
5. To create a debug build for Android run:

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
