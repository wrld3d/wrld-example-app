// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "IMenuView.h"
#include <vector>
#include "SearchResultModel.h"

@interface DirectionsMenuStaticView : UIView  <UITableViewDelegate, UITableViewDataSource>
{
}

@property (retain, nonatomic) IBOutlet UIButton *exitDirectionsBtn;
@property (retain, nonatomic) IBOutlet UIButton *reverseButton;
@property (retain, nonatomic) IBOutlet UITextField *endRouteTextField;
@property (retain, nonatomic) IBOutlet UITextField *startRouteTextField;
@property (retain, nonatomic) IBOutlet UIView *headerView;
@property (retain, nonatomic) IBOutlet UIView *bottomBarView;
@property (retain, nonatomic) IBOutlet UIView *hideOptionsView;
@property (retain, nonatomic) IBOutlet UIButton *myLocation;
@property (nonatomic) int resultCount;

- (void)updateSearchResultsSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)section;
- (void)updateStartSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results;
- (void)updateEndSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results;

-(float)getEstimatedHeight;
-(void)SetSearchMenuView:(UIView *)parentView;
- (IBAction)MyLocationSelected:(id)sender;

-(void)SetHighlightItem:(int)highlightItem;
- (IBAction)cancelSuggestions:(id)sender;
- (void)showEndSuggestions;
- (void)showStartSuggestions;
- (Eegeo::Space::LatLong) GetStartLocation;
- (Eegeo::Space::LatLong) GetEndLocation;
- (BOOL) shouldPerformSearch;
- (void) resetSuggestionItem;
- (void)reverseAction;
@end
