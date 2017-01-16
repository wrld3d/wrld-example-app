//
//  SLGeofencingListener.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLGeometry.h"

/**
 @protocol SLGeofencingDelegate
 To receive notifications for geofencing, this protocol must be implemented.
 */
@protocol SLGeofencingDelegate <NSObject>
/**
 Called when an area is entered.
 @param geometry Area that is detected.
 */
- (void) didEnterGeometry:(id<SLGeometry>)geometry;

/**
 Called when an area is left.
 @param geometry Area that is detected.
 */
- (void) didLeaveGeometry:(id<SLGeometry>)geometry;
@end
