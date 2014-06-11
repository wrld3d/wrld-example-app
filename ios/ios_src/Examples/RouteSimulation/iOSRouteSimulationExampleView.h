//
//  iOSRouteSimulationExampleView.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__iOSRouteSimulationExampleView__
#define __ExampleApp__iOSRouteSimulationExampleView__

#include "Types.h"
#include "IRouteSimulationExampleView.h"
#import <UIKit/UIKit.h>
#include <vector>

namespace Examples
{
class iOSRouteSimulationExampleView;
}

@interface IRouteSimulationExampleBinding : NSObject

-(void) setExampleInstance:(Examples::iOSRouteSimulationExampleView*)pExample :(UIButton*)direction :(UIButton*)increaseSpeed :(UIButton*)decreaseSpeed :(UIButton*)rotateToFollow;

-(void) toggleFollowCamera;
-(void) changeFollowDirection;
-(void) increaseSpeedFollowed;
-(void) decreaseSpeedFollowed;
-(void) rotateToFollow;
-(void) toggleSideOfRoadToDriveOn;

@end

namespace Examples
{
class iOSRouteSimulationExampleView : public IRouteSimulationExampleView, private Eegeo::NonCopyable
{
	std::vector<IUIActionHandler*> m_followCameraToggledHandlers;
	std::vector<IUIActionHandler*> m_directionChangedHandlers;
	std::vector<IUIActionHandler*> m_increaseSpeedHandlers;
	std::vector<IUIActionHandler*> m_decreaseSpeedHandlers;
	std::vector<IUIActionHandler*> m_rotateToFollowToggledHandlers;
	std::vector<IUIActionHandler*> m_roadSideChangedHandlers;

	UIView* m_pView;
	IRouteSimulationExampleBinding* m_pBinding;
	UIButton* m_pToggleFollowButton;
	UIButton* m_pIncreaseSpeedButton;
	UIButton* m_pDecreaseSpeedButton;
	UIButton* m_pRotateToFollowButton;
	UIButton* m_pChangeDirectionButton;
	UIButton* m_pToggleSideOfRoadToDriveOnButton;

public:

	iOSRouteSimulationExampleView(UIView* pView);

	~iOSRouteSimulationExampleView();

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

private:

	void ToggleFollowMode(bool followEnabled);
};
}


#endif /* defined(__ExampleApp__iOSRouteSimulationExampleView__) */
