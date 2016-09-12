// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "IMenuView.h"
#include "ViewWrap.h"

@class SearchResultsTableDataProvider;
@class SearchMenuView;

class SearchResultsTableDataProviderWrapper : public ViewWrap<SearchResultsTableDataProvider>
{
    using ViewWrap::ViewWrap;
};

@interface SearchResultsTableDataProvider : UITableViewController<UITableViewDelegate, UITableViewDataSource>
{
    
}

- (void)updateSearchResultsSection:(nonnull ExampleApp::Menu::View::IMenuSectionViewModel*)section;

- (float)getRealTableHeight;

- (nonnull id)initWithParams:(nonnull SearchMenuView*)view;

@end;