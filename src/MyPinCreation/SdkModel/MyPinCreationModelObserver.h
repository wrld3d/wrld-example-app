// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "IMyPinCreationModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class MyPinCreationModelObserver : public Eegeo::NonCopyable
            {
            public:
                MyPinCreationModelObserver(IMyPinCreationModel& myPinCreationModel,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinCreationModelObserver();

            private:
                IMyPinCreationModel& m_myPinCreationModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinCreationModelObserver, MyPinCreationStage> m_callback;

                void HandlePoiCreationModelStateChange(MyPinCreationStage& stage);
            };
        }
    }
}
