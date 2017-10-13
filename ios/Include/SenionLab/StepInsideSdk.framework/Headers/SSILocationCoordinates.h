//
//  SSILocationCoordinates.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIFloorId;

/**
 This class contains the coordinates required to locate a position, with an optional floor ID.
 */
@interface SSILocationCoordinates: NSObject

/**
 The latitude coordinate.
 */
@property (nonatomic, readonly) double latitude;

/**
 The longitude coordinate.
 */
@property (nonatomic, readonly) double longitude;

/**
 The floor ID, if present.
 */
@property (nullable, nonatomic, strong, readonly) SSIFloorId *floorId;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with a pair of coordinates.
 
 @param latitude The latitude coordinate.
 @param longitude The longitude coordinate.
 */
- (nonnull instancetype)initWithLatitude:(double)latitude
                               longitude:(double)longitude;

/**
 Initializes this class with a pair of coordinates and an optional floor ID.
 
 @param latitude The latitude coordinate.
 @param longitude The longitude coordinate.
 @param floorId The floor ID, may be nil.
 */
- (nonnull instancetype)initWithLatitude:(double)latitude
                               longitude:(double)longitude
                                 floorId:(nullable SSIFloorId *)floorId;

/**
 Calculates the distance in meters to another pair of location coordinates. Does not account for locations being on different floors.
 
 @param locationCoordinates The other location coordinates.
 
 @return The distance in meters.
 */
- (double)horizontalDistanceToLocationCoordinates:(nonnull SSILocationCoordinates *)locationCoordinates;

/**
 Method to check if two instances of `SSILocationCoordinates` are equal.
 
 @param locationCoordinates The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToLocationCoordinates:(nullable SSILocationCoordinates *)locationCoordinates;

/**
 Method to check if two instances of `SSILocationCoordinates` are near of each other with an accuracy.
 
 @param locationCoordinates The other instance.
 @param accuracy The accuracy.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isNearOfLocationCoordinates:(nullable SSILocationCoordinates *)locationCoordinates
                       withAccuracy:(double)accuracy;

@end
