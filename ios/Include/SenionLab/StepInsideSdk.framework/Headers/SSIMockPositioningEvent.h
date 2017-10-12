//
//  SSIMockPositioningEvent.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This protocol defines a mock positioning event.
 */
@protocol SSIMockPositioningEvent <NSObject>

/**
 The delay to be applied before emitting the event.
 */
@property (nonatomic, readonly) NSTimeInterval delayTimeInterval;

@end
