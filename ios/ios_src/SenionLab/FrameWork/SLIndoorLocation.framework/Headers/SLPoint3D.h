//
//  SLPoint3D.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import "SLPoint2D.h"
#import "FloorNr.h"

/**
 * SLPoint3D is used to give a location in a metric coordinate system with floor number.
 */
@interface SLPoint3D : SLPoint2D

/// @name Initializers

/**
 Constructor.
 
 @param x x-coordinate in meters.
 @param y y-coordinate in meters.
 @param floorNr Floor number.
 */
- (instancetype)initWithX:(double)x andY:(double)y andFloorNr:(FloorNr)floorNr;

/**
 Constructor.
 
 @param point A point in 2D.
 @param floorNr Floor number.
 */
- (instancetype)initWithSLPoint2D:(SLPoint2D *)point andFloorNr:(FloorNr)floorNr;

/**
 Constructor.
 
 @param point A point in 3D.
 */
- (instancetype)initWithSLPoint3D:(SLPoint3D *)point;

/// @name Properties

/**
 Floor number
 */
@property (nonatomic) FloorNr floorNr;

@end
