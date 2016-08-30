// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinVisibilityStateChangedHandlerFactory.h"
#include "Types.h"
#include "MyPins.h"
#include <memory>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinVisibilityStateChangedHandlerFactory : public IMyPinVisibilityStateChangedHandlerFactory, private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<MyPins::SdkModel::IMyPinBoundObjectRepository> m_myPinBoundObjectRepository;
                
            public:
                MyPinVisibilityStateChangedHandlerFactory(const std::shared_ptr<MyPins::SdkModel::IMyPinBoundObjectRepository>& myPinBoundObjectRepository);
                
                WorldPins::SdkModel::IWorldPinVisibilityStateChangedHandler* CreateMyPinVisibilityStateChangedHandler(MyPinModel& myPinModel) const;
            };
        }
    }
}
