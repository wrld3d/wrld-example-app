// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "SearchMenuViewIncludes.h"
#include "SearchMenuResultsSpinner.h"
#include "SearchMenuDragTab.h"

@interface SearchMenuInputDelegate : NSObject<UITextFieldDelegate>

- (id)initWithTextField:(UITextField*)textField
            clearButton:(UIButton*)clearButton
            resultsSpinner:(SearchMenuResultsSpinner*)resultsSpinner
            interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop
            searchMenuScrollButton:(UIButton*)searchMenuScrollButton
            searchMenuScrollView:(UIScrollView*)searchMenuScrollView
                dragTab:(SearchMenuDragTab*)dragTab;

- (void) setSearchInProgress;

- (void) setSearchEnded;

- (void) removeSeachKeyboard;

- (void) setEditText :(NSString*)searchText
                     :(bool)isTag;

- (std::string) getEditText;

- (bool) hasTagSearch;

- (void) clearSearch;

- (void) interopClearSearch;

- (void) setHasResults :(bool)hasResults;

- (void) setMenuOpen :(bool)menuOpen;

@end
