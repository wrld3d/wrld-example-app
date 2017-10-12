//
//  SSIMockLocationEvent.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSIMockPositioningEvent.h"

@class SSILocation;

/**
 This class represent a mock location event.
 */
@interface SSIMockLocationEvent : NSObject <SSIMockPositioningEvent>

/**
 The mock location.
 */
@property (nonnull, nonatomic, strong, readonly) SSILocation *location;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with a location and a delay.
 
 @param location The mock location.
 @param delayTimeInterval The delay to be applied before emitting the event.
 */
- (nonnull instancetype)initWithLocation:(nonnull SSILocation *)location
                       delayTimeInterval:(NSTimeInterval)delayTimeInterval;

@end
