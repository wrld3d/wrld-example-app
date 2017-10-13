//
//  SSILocation.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIFloorId;
@class SSILocationCoordinates;
@protocol SSILocationSource;
@class SSILocationCoordinates;

/**
 This class represent a location emitted by `SSIPositioningApi`.
 
 Apart from the usual coordinates a location also has a source in the form of a `SSILocationSource. The type of source will depend upon which underlying positioning system provided the location fix.
 */
@interface SSILocation : NSObject

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

/**
 The uncertainty radius of the location in meters.
 */
@property (nonatomic, readonly) double uncertaintyRadius;

/**
 The location source.
 */
@property (nonnull, nonatomic, strong, readonly) id<SSILocationSource> source;

/**
 The time when the location was determined.
 */
@property (nonnull, nonatomic, strong, readonly) NSDate *time;

/**
 A `SSILocationCoordinates` with the same coordinate values as the location.
 */
@property (nonnull, readonly) SSILocationCoordinates *coordinates;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class.
 
 @param latitude The latitude coordinate.
 @param longitude The longitude coordinate.
 @param floorId The floor ID, may be nil.
 @param uncertaintyRadius The uncertainty radius of the location in meters.
 @param source The location source.
 @param time The time when the location was determined.
 */
- (nonnull instancetype)initWithLatitude:(double)latitude
                               longitude:(double)longitude
                                 floorId:(nullable SSIFloorId *)floorId
                       uncertaintyRadius:(double)uncertaintyRadius
                                  source:(nonnull id<SSILocationSource>)source
                                    time:(nonnull NSDate *)time;

/**
 Calculates the distance in meters to another location. Does not account for locations being on different floors.
 
 @param location The other location.
 
 @return The distance in meters.
 */
- (double)horizontalDistanceToLocation:(nonnull SSILocation *)location;

/**
 Method to check if two instances of `SSILocation` are equal.
 
 @param location The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToLocation:(nullable SSILocation *)location;

@end
