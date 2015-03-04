// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"
#include "MyPinModel.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

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
                
                Metrics::IMetricsService& m_metricsService;

            public:
                MyPinSelectionHandler(MyPinModel& myPinModel,
                                      MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository,
                                      Metrics::IMetricsService& metricsService);

                void SelectPin();
            };
        }
    }
}
