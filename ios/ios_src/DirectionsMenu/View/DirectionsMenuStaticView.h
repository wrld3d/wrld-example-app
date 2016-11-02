// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "IMenuView.h"


@interface DirectionsMenuStaticView : UIView  <UITableViewDelegate, UITableViewDataSource>
{
}

@property (retain, nonatomic) IBOutlet UIButton *exitDirectionsBtn;
@property (retain, nonatomic) IBOutlet UITextField *endRouteTextField;
@property (retain, nonatomic) IBOutlet UITextField *startRouteTextField;
@property (retain, nonatomic) IBOutlet UIView *headerView;
@property (retain, nonatomic) IBOutlet UIView *bottomBarView;
@property (retain, nonatomic) IBOutlet UIView *hideOptionsView;
@property (nonatomic) int resultCount;

- (void)updateSearchResultsSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)section;
-(float)getEstimatedHeight;
-(void)SetSearchMenuView:(UIView *)parentView;

-(void)SetHighlightItem:(int)highlightItem;
- (IBAction)cancelSuggestions:(id)sender;
- (void)showEndSuggestions;
- (void)showStartSuggestions;
@end
