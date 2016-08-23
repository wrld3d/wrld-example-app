// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ICameraTransitionController.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "Types.h"
#include "IRestrictedBuildingService.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace SdkModel
        {
            class SearchResultSectionItemSelectedMessageHandler : private Eegeo::NonCopyable
            {
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultSectionItemSelectedMessageHandler, const SearchResultSectionItemSelectedMessage&> m_handleSearchResultSectionItemSelectedMessageBinding;

                void OnSearchResultSectionItemSelectedMessage(const SearchResultSectionItemSelectedMessage& message);
                
                ExampleApp::WifiInfo::IRestrictedBuildingService& m_restrictedBuildingInformationService;
                
            public:
                SearchResultSectionItemSelectedMessageHandler(
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    ExampleApp::WifiInfo::IRestrictedBuildingService& restrictedBuildingInformationService);

                ~SearchResultSectionItemSelectedMessageHandler();
            };
        }
    }
}
