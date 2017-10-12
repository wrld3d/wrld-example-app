//
//  SSIStepInsideSdkManager.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIStepInsideSdkManagerConfig;
@class SSIStepInsideSdk;

/**
 This class is responsible for initializing the SDK and activating the resources used by the SDK.
 
 When calling the method `loadSdk`, it will initialize the SDK internally. 
 
 After `loadSdk` have been called, you can call any of the attach-methods depending on your need.
 
 - Note: You always need to keep a reference to this class to keep it alive. If this class gets deallocated, it will terminate the SDK. Also, you can only have one instance of this class at the same time.
 
 */
@interface SSIStepInsideSdkManager : NSObject

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes the manager and fetches the configuration in the provided block.
 
 - Warning: If you have not provided all required configuration, this method will throw `NSInternalInconsistencyException`.
 
 @param config Configuration block.
*/
+ (nonnull instancetype)managerWithConfig:(nonnull void (^)(SSIStepInsideSdkManagerConfig * _Nonnull config))config;

/**
 Load the internal SDK engine. Calling this method will allow the SDK to initialize all resources required. This includes downloading all the data required to start the positioning engine later.
 
 Must be called before either `attachForeground` or `attachBackground`.
*/
- (void)loadSdk;

/**
 Creates an `SSIStepInsideSdk` in high performance mode and attaches it to the internal SDK engine.
 
 Using this attach method will put the internal positioning engine in high performance mode. This is the default mode.
 
 - Warning: If you have not called `loadSdk` before calling this method, it will throw `NSInternalInconsistencyException`.
 
 @return An instance of `SSIStepInsideSdk`.
 */
- (nonnull SSIStepInsideSdk *)attachHighPerformanceMode;

/**
 Creates an `SSIStepInsideSdk` in power save mode and attaches it to the internal SDK engine.
 
 Using this attach method will put the internal positioning engine in power save mode, as long as no `SSIStepInsideSdk` in high performance mode is attached.
 
 Note that this mode will reduce the number of scans and disable use of motion sensors. This will in turn decrease the accuracy of the received positions from the SDK.
 
 - Warning: If you have not called `loadSdk` before calling this method, it will throw `NSInternalInconsistencyException`.
 
 @return An instance of `SSIStepInsideSdk`.
 */
- (nonnull SSIStepInsideSdk *)attachPowerSaveMode;

@end
