//
//  SSIMockPositioningProvider.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol SSIMockPositioningEvent;

/**
 This protocol defines a mock positioning provider. 
 
 A mock positioning provider may be used when testing in an area where the positioning system has not been installed.
 */
@protocol SSIMockPositioningProvider <NSObject>

/**
 Yields the next mock positioning event to be emitted.
 
 @return The next mock positioning event to be emitted.
 */
- (nonnull id<SSIMockPositioningEvent>)yieldNextMockPositioningEvent;

@end
