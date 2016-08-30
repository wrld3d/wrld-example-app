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

                MyPinCreationViewSavePinHandler(const std::shared_ptr<IMyPinCreationModel>& myPinCreationModel,
                                                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~MyPinCreationViewSavePinHandler();

            private:
                const std::shared_ptr<IMyPinCreationModel> m_myPinCreationModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinCreationViewSavePinHandler, const MyPinCreationViewSavePinMessage&> m_handler;

                void OnMyPinCreationViewSavePinMessageMessage(const MyPinCreationViewSavePinMessage& message);
            };
        }
    }
}
