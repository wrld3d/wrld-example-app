// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "ISearchResultMenuModule.h"
#include "IIdentity.h"
#include "CameraTransitions.h"
#include "Reaction.h"
#include "SearchResultMenuViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultMenuModule: public ISearchResultMenuModule, private Eegeo::NonCopyable
        {
        private:
            Menu::IMenuModel* m_pModel;
            Menu::IMenuOptionsModel* m_pMenuOptionsModel;
            SearchResultMenuViewModel* m_pViewModel;
            ISearchResultMenuModel* m_pSearchResultMenuModel;
            
            Menu::IMenuSectionViewModel* m_pMenuSection;
            
        public:
            SearchResultMenuModule(Search::ISearchResultRepository& searchResultRepository,
                                   Eegeo::Helpers::IIdentityProvider& identityProvider,
                                   CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                   Reaction::IReactionControllerModel& reactionControllerModel,
                                   const Search::ISearchQueryPerformer& queryPerformer,
                                   Search::ISearchService& searchService);
            
            ~SearchResultMenuModule();
            
            Menu::IMenuModel& GetSearchResultMenuModel() const;
            
            ISearchResultMenuModel& GetSearchResultModel() const;
            
            Menu::IMenuViewModel& GetMenuViewModel() const;
            
            ISearchResultMenuViewModel& GetSearchResultMenuViewModel() const;
        };
    }
}
