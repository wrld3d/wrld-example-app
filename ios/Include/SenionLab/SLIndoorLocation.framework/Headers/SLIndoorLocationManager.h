//
//  SLIndoorLocationManager.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SLIndoorLocationManagerDelegate.h"
#import "SLLocationState.h"
#import "SLGeofencing.h"
#import "SLGeomessenger.h"
#import "SLPath.h"

/**
 SLIndoorLocationManager specifies the positioning interactions. Initiation, starting the positioning,
 ending the positioning, changing the user position and step length, all is specified there.
 */
@interface SLIndoorLocationManager: NSObject

/// @name Initializer

/**
 Create the default SLIndoorLocationManager for one specific Map Key. 
 
 @param mapKey Map Key (obtained from Senion).
 @param customerId Customer ID (obtained from Senion).
 */
+ (instancetype)defaultIndoorLocationMangerWithMapKey:(NSString *)mapKey customerId:(NSString *)customerId;

/**
 Create the default SLIndoorLocationManager for multiple Map Keys. This location manager selects the current building (Map Key) automatically based on the beacons in range.
 
 @param mapKeys Array of Map Keys (obtained from Senion).
 @param customerId Customer ID (obtained from Senion).
 */
+ (instancetype)defaultIndoorLocationMangerWithMapKeys:(NSArray<NSString *> *)mapKeys customerId:(NSString *)customerId;

/**
 Create the automatic wakeup SLIndoorLocationManager for one specific Map Key. This location manager will launch the app (if suspended) when entering the building if iOS wakeup is enabled on the installed beacons.
 
 To use this method 10 available monitored regions are required in CLLocationManager. Also, you need to enable both background and foreground location updates. Please review the "Background app launch" section on the page [iOS Authorization](ios-authorization.html) before using this method.
 
 @param mapKey Map Key (obtained from Senion).
 @param customerId Customer ID (obtained from Senion).
 */
+ (instancetype)automaticWakeupIndoorLocationMangerWithMapKey:(NSString *)mapKey customerId:(NSString *)customerId;

/**
 Create the automatic wakeup SLIndoorLocationManager for multiple Map Keys. This location manager will launch the app (if suspended) when entering one of the buildings. Also, this location manager selects the current building (Map Key) automatically based on the beacons in range.

 To use this method 10 available monitored regions are required in CLLocationManager. Also, you need to enable both background and foreground location updates. Please review the "Background app launch" section on the page [iOS Authorization](ios-authorization.html) before using this method.
 
 @param mapKeys Array of Map Keys (obtained from Senion).
 @param customerId Customer ID (obtained from Senion).
 */
+ (instancetype)automaticWakeupIndoorLocationMangerWithMapKeys:(NSArray<NSString *> *)mapKeys customerId:(NSString *)customerId;

/**
 Create the mockup SLIndoorLocationManager for testing off site.
 
 @param locationState A SLLocationState.
 @param timeInterval A time interval in seconds between location updates.
 */
+ (instancetype)mockupIndoorLocationManagerWithLocationState:(SLLocationState *)locationState timeInterval:(NSTimeInterval)timeInterval;

/**
 Create the mockup SLIndoorLocationManager for testing off site.
 
 @param locationStates An array of SLLocationState.
 @param timeInterval A time interval in seconds between location updates.
 */
+ (instancetype)mockupIndoorLocationManagerWithLocationStates:(NSArray<SLLocationState *> *)locationStates timeInterval:(NSTimeInterval)timeInterval;

/**
 @warning The use of this method have been deprecated and will be removed in a future release of the SDK. Please use ``defaultIndoorLocationMangerWithMapKey:customerId:`` instead.

 Init location manager using Map Key and Customer ID.
 
 @param mapKey Map Key (obtained from Senion).
 @param customerId Customer ID (obtained from Senion).
 */
- (instancetype)initWithMapKey:(NSString *)mapKey andCustomerId:(NSString *)customerId __attribute__((deprecated("'initWithMapKey:andCustomerId:' has been deprecated, please use 'defaultIndoorLocationMangerWithMapKey:customerId:' instead")));

/// @name Delegate

/**
 The delegate object to receive update events from SLIndoorLocationManager.
 */
@property (nonatomic, weak) id<SLIndoorLocationManagerDelegate> delegate;

/// @name Start/Stop location updates

/**
 Start location updates. Must be called to start location updates after initializing the class.
 */
- (void)startUpdatingLocation;

/**
 Stops location updates. To start positioning again, use [SLIndoorLocationManager startUpdatingLocation].
 */
- (void)stopUpdatingLocation;

/// @name Getter/Setter

/**
 Check if bluetooth is powered on.
 
 @return YES if BLE is enabled.
 */
- (BOOL)isBleEnabled;

/**
 @return The map ID of the loaded map.
 */
- (NSString *)getMapId;

/**
 @return The map version ID of the loaded map.
 */
- (NSString *)getMapVersionId;

/**
 @return The current location availability status.
 */
- (SLLocationAvailability)getLocationAvailability;

/**
 @return YES if location availability status is SLLocationAvailabilityAvailable.
 */
- (BOOL)isLocationAvailable;

/// @name Heading calibration

/**
 Set if the calibration display popped up by iOS should be shown.
 
 @param displayCalibration Set to true if the calibration display should be shown, false otherwise.
 */
- (void)shouldDisplayHeadingCalibration:(BOOL)displayCalibration;

/// @name Geofencing/Geomessenger

/**
 @return The Geofencing manager, used to create alerts when the user enters specific areas.
 */
- (id<SLGeofencing>)getGeofencingManager;

/**
 @return the GeoMessenger manager, used to recieve notifications when the user enters specific areas defined on our servers.
 */
- (id<SLGeoMessenger>)getGeoMessengerManager;

/// @name Shortest path

/**
 Get shortest path between two locations in the same building. This method does not work for multiple buildings and will only give you the shortest path for the building the user is currently inside.
 
 @note Note that this function is mainly for demonstrating a possible user navigation feature. Please contact Senion if you plan to use this feature in your app.
 
 @param startLocation The start location.
 @param endLocation The end location.
 
 @return A path object containing a list of locations from startLocation to endLocation and the path length.
 */
- (SLPath *)computeShortestPathFromLocation:(SLCoordinate3D *)startLocation toLocation:(SLCoordinate3D *)endLocation;

/// @name Class methods

/**
 @return The current SDK version.
 */
+ (NSString *)getSdkVersion;

/**
 Call this function to set which authorization method that should be requested by the SDK. This function must
 be called before initializing this class otherwise the default value of SLRequestAlwaysAuthorization will be
 used.
 
 Apple requests that you update your Info.plist with the following strings:
 
 -  For SLRequestAlwaysAuthorization the NSLocationAlwaysUsageDescription need to be present.
 -  For SLRequestWhenInUseAuthorization the NSLocationWhenInUseUsageDescription need to be present.
 
 @param method SLIbeaconAutorizationMethod.
 */
+ (void)setIbeaconAuthorizationMethod:(SLIbeaconAuthorizationMethod)method;

@end
