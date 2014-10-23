// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "Menu.h"
#include "MenuViewController.h"
#include "Modality.h"
#include "Search.h"
#include "CategorySearch.h"
#include "SearchResultMenu.h"

@class SearchResultMenuView;

FOUNDATION_EXPORT CGFloat const SearchResultRowHeight;

@interface SearchResultMenuViewController : MenuViewController
{
    ExampleApp::CategorySearch::ICategorySearchRepository* m_pCategorySearchRepository;
    ExampleApp::Search::ISearchQueryPerformer* m_pQueryPerformer;
    ExampleApp::SearchResultMenu::ISearchResultMenuViewModel* m_pSearchResultMenuViewModel;
}

- (id)initWithParams:(ExampleApp::Search::ISearchService*) pSearchService
                    :(ExampleApp::Search::ISearchQueryPerformer*) pQueryPerformer
                    :(ExampleApp::CategorySearch::ICategorySearchRepository*) pCategorySearchRepository
                    :(ExampleApp::Menu::IMenuModel *)pMenuModel
                    :(ExampleApp::Menu::IMenuViewModel *)pMenuViewModel
                    :(ExampleApp::SearchResultMenu::ISearchResultMenuViewModel *)pSearchResultMenuViewModel
                    :(SearchResultMenuView*)pMenuView
                    :(ExampleApp::Modality::IModalityModel*)pModalityModel;

- (void)updateHeaderInResponseToQueryIssued:(std::string)query;

- (void)updateHeaderInResponseToQueryResultsReceived:(std::string)query :(size_t)resultsReceived;

@end
