// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Menu.h"
#include "Types.h"
#include "ISearchResultMenuModel.h"
#include "Search.h"
#include "ICallback.h"
#include "CameraTransitions.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultMenuModel : public ISearchResultMenuModel, private Eegeo::NonCopyable
        {
            Search::ISearchResultRepository& m_searchResultRepository;
            Menu::IMenuOptionsModel& m_menuOptions;
            Eegeo::Helpers::ICallback1<Search::SearchResultModel*>* m_pSearchResultAddedCallback;
            Eegeo::Helpers::ICallback1<Search::SearchResultModel*>* m_pSearchResultRemovedCallback;
            CameraTransitions::ICameraTransitionController& m_cameraTransitionController;
            OpenableControlViewModel::IOpenableControlViewModel& m_searchResultsMenuOpenableViewModel;
            
        public:
            SearchResultMenuModel(Menu::IMenuOptionsModel& menuOptions,
                                  Search::ISearchResultRepository& searchResultRepository,
                                  CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                  OpenableControlViewModel::IOpenableControlViewModel& searchResultsMenuOpenableViewModel);
            
            ~SearchResultMenuModel();
            
        private:
            void AddSearchResult(Search::SearchResultModel*& pModel);
            
            void RemoveSearchResult(Search::SearchResultModel*& pModel);
        };
    }
}
