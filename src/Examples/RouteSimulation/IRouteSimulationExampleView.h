// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef ExampleApp_IRouteSimulationExampleView_h
#define ExampleApp_IRouteSimulationExampleView_h

#include "Types.h"
#include "IUIActionHandler.h"

namespace Examples
{
class IRouteSimulationExampleView
{
public:
	virtual ~IRouteSimulationExampleView() { }

	virtual void AddFollowCameraToggledHandler(IUIActionHandler& handler)=0;

	virtual void RemoveFollowCameraToggledHandler(IUIActionHandler& handler)=0;

	virtual void AddFollowCameraDirectionChangedHandler(IUIActionHandler& handler)=0;

	virtual void RemoveFollowCameraDirectionChangedHandler(IUIActionHandler& handler)=0;

	virtual void AddIncreaseSpeedHandler(IUIActionHandler& handler)=0;

	virtual void RemoveIncreaseSpeedHandler(IUIActionHandler& handler)=0;

	virtual void AddDecreaseSpeedHandler(IUIActionHandler& handler)=0;

	virtual void RemoveDecreaseSpeedHandler(IUIActionHandler& handler)=0;

	virtual void AddRotateToFollowToggledHandler(IUIActionHandler& handler)=0;

	virtual void RemoveRotateToFollowToggledHandler(IUIActionHandler& handler)=0;

	virtual void AddSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)=0;

	virtual void RemoveSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)=0;
};
}


#endif
