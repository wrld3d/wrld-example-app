// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinVisibilityStateChangedHandler.h"
#include "MyPinModel.h"
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinVisibilityStateChangedHandler : public WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler
            {
            private:
                MyPinModel& m_myPinModel;
                MyPins::SdkModel::IMyPinBoundObjectRepository& m_myPinBoundObjectRepository;
                
            public:
                MyPinVisibilityStateChangedHandler(MyPinModel& myPinModel,
                                                   MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository);
                
                ~MyPinVisibilityStateChangedHandler();
                
                void HandlePinBecameFullyVisible();
                
                void HandlePinBecameFullyInvisible();
            };
        }
    }
}
