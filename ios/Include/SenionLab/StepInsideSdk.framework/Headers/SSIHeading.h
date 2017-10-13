//
//  SSIHeading.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class represent a heading emitted by `SSIPositioningApi`.
 
 The heading angle is measured in degrees clockwise from geographic north. Values are in the range of 0 up to 360.
 */
@interface SSIHeading : NSObject

/**
 The angle in degrees.
 */
@property (nonatomic, readonly) double angle;

/**
 The time when the heading was determined.
 */
@property (nonnull, nonatomic, strong, readonly) NSDate *time;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class.
 
 @param angle The angle in degrees.
 @param time The time when the heading was determined.
 */
- (nonnull instancetype)initWithAngle:(double)angle
                                 time:(nonnull NSDate *)time;

/**
 Method to check if two instances of `SSIHeading` are equal.
 
 @param heading The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToHeading:(nullable SSIHeading *)heading;

@end
