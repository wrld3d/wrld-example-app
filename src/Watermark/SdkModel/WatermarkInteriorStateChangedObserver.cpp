// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkInteriorStateChangedObserver.h"
#include "WatermarkDataRepository.h"
#include "WatermarkModelChangedMessage.h"
#include "WatermarkModel.h"
#include "InteriorsModelRepository.h"
#include "InteriorsModel.h"
#include "WatermarkAlignmentStateChangedMessage.h"
#include "InteriorsExplorerModel.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace SdkModel
        {
            WatermarkInteriorStateChangedObserver::WatermarkInteriorStateChangedObserver(WatermarkModel& watermarkModel,
                                                                                         Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                                         Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                                                                         InteriorsExplorer::SdkModel::InteriorsExplorerModel& interiorsExplorerModel,
                                                                                         ExampleAppMessaging::TMessageBus& messageBus)
            : m_watermarkModel(watermarkModel)
            , m_interiorSelectionModel(interiorSelectionModel)
            , m_interiorsModelRepository(interiorsModelRepository)
            , m_interiorsExplorerModel(interiorsExplorerModel)
            , m_messageBus(messageBus)
            , m_interiorExplorerEnteredCallback(this, &WatermarkInteriorStateChangedObserver::OnInteriorExplorerEntered)
            , m_interiorExplorerExitCallback(this, &WatermarkInteriorStateChangedObserver::OnInteriorExplorerExit)
            {
                m_interiorsExplorerModel.InsertInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.InsertInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
                
            WatermarkInteriorStateChangedObserver::~WatermarkInteriorStateChangedObserver()
            {
                m_interiorsExplorerModel.RemoveInteriorExplorerEnteredCallback(m_interiorExplorerEnteredCallback);
                m_interiorsExplorerModel.RemoveInteriorExplorerExitedCallback(m_interiorExplorerExitCallback);
            }
            
            void WatermarkInteriorStateChangedObserver::OnInteriorExplorerEntered()
            {
                const std::string& interiorName = m_interiorSelectionModel.GetSelectedInteriorId().Value();
                
                if (m_interiorsModelRepository.HasInterior(interiorName))
                {
                    Eegeo::Resources::Interiors::InteriorsModel& interiorModel = m_interiorsModelRepository.GetInterior(interiorName);
                    const std::string& sourceVendor = interiorModel.GetSourceVendor();
                    
                    m_watermarkModel.SetId(sourceVendor);
                    m_messageBus.Publish(WatermarkAlignmentStateChangedMessage(false, true));
                    m_messageBus.Publish(WatermarkModelChangedMessage(m_watermarkModel.GetId()));
                }
            }
            
            void WatermarkInteriorStateChangedObserver::OnInteriorExplorerExit()
            {
                m_watermarkModel.SetId(DefaultEegeoWatermarkId);
                m_messageBus.Publish(WatermarkAlignmentStateChangedMessage(false, false));
                m_messageBus.Publish(WatermarkModelChangedMessage(m_watermarkModel.GetId()));
            }
        }
    }
}
