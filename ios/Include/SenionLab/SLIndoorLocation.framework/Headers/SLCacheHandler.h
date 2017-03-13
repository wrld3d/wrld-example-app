//
//  SLCacheHandler.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 The domain for all errors from SLCacheHandler.
 */
static NSString *const SLCacheHandlerErrorDomain = @"com.senionlab.slindoorlocation.slcachehandler";

/**
 The enum of all error types from SLCacheHandler.
 */
typedef NS_ENUM(NSInteger, SLCacheHandlerErrorType) {
    
    /**
     The Map Key or Customer ID provided to SLCacheHandler is invalid.
     */
    SLCacheHandlerErrorTypeInvalidId,
    
    /**
     Missing internet connection.
     */
    SLCacheHandlerErrorTypeMissingInternetConnection
};

/**
 This class can be used to pre-fetch positioning maps from Senion's server needed for positioning in one or more buildings. The positioning map for the provided Map Key will be cached to the device. For example, use this class when the app launches. Then when the user enters the map view, the indoor position should load faster.
 
 The use of this class is optional, but will improve the loading time of SLIndoorLocationManager.
 
 You should not initialize this class yourself. Instead use the shared instance you get from `+shared`.
 
 ### Note
 If you are using this class right next to where you are initializing the SLIndoorLocationManager, you are not gaining anything. This class is designed to be used anywhere else in the app to cache the positioning map, which will then improve the loading time when SLIndoorLocationMananger is initialized.
 
 ## Error
 
 The error is described in the enum [`SLCacheHandlerErrorType`](../Enums/SLCacheHandlerErrorType.html) and is in the [`SLCacheHandlerErrorDomain`](../Cache%20Handler.html#/c:SLCacheHandler.h@SLCacheHandlerErrorDomain) domain.
 
 */
@interface SLCacheHandler : NSObject

/// @name Initializer

/**
:nodoc:
 Do not initialize this class. Instead use the shared instance.
*/
- (instancetype)init UNAVAILABLE_ATTRIBUTE;

/**
 Get the shared instance of SLCacheHandler.
 */
+ (instancetype)shared;

/// @name Methods

/** 
 Downloads updated positioning map for the provided Map Key if it's available. This is also done when instantiating SLIndoorLocationManager.
 
 @param mapKey The Map Key which should be preloaded (obtained from Senion).
 @param customerId Your Customer ID (obtained from Senion).
 @param completion This block will be called after the Map Key is downloaded. The string is the mapKey for this callback. If successful, NSError will be nil, otherwise NSError will contain the occuring error. See Error in Detailed description.
 */
- (void)downloadUpdatedCacheDataIfAvailableForMapKey:(NSString *)mapKey
                                          customerId:(NSString *)customerId
                                      withCompletion:(void (^)(NSString *, NSError *))completion;

/**
 Downloads updated positioning maps for the provided Map Keys if it's available. This is also done when instantiating SLIndoorLocationManager.
 
 @param mapKeys An array of all Map Keys which should be preloaded (obtained from Senion).
 @param customerId Your Customer ID (obtained from Senion).
 @param completion This block will be called after each Map Key is downloaded. The string is the mapKey for this callback. If successful, NSError will be nil, otherwise NSError will contain the occuring error. See Error in Detailed description.
 */
- (void)downloadUpdatedCacheDataIfAvailableForMapKeys:(NSArray<NSString *> *)mapKeys
                                           customerId:(NSString *)customerId
                                       withCompletion:(void (^)(NSString *, NSError *))completion;

/**
 Removes all locally cached positioning maps from the device.
 */
- (void)clearAllData;

@end
