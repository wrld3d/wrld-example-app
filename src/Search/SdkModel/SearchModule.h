// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "Search.h"
#include "ISearchModule.h"
#include "Location.h"
#include "AppCamera.h"
#include "CameraTransitions.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "SearchQueryObserver.h"
#include "AppModes.h"
#include "Interiors.h"
#include "ITagSearchRepository.h"
#include "ITagSearchModule.h"
#include "IMetricsService.h"
#include "InteriorMenuObserver.h"
#include "YelpCategoryMapperUpdater.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchModule : public ISearchModule, private Eegeo::NonCopyable
            {
            private:
                ISearchResultRepository* m_pSearchResultRepository;
                ISearchQueryPerformer* m_pSearchQueryPerformer;
                ISearchRefreshService* m_pSearchRefreshService;
                SearchQueryObserver* m_pSearchQueryObserver;
                MyPins::ISearchResultMyPinsService* m_pSearchResultMyPinsService;
                MyPins::IMyPinsSearchResultRefreshService* m_pMyPinsSearchResultRefreshService;
                TagSearch::SdkModel::ITagSearchModule* m_pTagSearchModule;
                InteriorMenuObserver* m_pInteriorMenuObserver;
            public:
                SearchModule(ISearchService& searchService,
                             ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController,
                             CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionsController,
                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                             ExampleAppMessaging::TMessageBus& messageBus,
                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                             Metrics::IMetricsService& metricsService,
                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                             Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository& interiorMetaDataRepo,
                             Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater,
                             std::vector<TagSearch::View::TagSearchModel> defaultFindMenuEntries,
                             Search::SdkModel::TagIconKey defaultIconKey);
                
                ~SearchModule();

                ISearchResultRepository& GetSearchResultRepository() const;

                ISearchQueryPerformer& GetSearchQueryPerformer() const;

                ISearchRefreshService& GetSearchRefreshService() const;
                
                MyPins::ISearchResultMyPinsService& GetSearchResultMyPinsService() const;
                
                MyPins::IMyPinsSearchResultRefreshService& GetMyPinsSearchResultRefreshService() const;
                
                ExampleApp::TagSearch::SdkModel::ITagSearchModule& GetTagSearchModule() const;
                
                InteriorMenuObserver& GetInteriorMenuObserver() const;
            };
        }
    }
}
