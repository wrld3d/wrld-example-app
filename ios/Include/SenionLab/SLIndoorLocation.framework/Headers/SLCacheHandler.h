//
//  SLCacheHandler.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

static NSString *const SLCacheHandlerErrorDomain = @"com.senionlab.slindoorlocation.slcachehandler";

typedef NS_ENUM(NSInteger, SLCacheHandlerErrorType) {
    SLCacheHandlerErrorTypeInvalidId,
    SLCacheHandlerErrorTypeMissingInternetConnection
};

/**
 This class can be used to pre-fetch data from server needed for positioning in one or more buildings. This is optional, but will speed up the loading of SLIndoorLocationManager.
 
 ## Note
 
 This class should not be used while the SLIndoorLocationManager is running as it may interfere with the correct operation of that service. Also, do not initialize SLIndoorLocationManager while SLCacheHandler is running. The SDK's behaviour is not defined for these situations.
 
 ## Error
 
 The error block will include an NSError which will be any of the errors declared in SLCacheHandlerErrorType:
 
    enum SLCacheHandlerErrorType {
        SLCacheHandlerErrorTypeInvalidId = 0
        SLCacheHandlerErrorTypeMissingInternetConnection = 1
    }
 
 */
@interface SLCacheHandler : NSObject

/// @name Initializer

/**
 Instantiate SLCacheHandler.
 
 @param customerId Your Customer ID (obtained from SenionLab).
 */
- (instancetype)initWithCustomerId:(NSString *)customerId;

/// @name Methods

/** 
 Downloads updated cache data for the provided Map Key if it's available. This is also done when instantiating SLIndoorLocationManager.
 
 Please note that if the Map Key fail with invaild id and a callback to error, you will still receive a callback to completion.
 
 @param mapKey The Map Key which should be preloaded (obtained from SenionLab).
 @param completion This block will be called after the Map Key is downloaded.
 @param error This block will be called if any error occur during the download. See Error in Detailed description.
 */
- (void)downloadUpdatedCacheDataIfAvailableForMapKey:(NSString *)mapKey
                                      withCompletion:(void (^)())completion
                                               error:(void (^)(NSError *))error;

/**
 Downloads updated cache data for the provided Map Keys if it's available. This is also done when instantiating SLIndoorLocationManager.
 
 Please note that if one Map Key fail with invaild id and a callback to error, the rest of the list will still be executed and finish with a callback to completion.
 
 @param mapKeys An array of all Map Keys which should be preloaded (obtained from SenionLab).
 @param completion This block will be called after all Map Keys is downloaded.
 @param error This block will be called if any error occur during the download. See Error in Detailed description.
 */
- (void)downloadUpdatedCacheDataIfAvailableForMapKeys:(NSArray<NSString *> *)mapKeys
                                       withCompletion:(void (^)())completion
                                                error:(void (^)(NSError *))error;

/**
 Removes all locally cached map data from the device.
 */
- (void)clearAllData;

@end
