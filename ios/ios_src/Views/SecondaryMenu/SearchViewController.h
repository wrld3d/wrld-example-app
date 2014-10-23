// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Search.h"
#include "Menu.h"
#include "SearchViewControllerInterop.h"

@interface SearchViewController : UIViewController<UITextFieldDelegate>
{
    bool m_keyboardActive;
    bool m_returnPressed;
    ExampleApp::Search::ISearchQueryPerformer* m_pSearchQueryPerformer;
    ExampleApp::Search::ISearchService* m_pSearchService;
    ExampleApp::Menu::IMenuViewModel* m_pMenuViewModel;
    ExampleApp::SecondaryMenu::SearchViewControllerInterop* m_pInterop;
}

- (id)initWithParams:(UITextField*)pView
                    :(ExampleApp::Search::ISearchQueryPerformer*)pSearchQueryPerformer
                    :(ExampleApp::Search::ISearchService*) pSearchService
                    :(ExampleApp::Menu::IMenuViewModel*) pMenuViewModel;

- (void) enableEdit;

- (void) disableEdit;

- (void) removeSeachKeyboard;

@property (nonatomic, retain) UITextField* pTextView;

@end
