// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkInteriorStateChangedObserver.h"
#include "WatermarkDataRepository.h"
#include "WatermarkModelChangedMessage.h"
#include "WatermarkModel.h"
#include "InteriorsModelRepository.h"
#include "InteriorsModel.h"
#include "WatermarkAlignmentStateChangedMessage.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            WatermarkInteriorStateChangedObserver::WatermarkInteriorStateChangedObserver(WatermarkModel& watermarkModel,
                                                                                         Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                                         ExampleAppMessaging::TMessageBus& messageBus,
                                                                                         ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus)
            : m_watermarkModel(watermarkModel)
            , m_interiorsModelRepository(interiorsModelRepository)
            , m_messageBus(messageBus)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_interiorExplorerEnteredCallback(this, &WatermarkInteriorStateChangedObserver::OnInteriorExplorerEntered)
            , m_interiorExplorerExitCallback(this, &WatermarkInteriorStateChangedObserver::OnInteriorExplorerExit)
            {
                m_messageBus.SubscribeNative(m_interiorExplorerExitCallback);
                m_sdkModelDomainEventBus.Subscribe(m_interiorExplorerEnteredCallback);
            }
                
            WatermarkInteriorStateChangedObserver::~WatermarkInteriorStateChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_interiorExplorerExitCallback);
                m_sdkModelDomainEventBus.Unsubscribe(m_interiorExplorerEnteredCallback);
            }
            
            void WatermarkInteriorStateChangedObserver::OnInteriorExplorerEntered(const InteriorsExplorer::InteriorsExplorerEnteredMessage& message)
            {
                const std::string& interiorName = message.GetInteriorId().Value();
                
                if (m_interiorsModelRepository.HasInterior(interiorName))
                {
                    Eegeo::Resources::Interiors::InteriorsModel& interiorModel = m_interiorsModelRepository.GetInterior(interiorName);
                    const std::string& sourceVendor = interiorModel.GetSourceVendor();
                    
                    m_watermarkModel.SetId(sourceVendor);
                    
                    m_messageBus.Publish(WatermarkAlignmentStateChangedMessage(true));
                    m_messageBus.Publish(WatermarkModelChangedMessage(m_watermarkModel.GetId()));
                }
            }
            
            void WatermarkInteriorStateChangedObserver::OnInteriorExplorerExit(const InteriorsExplorer::InteriorsExplorerExitMessage& message)
            {
                m_watermarkModel.SetId(DefaultEegeoWatermarkId);
                m_messageBus.Publish(WatermarkAlignmentStateChangedMessage(false));
                m_messageBus.Publish(WatermarkModelChangedMessage(m_watermarkModel.GetId()));
            }
        }
    }
}