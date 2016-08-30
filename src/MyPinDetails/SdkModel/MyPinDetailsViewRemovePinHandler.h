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

                MyPinDetailsViewRemovePinHandler(const std::shared_ptr<MyPins::SdkModel::IMyPinsService>& myPinsService,
                                                 const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~MyPinDetailsViewRemovePinHandler();

            private:
                
                const std::shared_ptr<MyPins::SdkModel::IMyPinsService>& m_myPinsService;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinDetailsViewRemovePinHandler, const MyPinDetailsViewRemovePinMessage&> m_handler;

                void OnMyPinCreationViewSavePinMessage(const MyPinDetailsViewRemovePinMessage& message);
            };
        }
    }
}
