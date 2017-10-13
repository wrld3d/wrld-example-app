//
//  SSIGeoMessengerApiDelegate.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIGeoMessengerApi;
@class SSIGeoMessengerZone;

/**
 This delegate protocol allows for the receiver to get notified about any GeoMessenger events.
 
 The methods of your delegate object are called from the main queue.
 */
@protocol SSIGeoMessengerApiDelegate <NSObject>

@optional
/**
 This method is called whenever the user enters a zone.
 
 @param geoMessengerApi The instance that generated the event.
 @param geoMessengerZone The zone.
 */
- (void)geoMessengerApi:(nonnull SSIGeoMessengerApi *)geoMessengerApi didEnterZone:(nonnull SSIGeoMessengerZone *)geoMessengerZone NS_SWIFT_NAME(geoMessengerApi(_:didEnterZone:));

@optional
/**
 This method is called whenever the user exits a zone.
 
 @param geoMessengerApi The instance that generated the event.
 @param geoMessengerZone The zone.
 */
- (void)geoMessengerApi:(nonnull SSIGeoMessengerApi *)geoMessengerApi didExitZone:(nonnull SSIGeoMessengerZone *)geoMessengerZone NS_SWIFT_NAME(geoMessengerApi(_:didExitZone:));

@end
