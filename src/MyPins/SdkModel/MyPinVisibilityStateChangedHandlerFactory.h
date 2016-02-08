// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinVisibilityStateChangedHandlerFactory.h"
#include "MyPins.h"

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
                
            public:
                MyPinVisibilityStateChangedHandlerFactory(MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository);
                
                WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler* CreateMyPinVisibilityStateChangedHandler(MyPinModel& myPinModel) const;
            };
        }
    }
}
