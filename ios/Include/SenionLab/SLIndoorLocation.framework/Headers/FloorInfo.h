//
//  FloorInfo.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SLCoordinate2D.h"
#import "SLPixelPoint2D.h"
#import "FloorNr.h"

/**
 The floor info object from BuildingInfo. This class keeps information about a floor in the building the user is currently in and how the global properties of the floor relate to the bitmap such as the long/lat location, orientation and scale. Please refer to BuildingInfo for the data structure.
 
 ## Note
 The map information in this class is used only for showing the user location on a bitmap image of the building. This class is not used by SLIndoorLocationManager and the navigation filter.
 */
@interface FloorInfo : NSObject

/// @name Properties

/**
 The name of the floor.
 */
@property(readonly, nonatomic, strong) NSMutableString *floorName; 

/**
 The ID of the floor.
 
 This is an ID for the floor and should not be mistaken for the actual floor order in comparison to other floorNr in the same building. Please refer BuildingInfo and floorNrArray for the actual order of the floors.
 */
@property(readonly, nonatomic) FloorNr floorNr;

/**
 The file name of the bitmap image file. Preferably a PNG file, but not necessary.
 */
@property(readonly, nonatomic, strong) NSMutableString *bitmapFilename;

/**
 The location of the bitmap expressed in latitude and longitude [deg].
 */
@property(readonly, nonatomic) SLCoordinate2D *bitmapLocation;

/**
 The offset of the reference point \c bitmapLocation relative the bitmap origin (upper left corner).

 \c bitmapOffset is the location of the reference point \c bitmapLocation in the bitmap expressed in pixels relative the upper left corner of the bitmap with x-axis pointing to the right and the y-axis pointing downwards, i.e., the standard computer vision definition. For example, if \c bitmapLocation represent the location of the upper left corner of the bitmap the offset is (x,y) = (0,0).
 */
@property(readonly, nonatomic) SLPixelPoint2D *bitmapOffset;

/**
 The orientation of the bitmap. The orientation is defined as the angle between true North in the bitmap and the up-direction of the bitmap (i.e., the minus y-axis) in the clock-wise direction. For example, if North is pointing to the left in the bitmap, then the orientation is 90 degrees.
 */
@property(readonly, nonatomic) double bitmapOrientation;

/**
 The scale of the bitmap. The number of pixels in the bitmap corresponding to one meter.
 */
@property(readonly, nonatomic) double pixelsPerMeter;

/**
 Image dimensions along x-axis.
 */
@property (readonly, nonatomic) NSInteger xMaxPixels;

/**
 Image dimensions along y-axis.
 */
@property (readonly, nonatomic) NSInteger yMaxPixels;

@end
