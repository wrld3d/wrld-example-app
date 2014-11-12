// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>
#include "Types.h"
#include "ICompassModel.h"
#include "Rendering.h"
#include "CallbackCollection.h"
#include "GlobeCamera.h"
#include "Location.h"

namespace ExampleApp
{
namespace Compass
{
class CompassModel : public ICompassModel, private Eegeo::NonCopyable
{
	Eegeo::Location::NavigationService& m_navigationService;
	Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;
	Eegeo::Helpers::CallbackCollection0 m_gpsModeChangedCallbacks;
	GpsMode::Values m_gpsMode;
	std::map<Eegeo::Location::NavigationService::GpsMode, GpsMode::Values> m_compassGpsModeToNavigationGpsMode;
	std::map<GpsMode::Values, Eegeo::Location::NavigationService::GpsMode> m_navigationGpsModeToCompassGpsMode;

public:

	CompassModel(Eegeo::Location::NavigationService& navigationService,
	             Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& controller);

	~CompassModel();

	bool GetGpsModeActive() const;

	GpsMode::Values GetGpsMode() const;

	void DisableGpsMode();

	void TryUpdateToNavigationServiceGpsMode(Eegeo::Location::NavigationService::GpsMode value);

	float GetHeadingRadians() const;

	float GetHeadingDegrees() const;

	void CycleToNextGpsMode();

	void InsertGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback);

	void RemoveGpsModeChangedCallback(Eegeo::Helpers::ICallback0& callback);

private:
	void SetGpsMode(GpsMode::Values value);
};
}
}
