// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>



@interface DirectionsMenuStaticView : UIView  <UITableViewDelegate, UITableViewDataSource>
{
    
}


@property (retain, nonatomic) IBOutlet UIView *headerView;
@property (retain, nonatomic) IBOutlet UIView *bottomBarView;
@property (retain, nonatomic) IBOutlet UIView *scrollContentView;
@property (retain, nonatomic) IBOutlet UIView *hideOptionsView;
@property (retain, nonatomic) IBOutlet UITableView *wayPointsTableView;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *contentHeightConstraint;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *endHeightConstraint;
@property (retain, nonatomic) IBOutlet UIButton *optionsButton;
@property (retain, nonatomic) IBOutlet UIButton *exitDirectionsBtn;
@property (retain, nonatomic) IBOutlet UITextField *endRouteTextField;
@property (retain, nonatomic) IBOutlet UITextField *startRouteTextField;

- (IBAction)optionsAction:(id)sender;
@end
