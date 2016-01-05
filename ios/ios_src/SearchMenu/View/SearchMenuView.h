// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "MenuView.h"
#include "SearchMenuViewIncludes.h"

@class SearchMenuView;

@interface SearchMenuView : MenuView<UITextFieldDelegate>
{
    
}

- (ExampleApp::SearchMenu::View::SearchMenuViewInterop*) getSearchMenuInterop;

- (void) enableEdit;

- (void) disableEdit;

- (void) removeSeachKeyboard;

- (void) setEditText :(NSString*)searchText
                     :(bool)isCategory;

- (void) setSearchResultCount:(NSInteger)searchResultCount;

- (void) collapseAll;

@end
