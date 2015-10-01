// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowOfficeResultMenuOptionSelectedMessageHandler.h"

#include "MathFunc.h"

#include "ICameraTransitionController.h"
#include "SwallowOfficeResultMenuOptionSelectedMessage.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                SwallowOfficeResultMenuOptionSelectedMessageHandler::SwallowOfficeResultMenuOptionSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                                                                         ExampleAppMessaging::TMessageBus& messageBus)
                : m_cameraTransitionController(cameraTransitionController)
                , m_messageBus(messageBus)
                , m_binding(this, &SwallowOfficeResultMenuOptionSelectedMessageHandler::OnSwallowOfficeResultMenuOptionSelected)
                {
                    m_messageBus.SubscribeNative(m_binding);
                }
                    
                SwallowOfficeResultMenuOptionSelectedMessageHandler::~SwallowOfficeResultMenuOptionSelectedMessageHandler()
                {
                    m_messageBus.UnsubscribeNative(m_binding);
                }
                
                void SwallowOfficeResultMenuOptionSelectedMessageHandler::OnSwallowOfficeResultMenuOptionSelected(const SwallowOfficeResultMenuOptionSelectedMessage& message)
                {
                    m_cameraTransitionController.StartTransitionTo(message.GetLocation().ToECEF(), message.GetDistance(), Eegeo::Math::Deg2Rad(message.GetHeadingDegrees()));
                }
            }
        }
    }
}
