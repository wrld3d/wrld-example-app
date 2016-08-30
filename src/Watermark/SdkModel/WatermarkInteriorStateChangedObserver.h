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
                WatermarkInteriorStateChangedObserver(const std::shared_ptr<WatermarkModel>& watermarkModel,
                                                      const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel,
                                                      const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsModelRepository>& interiorsModelRepository,
                                                      const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel>& m_interiorsExplorerModel,
                                                      const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                
                ~WatermarkInteriorStateChangedObserver();
                
            private:
                const std::shared_ptr<WatermarkModel> m_watermarkModel;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel> m_interiorSelectionModel;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsModelRepository> m_interiorsModelRepository;
                const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorsExplorerModel> m_interiorsExplorerModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                
                void OnInteriorExplorerEntered();
                Eegeo::Helpers::TCallback0<WatermarkInteriorStateChangedObserver> m_interiorExplorerEnteredCallback;
                
                void OnInteriorExplorerExit();
                Eegeo::Helpers::TCallback0<WatermarkInteriorStateChangedObserver> m_interiorExplorerExitCallback;
            };
        }

    }
}