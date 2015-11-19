// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Watermark.h"
#include "Interiors.h"
#include "ICallback.h"
#include "InteriorsExplorerEnteredMessage.h"
#include "InteriorsExplorerExitMessage.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"

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
                                                      Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                      ExampleAppMessaging::TMessageBus& messageBus,
                                                      ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus);
                
                ~WatermarkInteriorStateChangedObserver();
                
            private:
                WatermarkModel& m_watermarkModel;
                Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkModelDomainEventBus;
                
                void OnInteriorExplorerEntered(const InteriorsExplorer::InteriorsExplorerEnteredMessage& message);
                Eegeo::Helpers::TCallback1<WatermarkInteriorStateChangedObserver, const InteriorsExplorer::InteriorsExplorerEnteredMessage&> m_interiorExplorerEnteredCallback;
                
                void OnInteriorExplorerExit(const InteriorsExplorer::InteriorsExplorerExitMessage& message);
                Eegeo::Helpers::TCallback1<WatermarkInteriorStateChangedObserver, const InteriorsExplorer::InteriorsExplorerExitMessage&> m_interiorExplorerExitCallback;
            };
        }

    }
}