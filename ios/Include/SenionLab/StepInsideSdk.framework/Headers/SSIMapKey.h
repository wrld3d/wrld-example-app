//
//  SSIMapKey.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class represent a map key.
 */
@interface SSIMapKey : NSObject

/**
 The value of the map key.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *value;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with an map key as a string.
 
 @param value The value of the map key.
 */
- (nonnull instancetype)initWithValue:(nonnull NSString *)value;

/**
 Method to check if two instances of `SSIMapKey` are equal.
 
 @param mapKey The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToMapKey:(nullable SSIMapKey *)mapKey;

@end
