// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchResultMenuItemSelectedMessage.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace SdkModel
        {
            class SearchResultMenuItemSelectedMessageHandler : private Eegeo::NonCopyable
            {
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultMenuItemSelectedMessageHandler, const SearchResultMenuItemSelectedMessage&> m_handleSearchResultMenuItemSelectedMessageBinding;

                void OnSearchResultMenuItemSelectedMessage(const SearchResultMenuItemSelectedMessage& message);

            public:
                SearchResultMenuItemSelectedMessageHandler(
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~SearchResultMenuItemSelectedMessageHandler();
            };
        }
    }
}
