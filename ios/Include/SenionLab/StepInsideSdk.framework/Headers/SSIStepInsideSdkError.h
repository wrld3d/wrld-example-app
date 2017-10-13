//
//  SSIStepInsideSdkError.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The domain for all errors from the StepInside SDK.
 */
static NSString * _Nonnull const SSIStepInsideSdkErrorDomain = @"com.senion.stepinside.error";

/**
 This enum describe all error types you can expect from `SSIStepInsideSdkStatusDelegate`.
 */
typedef NS_ENUM(NSInteger, SSIStepInsideSdkErrorType) {
    
    /**
     The API Key or map key you have provided to `SSIStepInsideSdkManagerConfig` is invalid.
     
     This error is unrecoverable, and you need to reinitialize the SDK with the correct keys.
     
     - Note: If this error have occured, you will always get a notification about it whenever you add a new status delegate.
     */
    SSIStepInsideSdkErrorTypeInvalidKeys,
    
    /**
     The SDK failed to download the positioning package needed for positioning.
     
     The SDK will automatically retry. First retry is immediate, but it is extended for each download failiure.
     
     - Note: This error will only occure if you do not have any previously cached data on your device.
     */
    SSIStepInsideSdkErrorTypeFailedToLoadPositioningPackage,
    
    /**
     The device do not have BLE enabled.
     
     When this happen, you need to prompt the user and ask to enable BLE. The SDK will automatically continue once the user have enabled BLE on the device.
     
     This error will also occure if the user disables BLE during positioning.
     */
    SSIStepInsideSdkErrorTypeBleNotEnabled,
    
    /**
     The user has not yet made a choice regarding whether this app can use `Core Location` services.
     
     When this happen, you need to make a call to ether `[SSISensors requestCoreLocationWhenInUseAuthorization]` or `[SSISensors requestCoreLocationAlwaysAuthorization]` depending on your need. This will display the system promt asking the user for permission.
     
     The SDK will automatically continue once the user have given permission to use `Core Location` in this app.
     
     - Note: The SDK uses `Core Location`, `Core Bluetooth` and `Core Motion` to establish your location. This mean that you can still recieve locations even thought the user have not yet given permission to use `Core Location`. However, all services will not work fully until `Core Location` access is granted.
     */
    SSIStepInsideSdkErrorTypeCoreLocationAuthorizationNotDetermined,
    
    /**
     The app is not authorized to use `Core Location` services. This can happen if ether the user have denied authorization or if the user can't give authorization due to active restrictions in iOS settings.
     
     When this happens, you need to prompt the user and ask to grant authorization for this app. This mean the user need to go to iOS settings and change the authorization manually. It is not possible to display the system promt when this error happens.
     
     The SDK will automatically continue once the user have given permission to use `Core Location` in this app.
     
     - Note: The SDK uses `Core Location`, `Core Bluetooth` and `Core Motion` to establish your location. This mean that you can still recieve locations even thought the user have not yet given permission to use `Core Location`. However, all services will not work fully until `Core Location` access is granted.
     */
    SSIStepInsideSdkErrorTypeCoreLocationAuthorizationDenied,
    
    /**
     Generating a single location failed. An error occured inside the SDK while generating a location.
     
     This error is purely informational and no action is needed. This error is most likely one-time event, and the SDK will continue to try and generate locations.
     */
    SSIStepInsideSdkErrorTypeLocationFailed,
    
    /**
     The SDK has failed to load GeoMessenger data.
     
     This error is purely informational. The SDK will automatically retry to download later.
     */
    SSIStepInsideSdkErrorTypeFailedToLoadGeoMessengerData
};
