//
//  SLGeoMessengerDelegate.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SLGeoMessenger;
@class SLGeoMessengerZone;

/**
 The methods declared by the UIScrollViewDelegate protocol allows the adopting delegate to respond to messages from the SLGeoMessenger protocol. The protocol contains methods responding to events occuring during the startup of the SLGeoMessenger service and methods for continious GeoMessenger zone events.
 
 ### Note
 
 Errors from [SLGeoMessengerDelegate geoMessenger:didFailWithError:] are declared in SLGeoMessengerErrorType. If you get SLGeoMessengerErrorTypeLocationManagerNotLoaded you must restart SLGeoMessenger your self. The other error types will trigger a timer and will try again later.
 */
@protocol SLGeoMessengerDelegate <NSObject>

/// @name Startup events.

/**
 @abstract Called when the SLGeoMessenger have loaded and started.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 */
- (void)geoMessengerDidStart:(id<SLGeoMessenger>)geoMessenger;

/**
 @abstract Called if any error occur during the startup of SLGeoMessenger. The possible error is defined in SLGeoMessengerErrorType.
 
 @discussion If you get SLGeoMessengerErrorTypeLocationManagerNotLoaded you must restart SLGeoMessenger your self. The other error types will trigger a timer and will try again later.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 @param error the NSError occured, defined in SLGeoMessengerErrorType
 */
- (void)geoMessenger:(id<SLGeoMessenger>)geoMessenger didFailWithError:(NSError *)error;

/// @name GeoMessenger events

/**
 @abstract Called when a SLGeoMessengerZone is entered.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 @param zone The SLGeoMessengerZone entered.
 */
- (void)geoMessenger:(id<SLGeoMessenger>)geoMessenger didEnterZone:(SLGeoMessengerZone *)zone;

/**
 @abstract Called when a SLGeoMessengerZone is left.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 @param zone The SLGeoMessengerZone left.
 */
- (void)geoMessenger:(id<SLGeoMessenger>)geoMessenger didLeaveZone:(SLGeoMessengerZone *)zone;

@end
