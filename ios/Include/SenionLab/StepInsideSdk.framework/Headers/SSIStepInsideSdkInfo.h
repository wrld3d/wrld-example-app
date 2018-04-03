//
//  SSIStepInsideSdkInfo.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class only provides metadata related to the SDK.
 */
@interface SSIStepInsideSdkInfo : NSObject

/// :nodoc:
+ (nonnull instancetype)alloc UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 The version of the SDK.
 */
@property (class, nonnull, nonatomic, strong, readonly) NSString *sdkVersion;

@end




