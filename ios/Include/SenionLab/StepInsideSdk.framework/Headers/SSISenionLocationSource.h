//
//  SSISenionLocationSource.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSILocationSource.h"

@class SSIMapKey;
@class SSISenionLocationSourceDebugInformation;

/**
 This class represents the Senion positioning system.
 */
@interface SSISenionLocationSource : NSObject <SSILocationSource>

/**
 The map key.
 */
@property (nonnull, nonatomic, strong, readonly) SSIMapKey *mapKey;

/**
 The debug information, if present.
 */
@property (nullable, nonatomic, strong, readonly) SSISenionLocationSourceDebugInformation *debugInformation;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with a `SSIMapKey`.
 
 @param mapKey The map key.
 */
- (nonnull instancetype)initWithMapKey:(nonnull SSIMapKey *)mapKey;

/**
 Initializes this class with a `SSIMapKey` and an optional `SSISenionLocationSourceDebugInformation`.
 
 @param mapKey The map key.
 @param debugInformation The debug information, may be nil.
 */
- (nonnull instancetype)initWithMapKey:(nonnull SSIMapKey *)mapKey
                      debugInformation:(nullable SSISenionLocationSourceDebugInformation *)debugInformation;

/**
 Method to check if two instances of `SSISenionLocationSource` are equal.
 
 @param locationSource The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToLocationSource:(nullable SSISenionLocationSource *)locationSource;

@end
