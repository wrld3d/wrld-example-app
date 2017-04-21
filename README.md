<a href="http://www.wrld3d.com/">
    <img src="http://cdn2.eegeo.com/wp-content/uploads/2017/04/WRLD_Blue.png"  align="right" height="80px" />
</a>

# WRLD Example App

![WRLD](http://cdn2.eegeo.com/wp-content/uploads/2017/04/screenselection01.png)

* [Support](#support)
* [Getting Started](#getting-started)
    * [WRLD API Key](#wrld-api-key)
    * [Optional Steps](#optional-steps)
* [Features](#features)
* [SDK Documentation](#sdk-documentation)
* [License](#support)

This example app showcases the [WRLD SDK](http://www.wrld3d.com/), a cross-platform, OpenGL-based library for displaying beautiful and engaging 3D maps. It is also contains the source for the WRLD App on iOS and Android.

### What does the WRLD mapping platform have to offer?

* Detailed 3D coverage for the whole of Canada, UK & Ireland, Scandinavia, the United States, and more
* Indoor maps in full 3D
* Flexible themes, allowing you to change the style of your map
* Customisable pins and markers
* Support for custom 3D models and animation
* Compatibility with iOS, Android, Windows, and OS X
* Continuous deployment, meaning you get the latest features as they're developed

Download our app, [WRLD](https://www.wrld3d.com/app/), on Google Play or the App Store to see what the WRLD SDK can do. Or [read on](#getting-started) to build the app yourself.

## Support

If you have any questions, bug reports, or feature requests, feel free to submit to the [issue tracker](https://github.com/wrld3d/wrld-example-app/issues) for this repository.

## Getting Started

This example app demonstrates the use of the WRLD SDK to display beautiful 3D maps on iOS, Android, and Windows PCs. It can be used as the basis for your own app, or can be used as a reference when integrating WRLD's maps into an existing app.

The WRLD SDK is distributed as a C++ static library with headers. Most of this example application is also written in C++ and shared between platforms to reduce code duplication.

This section will walk you through the process of getting up and running quickly on each platform.

1.  Clone this repo: `git clone https://github.com/wrld3d/wrld-example-app`
2.  Obtain a [WRLD API key](https://www.wrld3d.com/developers/apikeys) and place it in the configuration file for the platform you are building:
    * [iOS app config](https://github.com/wrld3d/wrld-example-app/blob/master/ios/Resources/ApplicationConfigs/standard_config.json#L3).
    * [Android app config](https://github.com/wrld3d/wrld-example-app/blob/master/android/assets/ApplicationConfigs/standard_config.json#L3).
    * [Windows app config](https://github.com/wrld3d/wrld-example-app/blob/master/windows/Resources/ApplicationConfigs/standard_config.json#L3).
3.  Choose a platform from the table below to see detailed instructions for building the app.

Platform                                        | Languages         | UI 
------------------------------------------------|-------------------|-------------
[Getting started on Android](/android#readme)   | C++, Java         | Android UI
[Getting started on iOS](/ios#readme)           | C++, Objective-C  | Cocoa Touch
[Getting started on Windows](/windows#readme)   | C++, C#           | WPF

### WRLD API Key 

In order to use the WRLD 3D Maps SDK, you must sign up for a free developer account at https://www.wrld3d.com/developers. After signing up, you'll be able to create an [API key](https://www.wrld3d.com/developers/apikeys) for your apps. 

To run this example app, you must place the API key in the application configuration file for each of the platforms you are building, specifying the value of "EegeoApiKey":
* [iOS app config](https://github.com/wrld3d/wrld-example-app/blob/master/ios/Resources/ApplicationConfigs/standard_config.json#L3).
* [Android app config](https://github.com/wrld3d/wrld-example-app/blob/master/android/assets/ApplicationConfigs/standard_config.json#L3).
* [Windows app config](https://github.com/wrld/wrld-example-app/blob/master/windows/Resources/ApplicationConfigs/standard_config.json#L3).

### Optional Steps

This app uses third-party search service providers to allow users to search for places like caf&eacute;s, restaurants, and bars and have the results show up on the map. To enable this, you will to supply the credentials for those services.

1.  Obtain [Yelp credentials](https://www.yelp.com/developers) to enable Yelp search results in the app. Place them in the application config file appropriate for the platform you are building:
    * [iOS app config](https://github.com/wrld3d/wrld-example-app/blob/master/ios/Resources/ApplicationConfigs/standard_config.json#L12-L15).
    * [Android app config](https://github.com/wrld3d/wrld-example-app/blob/master/android/assets/ApplicationConfigs/standard_config.json#L12-L15).
    * [Windows app config](https://github.com/wrld3d/wrld-example-app/blob/master/windows/Resources/ApplicationConfigs/standard_config.json#L12-L15).
2.  Obtain a [GeoNames username](http://www.geonames.org/login) to enable GeoNames search results in the app. Place it in the application config file appropriate for the platform you are building:
    * [iOS app config](https://github.com/wrld3d/wrld-example-app/blob/master/ios/Resources/ApplicationConfigs/standard_config.json#L16).
    * [Android app config](https://github.com/wrld3d/wrld-example-app/blob/master/android/assets/ApplicationConfigs/standard_config.json#L16).
    * [Windows app config](https://github.com/wrld3d/wrld-example-app/blob/master/windows/Resources/ApplicationConfigs/standard_config.json#L16).

## Features

The [WRLD Example App](https://github.com/wrld3d/wrld-example-app) demonstrates a variety of SDK features and is a good starting point to learn how the SDK works.

![WRLD Example App features](http://cdn2.eegeo.com/wp-content/uploads/2017/04/FeatureExamples.jpg)

See [here](https://www.wrld3d.com/features/) to learn more about what the WRLD SDK has to offer.

## SDK Documentation

See the [WRLD API reference](http://cdn1.wrld3d.com/docs/mobile-sdk/namespaces.html) for documentation on the individual C++ SDK types.

## License

The WRLD 3D Maps Example App is released under the Simplified BSD License. See the [LICENSE.md](https://github.com/wrld3d/wrld-example-app/blob/master/LICENSE.md) file for details.
