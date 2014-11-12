// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

@interface CustomTableViewCell : UITableViewCell
{
	bool m_rightAlignFrame;
	bool m_rightAlignImage;
	bool m_isHeader;
	float m_initialWidth;
	UITableView* m_tableView;
}

- (void)setAlignInfo:(bool)rightAlignFrame :(bool)rightAlignImage :(bool)isHeader;

- (void)initCell:(float)initialWidth :(UITableView*)tableView;

- (void)layoutSubviews;

- (BOOL)canInteract;

@end
