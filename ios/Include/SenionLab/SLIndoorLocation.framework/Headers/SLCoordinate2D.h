//
//  SLCoordinate2D.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//
//

#import <Foundation/Foundation.h>

/**
 This class contains a geographical coordinate using the WGS 84 reference frame.
 */
@interface SLCoordinate2D : NSObject

/// @name Initializers

/**
 Constructor.
 @param latitude Latitude in degrees. Positive value is north of the equator, negative south.
 @param longitude Longitude in degrees. Positive value is east of the meridian, negative west.
 */
- (instancetype)initWithLatitude:(double)latitude andLongitude:(double)longitude;

- (NSDictionary *)writeObjectToDictionary;

+ (SLCoordinate2D *)readObjectFromDictionary:(NSDictionary *)dict;

- (BOOL)isEqualToSLCoordinate2D:(SLCoordinate2D *)p withAccuracy:(double)tol;

/// @name Properties

/**
 Latitude in degrees. Positive value is north of the equator, negative south.
 */
@property (nonatomic) double latitude;

/**
 Longitude in degrees. Positive value is east of the meridian, negative west.
 */
@property (nonatomic) double longitude;

@end
