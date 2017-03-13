// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "WorldPins.h"
#include "IWorldPinsVisibilityController.h"
#include "Location.h"
#include "Rendering.h"
#include "VectorMath.h"
#include "Modality.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SdkModelDomainEventBus.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsVisibilityController : public IWorldPinsVisibilityController, private Eegeo::NonCopyable
            {
            private:
                IWorldPinsRepository& m_worldPinsRepository;
                float m_modality;
                bool m_hideOutdoorPinsIndoors;
                bool m_pinsVisible;
                
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                const Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinsVisibilityController, const WorldPinsVisibilityMessage&> m_visibilityMessageHandlerBinding;
                
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkDomainEventBus;
                
                int m_visibilityMask;
                
            public:
                WorldPinsVisibilityController(IWorldPinsRepository& worldPinsRepository,
                                              ExampleAppMessaging::TMessageBus& messageBus,
                                              const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                              const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                              ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus);
                
                ~WorldPinsVisibilityController();
                
                void Update(float deltaSeconds);
                
                void SetModality(float modality);
                
                int GetVisibilityMask();
                
                void SetVisibilityMask(int visibilityMask);
                
                void SetHideOutdoorPinsIndoors(bool hideOutdoorPinsIndoors);
                
                void Show();
                void Hide();
                
                
            private:
                bool ShouldHidePin(WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel);
                
                void UpdateWorldPin(WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel,
                                    float deltaSeconds);
                
                void OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage& worldPinsVisibilityMessage);
            };
        }
    }
}
