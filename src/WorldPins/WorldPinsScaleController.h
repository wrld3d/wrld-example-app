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

namespace ExampleApp
{
	namespace WorldPins
	{
		class WorldPinsScaleController : public IWorldPinsScaleController, private Eegeo::NonCopyable
		{
		private:
            IWorldPinsRepository& m_worldPinsRepository;
			IWorldPinsService& m_worldPinsService;
			const Eegeo::Rendering::ScreenProperties& m_screenProperties;
			float m_modality;

		public:
			WorldPinsScaleController(IWorldPinsRepository& worldPinsRepository,
                                     WorldPins::IWorldPinsService& worldPinsService,
                                     const Eegeo::Rendering::ScreenProperties& screenProperties);

			~WorldPinsScaleController();

            void Update(float deltaSeconds, const Eegeo::Camera::RenderCamera& renderCamera);

			void SetModality(float modality);

		private:
            void UpdateWorldPin(WorldPins::WorldPinItemModel& worldPinItemModel,
                                float deltaSeconds,
                                const Eegeo::Camera::RenderCamera& renderCamera);

			void GetScreenLocation(const WorldPins::WorldPinItemModel& worldPinItemModel,
                                   Eegeo::v2& screenLocation,
                                   const Eegeo::Camera::RenderCamera& renderCamera) const;
		};
	}
}
