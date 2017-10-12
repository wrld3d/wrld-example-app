//
//  SSIMockLocationAvailabilityEvent.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSIMockPositioningEvent.h"
#import "SSILocationAvailability.h"

/**
 This class represent a mock location availability event.
 */
@interface SSIMockLocationAvailabilityEvent : NSObject <SSIMockPositioningEvent>

/**
 The mock location availability.
 */
@property (nonatomic, readonly) SSILocationAvailability locationAvailability;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with a location availability and a delay.
 
 @param locationAvailability The mock location availability.
 @param delayTimeInterval The delay to be applied before emitting the event.
 */
- (nonnull instancetype)initWithLocationAvailability:(SSILocationAvailability)locationAvailability
                                   delayTimeInterval:(NSTimeInterval)delayTimeInterval;

@end
