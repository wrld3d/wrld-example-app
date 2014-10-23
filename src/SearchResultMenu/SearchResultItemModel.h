// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "IMenuOption.h"
#include "Search.h"
#include "CameraTransitions.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultItemModel: public Menu::IMenuOption, private Eegeo::NonCopyable
        {
            std::string m_name;
            Search::SearchResultModel& m_searchResultModel;
            CameraTransitions::ICameraTransitionController& m_cameraTransitionController;
            OpenableControlViewModel::IOpenableControlViewModel& m_searchMenuViewModel;
            
            
        public:
            SearchResultItemModel(const std::string& name,
                                  Search::SearchResultModel& searchResultModel,
                                  CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                  OpenableControlViewModel::IOpenableControlViewModel& searchMenuViewModel);
            
            ~SearchResultItemModel();
            
            void Select();
        };
    }
    
}
