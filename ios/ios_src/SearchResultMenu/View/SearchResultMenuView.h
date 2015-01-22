// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "AppRunner.h"
#include "MenuView.h"
#include "SearchResultMenuViewInterop.h"

@class SearchResultMenuView;

@interface SearchResultMenuView : MenuView<UIGestureRecognizerDelegate>
{
    ExampleApp::SearchResultMenu::View::SearchResultMenuViewInterop* m_pSearchInterop;
}

- (void)initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells;

- (ExampleApp::SearchResultMenu::View::SearchResultMenuViewInterop*) getSearchInterop;

- (void) updateViewForQuery:(std::string)searchText :(bool)queryPending :(size_t)numResults;

- (void) onClearPressed:(UIButton *) sender;

@property (nonatomic, retain) UIView* pCategory;
@property (nonatomic, retain) UILabel* pHeading;
@property (nonatomic, retain) UIActivityIndicatorView* pSpinner;
@property (nonatomic, retain) UILabel* pResultsCount;
@property (nonatomic, retain) UIButton* pClearResults;

@end
