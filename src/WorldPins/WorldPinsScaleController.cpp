// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinsScaleController.h"

#include <limits>

#include "IWorldPinsService.h"
#include "ScreenProperties.h"
#include "RenderCamera.h"
#include "IWorldPinsRepository.h"

namespace ExampleApp
{
	namespace WorldPins
	{
		WorldPinsScaleController::WorldPinsScaleController(IWorldPinsRepository& worldPinsRepository,
                                                           WorldPins::IWorldPinsService& worldPinsService,
                                                           const Eegeo::Rendering::ScreenProperties& screenProperties)
			: m_worldPinsRepository(worldPinsRepository)
			, m_worldPinsService(worldPinsService)
			, m_screenProperties(screenProperties)
			, m_modality(0.f)
		{

		}

		WorldPinsScaleController::~WorldPinsScaleController()
		{

		}

        void WorldPinsScaleController::Update(float deltaSeconds, const Eegeo::Camera::RenderCamera& renderCamera)
		{
            for(size_t i = 0; i < m_worldPinsRepository.GetItemCount(); ++i)
            {
                WorldPinItemModel& worldPinItemModel = *m_worldPinsRepository.GetItemAtIndex(i);
				UpdateWorldPin(worldPinItemModel, deltaSeconds, renderCamera);
				const float globalScale = 1.f - m_modality;
				float scale = globalScale  * worldPinItemModel.TransitionStateValue();
				m_worldPinsService.UpdatePinScale(worldPinItemModel, scale);
			}
		}

		void WorldPinsScaleController::SetModality(float modality)
		{
			Eegeo_ASSERT(modality >= 0.f && modality <= 1.f, "Invalid modality value %f, valid range for modality is 0.0 to 1.0 inclusive.\n", modality);

			m_modality = modality;
		}

		void WorldPinsScaleController::UpdateWorldPin(WorldPins::WorldPinItemModel& worldPinItemModel,
                                                      float deltaSeconds,
                                                      const Eegeo::Camera::RenderCamera& renderCamera)
		{
			Eegeo::v2 screenLocation;
			GetScreenLocation(worldPinItemModel, screenLocation, renderCamera);

			const float ratioX = screenLocation.GetX() / m_screenProperties.GetScreenWidth();
			const float ratioY = screenLocation.GetY() / m_screenProperties.GetScreenHeight();
			const bool shouldHide = (ratioX < 0.1f) || (ratioX > 0.9f) || (ratioY < 0.15f) || (ratioY > 0.9f);

			if(shouldHide)
			{
				worldPinItemModel.Hide();
			}
			else
			{
				worldPinItemModel.Show();
			}

			worldPinItemModel.Update(deltaSeconds);
		}

		void WorldPinsScaleController::GetScreenLocation(const WorldPins::WorldPinItemModel& worldPinItemModel,
                                                         Eegeo::v2& screenLocation,
                                                         const Eegeo::Camera::RenderCamera& renderCamera) const
		{
			Eegeo::dv3 ecefLocation;
			m_worldPinsService.GetPinEcefAndScreenLocations(worldPinItemModel, ecefLocation, screenLocation);
			Eegeo::v3 cameraLocal = (ecefLocation - renderCamera.GetEcefLocation()).ToSingle();
			Eegeo::v3 screenPos;
			renderCamera.Project(cameraLocal, screenPos);
			screenLocation.Set(screenPos.GetX(), screenPos.GetY());
		}
	}
}
