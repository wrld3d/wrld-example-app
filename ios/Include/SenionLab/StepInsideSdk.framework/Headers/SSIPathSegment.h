//
//  SSIPathSegment.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSILocationCoordinates;

/**
 This class represent a path segment between two location coordinates.
 */
@interface SSIPathSegment : NSObject

/**
 The start location coordinates.
 */
@property (nonnull, nonatomic, strong, readonly) SSILocationCoordinates *startCoordinates;

/**
 The end location coordinates.
 */
@property (nonnull, nonatomic, strong, readonly) SSILocationCoordinates *endCoordinates;

/**
 The length of the segment in meters.
 */
@property (nonatomic, readonly) double length;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with a start and end coordinates.
 
 @param startCoordinates The start location coordinates.
 @param endCoordinates The end location coordinates.
 */
- (nonnull instancetype)initWithStartCoordinates:(nonnull SSILocationCoordinates *)startCoordinates
                                  endCoordinates:(nonnull SSILocationCoordinates *)endCoordinates;

/**
 Method to check if two instances of `SSIPathSegment` are equal.
 
 @param pathSegment The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToPathSegment:(nullable SSIPathSegment *)pathSegment;

@end
