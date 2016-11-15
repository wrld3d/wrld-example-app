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
#include "NetIncludes.h"

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
                    Net::SdkModel::INetworkCapabilities& m_networkCapabilities;

                    bool m_hasPerformedFirstSearch;
                    bool m_clearSearchNextUpdate;
                    bool m_hasTransitionPoiResults;
                    
                    Eegeo::Helpers::TCallback2<SwallowSearchServiceModule, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_handleSearchServiceReceivedQueryResults;
                    Eegeo::Helpers::TCallback0<SwallowSearchServiceModule> m_handleNetworkCapabilitiesChanged;
                    
                    void OnSearchServiceReceivedQueryResults(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);

                    void OnNetworkCapabilitiesChanged();

                    void PerformTransitionPoiSearch();

                public:
                    SwallowSearchServiceModule(Search::SdkModel::ISearchService& searchService,
                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               AppCamera::SdkModel::IAppCameraController& appCameraController,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                               Net::SdkModel::INetworkCapabilities& networkCapabilities);
                    
                    ~SwallowSearchServiceModule();

                    void Start();

                    void Update();
                   
                    std::vector<TagSearch::View::TagSearchModel> GetTagSearchModels() const;
                    
                    SwallowSearchTransitionPinController& GetSwallowSearchTransitionPinController() const;
                    
                };
            }
        }
    }
}