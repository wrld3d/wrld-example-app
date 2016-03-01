// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "Search.h"
#include "ISearchModule.h"
#include "Location.h"
#include "GlobeCameraController.h"
#include "CameraTransitions.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "SearchQueryObserver.h"
#include "AppModes.h"
#include "Interiors.h"

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

            public:
                SearchModule(ISearchService& searchService,
                             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController,
                             CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionsController,
                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                             ExampleAppMessaging::TMessageBus& messageBus,
                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus);

                ~SearchModule();

                ISearchResultRepository& GetSearchResultRepository() const;

                ISearchQueryPerformer& GetSearchQueryPerformer() const;

                ISearchRefreshService& GetSearchRefreshService() const;
                
                MyPins::ISearchResultMyPinsService& GetSearchResultMyPinsService() const;
                
                MyPins::IMyPinsSearchResultRefreshService& GetMyPinsSearchResultRefreshService() const;
            };
        }
    }
}
