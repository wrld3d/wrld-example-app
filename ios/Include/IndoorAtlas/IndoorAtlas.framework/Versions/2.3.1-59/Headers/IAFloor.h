// IndoorAtlas iOS SDK
// IAFloor.h

#import <Foundation/Foundation.h>
#define INDOORATLAS_API __attribute__((visibility("default")))

/*
 *  IACertainty
 *
 *  Discussion:
 *    Type used to represent the certainty that something is true.
 *    Has a value from 0.0 to 1.0, inclusive. A negative value indicates an invalid certainty.
 */
typedef double IACertainty;

/**
 * IAFloor specifies the floor of the building on which the user is located.
 * It is a replacement for CoreLocation’s CLFloor as the interface for that isn’t open.
 */
INDOORATLAS_API
@interface IAFloor : NSObject <NSCoding>

/**
 * Initializes and returns a floor object with the specified level information.
 * @param level initializes level value
 */
+ (nonnull IAFloor*)floorWithLevel:(NSInteger)level;

/**
 * Level value represent logical levels above or below ground level and are not intended to correspond to any numbering scheme in use by the building itself.
 * The ground floor of a building is always represented by the value 0. Floors above the grouond floor are represented by positive integers, so a value of 1
 * represents the floor above ground level, a value of 2 represents two floors above ground level, and so on. Floors below the ground floor are represented by
 * corresponding negative integers, with a value of -1 representing the floor immediately below ground level and so on.
 *
 * It is erroneous to use the user's level in a building as an estimate of altitude.
 */
@property (nonatomic, readonly) NSInteger level;

/**
 * Certainty that IALocation floor has the correct value.
 */
@property (nonatomic, readonly) IACertainty certainty;

@end

#undef INDOORATLAS_API
