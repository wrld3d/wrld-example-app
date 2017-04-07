// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AppInterface.h"
#include "BidirectionalBus.h"
#include "ICompassTouchController.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassTouchController : public ICompassTouchController, private Eegeo::NonCopyable
            {
            public:
                CompassTouchController(ExampleAppMessaging::TMessageBus& messageBus);

                void HandleRotateStart(const AppInterface::RotateData& data) const;
                void HandleRotateEnd(const AppInterface::RotateData& data) const;

            private:
                void PublishIsRotatingStateChangedMessage(bool isRotating) const;

                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}
