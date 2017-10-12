//
//  SSIMockHeadingEvent.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSIMockPositioningEvent.h"

@class SSIHeading;

/**
 This class represent a mock heading event.
 */
@interface SSIMockHeadingEvent : NSObject <SSIMockPositioningEvent>

/**
 The mock heading.
 */
@property (nonnull, nonatomic, strong, readonly) SSIHeading *heading;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with a heading and a delay.
 
 @param heading The mock heading.
 @param delayTimeInterval The delay to be applied before emitting the event.
 */
- (nonnull instancetype)initWithHeading:(nonnull SSIHeading *)heading
                      delayTimeInterval:(NSTimeInterval)delayTimeInterval;

@end
