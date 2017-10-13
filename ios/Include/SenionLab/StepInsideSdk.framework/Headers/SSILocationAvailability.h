//
//  SSILocationAvailability.h
//  StepInsideSdk
//
//  Copyright © 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This enum represent the location availability from `SSIPositioningApi`.
 */
typedef NS_ENUM(NSInteger, SSILocationAvailability) {

    /**
     The positioning API is currently producing locations.
     */
    SSILocationAvailabilityAvailable,
        
    /**
     The positioning API is not currently able to produce locations for some reason.
     
     The user might for example be outside of the calibrated area or the accuracy might be too low.
    */
    SSILocationAvailabilityNotAvailable
};
