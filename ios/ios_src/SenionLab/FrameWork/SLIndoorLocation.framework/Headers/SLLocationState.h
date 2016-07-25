//
//  SLLocationState.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLIndoorLocationEnums.h"

@class SLCoordinate3D;

/**
 THis class represent a location with it's coordinate, uncertaintyRadius and status.
 */
@interface SLLocationState : NSObject

/// @name Initializers

/**
 Initialize a SLLocationState
 
 @param location the location
 @param locationUncertaintyRadius the uncertainty radius for the location
 @param locationStatus the status of the location
 */
- (instancetype)initWithLocation:(SLCoordinate3D *)location andLocationUncertainty:(double)locationUncertaintyRadius andLocationStatus:(SLLocationStatus)locationStatus;

/// @name Properties

/**
 Current location
 */
@property (nonatomic, strong) SLCoordinate3D* location;

/**
 Current uncertainty in [m]
 */
@property (nonatomic) double locationUncertaintyRadius;

/**
 Current location status.
 */
@property (nonatomic) SLLocationStatus locationStatus;

@end
