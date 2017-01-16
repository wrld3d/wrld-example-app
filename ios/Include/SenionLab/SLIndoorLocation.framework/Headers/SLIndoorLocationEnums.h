//
//  SLIndoorLocationEnums.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#ifndef SLIndoorLocation_SLIndoorLocationEnums_h
#define SLIndoorLocation_SLIndoorLocationEnums_h

/**
 Gives a status of the location estimate.
 */
typedef enum SLLocationStatus : NSInteger SLLocationStatus;
enum SLLocationStatus : NSInteger {
    SLLocationStatusConfirmed,
    SLLocationStatusUnconfirmed,
    SLLocationStatusUnconfirmedWithRadioDisturbances
};

static NSString * const SLLocationStatus_toString[] = {
    [SLLocationStatusConfirmed] = @"CONFIRMED",
    [SLLocationStatusUnconfirmed] = @"UNCONFIRMED",
    [SLLocationStatusUnconfirmedWithRadioDisturbances] = @"UNCONFIRMED_RADIO_DISTURBANCES"
};

/**
 Enum for requesting permission to iBeacon data.
 */
typedef enum SLIbeaconAuthorizationMethod : NSInteger SLIbeaconAuthorizationMethod;
enum SLIbeaconAuthorizationMethod : NSInteger {
    SLRequestAlwaysAuthorization, /**< Requests authorization to monitor iBeacon data in the background. */
    SLRequestWhenInUseAuthorization /**< Requests authorization to monitor iBeacon data only in foreground. */
};

static NSString * const SLIbeaconAuthorizationMethod_toString[] = {
    [SLRequestAlwaysAuthorization] = @"requestAlwaysAuthorization",
    [SLRequestWhenInUseAuthorization] = @"requestWhenInUseAuthorization",
};

typedef enum SLMotionState : NSInteger SLMotionState;
enum SLMotionState : NSInteger {
    SLMotionStateUnknown,
    SLMotionStateStanding,
    SLMotionStateWalking,
    SLMotionStateRunning,
    SLMotionStateStair,
    SLMotionStateEscalator,
    SLMotionStateElevator
};

static NSString * const SLMotionState_toString[] = {
    [SLMotionStateUnknown] = @"Unknown",
    [SLMotionStateStanding] = @"Standing",
    [SLMotionStateWalking] = @"Walking",
    [SLMotionStateRunning] = @"Running",
    [SLMotionStateStair] = @"Stair",
    [SLMotionStateEscalator] = @"Escalator",
    [SLMotionStateElevator] = @"Elevator"
};

#endif
