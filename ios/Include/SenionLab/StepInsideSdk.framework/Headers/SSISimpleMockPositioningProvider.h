//
//  SSISimpleMockPositioningProvider.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSIMockPositioningProvider.h"

@protocol SSIMockPositioningEvent;
@class SSILocation;

/**
 This class is a simple implementation of the `SSIMockPositioningProvider` that only yields mock location events to be emitted at a fixed interval.
 */
@interface SSISimpleMockPositioningProvider : NSObject <SSIMockPositioningProvider>

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with an array of locations and a time interval.
 
 @param locations The mock locations.
 @param delayTimeInterval The delay to be applied before emitting an event.
 */
- (nonnull instancetype)initWithLocations:(nonnull NSArray<SSILocation *> *)locations
                        delayTimeInterval:(NSTimeInterval)delayTimeInterval;

@end
