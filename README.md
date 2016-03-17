<a href="http://www.eegeo.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo_logo_quite_big.png" alt="eeGeo Logo" title="eegeo" align="right" height="80px" />
</a>

# eeGeo Example App

* [Getting Started](#getting-started)
    * [eeGeo API Key](#eegeo-api-key)
    * [Optional Steps](#optional-steps)
* [Features](#features)
* [SDK Documentation](#sdk-documentation)
* [Support](#support)
* [License](#support)

The [eeGeo SDK](http://www.eegeo.com/developers/) is a cross-platform, OpenGL-based library for [beautiful and customisable 3D maps](http://www.eegeo.com).

This cross-platform example app demonstrates how a developer can use the eeGeo 3D Maps SDK to display beautiful 3D maps on iOS, Android, and Windows PCs. This app can be used as the basis for your own app, or can be used as a reference when integrating eeGeo's maps into an existing app.

The eeGeo SDK is distributed as a C++ static library with headers. Most of this example application is written in C++ and shared between platforms to reduce code duplication. A notable exception to this is the UI: the app uses the native UI system on each platform.

## Getting Started

This section will walk you through the process of getting up and running quickly on each platform.

1.  Clone this repo: `https://github.com/eegeo/mobile-example-app`
2.  Obtain an [eeGeo API key](https://www.eegeo.com/developers/apikeys) and place it in the [ApiKey.h](https://github.com/eegeo/mobile-example-app/blob/master/src/ApiKey.h#L12) file.
3.  Choose a platform from the below table to see detailed instructions for building the app.

Platform             							| Languages
------------------------------------------------|-----------------
[Android](/android#getting-started-on-android)  | C++, Java
[iOS](/ios#getting-started-on-ios)          	| C++, Objective-C
[Windows](/windows#getting-started-on-windows)  | C++, C#

### eeGeo API Key 

In order to use the eeGeo 3D Maps SDK, you must sign up for a free developer account at https://www.eegeo.com/developers. After signing up, you'll be able to create an [API key](https://www.eegeo.com/developers/apikeys) for your apps. 

To run this example app, you must place the API key in the [ApiKey.h](https://github.com/eegeo/mobile-example-app/blob/master/src/ApiKey.h#L12) file.

If you are creating a new app, or integrating eeGeo 3D Maps into an existing app, the API key should be passed as the first argument to the constructor of [EegeoWorld](http://cdn1.eegeo.com/docs/mobile-sdk/class_eegeo_1_1_eegeo_world.html).

### Optional Steps

1.  Obtain Yelp credentials to enable Yelp search results in the app. Place them in [ApiKey.h](https://github.com/eegeo/mobile-example-app/blob/master/src/ApiKey.h#L15-L18).
2.  Obtain a GeoNames username to enable GeoNames search results in the app. Place it in [ApiKey.h](https://github.com/eegeo/mobile-example-app/blob/master/src/ApiKey.h#L21).

## Features

The [eeGeo Example App](https://github.com/eegeo/mobile-example-app) demonstrates a variety of SDK features and is a good starting point to learn how the SDK works.

![eeGeo Example App features](http://cdn2.eegeo.com/wp-content/uploads/2016/03/eegeo-example-app-features.jpg)

Some of those features include:

*   3D map display
*   Indoor maps
*   Tactile UX for controlling the application
*   Animated camera transitions
*   Dynamic theming to control weather, season, and time of day
*   Category and free-text searching using third party search services
*   In-world display for points of interest
*   Background preloading of environment resources

## SDK Documentation

See the [eeGeo API reference](http://cdn1.eegeo.com/docs/mobile-sdk/namespaces.html) for documentation on the individual SDK types.

## Support

If you have any questions, bug reports, or feature requests, feel free to submit to the [issue tracker](https://github.com/eegeo/mobile-example-app/issues) for this repository. Alternatively, you can contact us at [support@eegeo.com](mailto:support@eegeo.com).

## License

The eeGeo 3D Maps SDK is released under the Eegeo Platform SDK Evaluation license. See the [LICENSE.md](https://github.com/eegeo/mobile-example-app/blob/master/LICENSE.md) file for details.