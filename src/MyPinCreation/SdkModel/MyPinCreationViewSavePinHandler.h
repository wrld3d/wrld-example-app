// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "MyPinCreationViewSavePinMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class MyPinCreationViewSavePinHandler
            {
            public:

                MyPinCreationViewSavePinHandler(IMyPinCreationModel& myPinCreationModel,
                                                ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinCreationViewSavePinHandler();

            private:
                IMyPinCreationModel& m_myPinCreationModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinCreationViewSavePinHandler, const MyPinCreationViewSavePinMessage&> m_handler;

                void OnMyPinCreationViewSavePinMessageMessage(const MyPinCreationViewSavePinMessage& message);
            };
        }
    }
}
