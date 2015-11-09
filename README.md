![eeGeo](http://cdn2.eegeo.com/wp-content/uploads/2015/06/wide_eegeo_logo_hero.jpg)

# eeGeo 3D Maps C++ SDK

The [eeGeo SDK](http://www.eegeo.com/developers/) is a cross-platform, OpenGL-based library for [beautiful and customisable 3D maps](http://www.eegeo.com). 

This document provides the information you need to quickly get up and running in a pre-made app, which demonstrates how an application can use the eeGeo 3D maps SDK to display beautiful 3D maps. The example can be used as the basis for your own cross-platform app, or can be used as a reference when integrating the eeGeo 3D map into an existing app. We'll also cover how to get an API key, and link out to more detailed documentation for main SDK features and types.


## Getting Started 

This section will walk you through the process of getting up and running quickly.

### SDK distribution

The SDK is distributed as a C++ static library with headers, with an [example app](https://github.com/eegeo/mobile-example-app) to demonstrate project configuration and show the use of the SDK in practice. A [shell script](https://github.com/eegeo/mobile-example-app/blob/master/update.platform.sh) is provided in the example app repo root which fetches the SDK. The SDK is deployed continuously; the most up to date version can be obtained by running this shell script. We recommend doing so often, in order to reduce the impact of updating.

Both C++ 03 and C++ 11 versions of the SDK binaries are provided in order to maximise compatibility.

### Cross-Platform Mobile Example App

The [Mobile Example App](https://github.com/eegeo/mobile-example-app) is an open source version of eeGeo's [Recce](https://www.eegeo.com/recce) app, available for [iOS](https://itunes.apple.com/gb/app/recce/id858600575) and [Android](https://play.google.com/store/apps/details?id=com.eegeo.recce). This repo is intended to demonstrate a practical application of the eeGeo SDKs cross-platform capabilities by presenting an architecture that shares all of the domain model code between iOS and Android, with platform-specific implementations only for views and OS dependent services (such as IO).

Much of the application code is shared between platforms, reducing duplication and maintenance overhead for developers.  

**To get started with the example app (iOS):**

The following steps assume XCode is present.

1. Clone the repo: **git clone git@github.com:eegeo/mobile-example-app.git**.
2. Get the latest iOS SDK by running **sh ./update.platform -p ios** from the repo root.
3. Obtain an [eeGeo API key](https://www.eegeo.com/developers/apikeys) and add it to the [ApiKey file](https://github.com/eegeo/mobile-example-app/blob/master/src/ApiKey.h#L10).
4. Open and build the **./ios/ExampleApp.xcodeproj**.

To build at the command line, run **./build.sh -p ios** from the repository root.

**Note**: In step 2, we download a C++ 03 binary. If you require a C++ 11 binary, run **sh ./update.platform -p ios -c**.

* **./update.platform.sh -p ios -c** will fetch c++ 11/libc++ ABI compatible versions of the SDK for libc++
* **./build.sh -p ios -c** from the command line will build targeting c++ 11 / libc++
* An additional target in the XCode project file is provided for c++ 11 support: ExampleAppCpp11


**To get started with the example app (Android):**

The following steps assume Eclipse and the NDK are present. In order to run, your version of Android Developer Tools must be >= 22.6. In order to support 64-bit ABIs, you must be using [Android NDK revision](http://developer.android.com/tools/sdk/ndk/index.html#Revisions) 10d or later.

1. Clone the repo: **git clone git@github.com:eegeo/mobile-example-app.git**.
2. Get the latest Android SDK by running **sh ./update.platform -p android** from the repo root.
3. Obtain an [eeGeo API key](https://www.eegeo.com/developers/apikeys) and add it to the [ApiKey file](https://github.com/eegeo/mobile-example-app/blob/master/src/ApiKey.h#L10).
4. Create an Eclipse Android workspace for the ./android directory, with NDK native support. For more detailed instructions on how to easily set up a native Android development environment, see [this blog post](https://www.eegeo.com/2015/06/easily-set-up-a-native-android-development-environment/).

The project is configured to build for multiple target CPU architectures, creating a universal .apk containing exectutables for each of these architectures.

* The supported architectures are defined in [./Android/jni/Application.mk](https://github.com/eegeo/mobile-example-app/blob/master/android/jni/Application.mk#L4), by the line: *APP_ABI := armeabi,armeabi-v7a,arm64-v8a*
* Removing the APP_ABI line will build and package for the default armeabi architecture. The armeabi architecture is backwards-compatible with armeabi-v7a, but will not run on devices 64-bit ARM instruction sets.
* For further information about supporting multiple architectures see: http://developer.android.com/google/play/publishing/multiple-apks.html

[build.sh](https://github.com/eegeo/mobile-example-app/blob/master/build.sh) can be used to generate the native library if you want to manually package the .apk. To build at the command line, run **./build.sh -p android** from the repository root.

**Note**: In step 2, we download a C++ 03 binary. If you require a C++ 11 binary, run **sh ./update.platform -p android -c**.

* Android c++ 11 support is **EXPERIMENTAL** due to the experimental nature of c++ 11 support in the NDK (more information [here]( https://developer.android.com/tools/sdk/ndk/index.html) & [here](https://gcc.gnu.org/gcc-4.8/cxx0x_status.html))
* Only tested against Android [NDK](https://developer.android.com/tools/sdk/ndk/index.html) version r10d 
* Only tested against gcc 4.9 & gnu libstd++ (see [android/jni/Application.mk](https://github.com/eegeo/mobile-example-app/blob/master/android/jni/Application.mk) for how to target these)
* **./update.platform.sh -p android -c** will fetch c++ 11/gnu libstdc++ ABI compatible versions of the SDK
* **./build -p android -c** from the command line will build targeting c++ 11
* Pass COMPILE_CPP_11=1 to ndk-build to build cpp11

**To get started with the example app (Windows):**

* The following steps assume Visual Studio 2015 and MinGW are installed.
* Clone this repository and run `./update.platform.sh -p windows`
* Open ./windows/ExampleApp/ExampleApp.sln
* Right click the ExampleAppWPF project and choose `Set as StartUp Project`
* Build and Run the app

### API Key 

In order to use the eeGeo 3D Maps API, you must sign up for a free developer account at https://www.eegeo.com/developers. After signing up, you'll be able to create an [API key](https://www.eegeo.com/developers/apikeys) for your apps. 

After signing up for a developer account and creating an API key, add it to the example app [ApiKey file](https://github.com/eegeo/mobile-example-app/blob/master/src/ApiKey.h#L10) as described in the previous section.


## SDK Overview 

The [example app](https://github.com/eegeo/mobile-example-app) demonstrates a variety of SDK features, and is a good starting point to get to know how the SDK works. 

![eeGeo](http://cdn2.eegeo.com/wp-content/uploads/2015/09/intro_screen.jpg)

Among the use cases demonstrated by the example app are:

* A tactile menu based user experience for manipulating the application
* Category and free-text point of interest search and display using an off the shelf third party search service
* In world display for points of interest using both 2D native UI widgets and 3D pins
* Dynamic weather and season control
* Environment flattening to enter "map-mode"
* Animated camera transitioning between in-world locations
* GPS usage to control a compass widget
* Background preloading of environment resources
* A model for implementing an initial user experience

For a detailed walkthrough on the example app, and the SDK features exercised by the app, see the [documentation page](http://www.eegeo.com/developers/documentation/mobileexampleapp). 

The [SDK documentation](http://www.eegeo.com/developers/documentation/) covers various SDK features in greater detail, and an [API reference](http://cdn1.eegeo.com/docs/mobile-sdk/annotated.html) is available documenting the individual SDK types.

![eeGeo](http://cdn2.eegeo.com/wp-content/uploads/2015/09/mea_search_result.jpg)

## Support

If you **need help**, contact [support@eegeo.com](mailto:support@eegeo.com). Bug reports or feature requests are also accepted.

## License

The eeGeo 3D Maps SDK is released under the Eegeo Platform SDK Evaluation license. See the [LICENSE.md](https://github.com/eegeo/mobile-example-app/blob/master/LICENSE.md) file for details.
