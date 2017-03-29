// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "MenuView.h"
#include "SearchMenuInputDelegate.h"
#include "SearchMenuViewIncludes.h"
#include "CustomTableRowSelectionDelegate.h"

@class SearchMenuView;
@class SearchResultsTableDataProvider;

@interface SearchMenuView : MenuView<CustomTableRowSelectionDelegate, UIScrollViewDelegate>
{
    
}

- (id)initWithParams:(float)width
                    :(float)height
                    :(float)pixelScale
                    :(CustomTableDataProvider*)dataProvider
                    :(int)tableCount
                    :(SearchResultsTableDataProvider*)searchResultsDataProvider;

- (ExampleApp::SearchMenu::View::SearchMenuViewInterop*) getSearchMenuInterop;

- (void) setSearchResultCount:(NSInteger)searchResultCount;

- (void) hideSearchResultCount;

- (void) removeSearchQueryResults;

- (void) collapseAll;

- (void) setSearchSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)searchSection;

@property (nonatomic, retain) UIScrollView* pSearchResultsTableContainerView;
@property (nonatomic, retain) CustomTableView* pSearchResultsTableView;
@property (nonatomic, retain) SearchMenuInputDelegate* pInputDelegate;

@end
