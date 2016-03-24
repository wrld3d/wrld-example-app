// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InteriorsExplorerViewIncludes.h"
#include <string>
#include <vector>

@class InteriorsExplorerFloorItemView;

@interface InteriorsExplorerFloorItemView : UIView
{
    
}

- (id) initWithParams:(float)labelWidth :(float)labelSpacing :(float)divisionWidth :(float)height :(float)pixelScale :(NSString*)floorName :(BOOL)isBottom :(BOOL)isTop;

- (void) showName;

- (void) hideName;

@property(nonatomic, retain) UILabel* pFloorNameLabel;
@property(nonatomic, retain) UIView* pLines;

@end
