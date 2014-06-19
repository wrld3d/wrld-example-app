// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__AndroidRouteSimulationExampleView__
#define __ExampleApp__AndroidRouteSimulationExampleView__

#include "Types.h"
#include "IRouteSimulationExampleView.h"
#include "AndroidNativeState.h"
#include <vector>
#include <jni.h>

namespace Examples
{
class AndroidRouteSimulationExampleView : public IRouteSimulationExampleView, private Eegeo::NonCopyable
{
	std::vector<IUIActionHandler*> m_followCameraToggledHandlers;
	std::vector<IUIActionHandler*> m_directionChangedHandlers;
	std::vector<IUIActionHandler*> m_increaseSpeedHandlers;
	std::vector<IUIActionHandler*> m_decreaseSpeedHandlers;
	std::vector<IUIActionHandler*> m_rotateToFollowToggledHandlers;
	std::vector<IUIActionHandler*> m_roadSideChangedHandlers;

	AndroidNativeState& m_nativeState;
	jclass m_routeSimulationExampleHudClass;
	jobject m_routeSimulationExampleHud;

public:
	AndroidRouteSimulationExampleView(
	    AndroidNativeState& androidNativeState,
	    bool usingFollowCamera);

	~AndroidRouteSimulationExampleView();

	void AddFollowCameraToggledHandler(IUIActionHandler& handler);

	void RemoveFollowCameraToggledHandler(IUIActionHandler& handler);

	void ToggleFollowCamera();

	void AddFollowCameraDirectionChangedHandler(IUIActionHandler& handler);

	void RemoveFollowCameraDirectionChangedHandler(IUIActionHandler& handler);

	void ToggleCameraDirection();

	void AddIncreaseSpeedHandler(IUIActionHandler& handler);

	void RemoveIncreaseSpeedHandler(IUIActionHandler& handler);

	void IncreaseSpeed();

	void AddDecreaseSpeedHandler(IUIActionHandler& handler);

	void RemoveDecreaseSpeedHandler(IUIActionHandler& handler);

	void DecreaseSpeed();

	void AddRotateToFollowToggledHandler(IUIActionHandler& handler);

	void RemoveRotateToFollowToggledHandler(IUIActionHandler& handler);

	void ToggleRotateToFollow();

	void AddSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler);

	void RemoveSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler);

	void ChangeSideOfRoad();

};
}

#endif /* defined(__ExampleApp__AndroidRouteSimulationExampleView__) */
