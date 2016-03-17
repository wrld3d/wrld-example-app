// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"

#include "AppCamera.h"
#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "SwallowPoiDb.h"
#include "SwallowSearch.h"
#include "WorldPins.h"
#include "SearchQuery.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowSearchServiceModule : private Eegeo::NonCopyable
                {
                private:
                    SwallowSearchTransitionPinController* m_pSwallowSearchTransitionPinController;
                    SwallowOfficeResultMenuOptionSelectedMessageHandler* m_pSwallowOfficeResultMenuOptionSelectedMessageHandler;
                    Search::SdkModel::ISearchService& m_searchService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    bool m_clearSearchNextUpdate;
                    
                    Eegeo::Helpers::TCallback2<SwallowSearchServiceModule, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>& > m_transitionCallback;
                    
                    void OnTransitionResult(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                public:
                    SwallowSearchServiceModule(Search::SdkModel::ISearchService& searchService,
                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               AppCamera::SdkModel::IAppCameraController& appCameraController,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               WorldPins::SdkModel::IWorldPinsService& worldPinsService);
                    
                    ~SwallowSearchServiceModule();

                    void Update();
                   
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                    
                    SwallowSearchTransitionPinController& GetSwallowSearchTransitionPinController() const;
                    
                };
            }
        }
    }
}