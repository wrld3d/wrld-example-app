// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinsModule.h"
#include "WorldPins.h"
#include "Pins.h"
#include "PinController.h"
#include "Rendering.h"
#include "Camera.h"
#include "BidirectionalBus.h"
#include "WorldPinInFocusObserver.h"
#include "IIdentity.h"
#include "IScreenControlViewModel.h"
#include "WorldPinsModalityObserver.h"
#include "Interiors.h"
#include "SdkModelDomainEventBus.h"
#include "IMenuReactionModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsModule : public IWorldPinsModule
            {
                IWorldPinsFactory* m_pWorldPinsFactory;
                IWorldPinsService* m_pWorldPinsService;
                IWorldPinsRepository* m_pWorldPinsRepository;
                IWorldPinsScaleController* m_pWorldPinsScaleController;
                IWorldPinsFloorHeightController* m_pWorldPinsFloorHeightController;
                View::WorldPinInFocusViewModel* m_pWorldPinsInFocusViewModel;
                IWorldPinsInFocusController* m_pWorldPinsInFocusController;
                View::WorldPinInFocusObserver* m_pWorldPinInFocusObserver;
                WorldPinsModalityObserver* m_pWorldPinsModalityObserver;
                IWorldPinIconMapping* m_pWorldPinIconMapping;

            public:
                WorldPinsModule(Eegeo::Pins::PinRepository& pinRepository,
                                Eegeo::Pins::PinController& pinController,
                                const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                Eegeo::Helpers::IIdentityProvider& identityProvider,
                                ExampleAppMessaging::TMessageBus& messageBus,
                                const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus,
                                const bool interiorsAffectedByFlattening,
                                const Menu::View::IMenuReactionModel& menuReaction,
                                const float screenOversampleScale,
                                const IWorldPinIconMappingFactory& worldPinIconMappingFactory);

                ~WorldPinsModule();

                IWorldPinsService& GetWorldPinsService() const;

                IWorldPinsFactory& GetWorldPinsFactory() const;

                IWorldPinsScaleController& GetWorldPinsScaleController() const;
                
                IWorldPinsFloorHeightController& GetWorldPinsFloorHeightController() const;

                View::IWorldPinInFocusViewModel& GetWorldPinInFocusViewModel() const;

                IWorldPinsInFocusController& GetWorldPinsInFocusController() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
                
                IWorldPinIconMapping& GetWorldPinIconMapping() const;
            };
        }
    }
}
