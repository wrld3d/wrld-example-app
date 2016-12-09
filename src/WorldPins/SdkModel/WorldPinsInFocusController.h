// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WorldPins.h"
#include "IWorldPinsInFocusController.h"
#include "VectorMathDecl.h"
#include "Location.h"
#include "Camera.h"
#include "BidirectionalBus.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsInFocusController : public IWorldPinsInFocusController, private Eegeo::NonCopyable
            {
            private:
                IWorldPinsRepository& m_worldPinsRepository;
                IWorldPinsService& m_worldPinsService;

                const IWorldPinsInFocusModel* m_pLastFocussedModel;

                bool m_focusEnabled;
                bool m_directionEnabled;
                const float m_screenOversampleScale;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinsInFocusController, const WorldPinsVisibilityMessage&> m_visibilityMessageHandlerBinding;
                Eegeo::Helpers::TCallback1<WorldPinsInFocusController, const WorldPinsSelectedFocussedMessage&> m_selectedFocussedMessageHandlerBinding;

                void OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage& worldPinsVisibilityMessage);
                void OnSelectedFocussedMessage(const WorldPinsSelectedFocussedMessage& worldPinsSelectedFocussedMessage);

            public:
                WorldPinsInFocusController(IWorldPinsRepository& worldPinsRepository,
                                           IWorldPinsService& worldPinsService,
                                           float screenOversampleScale,
                                           ExampleAppMessaging::TMessageBus& messageBus);

                ~WorldPinsInFocusController();

                void Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint, const Eegeo::Camera::RenderCamera& renderCamera);
                
                void SetDiretionMenuState(bool open);

            };
        }
    }
}
