// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuModule.h"
#include "MenuModel.h"
#include "MenuViewModel.h"
#include "MenuOptionsModel.h"
#include "SearchResultMenuModel.h"
#include "MenuSectionViewModel.h"
#include "SearchResultMenuViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        SearchResultMenuModule::SearchResultMenuModule(Search::ISearchResultRepository& searchResultRepository,
                                                       Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                       CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                                       Reaction::IReactionControllerModel& reactionControllerModel,
                                                       const Search::ISearchQueryPerformer& queryPerformer,
                                                       Search::ISearchService& searchService)
        {
            m_pModel = Eegeo_NEW(Menu::MenuModel)();
            
            m_pMenuOptionsModel = Eegeo_NEW(Menu::MenuOptionsModel)(*m_pModel);
        
            m_pViewModel = Eegeo_NEW(SearchResultMenuViewModel)(*m_pModel,
                                                                false,
                                                                identityProvider.GetNextIdentity(),
                                                                reactionControllerModel,
                                                                queryPerformer,
                                                                searchService);
            
            m_pSearchResultMenuModel = Eegeo_NEW(SearchResultMenuModel)(*m_pMenuOptionsModel,
                                                                        searchResultRepository,
                                                                        cameraTransitionController,
                                                                        *m_pViewModel);
            
            m_pMenuSection = Eegeo_NEW(Menu::MenuSectionViewModel)("Search", "search", *m_pModel, false);
            m_pViewModel->AddSection(*m_pMenuSection);
        }
        
        SearchResultMenuModule::~SearchResultMenuModule()
        {
            Eegeo_DELETE m_pMenuSection;
            Eegeo_DELETE m_pViewModel;
            Eegeo_DELETE m_pSearchResultMenuModel;
            Eegeo_DELETE m_pMenuOptionsModel;
            Eegeo_DELETE m_pModel;
        }
        
        Menu::IMenuModel& SearchResultMenuModule::GetSearchResultMenuModel() const
        {
            return *m_pModel;
        }
        
        ISearchResultMenuModel& SearchResultMenuModule::GetSearchResultModel() const
        {
            return *m_pSearchResultMenuModel;
        }
        
        Menu::IMenuViewModel& SearchResultMenuModule::GetMenuViewModel() const
        {
            return *m_pViewModel;
        }
        
        ISearchResultMenuViewModel& SearchResultMenuModule::GetSearchResultMenuViewModel() const
        {
            return *m_pViewModel;
        }
    }
}
