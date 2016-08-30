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

                MyPinCreationViewStateChangedHandler(const std::shared_ptr<IMyPinCreationModel>& myPinCreationModel,
                                                     const std::shared_ptr<Search::SdkModel::ISearchRefreshService>& searchRefreshService,
                                                     const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~MyPinCreationViewStateChangedHandler();

            private:
                const std::shared_ptr<IMyPinCreationModel> m_myPinCreationModel;
                const std::shared_ptr<Search::SdkModel::ISearchRefreshService> m_searchRefreshService;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinCreationViewStateChangedHandler, const MyPinCreationViewStateChangedMessage&> m_handler;

                void OnMyPinCreationViewStateChangedMessage(const MyPinCreationViewStateChangedMessage& message);
            };
        }
    }
}
