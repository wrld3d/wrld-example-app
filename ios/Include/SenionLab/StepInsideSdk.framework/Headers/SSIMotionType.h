//
//  SSIMotionType.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This enum represent the current type of user motion.
 */
typedef NS_ENUM(NSInteger, SSIMotionType) {
    
    /**
     The positioning API can not determine a motion type.
     */
    SSIMotionTypeUnknown,
    
    /**
     The motion type is standing.
     */
    SSIMotionTypeStanding,
    
    /**
     The motion type is walking.
     */
    SSIMotionTypeWalking,
    
    /**
     The motion type is running.
     */
    SSIMotionTypeRunning
};
