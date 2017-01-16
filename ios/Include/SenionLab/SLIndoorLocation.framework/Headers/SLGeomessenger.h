//
//  SLGeoMessenger.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SLGeoMessengerDelegate;
@class SLGeoMessengerZone;

/**
 The domain for all errors from SLGeoMessenger.
 */
static NSString *const SLGeoMessengerErrorDomain = @"com.senionlab.slindoorlocation.slgeomessenger";

/**
 This enum descripe the error types you can expect from SLIndoorLocationManagerDelegate.geoMessenger:didFailWithError:
 */
typedef NS_ENUM(NSInteger, SLGeoMessengerErrorType) {
    
    /**
     SLIndoorLocationManager not loaded.
     */
    SLGeoMessengerErrorTypeLocationManagerNotLoaded,
    
    /**
     Missing internet connection.
     */
    SLGeoMessengerErrorTypeMissingInternetConnection,
    
    /**
     Failed server communication.
     */
    SLGeoMessengerErrorTypeFailedServerCommunication,
    
    /**
     Unknown error.
     */
    SLGeoMessengerErrorTypeUnknown
};

/**
 The SLGeoMessenger protocol provides support for manageing the GeoMessenger service. This protocol enables starting and stopping of the service and while the service is started, it can also provide all the GeoMessenger zones the device is currently in. For continous updates about GeoMessenger, use SLGeoMessengerDelegate and add your delegate with this protocol. This will enables direct callbacks when entering and leaving zones.
 
 ### Note
 
 This protocol and its service can only be used when SLIndoorLocationManager is started, and you have got a callback to [SLIndoorLocationManagerDelegate didFinishLoadingManager]. Also, do not forget to stop the service when you do not want to use it any more, e.g. when navigating away from the map.
 */
@protocol SLGeoMessenger <NSObject>

/// @name Lifecycle

/**
 @abstract Start SLGeoMessenger.
 
 @discussion If already started this will not do anyting. If SLIndoorLocationManager is not loaded, this method will only send an SLGeoMessengerErrorTypeLocationManagerNotLoaded error to SLIndoorLocationManagerDelegate.geoMessenger:didFailWithError: and not do any thing more.
 */
- (void)start;

/**
 @abstract Stop SLGeoMessenger.
 */
- (void)stop;

/**
 @abstract Checks if SLGeoMessenger is started and ready to be used.
 
 @return true if the SLGeoMessenger is loaded and started.
 */
- (BOOL)isStarted;

/// @name Current zones

/**
 @abstract This method returns all the zones the user is currently in.
 
 @discussion If the user isn't in a zone, or if there haven't been any locaiton update yet, it returns an empty array.
 
 @return an NSArray with all SLGeoMessengerZone the user is currently in.
 */
- (NSArray<SLGeoMessengerZone *> *)currentZones;

/// @name Delegate

/**
 @abstract Use this method to get updates to the delegate when entering and leaving monitored areas.
 
 @param delegate The delegate object.
 */
- (void)addDelegate:(id<SLGeoMessengerDelegate>)delegate;

/**
 @abstract Use this method to stop get updates to the delegate.
 
 @param delegate The delegate object.
 */
- (void)removeDelegate:(id<SLGeoMessengerDelegate>)delegate;

@end
