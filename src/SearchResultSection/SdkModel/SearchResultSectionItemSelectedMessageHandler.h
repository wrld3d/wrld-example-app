// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ICameraTransitionController.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "ISearchRefreshService.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            class SearchResultSectionItemSelectedMessageHandler : private Eegeo::NonCopyable
            {
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Search::SdkModel::ISearchRefreshService& m_searchRefreshService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultSectionItemSelectedMessageHandler, const SearchResultSectionItemSelectedMessage&> m_handleSearchResultSectionItemSelectedMessageBinding;
                Eegeo::Helpers::TCallback0<SearchResultSectionItemSelectedMessageHandler> m_transitionChangedCallback;

                void OnSearchResultSectionItemSelectedMessage(const SearchResultSectionItemSelectedMessage& message);
                void OnTransitioningChangedCallback();

            public:
                SearchResultSectionItemSelectedMessageHandler(
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    Search::SdkModel::ISearchRefreshService& searchRefreshService,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultSectionItemSelectedMessageHandler();
            };
        }
    }
}
