//
//  SSIPath.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIPathSegment;

/**
 This class represent a path made up by zero or more `SSIPathSegments`.
 */
@interface SSIPath : NSObject

/**
 The individual segments.
 */
@property (nonnull, nonatomic, strong, readonly) NSArray<SSIPathSegment *> *segments;

/**
 The total length in meters.
 */
@property (nonatomic, readonly) double totalLength;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class with an array of `SSIPathSegments`.
 
 @param segments The individual segments.
 */
- (nonnull instancetype)initWithSegments:(nonnull NSArray<SSIPathSegment *> *)segments;

/**
 Method to check if two instances of `SSIPath` are equal.
 
 @param path The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToPath:(nullable SSIPath *)path;

@end
