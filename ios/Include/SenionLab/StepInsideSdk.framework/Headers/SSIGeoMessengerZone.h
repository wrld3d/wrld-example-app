//
//  SSIGeoMessengerZone.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SSIGeoMessengerMessage;

/**
 This class represent a GeoMessenger zone.
 */
@interface SSIGeoMessengerZone : NSObject

/**
 The unique zone ID.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *zoneId;

/**
 The name.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *name;

/**
 A list of messages linked to this zone.
 */
@property (nonnull, nonatomic, strong, readonly) NSArray<SSIGeoMessengerMessage *> *messages;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class.
 
 @param zoneId The unique zone ID.
 @param name The name.
 @param messages A list of messages linked to this zone.
 */
- (nonnull instancetype)initWithZoneId:(nonnull NSString *)zoneId
                                  name:(nonnull NSString *)name
                              messages:(nonnull NSArray<SSIGeoMessengerMessage *> *)messages;

/**
 Method to check if two instances of `SSIGeoMessengerZone` are equal.
 
 @param geoMessengerZone The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToGeoMessengerZone:(nullable SSIGeoMessengerZone *)geoMessengerZone;

@end
