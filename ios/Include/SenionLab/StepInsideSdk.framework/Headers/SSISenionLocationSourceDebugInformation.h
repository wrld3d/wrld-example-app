//
//  SSISenionLocationSourceDebugInformation.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class contains information that may be useful in debugging scenarios.
 */
@interface SSISenionLocationSourceDebugInformation : NSObject

/**
 The map ID.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *mapId;

/**
 The map version ID.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *mapVersionId;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with a map ID and a map version ID.
 
 @param mapId The map id.
 @param mapVersionId The map version ID.
 */
- (nonnull instancetype)initWithMapId:(nonnull NSString *)mapId
                         mapVersionId:(nonnull NSString *)mapVersionId;

/**
 Method to check if two instances of `SSISenionLocationSourceDebugInformation` are equal.
 
 @param debugInformation The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToDebugInformation:(nullable SSISenionLocationSourceDebugInformation *)debugInformation;

@end
