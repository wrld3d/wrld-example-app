// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "Search.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "Labels.h"
#include "LabelLayer.h"

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
                                                     Eegeo::Labels::ILabelFilterModel& labelFilterModel,
                                                     const Eegeo::Labels::LabelLayer::IdType& interiorMarkerLabelLayer,
                                                     ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinCreationViewStateChangedHandler();

            private:
                IMyPinCreationModel& m_myPinCreationModel;
                Search::SdkModel::ISearchRefreshService& m_searchRefreshService;
                Eegeo::Labels::ILabelFilterModel& m_labelFilterModel;
                Eegeo::Labels::LabelLayer::IdType m_interiorMarkerLabelLayer;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinCreationViewStateChangedHandler, const MyPinCreationViewStateChangedMessage&> m_handler;

                void OnMyPinCreationViewStateChangedMessage(const MyPinCreationViewStateChangedMessage& message);
            };
        }
    }
}
