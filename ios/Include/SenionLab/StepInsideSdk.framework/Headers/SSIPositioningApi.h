//
//  SSIPositioningApi.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSILocationAvailability.h"
#import "SSIMotionType.h"
#import "SSIHeadingAvailability.h"

@protocol SSIPositioningApiDelegate;
@class SSILocation;
@class SSIHeading;

/**
 This class provides access to the Positioning API. This API have methods for last known positioning data and enables access to the `SSIPositioningApiDelegate`.
 */
@interface SSIPositioningApi : NSObject

/**
 The last known location.
 
 May be nil before any location has been determined.
 */
@property (nullable, nonatomic, strong, readonly) SSILocation *lastLocation;

/**
 The last known heading.
 
 May be nil before any heading has been determined.
 */
@property (nullable, nonatomic, strong, readonly) SSIHeading *lastHeading;

/**
 The last known heading availability.
 
 Defaults to `SSIHeadingAvailabilityNotAvailable`.
 */
@property (nonatomic, readonly) SSIHeadingAvailability lastHeadingAvailability;

/**
 The last known location availability.
 
 Defaults to `SSILocationAvailabilityNotAvailable`.
 */
@property (nonatomic, readonly) SSILocationAvailability lastLoctionAvailability;

/**
 The last known motion type.
 
 Defaults to `SSIMotionTypeUnknown`.
 */
@property (nonatomic, readonly) SSIMotionType lastMotionType;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Adds a `SSIPositioningApiDelegate` delegate.
 
 @param delegate The receiving delegate.
 */
- (void)addDelegate:(nonnull id<SSIPositioningApiDelegate>)delegate NS_SWIFT_NAME(addDelegate(_:));

/**
 Removes a `SSIPositioningApiDelegate` delegate.
 
 @param delegate The receiving delegate.
 */
- (void)removeDelegate:(nonnull id<SSIPositioningApiDelegate>)delegate NS_SWIFT_NAME(removeDelegate(_:));

@end
