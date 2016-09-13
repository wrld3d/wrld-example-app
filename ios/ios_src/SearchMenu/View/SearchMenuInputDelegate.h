// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "SearchMenuViewIncludes.h"
#include "SearchMenuResultsSpinner.h"

@interface SearchMenuInputDelegate : NSObject<UITextFieldDelegate>

- (id)initWithTextField:(UITextField*)textField
            clearButton:(UIButton*)clearButton
            resultsSpinner:(SearchMenuResultsSpinner*)resultsSpinner
            interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop
            searchMenuScrollButton:(UIButton*)searchMenuScrollButton
            searchMenuScrollView:(UIScrollView*)searchMenuScrollView;

- (void) setSearchInProgress;

- (void) setSearchEnded;

- (void) removeSeachKeyboard;

- (void) setEditText :(NSString*)searchText
                     :(bool)isTag;

- (void) clearSearch;

- (void) setHasResults :(bool)hasResults;

@end