// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ICameraTransitionController.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "Types.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            class SearchResultSectionItemSelectedMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController> m_cameraTransitionController;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultSectionItemSelectedMessageHandler, const SearchResultSectionItemSelectedMessage&> m_handleSearchResultSectionItemSelectedMessageBinding;

                void OnSearchResultSectionItemSelectedMessage(const SearchResultSectionItemSelectedMessage& message);

            public:
                SearchResultSectionItemSelectedMessageHandler(
                                                              const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController,
                                                              const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~SearchResultSectionItemSelectedMessageHandler();
            };
        }
    }
}
