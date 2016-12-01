//
//  SLGeomessengerDelegate.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SLGeomessenger;

/**
 To receive notifications for geomessenger, this protocol must be implemented.
 */
@protocol SLGeomessengerDelegate <NSObject>

/// @name Methods

/**
 Called when a geomessenger area is entered.
 
 @param geomessenger The geomessenger object handling the area entered.
 @param title Title of the area entered.
 @param message Message of the area entered.
 */
- (void)geomessenger:(id<SLGeomessenger>)geomessenger didEnterGeomessageWithTitle:(NSString *)title andMessage:(NSString *)message;

/**
 Called when a geomessenger area is left.
 
 @param geomessenger The geomessenger object handling the area left.
 @param title Title of the area left.
 @param message Message of the area left.
 */
- (void)geomessenger:(id<SLGeomessenger>)geomessenger didLeaveGeomessageWithTitle:(NSString *)title andMessage:(NSString *)message;


@optional
/**
 Optional
 
 Called if anything goes wrong with loading of the geomessenger areas.
 
 @param geomessenger The geomessenger object which failed loading.
 */
- (void)geomessengerDidFailLoadingGeomessages:(id<SLGeomessenger>)geomessenger;

@end