// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultItemModel.h"
#include "SearchResultModel.h"
#include "ICameraTransitionController.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        SearchResultItemModel::SearchResultItemModel(const std::string& name,
                                                     Search::SearchResultModel& searchResultModel,
                                                     CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                                     OpenableControlViewModel::IOpenableControlViewModel& searchMenuViewModel)
        : m_name(name)
        , m_searchResultModel(searchResultModel)
        , m_cameraTransitionController(cameraTransitionController)
        , m_searchMenuViewModel(searchMenuViewModel)
        {
            
        }
        
        SearchResultItemModel::~SearchResultItemModel()
        {
            
        }
        
        void SearchResultItemModel::Select()
        {
            EXAMPLE_LOG("Selected search result %s: %s\n", m_name.c_str(), m_searchResultModel.GetTitle().c_str());
            
            const float newDistanceFromInterest = 1000;
            m_cameraTransitionController.StartTransitionTo(m_searchResultModel.GetLocation().ToECEF(), newDistanceFromInterest);
            
            m_searchMenuViewModel.Close();
            
        }
    }
}
