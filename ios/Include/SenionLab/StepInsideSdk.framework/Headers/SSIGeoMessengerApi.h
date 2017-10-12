//
//  SSIGeoMessengerApi.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SSIGeoMessengerApiDelegate;
@class SSIGeoMessengerZone;

/**
 This class provides access to the GeoMessenger API. This API has a method for all current zones and enables access to the `SSIGeoMessengerApiDelegate`.
 */
@interface SSIGeoMessengerApi : NSObject

/**
 An array of all zones that the user is currently inside of.
 */
@property (nonnull, readonly) NSArray<SSIGeoMessengerZone *> *currentZones;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Adds a `SSIGeoMessengerApiDelegate` delegate.
 
 @param delegate The receiving delegate.
 */
- (void)addDelegate:(nonnull id<SSIGeoMessengerApiDelegate>)delegate NS_SWIFT_NAME(addDelegate(_:));

/**
 Removes a `SSIGeoMessengerApiDelegate` delegate.
 
 @param delegate The receiving delegate.
 */
- (void)removeDelegate:(nonnull id<SSIGeoMessengerApiDelegate>)delegate NS_SWIFT_NAME(removeDelegate(_:));

@end
