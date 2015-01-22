// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WorldPins.h"
#include "IWorldPinsScaleController.h"
#include "Location.h"
#include "Rendering.h"
#include "Camera.h"
#include "VectorMath.h"
#include "Modality.h"
#include "BidirectionalBus.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsScaleController : public IWorldPinsScaleController, private Eegeo::NonCopyable
            {
            private:
                IWorldPinsRepository& m_worldPinsRepository;
                IWorldPinsService& m_worldPinsService;
                float m_modality;
                float m_visibilityScale;
                float m_targetVisibilityScale;
                const float m_visibilityAnimationDuration;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinsScaleController, const WorldPinsVisibilityMessage&> m_visibilityMessageHandlerBinding;

            public:
                WorldPinsScaleController(IWorldPinsRepository& worldPinsRepository,
                                         WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                         ExampleAppMessaging::TMessageBus& messageBus);

                ~WorldPinsScaleController();

                void Update(float deltaSeconds, const Eegeo::Camera::RenderCamera& renderCamera);

                void SetModality(float modality);

                void Show();
                void Hide();


            private:
                void UpdateWorldPin(WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel,
                                    float deltaSeconds,
                                    const Eegeo::Camera::RenderCamera& renderCamera);

                void GetScreenLocation(const WorldPins::SdkModel::WorldPinItemModel& worldPinItemModel,
                                       Eegeo::v2& screenLocation,
                                       const Eegeo::Camera::RenderCamera& renderCamera) const;

                void OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage& worldPinsVisibilityMessage);
            };
        }
    }
}
