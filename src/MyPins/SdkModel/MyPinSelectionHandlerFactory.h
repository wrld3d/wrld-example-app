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
            class MyPinSelectionHandlerFactory : public IMyPinSelectionHandlerFactory, private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<MyPins::SdkModel::IMyPinBoundObjectRepository> m_myPinBoundObjectRepository;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

            public:
                MyPinSelectionHandlerFactory(const std::shared_ptr<MyPins::SdkModel::IMyPinBoundObjectRepository>& myPinBoundObjectRepository,
                                             const std::shared_ptr<Metrics::IMetricsService>& metricsService);

                MyPinSelectionHandler* CreateMyPinSelectionHandler(MyPinModel& myPinModel) const;
            };
        }
    }
}
