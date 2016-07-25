//
//  SLGeomessenger.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SLGeomessengerDelegate;

/**
 The SLGeomessenger protocol is used by classes that detects when certain areas are entered/left.
 */
@protocol SLGeomessenger <NSObject>

/// @name Delegate

/**
 Use this method to subscribe to updates when entering and leaving monitored areas.
 
 @param delegate The delegate object.
 */
- (void)addDelegate:(id<SLGeomessengerDelegate>)delegate;

/**
 Unsubscribe from notifications.
 
 @param delegate The delegate object.
 */
- (void)removeDelegate:(id<SLGeomessengerDelegate>)delegate;

@end
