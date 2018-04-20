//
//  SSIPositioningApiDelegate.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSILocationAvailability.h"
#import "SSIMotionType.h"
#import "SSIHeadingAvailability.h"

@class SSIPositioningApi;
@class SSILocation;
@class SSIHeading;
@protocol SSILocationSource;

/**
 This delegate protocol allows for the receiver to get notified about any Positioning events.
 
 The methods of your delegate object are called from the main queue.
 */
@protocol SSIPositioningApiDelegate <NSObject>

@optional
/**
 This method is called whenever a new location has been determined.
 
 @param positioningApi The instance that generated the event.
 @param location The location.
 */
- (void)positioningApi:(nonnull SSIPositioningApi *)positioningApi didUpdateLocation:(nonnull SSILocation *)location;

@optional
/**
 This method is called whenever a new heading has been determined.
 
 @param positioningApi The instance that generated the event.
 @param heading The heading.
 */
- (void)positioningApi:(nonnull SSIPositioningApi *)positioningApi didUpdateHeading:(nonnull SSIHeading *)heading;

@optional
/**
 This method is called whenever a new heading availability has been determined.
 
 @param positioningApi The instance that generated the event.
 @param headingAvailability The heading availability.
 */
- (void)positioningApi:(nonnull SSIPositioningApi *)positioningApi didUpdateHeadingAvailability:(SSIHeadingAvailability)headingAvailability;

@optional
/**
 This method is called whenever a new location availability has been determined.
 
 @param positioningApi The instance that generated the event.
 @param locationAvailability The location availability.
 */
- (void)positioningApi:(nonnull SSIPositioningApi *)positioningApi didUpdateLocationAvailability:(SSILocationAvailability)locationAvailability;

@optional
/**
 This method is called whenever a new location source has been determined.
 
 @param positioningApi The instance that generated the event.
 @param locationSource The location source.
 */
- (void)positioningApi:(nonnull SSIPositioningApi *)positioningApi didUpdateLocationSource:(nonnull id<SSILocationSource>)locationSource;

@optional
/**
 This method is called whenever a motion type of the user has been determined.
 
 @param positioningApi The instance that generated the event.
 @param motionType The motion type.
 */
- (void)positioningApi:(nonnull SSIPositioningApi *)positioningApi didUpdateMotionType:(SSIMotionType)motionType;

@end
