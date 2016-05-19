<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# Getting Started on Android

![eeGeo](http://cdn2.eegeo.com/wp-content/uploads/2016/03/readme-banner.jpg)

Before you begin, ensure you have completed the initial steps as described in the [root of the repository](https://github.com/eegeo/eegeo-example-app).

## Requirements

- [Android Studio] (https://developer.android.com/studio/index.html) (2.1 tested) 
- [Android NDK](http://developer.android.com/tools/sdk/ndk/index.html) (r11c tested)

## Setup

First, download the latest eeGeo Android SDK by running the following command in the root of the repository:

*   `./update.platform.sh -p android`
    *   We recommend you run this step frequently to keep your SDK version up to date.

### Setting up Android Studio
If you followed the standard Android Studio setup, you should be equipped with SDK v23 and Build Tools v23.0.3.

N.B. - There is currently a [bug](https://code.google.com/p/android/issues/detail?id=195135) prohibiting the ability to specify NDK platforms between build targets. This is scheduled to be fixed in Android Studio 2.2. As a current workaround, we've split our app into two configurations. Arm should be used for 32-bit builds (armeabi, armeabi-v7a) and arm64 should be used for 64-bit builds (arm64-v8a).

1.  Open Android Studio  
2.  Click Open an existing Android Studio Project  
3.  Select the 'android' directory of this repository (if you're prompted to update gradle settings, click 'ok')  
4.  You'll be prompted for an NDK location. Click `Select NDK->Select a valid NDK path` and point to your NDK installation
5.  Build and run the app by clicking `Run->Run...`, specifying the arm or arm64 configuration depending on your device
