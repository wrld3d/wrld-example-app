// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"

#include "AppCamera.h"
#include "BidirectionalBus.h"
#include "CameraTransitions.h"
#include "LaxSearch.h"
#include "WorldPins.h"
#include "SearchQuery.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                class LaxSearchServiceModule : private Eegeo::NonCopyable
                {
                private:
                    
                    LaxSearchTransitionPinController* m_pLaxSearchTransitionPinController;
                    LaxOfficeResultMenuOptionSelectedMessageHandler* m_pLaxOfficeResultMenuOptionSelectedMessageHandler;
                    Search::SdkModel::ISearchService& m_searchService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    
                    Eegeo::Helpers::TCallback2<LaxSearchServiceModule, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>& > m_transitionCallback;
                    
                    void OnTransitionResult(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                public:
                    LaxSearchServiceModule(Search::SdkModel::ISearchService& searchService,
                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               AppCamera::SdkModel::IAppCameraController& appCameraController,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               WorldPins::SdkModel::IWorldPinsService& worldPinsService);
                    
                    ~LaxSearchServiceModule();
                   
                    std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
                    
                    LaxSearchTransitionPinController& GetLaxSearchTransitionPinController() const;
                    
                };
            }
        }
    }
}