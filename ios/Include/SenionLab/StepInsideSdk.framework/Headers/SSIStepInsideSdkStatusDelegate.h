//
//  SSIStepInsideSdkStatusDelegate.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIStepInsideSdk;

/**
 This delegate protocol allows for the receiver to get notified about any error that occurs in the SDK.
 
 The methods of your delegate object are called from the main queue.
 */
@protocol SSIStepInsideSdkStatusDelegate <NSObject>

@optional
/**
 This method is called whenever an error occur in the SDK. Please refer to `SSIStepInsideSdkErrorType` for posible errors.
 
 @param stepInsideSdk The instance that generated the event.
 @param error The error containing information about the error. Domain is `SSIStepInsideSdkErrorDomain` and code is of type `SSIStepInsideErrorType`.
 */
- (void)stepInsideSdk:(nonnull SSIStepInsideSdk *)stepInsideSdk didFailWithError:(nonnull NSError *)error NS_SWIFT_NAME(stepInsideSdk(_:didFailWithError:));

@end
