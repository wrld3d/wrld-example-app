//
//  SLIndoorLocationManagerDelegate.h
//  SLIndoorLocationManager
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLIndoorLocationEnums.h"

@class SLCoordinate3D;
@class SLIndoorLocationManager;
@class SLLocationSource;

/**
 The methods declared by the SLIndoorLocationDelegate protocol allows the adopting delegate respond to messages from the SLIndoorLocationManager class. The protocol contains methods responding to events occuring during the startup of SLIndoorLocationManager and methods for continious locaiton updates.
 */
@protocol SLIndoorLocationManagerDelegate <NSObject>

/// @name Location manager loaded

@optional
/**
 Tells the delegate when the location manager have finished loading. (Optional)
 */
- (void)didFinishLoadingManager;

/// @name Location updates

@required
/**
 Updates the delegate with the new location of the device together with an uncertainty radius of the location in meters.
 
 Location updates will not occur unless [[SLIndoorLocationManager getLocationAvailability:]](../Classes/SLIndoorLocationManager.html#/c:objc(cs)SLIndoorLocationManager(im)getLocationAvailability) returns [SLLocationAvailabilityAvailable](../Enums/SLLocationAvailability.html#/c:@E@SLLocationAvailability@SLLocationAvailabilityAvailable)
 
 @param location The location of the device as SLCoordinate3D.
 @param uncertaintyRadius The uncertainty radius of the users location as a double.
 */
- (void)didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)uncertaintyRadius;

@optional
/**
 Updates the delegate with the new location of the device together with an uncertainty radius of the location in meters. This method also provides a locationSource with information about the location, e.g. the Map Key.
 
 Location updates will not occur unless [[SLIndoorLocationManager getLocationAvailability:]](../Classes/SLIndoorLocationManager.html#/c:objc(cs)SLIndoorLocationManager(im)getLocationAvailability) returns [SLLocationAvailabilityAvailable](../Enums/SLLocationAvailability.html#/c:@E@SLLocationAvailability@SLLocationAvailabilityAvailable)
 
 @param location The location of the device as SLCoordinate3D.
 @param uncertaintyRadius The uncertainty radius of the users location as a double.
 @param locationSource The lcoation source as SLLocationSource.
 */
- (void)didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)uncertaintyRadius locationSource:(SLLocationSource *)locationSource;

@optional
/**
 Updates the delegate when the location source has changed. This method provides the new locationSource with information about the location, e.g. the Map Key.
 
 @param locationSource The location source as SLLocationSource.
 */
- (void)didUpdateLocationSource:(SLLocationSource *)locationSource;

@required
/**
 Tells the delegate that the location availability have changed.
 
 @param locationAvailability The location availability status as [SLLocationAvailability](../Enums/SLLocationAvailability.html).
 */
- (void)didUpdateLocationAvailability:(SLLocationAvailability)locationAvailability;

@optional
/**
 @warning The use of this method have been deprecated and will be removed in a future release of the SDK. Instead use didUpdateLocation:withUncertainty: and didUpdateLocationAvailability:.
 
 Updates the delegate with the latitude/longitude of the device with an uncertainty radius (meters) and status.
 
 @param location The location of the device.
 @param radius The uncertainty radius of the devices location.
 @param locationStatus The status of the location.
 */
- (void)didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)radius andStatus:(SLLocationStatus)locationStatus __attribute__((deprecated));

@required
/**
 Updates the delegate with the new estimated heading of the device and the status of the heading.
 Heading is defined as clock-wise orientation relative north expressed in degrees in the range [0,360[.
 Status false indicates that the compass is uncalibrated or there is strong interference from local magnetic fields.
 
 @param heading The heading of the user.
 @param status The status of the heading.
 */
- (void)didUpdateHeading:(double)heading withStatus:(BOOL)status;

@required
/**
 Updates the delegate with the motion state of the device.
 
 @param motionState The motion state of the device.
 */
- (void)didUpdateMotionType:(SLMotionState)motionState;

/// @name Error callbacks

@required
/**
 Tells the delegate if internet connection is not working.
 
 @param error The corresponding error.
 */
- (void)didFailInternetConnectionWithError:(NSError *)error;

@required
/**
 Tells the delegate if invalid Customer ID or Map Key is used in the SDK.
 
 @param error The corresponding error.
 */
- (void)didFailInvalidIds:(NSError *)error;

@required
/**
 Tells the delegate if device has not authorized use of location status. This is a serious call, since the location might not be available.
 */
- (void)didFailLocationAuthorizationStatus;

@optional
/**
 Tells the delegate if any error occur while scanning bluetooth. (Optional)
 */
- (void)didFailScanningBT;

@end
