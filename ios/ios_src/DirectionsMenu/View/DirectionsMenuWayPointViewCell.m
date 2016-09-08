// Copyright eeGeo Ltd (2012-2015), All Rights Reserved



#import "DirectionsMenuWayPointViewCell.h"

@implementation DirectionsMenuWayPointViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (void)dealloc {

    [_wayPointImageView release];
    [_wayPointMainTitlelbl release];
    [_wayPointSubCategorylbl release];
    [_wayPointNumberViewWidthConstraint release];
    [_wayPointNumberlbl release];
    [super dealloc];
}
@end
