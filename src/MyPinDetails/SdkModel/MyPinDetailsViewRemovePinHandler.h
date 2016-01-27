// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "MyPinDetailsViewRemovePinMessage.h"
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            class MyPinDetailsViewRemovePinHandler
            {
            public:

                MyPinDetailsViewRemovePinHandler(MyPins::SdkModel::IMyPinsService& myPinsService,
                                                 ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinDetailsViewRemovePinHandler();

            private:
                
                MyPins::SdkModel::IMyPinsService& m_myPinsService;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinDetailsViewRemovePinHandler, const MyPinDetailsViewRemovePinMessage&> m_handler;

                void OnMyPinCreationViewSavePinMessage(const MyPinDetailsViewRemovePinMessage& message);
            };
        }
    }
}
