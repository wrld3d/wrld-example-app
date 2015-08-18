// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorPinScaleController.h"
#include "InteriorsPinsController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorPinScaleController::InteriorPinScaleController(Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
            : m_interiorsPinsController(interiorsPinsController)
            , m_messageBus(messageBus)
            , m_setScaleCallback(this, &InteriorPinScaleController::OnSetScaleMessageReceived)
            {
                m_messageBus.SubscribeNative(m_setScaleCallback);
            }
            
            InteriorPinScaleController::~InteriorPinScaleController()
            {
                m_messageBus.UnsubscribeNative(m_setScaleCallback);
            }
  
            void InteriorPinScaleController::OnSetScaleMessageReceived(const InteriorPinsSetScaleMessage& message)
            {
                m_interiorsPinsController.SetTargetPinScale(message.GetScale());
            }
        }
    }
}