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
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsInFocusController : public IWorldPinsInFocusController, private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<IWorldPinsRepository> m_worldPinsRepository;
                const std::shared_ptr<IWorldPinsService> m_worldPinsService;

                const IWorldPinsInFocusModel* m_pLastFocussedModel;

                bool m_focusEnabled;
                const float m_screenOversampleScale;

                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinsInFocusController, const WorldPinsVisibilityMessage&> m_visibilityMessageHandlerBinding;
                Eegeo::Helpers::TCallback1<WorldPinsInFocusController, const WorldPinsSelectedFocussedMessage&> m_selectedFocussedMessageHandlerBinding;

                void OnWorldPinsVisibilityMessage(const WorldPinsVisibilityMessage& worldPinsVisibilityMessage);
                void OnSelectedFocussedMessage(const WorldPinsSelectedFocussedMessage& worldPinsSelectedFocussedMessage);

            public:
                WorldPinsInFocusController(const std::shared_ptr<IWorldPinsRepository>& worldPinsRepository,
                                           const std::shared_ptr<IWorldPinsService>& worldPinsService,
                                           const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties,
                                           const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~WorldPinsInFocusController();

                void Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint, const Eegeo::Camera::RenderCamera& renderCamera);
            };
        }
    }
}
