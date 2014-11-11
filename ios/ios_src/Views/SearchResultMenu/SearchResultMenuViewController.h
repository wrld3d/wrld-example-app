// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Menu.h"
#include "MenuViewController.h"
#include "Modality.h"
#include "Search.h"
#include "CategorySearch.h"
#include "SearchResultMenu.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"

@class SearchResultMenuView;

FOUNDATION_EXPORT CGFloat const SearchResultRowHeight;

@interface SearchResultMenuViewController : MenuViewController
{
    ExampleApp::CategorySearch::ICategorySearchRepository* m_pCategorySearchRepository;
    ExampleApp::SearchResultMenu::ISearchResultMenuViewModel* m_pSearchResultMenuViewModel;
    ExampleApp::ExampleAppMessaging::UiToNativeMessageBus* m_pUiToNativeMessageBus;
}

- (id)initWithParams:(ExampleApp::CategorySearch::ICategorySearchRepository*) pCategorySearchRepository
                    :(ExampleApp::Menu::IMenuModel *)pMenuModel
                    :(ExampleApp::Menu::IMenuViewModel *)pMenuViewModel
                    :(ExampleApp::SearchResultMenu::ISearchResultMenuViewModel *)pSearchResultMenuViewModel
                    :(SearchResultMenuView*)pMenuView
                    :(ExampleApp::Modality::IModalityModel*)pModalityModel
                    :(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*)pUiToNativeMessageBus
                    :(ExampleApp::ExampleAppMessaging::NativeToUiMessageBus*)pNativeToUiMessageBus;

- (void)updateHeaderInResponseToQueryIssued:(std::string)query;

- (void)updateHeaderInResponseToQueryResultsReceived:(std::string)query :(size_t)resultsReceived;

@end
