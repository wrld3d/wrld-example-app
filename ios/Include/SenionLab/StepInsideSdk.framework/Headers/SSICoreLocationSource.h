//
//  SSICoreLocationSource.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SSILocationSource.h"

/**
 This class represents the Core Location positioning system.
 */
@interface SSICoreLocationSource : NSObject <SSILocationSource>

/**
 Method to check if two instances of `SSICoreLocationSource` are equal.
 
 @param locationSource The other instance.
 
 @return `YES` if equal, otherwise `NO`.
 */
- (BOOL)isEqualToLocationSource:(nullable SSICoreLocationSource *)locationSource;

@end
