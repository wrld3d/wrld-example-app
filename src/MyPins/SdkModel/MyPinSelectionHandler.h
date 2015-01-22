// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"
#include "MyPinModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
            {
            private:
                MyPinModel& m_myPinModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

            public:
                MyPinSelectionHandler(MyPinModel& myPinModel,
                                      ExampleAppMessaging::TMessageBus& messageBus);

                void SelectPin();
            };
        }
    }
}
