// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsModule.h"
#include "WorldPins.h"
#include "WorldPinsFactory.h"
#include "WorldPinsRepository.h"
#include "WorldPinsService.h"
#include "WorldPinsVisibilityController.h"
#include "WorldPinIconMappingFactory.h"
#include "WorldPinIconMapping.h"

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
                                             Eegeo::Markers::IMarkerService& markerService,
                                             Eegeo::Location::NavigationService& navigationService,
                                             Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultOnMapMyPinsService,
                                             CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            {
                m_pWorldPinsFactory = Eegeo_NEW(WorldPinsFactory);

                m_pWorldPinsRepository = Eegeo_NEW(WorldPinsRepository);
                
                m_pWorldPinsService = Eegeo_NEW(WorldPinsService)(*m_pWorldPinsRepository,
                                                                    interiorMarkerPickingService,
                                                                    markerService,
                                                                    sdkDomainEventBus,
                                                                    messageBus,
                                                                    navigationService,
                                                                    searchResultOnMapMyPinsService,
                                                                    cameraTransitionController);
                
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
