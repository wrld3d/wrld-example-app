//
//  SLSenionLocationSource.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLLocationSource.h"

/**
 This class contains information linked to the location source from Senion.
 */
@interface SLSenionLocationSource : SLLocationSource

/**
  Map Key for the location source.
 */
@property (nonatomic, strong, readonly) NSString *mapKey;

@end
