// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>

#include "SearchMenuViewIncludes.h"

@interface SearchMenuInputDelegate : NSObject<UITextFieldDelegate>

- (id)initWithTextField:(UITextField*)textField
                interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop;

- (void) enableEdit;

- (void) disableEdit;

- (void) removeSeachKeyboard;

- (void) setEditText :(NSString*)searchText
                     :(bool)isCategory;

@end