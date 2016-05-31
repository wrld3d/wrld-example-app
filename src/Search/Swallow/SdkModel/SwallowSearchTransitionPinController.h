// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>

#include "ICallback.h"
#include "Types.h"

#include "AppCamera.h"
#include "SearchResultIconCategoryMapper.h"
#include "SearchResultModel.h"
#include "WorldPins.h"
#include "CameraTransitions.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchTransitionPinController : private Eegeo::NonCopyable
                {
                public:
                    SwallowSearchTransitionPinController(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                         CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                         AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                         Search::SdkModel::ISearchService& searchService);
                    
                    ~SwallowSearchTransitionPinController();

                    void OnSearchServiceReceivedQueryResults(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                                        
                private:
                    void OnTransitionsLoaded(const std::vector<Search::SdkModel::SearchResultModel>& transitionResults);
                    
                    void ClearResults();
                    
                    CategorySearch::SearchResultIconCategoryMapper m_searchResultIconCategoryMapper;
                    WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                    CameraTransitions::SdkModel::ICameraTransitionController& m_transitionController;
                    Search::SdkModel::ISearchService& m_searchService;
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                    
                    std::vector<WorldPins::SdkModel::WorldPinItemModel*> m_transitionPins;
                    
                    Eegeo::Helpers::TCallback2<SwallowSearchTransitionPinController, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_handleSearchServiceReceivedQueryResults;
                };
            }
        }
    }
}