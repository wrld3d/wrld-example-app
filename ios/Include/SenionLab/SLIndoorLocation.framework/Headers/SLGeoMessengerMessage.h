//
//  SLGeoMessengerMessage.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class descripes the properties of a SLGeoMessenger message.
 */
@interface SLGeoMessengerMessage <NSObject>

/// @name Properties

/**
 The id of the message.
 */
@property (nonatomic, strong, readonly) NSString *messageId;

/**
 The type of the message.
 */
@property (nonatomic, strong, readonly) NSString *type;

/**
 The payload attached to the message.
 */
@property (nonatomic, strong, readonly) NSString *payload;

@end
