//
//  SLPoint2D.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * SLPoint2D is used to give a location in a metric coordinate system including a floorNr.
 */
@interface SLPoint2D : NSObject

/// @name Initializers

/**
 Constructor.
 
 @param x x-coordinate in meters.
 @param y y-coordinate in meters.
 */
- (instancetype)initWithX:(double)x andY:(double)y;

/**
 Constructor.
 
 @param point A point
 */
- (instancetype)initWithSLPoint2D:(SLPoint2D *)point;

/// @name Properties

/**
 x-coordinate in meters.
 */
@property (nonatomic) double x;

/**
 y-coordinate in meters.
 */
@property (nonatomic) double y;

@end
