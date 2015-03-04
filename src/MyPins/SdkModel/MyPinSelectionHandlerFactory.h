// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMyPinSelectionHandlerFactory.h"
#include "MyPins.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"

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
                
                Metrics::IMetricsService& m_metricsService;

            public:
                MyPinSelectionHandlerFactory(MyPins::SdkModel::IMyPinBoundObjectRepository& myPinBoundObjectRepository, Metrics::IMetricsService& metricsService);

                MyPinSelectionHandler* CreateMyPinSelectionHandler(MyPinModel& myPinModel) const;
            };
        }
    }
}
