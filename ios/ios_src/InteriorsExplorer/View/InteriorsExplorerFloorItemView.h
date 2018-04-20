// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "InteriorsExplorerViewIncludes.h"
#include <string>
#include <vector>

@class InteriorsExplorerFloorItemView;

@interface InteriorsExplorerFloorItemView : UITableViewCell
{
    
}

- (id)initWithFrame:(CGRect)frame
            spacing:(CGFloat)labelSpacing
       dividerWidth:(CGFloat)dividerWidth
            centerX:(CGFloat)x
    reuseIdentifier:(NSString*)reuseId;

- (void) setFloor :(NSString*)floorName :(BOOL)isTop :(BOOL)isBottom;

@property(nonatomic, retain) UILabel* pFloorNameLabel;
@property(nonatomic, retain) UIView* pLines;

@property(nonatomic, retain) CAShapeLayer* pDivisionShape;
@property(nonatomic, retain) CAShapeLayer* pTopDivisionShape;
@property(nonatomic, retain) CAShapeLayer* pBottomDivisionShape;

@end
