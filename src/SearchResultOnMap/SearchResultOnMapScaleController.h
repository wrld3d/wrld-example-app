// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultOnMapModel.h"
#include "WorldPins.h"
#include "SearchResultOnMap.h"
#include "ISearchResultOnMapScaleController.h"
#include "Location.h"
#include "Rendering.h"
#include "Camera.h"
#include "VectorMath.h"
#include "Modality.h"

namespace ExampleApp
{
namespace SearchResultOnMap
{
class SearchResultOnMapScaleController : public ISearchResultOnMapScaleController, private Eegeo::NonCopyable
{
private:
	SearchResultOnMapModel& m_searchResultOnMapModel;
	WorldPins::IWorldPinsService& m_worldPinsService;
	const Eegeo::Rendering::ScreenProperties& m_screenProperties;
	Eegeo::Camera::RenderCamera& m_renderCamera;
	float m_modality;

public:
	SearchResultOnMapScaleController(SearchResultOnMapModel& searchResultOnMapModel,
	                                 WorldPins::IWorldPinsService& worldPinsService,
	                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
	                                 Eegeo::Camera::RenderCamera& renderCamera);

	~SearchResultOnMapScaleController();

	void Update(float deltaSeconds);

	void SetModality(float modality);

private:
	float GetResultScale(Search::SearchResultModel& searchResultModel);

	void UpdateWorldPin(WorldPins::WorldPinItemModel& worldPinItemModel, float deltaSeconds);

	void GetScreenLocation(const WorldPins::WorldPinItemModel& worldPinItemModel, Eegeo::v2& screenLocation) const;
};
}
}
