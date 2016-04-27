// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"

#include "CameraTransitions.h"
#include "LaxOfficeResultMenuOptionSelectedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                class LaxOfficeResultMenuOptionSelectedMessageHandler : private Eegeo::NonCopyable
                {
                    CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
//                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    Eegeo::Helpers::TCallback1<LaxOfficeResultMenuOptionSelectedMessageHandler, const LaxOfficeResultMenuOptionSelectedMessage&> m_binding;
                    
                    void OnLaxOfficeResultMenuOptionSelected(const LaxOfficeResultMenuOptionSelectedMessage& message);
                    
                public:
                    LaxOfficeResultMenuOptionSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                        ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~LaxOfficeResultMenuOptionSelectedMessageHandler();
                };
            }
        }
    }
}
