// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinVisibilityStateChangedHandlerFactory.h"
#include "MyPins.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinVisibilityStateChangedHandlerFactory : public IMyPinVisibilityStateChangedHandlerFactory
            {
            private:
                MyPins::SdkModel::IMyPinBoundObjectRepository& m_myPinBoundObjectRepository;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
            public:
                MyPinVisibilityStateChangedHandlerFactory(MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository,
                                             ExampleAppMessaging::TMessageBus& messageBus);
                
                WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler* CreateMyPinVisibilityStateChangedHandler(MyPinModel& myPinModel) const;
            };
        }
    }
}
