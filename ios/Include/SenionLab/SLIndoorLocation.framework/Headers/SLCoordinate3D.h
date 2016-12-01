//
//  SLCoordinate3D.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import "SLCoordinate2D.h"
#import "FloorNr.h"

/**
 This class contains a geographical coordinate using the WGS 84 reference frame including a floorNr.
 */
@interface SLCoordinate3D : SLCoordinate2D

/// @name Initializers

/**
 Constructor.
 
 @param latitude Latitude in degrees. Positive value is north of the equator, negative south.
 @param longitude Longitude in degrees. Positive value is east of the meridian, negative west.
 @param floorNr Floor. Observe that this number should be seen as an ID rather than the actual floor number.
 */
- (instancetype)initWithLatitude:(double)latitude andLongitude:(double)longitude andFloorNr:(FloorNr)floorNr;

/**
 Constructor.
 
 @param coordinate A coordinate
 */
- (instancetype)initWithSLCoordinate3D:(SLCoordinate3D *)coordinate;

- (NSDictionary *)writeObjectToDictionary;

+ (SLCoordinate3D *)readObjectFromDictionary:(NSDictionary *)dict;

- (BOOL)isEqualToSLCoordinate3D:(SLCoordinate3D *)p withAccuracy:(double)tol;

/// @name Properties

/**
 Floor number
 */
@property (nonatomic) FloorNr floorNr;

@end
