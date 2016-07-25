//
//  SLPixelPoint2D.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class contains a pixel point.
 */
@interface SLPixelPoint2D : NSObject

/// @name Initializers

/**
 Constructor.
 @param x point in pixels
 @param y point in pixels
 */
- (instancetype)initWithX:(double)x andY:(double)y;

/// @name Properties

/**
 x point in pixels
 */
@property (nonatomic) double x;

/**
 y point in pixels
 */
@property (nonatomic) double y;

@end
