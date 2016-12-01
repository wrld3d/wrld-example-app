//
//  SLGeometryId.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 This class is used to identify a geometry that should be monitored. 
 
 Make sure that each geometry has a unique id.
 */
@interface SLGeometryId : NSObject <NSCopying>

/// @name Initializer

/**
 Constructor.
 
 @param geometryId Unique string that identifies your geometry.
 */
- (instancetype)initWithGeometryId:(NSString *)geometryId;

/// @name Properties

/**
 The geometry ID.
 */
@property(strong) NSString *geometryId;

@end
