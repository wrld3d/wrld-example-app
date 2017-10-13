//
//  SSIGeoMessengerMessage.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class represent a GeoMessenger message.
 */
@interface SSIGeoMessengerMessage : NSObject

/**
 The unique message ID.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *messageId;

/**
 The type.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *type;

/**
 The payload.
 */
@property (nonnull, nonatomic, strong, readonly) NSString *payload;

/// :nodoc:
+ (nonnull instancetype)new UNAVAILABLE_ATTRIBUTE;

/// :nodoc:
- (nonnull instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Initializes this class.
 
 @param messageId The unique message ID.
 @param type The type.
 @param payload The payload.
 */
- (nonnull instancetype)initWithMessageId:(nonnull NSString *)messageId
                                     type:(nonnull NSString *)type
                                  payload:(nonnull NSString *)payload;

/**
 Method to check if two instances of `SSIGeoMessengerMessage` are equal.
 
 @param geoMessengerMessage The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToGeoMessengerMessage:(nullable SSIGeoMessengerMessage *)geoMessengerMessage;

@end
