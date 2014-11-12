// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <limits>
#include "SearchResultOnMapScaleController.h"
#include "IWorldPinsService.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "ScreenProperties.h"
#include "RenderCamera.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapScaleController::SearchResultOnMapScaleController(SearchResultOnMapModel& searchResultOnMapModel,
		        WorldPins::IWorldPinsService& worldPinsService,
		        const Eegeo::Rendering::ScreenProperties& screenProperties,
		        Eegeo::Camera::RenderCamera& renderCamera)
			: m_searchResultOnMapModel(searchResultOnMapModel)
			, m_worldPinsService(worldPinsService)
			, m_screenProperties(screenProperties)
			, m_renderCamera(renderCamera)
			, m_modality(0.f)
		{

		}

		SearchResultOnMapScaleController::~SearchResultOnMapScaleController()
		{

		}

		void SearchResultOnMapScaleController::Update(float deltaSeconds)
		{
			for(SearchResultOnMapModel::mapIt it = m_searchResultOnMapModel.begin();
			        it != m_searchResultOnMapModel.end();
			        ++ it)
			{
				Search::SearchResultModel& searchResultModel = *it->first;
				WorldPins::WorldPinItemModel& worldPinItemModel = it->second;

				UpdateWorldPin(worldPinItemModel, deltaSeconds);
				const float globalScale = 1.f - m_modality;
				float scale = globalScale * GetResultScale(searchResultModel) * worldPinItemModel.TransitionStateValue();
				m_worldPinsService.UpdatePinScale(worldPinItemModel, scale);
			}
		}

		void SearchResultOnMapScaleController::SetModality(float modality)
		{
			Eegeo_ASSERT(modality >= 0.f && modality <= 1.f, "Invalid modality value %f, valid range for modality is 0.0 to 1.0 inclusive.\n", modality);

			m_modality = modality;
		}

		float SearchResultOnMapScaleController::GetResultScale(Search::SearchResultModel& searchResultModel)
		{
			// todo -- implement any per result scaling here, for example scaling the pins by
			// the popularity or relevance of search results, if data available.

			return 1.f;
		}

		void SearchResultOnMapScaleController::UpdateWorldPin(WorldPins::WorldPinItemModel& worldPinItemModel, float deltaSeconds)
		{
			Eegeo::v2 screenLocation;
			GetScreenLocation(worldPinItemModel, screenLocation);

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

		void SearchResultOnMapScaleController::GetScreenLocation(const WorldPins::WorldPinItemModel& worldPinItemModel, Eegeo::v2& screenLocation) const
		{
			Eegeo::dv3 ecefLocation;
			m_worldPinsService.GetPinEcefAndScreenLocations(worldPinItemModel, ecefLocation, screenLocation);
			Eegeo::v3 cameraLocal = (ecefLocation - m_renderCamera.GetEcefLocation()).ToSingle();
			Eegeo::v3 screenPos;
			m_renderCamera.Project(cameraLocal, screenPos);
			screenLocation.Set(screenPos.GetX(), screenPos.GetY());
		}
	}
}
