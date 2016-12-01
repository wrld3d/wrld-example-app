//
//  SLIndoorLocationManager.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
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
@interface SLIndoorLocationManager: NSObject <SLIndoorLocationManagerDelegate>

/// @name Initializer

/**
 Init location using Map Key and Customer ID.
 
 @param mapKey Map Key (obtained from SenionLab).
 @param customerId Customer ID (obtained from SenionLab).
 */
- (instancetype)initWithMapKey:(NSString *)mapKey andCustomerId:(NSString *)customerId;

/// @name Delegate

/**
 Set delegate class that will receive updates from SLIndoorLocationManager.
 
 @param delegate The delegate object.
 */
- (void)setDelegate:(id<SLIndoorLocationManagerDelegate>)delegate;

/// @name Start/Stop location updates

/**
 Start location updates. Must be called to start location updates after initializing the class.
 */
- (void)startUpdatingLocation;

/**
 Stops location updates (both real and mockup locations). To start positioning again, use SLIndoorLocationManager::startUpdatingLocation.
 */
- (void)stopUpdatingLocation;

/**
 This function can be called to simulate a position for testing purposes when testing off site. Observe that this function can only be used if [SLIndoorLocationManager startUpdatingLocation] has not been called.
 
 @param locationStateArray An array of SLLocationState.
 @param timeInterval A time interval in seconds between location updates.
 */
- (void)startMockupLocationWithLocationStateArray:(NSArray *)locationStateArray andTimeInterval:(double)timeInterval;

/**
 This function can be called to simulate a position for testing purposes when testing off site. Observe that this function can only be used if [SLIndoorLocationManager startUpdatingLocation] has not been called.
 
 @param locationState A SLLocationState.
 @param timeInterval A time interval in seconds between location updates.
 */
- (void)startMockupLocationWithLocationState:(SLLocationState *)locationState andTimeInterval:(double) timeInterval;


/**
 Stop mockup location updates. This function is also invoked if SLIndoorLocationManager::stopUpdatingLocation is called.
 */
- (void)stopUpdatingMockupLocation;

/// @name Getter/Setter

/**
 Step length in [m] is specified using this function. Since different users have different 
 steplengths, this should be possible to set.
 
 @param stepLength Step length in meters.
 */
- (void)setStepLength:(double)stepLength;

/**
 Check if bluetooth is powered on.
 
 @return YES if BLE is enabled.
 */
- (BOOL)isBleEnabled;

/**
 @return Current steplength in meters.
 */
- (double)stepLength;

/**
 @return The map ID of the loaded map.
 */
- (NSString *)getMapId;

/**
 @return The map version ID of the loaded map.
 */
- (NSString *)getMapVersionId;

/// @name Heading calibration

/**
 Set if the calibration display popped up by iOS should be shown.
 
 @param displayCalibration Set to true if the calibration display should be shown, false otherwise.
 */
- (void)shouldDisplayHeadingCalibration:(BOOL)displayCalibration;

/// @name Geofencing/Geomessenger

/**
 @return The geofencing manager, used to create alerts when the user enters specific areas.
 */
- (id<SLGeofencing>)getGeofencingManager;

/**
 @return the geomessenger manager, used to recieve notifications when the user enters specific areas defined on our servers.
 */
- (id<SLGeomessenger>)getGeomessengerManager;

/// @name Shortest path

/**
 Get shortest path between two locations.
 
 @warning Note that this function is mainly for demonstrating a possible user navigation feature. Please contact SenionLab if you plan to use this feature in your app.
 
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
