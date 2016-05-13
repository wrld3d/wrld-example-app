// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxOfficeResultMenuOptionSelectedMessageHandler.h"

#include "MathFunc.h"

#include "ICameraTransitionController.h"
#include "LaxOfficeResultMenuOptionSelectedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                LaxOfficeResultMenuOptionSelectedMessageHandler::LaxOfficeResultMenuOptionSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                                                                         ExampleAppMessaging::TMessageBus& messageBus)
                : m_cameraTransitionController(cameraTransitionController)
//                , m_messageBus(messageBus)
                , m_binding(this, &LaxOfficeResultMenuOptionSelectedMessageHandler::OnLaxOfficeResultMenuOptionSelected)
                {
                    //m_messageBus.SubscribeNative(m_binding);
                }
                    
                LaxOfficeResultMenuOptionSelectedMessageHandler::~LaxOfficeResultMenuOptionSelectedMessageHandler()
                {
                    //m_messageBus.UnsubscribeNative(m_binding);
                }
                
                void LaxOfficeResultMenuOptionSelectedMessageHandler::OnLaxOfficeResultMenuOptionSelected(const LaxOfficeResultMenuOptionSelectedMessage& message)
                {
                    m_cameraTransitionController.StartTransitionTo(message.GetLocation().ToECEF(), message.GetDistance(), Eegeo::Math::Deg2Rad(message.GetHeadingDegrees()));
                }
            }
        }
    }
}
