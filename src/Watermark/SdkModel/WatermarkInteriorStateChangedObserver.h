// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Watermark.h"
#include "Interiors.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            class WatermarkInteriorStateChangedObserver
            {
            public:
                WatermarkInteriorStateChangedObserver(WatermarkModel& watermarkModel,
                                                      Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                      Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                      InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel,
                                                      ExampleAppMessaging::TMessageBus& messageBus);
                
                ~WatermarkInteriorStateChangedObserver();
                
            private:
                WatermarkModel& m_watermarkModel;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                InteriorsExplorer::SdkModel::InteriorsExplorerModel& m_interiorsExplorerModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnInteriorExplorerEntered();
                Eegeo::Helpers::TCallback0<WatermarkInteriorStateChangedObserver> m_interiorExplorerEnteredCallback;
                
                void OnInteriorExplorerExit();
                Eegeo::Helpers::TCallback0<WatermarkInteriorStateChangedObserver> m_interiorExplorerExitCallback;
            };
        }

    }
}