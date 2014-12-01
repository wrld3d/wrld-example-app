// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "WorldPins.h"
#include "IWorldPinsInFocusController.h"
#include "VectorMathDecl.h"
#include "Location.h"
#include "Camera.h"
#include "NativeToUiMessageBus.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinsInFocusController : public IWorldPinsInFocusController, private Eegeo::NonCopyable
		{
		private:
            IWorldPinsRepository& m_worldPinsRepository;
            IWorldPinsService& m_worldPinsService;
            
            const IWorldPinsInFocusModel* m_pLastFocussedModel;
            
            bool m_focusEnabled;
            
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            Eegeo::Helpers::TCallback1<WorldPinsInFocusController, const WorldPinsVisibilityMessage&> m_visibilityMessageHandlerBinding;
            
            void HandleVisibilityChange(const WorldPinsVisibilityMessage& worldPinsVisibilityMessage);
            
		public:
			WorldPinsInFocusController(IWorldPinsRepository& worldPinsRepository,
                                       IWorldPinsService& worldPinsService,
                                       ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus,
                                       ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);

			~WorldPinsInFocusController();

            void Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint, const Eegeo::Camera::RenderCamera& renderCamera);
		};
	}
}
