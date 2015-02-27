// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"
#include "MyPinModel.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
            {
            private:
                MyPinModel& m_myPinModel;
                MyPins::SdkModel::IMyPinBoundObjectRepository& m_myPinBoundObjectRepository;

            public:
                MyPinSelectionHandler(MyPinModel& myPinModel,
                                      MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository);

                void SelectPin();
            };
        }
    }
}
