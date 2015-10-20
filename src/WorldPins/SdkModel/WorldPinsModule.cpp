// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsModule.h"
#include "WorldPins.h"
#include "WorldPinsFactory.h"
#include "WorldPinsRepository.h"
#include "WorldPinsService.h"
#include "WorldPinsScaleController.h"
#include "WorldPinsFloorHeightController.h"
#include "WorldPinsInFocusController.h"
#include "WorldPinInFocusViewModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsModule::WorldPinsModule(Eegeo::Pins::PinRepository& pinRepository,
                                             Eegeo::Pins::PinController& pinController,
                                             const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                             ExampleAppMessaging::TMessageBus& messageBus,
                                             Eegeo::Resources::Interiors::InteriorController& interiorController,
                                             ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus)
            {
                m_pWorldPinsFactory = Eegeo_NEW(WorldPinsFactory);

                m_pWorldPinsRepository = Eegeo_NEW(WorldPinsRepository);

                m_pWorldPinsService = Eegeo_NEW(WorldPinsService)(*m_pWorldPinsRepository,
                                      *m_pWorldPinsFactory,
                                      pinRepository,
                                      pinController,
                                      environmentFlatteningService);

                m_pWorldPinsScaleController = Eegeo_NEW(WorldPinsScaleController)(*m_pWorldPinsRepository,
                                              *m_pWorldPinsService,
                                              messageBus,
                                              interiorController,
                                              sdkDomainEventBus);
                
                
                m_pWorldPinsFloorHeightController = Eegeo_NEW(WorldPinsFloorHeightController)(*m_pWorldPinsRepository,
                                                                                              pinRepository,
                                                                                              interiorController);

                m_pWorldPinsInFocusViewModel = Eegeo_NEW(View::WorldPinInFocusViewModel)(identityProvider.GetNextIdentity(),
                                               *m_pWorldPinsService);

                m_pWorldPinsInFocusController = Eegeo_NEW(WorldPinsInFocusController)(*m_pWorldPinsRepository,
                                                *m_pWorldPinsService,
                                                messageBus);


                m_pWorldPinInFocusObserver = Eegeo_NEW(View::WorldPinInFocusObserver)(*m_pWorldPinsInFocusViewModel,
                                             messageBus);

                m_pWorldPinsModalityObserver = Eegeo_NEW(WorldPinsModalityObserver)(*m_pWorldPinsScaleController,
                                               messageBus);


            }

            WorldPinsModule::~WorldPinsModule()
            {
                Eegeo_DELETE m_pWorldPinsModalityObserver;
                Eegeo_DELETE m_pWorldPinInFocusObserver;
                Eegeo_DELETE m_pWorldPinsInFocusController;
                Eegeo_DELETE m_pWorldPinsInFocusViewModel;
                Eegeo_DELETE m_pWorldPinsFloorHeightController;
                Eegeo_DELETE m_pWorldPinsScaleController;
                Eegeo_DELETE m_pWorldPinsService;
                Eegeo_DELETE m_pWorldPinsRepository;
                Eegeo_DELETE m_pWorldPinsFactory;
            }

            IWorldPinsService& WorldPinsModule::GetWorldPinsService() const
            {
                return *m_pWorldPinsService;
            }

            IWorldPinsFactory& WorldPinsModule::GetWorldPinsFactory() const
            {
                return *m_pWorldPinsFactory;
            }

            IWorldPinsScaleController& WorldPinsModule::GetWorldPinsScaleController() const
            {
                return *m_pWorldPinsScaleController;
            }
            
            IWorldPinsFloorHeightController& WorldPinsModule::GetWorldPinsFloorHeightController() const
            {
                return *m_pWorldPinsFloorHeightController;
            }

            View::IWorldPinInFocusViewModel& WorldPinsModule::GetWorldPinInFocusViewModel() const
            {
                return *m_pWorldPinsInFocusViewModel;
            }

            IWorldPinsInFocusController& WorldPinsModule::GetWorldPinsInFocusController() const
            {
                return *m_pWorldPinsInFocusController;
            }

            ScreenControl::View::IScreenControlViewModel& WorldPinsModule::GetScreenControlViewModel() const
            {
                return m_pWorldPinsInFocusViewModel->GetScreenControlViewModel();
            }
        }
    }
}
