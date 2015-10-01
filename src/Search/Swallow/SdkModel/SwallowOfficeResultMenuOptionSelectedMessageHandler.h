// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"

#include "CameraTransitions.h"
#include "SwallowOfficeResultMenuOptionSelectedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                class SwallowOfficeResultMenuOptionSelectedMessageHandler : private Eegeo::NonCopyable
                {
                    CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    Eegeo::Helpers::TCallback1<SwallowOfficeResultMenuOptionSelectedMessageHandler, const SwallowOfficeResultMenuOptionSelectedMessage&> m_binding;
                    
                    void OnSwallowOfficeResultMenuOptionSelected(const SwallowOfficeResultMenuOptionSelectedMessage& message);
                    
                public:
                    SwallowOfficeResultMenuOptionSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                        ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~SwallowOfficeResultMenuOptionSelectedMessageHandler();
                };
            }
        }
    }
}
