// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuViewModule.h"
#include "IMenuModel.h"
#include "IMenuViewModel.h"
#include "SearchResultMenuViewController.h"
#include "SearchResultMenuView.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        SearchResultMenuViewModule::SearchResultMenuViewModule(Search::ISearchService& searchService,
                                                               Search::ISearchQueryPerformer& searchQueryPerformer,
                                                               CategorySearch::ICategorySearchRepository& categorySearchRepository,
                                                               Menu::IMenuModel& searchResultMenuModel,
                                                               Menu::IMenuViewModel& menuViewModel,
                                                               SearchResultMenu::ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                               const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                               Modality::IModalityModel& modalityModel)
        {
            m_pView = [[SearchResultMenuView alloc]  initWithDimensions
                       :screenProperties.GetScreenWidth()
                       :screenProperties.GetScreenHeight()
                       :screenProperties.GetPixelScale()];
            
            m_pMenuViewController = [[SearchResultMenuViewController alloc] initWithParams
                                     :&searchService
                                     :&searchQueryPerformer
                                     :&categorySearchRepository
                                     :&searchResultMenuModel
                                     :&menuViewModel
                                     :&searchResultMenuViewModel
                                     :m_pView
                                     :&modalityModel];
        }
        
        SearchResultMenuViewModule::~SearchResultMenuViewModule()
        {
            [m_pMenuViewController release];
            [m_pView release];
        }
        
        MenuViewController& SearchResultMenuViewModule::GetSearchResultMenuViewController() const
        {
            return *m_pMenuViewController;
        }
        
        SearchResultMenuView& SearchResultMenuViewModule::GetSearchResultMenuView() const
        {
            return *m_pView;
        }
    }
}
