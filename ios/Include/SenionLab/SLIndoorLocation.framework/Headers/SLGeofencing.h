//
//  SLGeofencing.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLGeofencingDelegate.h"

/**
 The SLGeofencing protocol is used by classes that detects when certain areas are entered/left.
 */

@protocol SLGeofencing <NSObject>

/// @name Delegate

/**
 Use this method to subscribe to updates when entering leaving monitored areas.
 
 @param delegate The delegate object.
 */
- (void)addDelegate:(id<SLGeofencingDelegate>)delegate;

/**
 Unsubscribe from notifications.
 
 @param delegate The delegate object.
 */
- (void)removeDelegate:(id<SLGeofencingDelegate>)delegate;

/// @name Other methods

/**
 Add an area that should be monitored.
 
 @param geometry The geometry object to add.
 */
- (void)addGeometry:(id<SLGeometry>)geometry;

/**
 Add an array of areas that should be monitored.
 
 @param geometryArray An array of geometry objects to add.
 */
- (void)addGeometryArray:(NSArray *)geometryArray;

/**
 Remove an area that should not be monitored anymore.
 
 @param geometry The geometry object to remove.
 */
- (void)removeGeometry:(id<SLGeometry>)geometry;

/**
 Remove an array of areas that should not be monitored anymore.
 
 @param geometryArray An array of geometry objects to remove.
 */
- (void)removeGeometryArray:(NSArray *)geometryArray;

/**
 Remove all areas that was monitored.
 */
- (void)clearGeometryList;

@end
