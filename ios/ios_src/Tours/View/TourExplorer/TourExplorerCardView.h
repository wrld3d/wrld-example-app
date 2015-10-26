// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#import "FXImageView.h"

@interface TourExplorerCardView : UIView

@property (nonatomic, retain) UIImageView* pBackgroundImage;
@property (nonatomic, retain) UIView* pTextContainer;
@property (nonatomic, retain) UILabel* pTextLabel;
@property (nonatomic, retain) UIView* pDetailTextContainer;
@property (nonatomic, retain) UILabel* pDetailTextLabel;

- (id)init;

- (void)setContent:(NSString*)strImagePath
                  :(NSString*)strText
                  :(NSString*)strDetailText;

@end
