//
//  SSIFloorId.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class represent a floor ID which is used to identify a floor.
 */
@interface SSIFloorId : NSObject

/**
 The value of the floor ID.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *value;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with an floor ID as a string.
 
 @param value The value of the floor ID.
 */
- (nonnull instancetype)initWithValue:(nonnull NSString *)value;

/**
 Method to check if two instances of `SSIFloorId` are equal.
 
 @param floorId The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToFloorId:(nullable SSIFloorId *)floorId;

@end
