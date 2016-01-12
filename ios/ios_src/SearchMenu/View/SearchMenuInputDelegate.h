// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "SearchMenuViewIncludes.h"
#include "SearchMenuResultsSpinner.h"

@interface SearchMenuInputDelegate : NSObject<UITextFieldDelegate>

- (id)initWithTextField:(UITextField*)textField
            clearButton:(UIButton*)clearButton
         resultsSpinner:(SearchMenuResultsSpinner*)resultsSpinner
                interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop;

- (void) enableEdit;

- (void) disableEdit;

- (void) removeSeachKeyboard;

- (void) setEditText :(NSString*)searchText
                     :(bool)isCategory;

- (void) clearSearch;

@end