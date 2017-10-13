//
//  SSIApiKey.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class represent an API key. Used by the `SSIStepInsideSdkManagerConfig` when configuring `SSIStepInsideSdkManager`.
 
 API keys may be managed on our [Developer portal](https://developer.senion.com).
 */
@interface SSIApiKey : NSObject

/**
 The value of the API key.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *value;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with an API key as a string.
 
 @param value The value of the API key.
 */
- (nonnull instancetype)initWithValue:(nonnull NSString *)value;

/**
 Method to check if two instances of `SSIApiKey` are equal.
 
 @param apiKey The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToApiKey:(nullable SSIApiKey *)apiKey;

@end
