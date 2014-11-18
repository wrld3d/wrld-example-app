// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "WorldPins.h"
#include "IWorldPinsInFocusController.h"
#include "VectorMathDecl.h"
#include "Location.h"
#include "Camera.h"
#include "NativeToUiMessageBus.h"

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
            
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            
		public:
			WorldPinsInFocusController(IWorldPinsRepository& worldPinsRepository,
                                       IWorldPinsService& worldPinsService,
                                       ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);

			~WorldPinsInFocusController();

            void Update(float deltaSeconds, const Eegeo::dv3& ecefInterestPoint, const Eegeo::Camera::RenderCamera& renderCamera);
		};
	}
}
