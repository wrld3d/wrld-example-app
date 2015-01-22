// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "Search.h"
#include "MyPinCreationViewStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationViewStateChangedHandler
        {
        public:
            
            MyPinCreationViewStateChangedHandler(IMyPinCreationModel& myPinCreationModel,
                                                 Search::ISearchRefreshService& searchRefreshService,
                                                 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~MyPinCreationViewStateChangedHandler();

        private:
            IMyPinCreationModel& m_myPinCreationModel;
            Search::ISearchRefreshService& m_searchRefreshService;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinCreationViewStateChangedHandler, const MyPinCreationViewStateChangedMessage&> m_handler;
            
            void OnMyPinCreationViewStateChangedMessageReceived(const MyPinCreationViewStateChangedMessage& message);
        };
    }
}
