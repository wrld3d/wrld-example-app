//
//  SLPixelPoint3D.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import "SLPixelPoint2D.h"
#import "FloorNr.h"

/**
 This class contains a pixel point including a floorNr.
 */
@interface SLPixelPoint3D : SLPixelPoint2D

/// @name Initializers

/**
 Constructor.
 @param x point in pixels
 @param y point in pixels
 @param floorNr of point
 */
- (instancetype)initWithX:(double)x andY:(double)y andFloorNr:(FloorNr)floorNr;

/// @name Properties

/**
 FloorNr
 */
@property (nonatomic) FloorNr floorNr;

@end
