//
//  SSISensors.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This utility class contains helper method for the sensors on the device.
 */
@interface SSISensors : NSObject

/// :nodoc:
+ (nonnull instancetype)alloc UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Checks if BLE is enabled on the device.
 */
@property (readonly) BOOL isBleEnabled;

/**
 Displays the system prompt requesting the user for "When In Use" Core Location authorization.
 */
+ (void)requestCoreLocationWhenInUseAuthorization;

/**
 Displays the system prompt requesting the user for "Always" Core Location authorization.
 */
+ (void)requestCoreLocationAlwaysAuthorization;

/**
 Sets if the iOS calibration display should be shown when requested.
 
 @param displayCalibration Set to `YES` if the calibration display should be shown, `NO` otherwise.
 */
+ (void)shouldDisplayHeadingCalibration:(BOOL)displayCalibration;

@end
