//
//  SLLocationState.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLIndoorLocationEnums.h"

@class SLCoordinate3D;

/**
 This class represent a location with it's coordinate and uncertaintyRadius.
 
 @note The use of [SLLocationStatus](../Enums/SLLocationStatus.html) in this class have been deprecated and will be removed in a future release of the SDK.
 */
@interface SLLocationState : NSObject

/// @name Initializers

/**
Initialize a SLLocationState.

@param location The location.
@param locationUncertaintyRadius The uncertainty radius for the location.
*/
- (instancetype)initWithLocation:(SLCoordinate3D *)location andLocationUncertainty:(double)locationUncertaintyRadius;

/**
 @warning The use of this initializer have been deprecated and will be removed in a future release of the SDK.
 
 Initialize a SLLocationState.
 
 @param location The location.
 @param locationUncertaintyRadius The uncertainty radius for the location.
 @param locationStatus The status of the location.
 */
- (instancetype)initWithLocation:(SLCoordinate3D *)location andLocationUncertainty:(double)locationUncertaintyRadius andLocationStatus:(SLLocationStatus)locationStatus __attribute__((deprecated));

/// @name Properties

/**
 Current location.
 */
@property (nonatomic, strong) SLCoordinate3D* location;

/**
 Current uncertainty in [m].
 */
@property (nonatomic) double locationUncertaintyRadius;

/**
 NOTE! The use of this property have been deprecated and will be removed in a future release of the SDK.
 
 Current location status.
 */
@property (nonatomic) SLLocationStatus locationStatus __attribute__((deprecated));

@end
