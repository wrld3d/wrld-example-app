//
//  SSIHeadingAvailability.h
//  StepInsideSdk
//
//  Copyright © 2017 SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This enum represent the location availability from `SSIPositioningApi`.
 */
typedef NS_ENUM(NSInteger, SSIHeadingAvailability) {
    
    /**
     The positioning API is currently producing a heading.
     */
    SSIHeadingAvailabilityAvailable,
    
    /**
     The positioning API is not currently able to produce a heading for some reason.
     
     The estimated accuracy might for example be too low.
     */
    SSIHeadingAvailabilityNotAvailable
};
