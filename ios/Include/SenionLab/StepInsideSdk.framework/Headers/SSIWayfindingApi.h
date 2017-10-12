//
//  SSIWayfindingApi.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIPath;
@class SSILocationCoordinates;

/**
  This class provides access to the Wayfinding API. This API has methods for finding a path between one location coordinates and another.
 */
@interface SSIWayfindingApi : NSObject

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Finds a path between the last known location coordinates and the specified location coordinates.
 
 @param to The location coordinates to find a path to.
 
 @return A path to the specified location coordinate. If there is no last known location or a path could not be found, it will return `nil`.
 */
- (nullable SSIPath *)findPathTo:(nonnull SSILocationCoordinates *)to;

/**
 Finds a path between two location coordinates. From `from` to `to`.
 
 @param from The location coordinates to find a path from.
 @param to The location coordinates to find a path to.
 
 @return A path between the two location coordinate. If a path could not be found, it will return `nil`.
 */
- (nullable SSIPath *)findPathFrom:(nonnull SSILocationCoordinates *)from to:(nonnull SSILocationCoordinates *)to;

@end
