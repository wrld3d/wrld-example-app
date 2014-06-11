//
//  AndroidRouteSimulationExampleView.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__AndroidRouteSimulationExampleView__
#define __ExampleApp__AndroidRouteSimulationExampleView__

#include "Types.h"
#include "IRouteSimulationExampleView.h"
#include "AndroidNativeState.h"
#include <vector>
#include <jni.h>

namespace Examples
{
class AndroidRouteSimulationProxy;

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
	AndroidRouteSimulationProxy* m_pProxy;

public:
	AndroidRouteSimulationExampleView(
	    AndroidNativeState& androidNativeState,
	    AndroidRouteSimulationProxy* pProxy,
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
