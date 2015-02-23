// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinSelectionHandlerFactory.h"
#include "MyPins.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinSelectionHandlerFactory : public IMyPinSelectionHandlerFactory
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                MyPinSelectionHandlerFactory(ExampleAppMessaging::TMessageBus& messageBus);

                MyPinSelectionHandler* CreateMyPinSelectionHandler(MyPinModel& myPinModel) const;
            };
        }
    }
}
