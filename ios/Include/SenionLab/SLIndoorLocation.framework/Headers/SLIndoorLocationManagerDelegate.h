//
//  SLIndoorLocationManagerDelegate.h
//  SLIndoorLocationManager
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLIndoorLocationEnums.h"

@class SLCoordinate3D;
@class SLIndoorLocationManager;

/**
 Callback functions for the delegate of the SLIndoorLocationManager.
 */
@protocol SLIndoorLocationManagerDelegate <NSObject>

/// @name Location manager loaded

/**
 Called when the location manager have finished loading.
 */
@optional
- (void) didFinishLoadingManager;

/// @name Location updates

/**
 Returns the latitude/longitude of the user with an uncertainty radius (meters) and status (true=confirmed, false=unconfirmed).
 
 @param location The location of the user.
 @param radius The uncertainty radius of the users location.
 @param locationStatus The status of the location.
 */
@required
- (void)didUpdateLocation:(SLCoordinate3D *)location withUncertainty:(double)radius andStatus:(SLLocationStatus)locationStatus;

/**
 Returns the estimated device heading and its status.
 Heading is defined as clock-wise orientation relative north expressed in degrees in the range [0,360[.
 Status false indicates that the compass is uncalibrated or there is strong interference from local magnetic fields.
 
 @param heading The heading of the user.
 @param status The status of the heading.
 */
@required
- (void) didUpdateHeading:(double)heading withStatus:(BOOL)status;

/**
 Returns the motion state of the user.
 
 @param motionState The motion state of the user.
 */
@required
- (void) didUpdateMotionType:(SLMotionState)motionState;

/// @name Error callbacks

/**
 Called if internet connection is not working.
 
 @param error The corresponding error.
 */
@required
- (void) didFailInternetConnectionWithError:(NSError *)error;

/**
 Called if invalid Customer ID or Map Key is used in the SDK.
 
 @param error The corresponding error.
 */
@required
- (void) didFailInvalidIds:(NSError *)error;

/**
 Called if user has not authorized use of location status. This is a serious call, since the location might not be available.
 */
@required
- (void) didFailLocationAuthorizationStatus;

/**
 Called if any error occur while scanning bluetooth.
 */
@optional
- (void) didFailScanningBT;

@end
