// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "MenuView.h"
#include "DirectionsMenuViewIncludes.h"
#include <vector>
#include "SearchResultModel.h"

@class DirectionsMenuView;

@interface DirectionsMenuView : MenuView<UIScrollViewDelegate>
{
    
}

- (id)initWithParams:(float)width
                    :(float)height
                    :(float)pixelScale;

- (ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop*) getDirectionsMenuInterop;

- (void)CollapseAll;

- (void)HighlightItemIndex:(int)itemIndex;

- (void)SetSearchSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)searchSection;

- (void)SetGeoNamesStartSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results;

- (void)SetGeoNamesEndSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results;

- (void)ExitDirectionsClicked;

@property (nonatomic, retain) UIScrollView* pSearchResultsTableContainerView;

@end
