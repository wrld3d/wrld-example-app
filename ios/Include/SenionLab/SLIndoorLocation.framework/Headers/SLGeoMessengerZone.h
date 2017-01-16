//
//  SLGeoMessengerZone.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SLGeoMessengerMessage;

/**
 This class descripes the properties of a SLGeoMessenger zone.
 */
@interface SLGeoMessengerZone <NSObject>

/// @name Properties

/**
 The id of the zone.
 */
@property (nonatomic, strong, readonly) NSString *zoneId;

/**
 The name of the zone.
 */
@property (nonatomic, strong, readonly) NSString *name;

/**
 The messages attached to the zone, if any.
 */
@property (nonatomic, strong, readonly) NSArray<SLGeoMessengerMessage *> *messages;

@end
