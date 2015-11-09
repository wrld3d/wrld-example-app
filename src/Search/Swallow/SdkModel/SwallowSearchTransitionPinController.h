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
                class SwallowSearchTransitionPinController : public Eegeo::Helpers::TCallback1<SwallowSearchTransitionPinController, const std::vector<Search::SdkModel::SearchResultModel>&>, Eegeo::NonCopyable
                {
                public:
                    SwallowSearchTransitionPinController(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                         CameraTransitions::SdkModel::ICameraTransitionController& transitionController,
                                                         AppCamera::SdkModel::IAppCameraController& appCameraController);
                    
                    ~SwallowSearchTransitionPinController();
                    
                private:
                    void OnTransitionsLoaded(const std::vector<Search::SdkModel::SearchResultModel>& transitionResults);
                    
                    void ClearResults();
                    
                    CategorySearch::SearchResultIconCategoryMapper m_searchResultIconCategoryMapper;
                    WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                    CameraTransitions::SdkModel::ICameraTransitionController& m_transitionController;
                    AppCamera::SdkModel::IAppCameraController& m_appCameraController;
                    
                    std::vector<WorldPins::SdkModel::WorldPinItemModel*> m_transitionPins;
                };
            }
        }
    }
}