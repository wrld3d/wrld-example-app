// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsModule.h"
#include "WorldPins.h"
#include "WorldPinsFactory.h"
#include "WorldPinsRepository.h"
#include "WorldPinsService.h"
#include "WorldPinsVisibilityController.h"
#include "WorldPinIconMappingFactory.h"
#include "WorldPinIconMapping.h"
#include "ILabelModelService.h"
#include "LabelAnchorCategory.h"
#include "LabelLayer.h"
#include "ILabelFilterModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsModule::WorldPinsModule(ExampleAppMessaging::TMessageBus& messageBus,
                                             const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus,
                                             Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService,
                                             Eegeo::Labels::ILabelModelService& labelModelService,
                                             Eegeo::Labels::ILabelAnchorFilterModel& labelAnchorFilterModel,
                                             Eegeo::Labels::ILabelFilterModel& labelFilterModel,
                                             Eegeo::Labels::ILabelPicker& labelPicker,
                                             bool isInKioskMode)
            {
                m_pWorldPinsFactory = Eegeo_NEW(WorldPinsFactory);

                m_pWorldPinsRepository = Eegeo_NEW(WorldPinsRepository);
                
                Eegeo::Labels::LabelLayer::IdType labelLayerId = labelModelService.RegisterLayer("pins");
                labelFilterModel.SetLayerShownInExterior(labelLayerId, true);
                labelFilterModel.SetLayerShownInInterior(labelLayerId, true);
                m_pWorldPinLabelCategory = Eegeo::Labels::LabelAnchorCategory::Create("eea_pin_label", labelLayerId, 0, 14, Eegeo::Labels::LabelPlacement::Point, true);
                m_pWorldPinsService = Eegeo_NEW(WorldPinsService)(labelModelService,
                                                                  labelAnchorFilterModel,
                                                                  *m_pWorldPinLabelCategory,
                                                                  labelPicker,
                                                                  labelLayerId,
                                                                  *m_pWorldPinsRepository,
                                                                  interiorMarkerPickingService);
                
                m_pWorldPinsVisibilityController = Eegeo_NEW(WorldPinsVisibilityController)(*m_pWorldPinsRepository,
                                                                                            messageBus,
                                                                                            interiorInteractionModel,
                                                                                            interiorTransitionModel,
                                                                                            sdkDomainEventBus);
                
                m_pWorldPinsModalityObserver = Eegeo_NEW(WorldPinsModalityObserver)(*m_pWorldPinsVisibilityController,
                                                                                    messageBus);
            }

            WorldPinsModule::~WorldPinsModule()
            {
                Eegeo_DELETE m_pWorldPinsModalityObserver;
                Eegeo_DELETE m_pWorldPinsVisibilityController;
                Eegeo_DELETE m_pWorldPinsService;
                Eegeo_DELETE m_pWorldPinsRepository;
                Eegeo_DELETE m_pWorldPinsFactory;
            }
            
            void WorldPinsModule::Update(float dt)
            {
                m_pWorldPinsService->Update(dt);
                m_pWorldPinsVisibilityController->Update(dt);
            }

            IWorldPinsService& WorldPinsModule::GetWorldPinsService() const
            {
                return *m_pWorldPinsService;
            }

            IWorldPinsFactory& WorldPinsModule::GetWorldPinsFactory() const
            {
                return *m_pWorldPinsFactory;
            }

            IWorldPinsVisibilityController& WorldPinsModule::GetWorldPinsVisibilityController() const
            {
                return *m_pWorldPinsVisibilityController;
            }
        }
    }
}
