// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "WorldPins.h"
#include "IWorldPinsScaleController.h"
#include "Location.h"
#include "Rendering.h"
#include "Camera.h"
#include "VectorMath.h"
#include "Modality.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace WorldPins
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
            
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            Eegeo::Helpers::TCallback1<WorldPinsScaleController, const WorldPinsVisibilityMessage&> m_visibilityMessageHandlerBinding;

		public:
			WorldPinsScaleController(IWorldPinsRepository& worldPinsRepository,
                                     WorldPins::IWorldPinsService& worldPinsService,
                                     ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~WorldPinsScaleController();

            void Update(float deltaSeconds, const Eegeo::Camera::RenderCamera& renderCamera);

			void SetModality(float modality);
            
            void Show();
            void Hide();
            

		private:
            void UpdateWorldPin(WorldPins::WorldPinItemModel& worldPinItemModel,
                                float deltaSeconds,
                                const Eegeo::Camera::RenderCamera& renderCamera);

			void GetScreenLocation(const WorldPins::WorldPinItemModel& worldPinItemModel,
                                   Eegeo::v2& screenLocation,
                                   const Eegeo::Camera::RenderCamera& renderCamera) const;
            
            void HandleVisibilityChange(const WorldPinsVisibilityMessage& worldPinsVisibilityMessage);
		};
	}
}
