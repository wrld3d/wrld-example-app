// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "AppInterface.h"
#include "BidirectionalBus.h"
#include "CompassTouchController.h"
#include "CompassIsRotatingStateChangedMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassTouchController::CompassTouchController(ExampleAppMessaging::TMessageBus& messageBus)
                : m_messageBus(messageBus)
            {
            }

            void CompassTouchController::HandleRotateStart(const AppInterface::RotateData& data) const
            {
                PublishIsRotatingStateChangedMessage(true);
            }
            
            void CompassTouchController::HandleRotateEnd(const AppInterface::RotateData& data) const
            {
                PublishIsRotatingStateChangedMessage(false);
            }

            void CompassTouchController::PublishIsRotatingStateChangedMessage(bool isRotating) const
            {
                m_messageBus.Publish(CompassIsRotatingStateChangedMessage(isRotating));
            }
        }
    }
}
