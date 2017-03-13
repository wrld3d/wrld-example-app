//
//  SLRectangle.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLGeometryId.h"
#import "SLCoordinate3D.h"
#import "SLGeometry.h"

/**
 Class used to define a geofencing area in form of a parallelogram.
 The coordinates that needs to be supplied is marked in the figure below.
 
 ![Image Alt](../img/parallelogram.jpg)
 */
@interface SLParallelogram : NSObject <SLGeometry>

/// @name Initializers

/**
 Constructor for SLParallelogram.
 
 @param geometryId Id used to identify a geometry, make sure that this is unique to be able identify which region that is detected.
 @param base Base coordinate of the parallelogram.
 @param edge1 The first edge of the parallelogram goes from the base to the edge1 coordinate.
 @param edge2 The second edge of the parallelogram goes from the base to the edge2 coordinate.
 */
- (instancetype)initWithId:(SLGeometryId *)geometryId andBase:(SLCoordinate3D *)base andEdge1:(SLCoordinate3D *)edge1 andEdge2:(SLCoordinate3D *)edge2;

@end
