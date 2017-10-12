//
//  SSIStepInsideSdk.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SSIStepInsideSdkStatusDelegate;
@class SSIPositioningApi;
@class SSIGeoMessengerApi;
@class SSIWayfindingApi;

/**
 This class is the main class for accessing the SDK and its subsystems.
 */
@interface SSIStepInsideSdk : NSObject

/**
 This methods allows for access to the Positioning API.
 
 The Positioning API is used to subscribe to positioning events.
 */
@property (nonnull, nonatomic, strong, readonly) SSIPositioningApi *positioning;

/**
 This methods allows for access to the GeoMessenger API.
 
 The GeoMessenger API is used to subscribe to events whenever the user enters or exits predefined areas on the map.
 */
@property (nonnull, nonatomic, strong, readonly) SSIGeoMessengerApi *geoMessenger;

/**
 This methods allows for access to the WayFinding API.
 
 The WayFinding API is used to calculate paths between two points on the map.
 */
@property (nonnull, nonatomic, strong, readonly) SSIWayfindingApi *wayfinding;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Adds a `SSIStepInsideSdkStatusDelegate` delegate.
 
 @param delegate The receiving status delegate.
 */
- (void)addStatusDelegate:(nonnull id<SSIStepInsideSdkStatusDelegate>)delegate NS_SWIFT_NAME(addStatusDelegate(_:));

/**
 Removes a `SSIStepInsideSdkStatusDelegate` delegate.
 
 @param delegate The receiving status delegate.
 */
- (void)removeStatusDelegate:(nonnull id<SSIStepInsideSdkStatusDelegate>)delegate NS_SWIFT_NAME(removeStatusDelegate(_:));

/**
 Starts all the SDK components.
 
 If already started, any call to this method will be ignored.
 */
- (void)start;

/**
 Stops all the SDK components.
 
 If already stopped, any call to this method will be ignored.
 */
- (void)stop;

@end
