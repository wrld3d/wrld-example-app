// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "Search.h"
#include "MyPinCreationViewStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            class MyPinCreationViewStateChangedHandler
            {
            public:

                MyPinCreationViewStateChangedHandler(IMyPinCreationModel& myPinCreationModel,
                                                     Search::SdkModel::ISearchRefreshService& searchRefreshService,
                                                     ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinCreationViewStateChangedHandler();

            private:
                IMyPinCreationModel& m_myPinCreationModel;
                Search::SdkModel::ISearchRefreshService& m_searchRefreshService;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinCreationViewStateChangedHandler, const MyPinCreationViewStateChangedMessage&> m_handler;

                void OnMyPinCreationViewStateChangedMessage(const MyPinCreationViewStateChangedMessage& message);
            };
        }
    }
}
