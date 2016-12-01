//
//  SLPath.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class represent a path. Currently used for Shortest path.
 */
@interface SLPath : NSObject

/// @name Initializer

/**
 Initializer.
 
 @param pathNodes Coordinates for all nodes on the path.
 @param pathLength The total length of the path.
 @param segmentLengths The length of each segment.
 */
- (instancetype)initWithLocations:(NSArray *)pathNodes
                   andPathLength:(double)pathLength
                andSegmentLengts:(NSArray *)segmentLengths;

/// @name Properties

/**
 @return Coordinates for all nodes on the path.
 */
@property (nonatomic, strong, readonly) NSArray *pathNodes;

/**
 @return The total length of the path.
 */
@property (nonatomic, readonly) double pathLength;

/**
 @return The length of each segment.
 */
@property (nonatomic, strong, readonly) NSArray *segmentLengths;

@end
