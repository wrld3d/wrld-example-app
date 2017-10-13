//
//  SSIStepInsideSdkManagerConfig.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIApiKey;
@class SSIMapKey;
@protocol SSIMockPositioningProvider;

/**
 This class is used to configurate the SDK. Do not initialize this class by yourself. Instead use the instance provided in the `SSIStepInsideSdkManager` initializer.
 
 Valid configurations:
 
 - When using the default positioning provider, an API key and at least one map key must be provided.
 - When using the mock positioning provider, it is optional to provide an API Key and map key. However, in order to be able to mock GeoMessenger and Wayfinding, an API key and one map key must be provided.
 
 - Note: The mock positioning provider can not be used together with the native positioning fallback.
 
 - Note: Only one map key can be used together with the mock positioning provider.
 */
@interface SSIStepInsideSdkManagerConfig : NSObject

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Specifies the API Key used to authenticate the SDK.
 */
- (void)withApiKey:(nonnull SSIApiKey *)apiKey;

/**
 Specifies the map key used by the positioning system.
 
 The map key can be accessed on our [Developer pages](https://developer.senion.com).
 
 Calling this method will override any earlier call to `withMapKeys`.
 */
- (void)withMapKey:(nonnull SSIMapKey *)mapKey;

/**
 Specifies the map keys used by the positioning system.
 
 The map key can be accessed on our [Developer pages](https://developer.senion.com).
 
 Calling this method will override any earlier call to `withMapKey`.
 */
- (void)withMapKeys:(nonnull NSArray<SSIMapKey *> *)mapKeys;

/**
 Enables the GeoMessenger functionality of the SDK.
 */
- (void)withGeoMessenger;

/**
 Specifies that a mock positioning provider shall be used instead of the real positioning engine.
 */
- (void)withMockPositioningProvider:(nonnull id<SSIMockPositioningProvider>)mockPositioningProvider;

/**
 Enables the SDK to fallback on Core Location positioning system when the SDK is unable to get a good location fix.
 */
- (void)withNativePositioningFallback;

@end
