// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#import <UIKit/UIKit.h>

@interface DirectionsMenuWayPointViewCell : UITableViewCell
{
}
@property (retain, nonatomic) IBOutlet UIImageView *wayPointImageView;
@property (retain, nonatomic) IBOutlet UILabel *wayPointMainTitlelbl;
@property (retain, nonatomic) IBOutlet UILabel *wayPointSubCategorylbl;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *wayPointNumberViewWidthConstraint;
@property (retain, nonatomic) IBOutlet UILabel *wayPointNumberlbl;
@property (retain, nonatomic) IBOutlet UIView *mainContainerView;

@end
