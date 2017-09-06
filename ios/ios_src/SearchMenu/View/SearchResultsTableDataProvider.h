// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "IMenuView.h"
#include "SearchResultsTableScrollDelegate.h"

@class SearchMenuView;

@interface SearchResultsTableDataProvider : UITableViewController<UITableViewDelegate, UITableViewDataSource>
{
    
}

- (void)updateSearchResultsSection:(nonnull ExampleApp::Menu::View::IMenuSectionViewModel*)section;

- (float)getRealTableHeight;

- (nonnull id)initWithParams:(nonnull SearchMenuView*)view;

@property (nonatomic, retain, nullable) id  <SearchResultsTableScrollDelegate> scrollDelegate;

@end;
