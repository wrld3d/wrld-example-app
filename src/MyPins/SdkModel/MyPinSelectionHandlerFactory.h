// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinSelectionHandlerFactory.h"
#include "MyPins.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinSelectionHandlerFactory : public IMyPinSelectionHandlerFactory
            {
            private:
                MyPins::SdkModel::IMyPinBoundObjectRepository& m_myPinBoundObjectRepository;

            public:
                MyPinSelectionHandlerFactory(MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository);

                MyPinSelectionHandler* CreateMyPinSelectionHandler(MyPinModel& myPinModel) const;
            };
        }
    }
}
