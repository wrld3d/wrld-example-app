// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinsModule.h"
#include "WorldPins.h"
#include "Pins.h"
#include "PinController.h"
#include "Rendering.h"
#include "Camera.h"
#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "IScreenControlViewModel.h"
#include "WorldPinsModalityObserver.h"
#include "Interiors.h"
#include "SdkModelDomainEventBus.h"
#include "IMenuReactionModel.h"
#include "Labels.h"

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
                IWorldPinsVisibilityController* m_pWorldPinsVisibilityController;
                WorldPinsModalityObserver* m_pWorldPinsModalityObserver;
                
                Eegeo::Labels::LabelAnchorCategory* m_pWorldPinLabelCategory;

            public:
                WorldPinsModule(ExampleAppMessaging::TMessageBus& messageBus,
                                const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus,
                                Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService,
                                Eegeo::Labels::ILabelModelService& labelModelService,
                                Eegeo::Labels::ILabelAnchorFilterModel& labelAnchorFilterModel,
                                Eegeo::Labels::ILabelFilterModel& labelFilterModel,
                                Eegeo::Labels::ILabelPicker& labelPicker);

                ~WorldPinsModule();
                
                void Update(float dt);

                IWorldPinsService& GetWorldPinsService() const;

                IWorldPinsFactory& GetWorldPinsFactory() const;

                IWorldPinsVisibilityController& GetWorldPinsVisibilityController() const;
            };
        }
    }
}
