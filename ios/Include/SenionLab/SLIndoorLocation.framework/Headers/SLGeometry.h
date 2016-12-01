//
//  SLGeometry.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SLGeometryId;

/**
 Protocol used by all areas that should be monitored in geofencing.
 */
@protocol SLGeometry <NSObject>

/// @name Methods

/**
 @return Get the id for this area.
 */
- (SLGeometryId *)getGeometryId;

@end
