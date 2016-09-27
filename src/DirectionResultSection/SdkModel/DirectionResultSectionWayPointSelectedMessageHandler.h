// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ICameraTransitionController.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "Types.h"
#include "DirectionResultSectionItemSelectedMessage.h"


namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace SdkModel
        {
            class DirectionResultSectionWayPointSelectedMessageHandler : private Eegeo::NonCopyable
            {
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                //TODO: Create new message for direction way point
                Eegeo::Helpers::TCallback1<DirectionResultSectionWayPointSelectedMessageHandler, const DirectionResultSection::DirectionResultSectionItemSelectedMessage&> m_handleDirectionResultSectionItemSelectedMessageBinding;
                
                void OnSearchResultSectionItemSelectedMessage(const DirectionResultSection::DirectionResultSectionItemSelectedMessage& message);
                
            public:
                DirectionResultSectionWayPointSelectedMessageHandler(
                                                              CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                              ExampleAppMessaging::TMessageBus& messageBus);
                
                ~DirectionResultSectionWayPointSelectedMessageHandler();
            };
        }
    }
}
