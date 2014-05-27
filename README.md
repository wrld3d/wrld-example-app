iOS mobile-sdk-harness
==================

* Run ./update.platform.sh ios to get the latest platform libraries and headers.
* The accompanying project has no code signing, so run in the simulator (or provide your own credentials).
* The platform needs an API key to operate. Sign up at https://appstore.eegeo.com/ to get your API key and introduce it into the following line in ViewController.mm : 
	#define API_KEY "OBTAIN API_KEY FROM https://appstore.eegeo.com AND INSERT IT HERE".
* Scroll between the examples using the Next and Previous buttons; the current example name is displayed at the top of the screen.
* To build at the command line, run ./build ios from the repository root.

android mobile-sdk-harness
==========================

* Install the Android SDK and NDK
* Run ./update.platform.sh android to get the latest platform libraries and headers.
* Open an ADT Eclipse workspace, importing this repository as an Android project
* Set the NDK location in the ADT Eclipse workspace to where it was installed (Menu->ADT->Android->NDK)
* Bring up the project menu, from within Android Tools add native support to the project
* The platform needs an API key to operate. Sign up at https://appstore.eegeo.com/ to get your API key and introduce it into the following line in jni/main.cpp : 
	#define API_KEY "OBTAIN API_KEY FROM https://appstore.eegeo.com AND INSERT IT HERE"
* Build and debug from within ADT Eclipse
* build.sh can be used to generate the native library if you want to manually package the .apk
* Scroll between the examples using the Next and Previous buttons, or select the example from the drop-down list; the current example name is displayed at the top of the screen. 
* To build at the command line, run ./build android from the repository root.