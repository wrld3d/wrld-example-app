//
//  iOSRouteSimulationExampleView.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "iOSRouteSimulationExampleView.h"
#include "UIHelpers.h"

using namespace Examples;

@implementation IRouteSimulationExampleBinding

Examples::iOSRouteSimulationExampleView* m_pExample;
UIButton* m_pDirection;
UIButton* m_pIncreaseSpeed;
UIButton* m_pDecreaseSpeed;
UIButton* m_pRotateToFollow;

-(void) setExampleInstance:(Examples::iOSRouteSimulationExampleView*)pExample :(UIButton*)direction :(UIButton*)increaseSpeed :(UIButton*)decreaseSpeed :(UIButton*)rotateToFollow
{
	m_pExample = pExample;
	m_pDirection = direction;
	m_pIncreaseSpeed = increaseSpeed;
	m_pDecreaseSpeed = decreaseSpeed;
	m_pRotateToFollow = rotateToFollow;
}

-(void) toggleFollowCamera
{
	m_pExample->ToggleFollowCamera();

	[m_pDirection setHidden: ![m_pDirection isHidden]];
	[m_pIncreaseSpeed setHidden: ![m_pIncreaseSpeed isHidden]];
	[m_pDecreaseSpeed setHidden: ![m_pDecreaseSpeed isHidden]];
	[m_pRotateToFollow setHidden: ![m_pRotateToFollow isHidden]];
}

-(void) changeFollowDirection
{
	m_pExample->ToggleCameraDirection();
}

-(void) increaseSpeedFollowed
{
	m_pExample->IncreaseSpeed();
}

-(void) decreaseSpeedFollowed
{
	m_pExample->DecreaseSpeed();
}

-(void) rotateToFollow
{
	m_pExample->ToggleRotateToFollow();
}

-(void) toggleSideOfRoadToDriveOn
{
	m_pExample->ChangeSideOfRoad();
}

@end

iOSRouteSimulationExampleView::iOSRouteSimulationExampleView(UIView* pView)
	: m_pView(pView)
{
	m_pBinding = [[IRouteSimulationExampleBinding alloc] init];

	// Grab the window frame and adjust it for orientation
	UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
	                    rootViewController].view;
	CGRect originalFrame = [[UIScreen mainScreen] bounds];
	CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];

	float screenHeight = adjustedFrame.size.height - 80.f;

	m_pToggleFollowButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	m_pToggleFollowButton.frame = CGRectMake(10, screenHeight, 200, 50);
	[m_pToggleFollowButton setTitle:@"Toggle Follow!" forState:UIControlStateNormal];
	[m_pToggleFollowButton addTarget:m_pBinding action:@selector(toggleFollowCamera) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pToggleFollowButton];

	screenHeight -= 60.f;

	m_pIncreaseSpeedButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	m_pIncreaseSpeedButton.frame = CGRectMake(10, screenHeight, 200, 50);
	[m_pIncreaseSpeedButton setTitle:@"Increase Speed!" forState:UIControlStateNormal];
	[m_pIncreaseSpeedButton addTarget:m_pBinding action:@selector(increaseSpeedFollowed) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pIncreaseSpeedButton];

	screenHeight -= 60.f;

	m_pDecreaseSpeedButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	m_pDecreaseSpeedButton.frame = CGRectMake(10, screenHeight, 200, 50);
	[m_pDecreaseSpeedButton setTitle:@"Decrease Speed!" forState:UIControlStateNormal];
	[m_pDecreaseSpeedButton addTarget:m_pBinding action:@selector(decreaseSpeedFollowed) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pDecreaseSpeedButton];

	screenHeight -= 60.f;

	m_pChangeDirectionButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	m_pChangeDirectionButton.frame = CGRectMake(10, screenHeight, 200, 50);
	[m_pChangeDirectionButton setTitle:@"Change Direction!" forState:UIControlStateNormal];
	[m_pChangeDirectionButton addTarget:m_pBinding action:@selector(changeFollowDirection) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pChangeDirectionButton];

	screenHeight -= 60.f;

	m_pRotateToFollowButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	m_pRotateToFollowButton.frame = CGRectMake(10, screenHeight, 200, 50);
	[m_pRotateToFollowButton setTitle:@"Rotate to Follow!" forState:UIControlStateNormal];
	[m_pRotateToFollowButton addTarget:m_pBinding action:@selector(rotateToFollow) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pRotateToFollowButton];

	//this one goes beside toggle follow as we can do it any time
	m_pToggleSideOfRoadToDriveOnButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	m_pToggleSideOfRoadToDriveOnButton.frame = CGRectMake(m_pToggleFollowButton.frame.origin.x + m_pToggleFollowButton.frame.size.width + 10, m_pToggleFollowButton.frame.origin.y, 200, 50);
	[m_pToggleSideOfRoadToDriveOnButton setTitle:@"Toggle Road Side!" forState:UIControlStateNormal];
	[m_pToggleSideOfRoadToDriveOnButton addTarget:m_pBinding action:@selector(toggleSideOfRoadToDriveOn) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pToggleSideOfRoadToDriveOnButton];

	[m_pBinding setExampleInstance:this :m_pChangeDirectionButton :m_pIncreaseSpeedButton :m_pDecreaseSpeedButton :m_pRotateToFollowButton];

	ToggleFollowMode(false);
}

iOSRouteSimulationExampleView::~iOSRouteSimulationExampleView()
{
	[m_pToggleFollowButton removeFromSuperview];
	m_pToggleFollowButton = nil;

	[m_pIncreaseSpeedButton removeFromSuperview];
	m_pIncreaseSpeedButton = nil;

	[m_pDecreaseSpeedButton removeFromSuperview];
	m_pDecreaseSpeedButton = nil;

	[m_pRotateToFollowButton removeFromSuperview];
	m_pRotateToFollowButton = nil;

	[m_pChangeDirectionButton removeFromSuperview];
	m_pChangeDirectionButton = nil;

	[m_pToggleSideOfRoadToDriveOnButton removeFromSuperview];
	m_pToggleSideOfRoadToDriveOnButton = nil;

	[m_pBinding release];
	m_pBinding = nil;
}

void iOSRouteSimulationExampleView::ToggleFollowMode(bool followEnabled)
{
	[m_pChangeDirectionButton setHidden: !followEnabled];
	[m_pIncreaseSpeedButton setHidden: !followEnabled];
	[m_pDecreaseSpeedButton setHidden: !followEnabled];
	[m_pRotateToFollow setHidden: !followEnabled];
}

void iOSRouteSimulationExampleView::AddFollowCameraToggledHandler(IUIActionHandler& handler)
{
	m_followCameraToggledHandlers.push_back(&handler);
}

void iOSRouteSimulationExampleView::RemoveFollowCameraToggledHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_followCameraToggledHandlers, &handler);
}

void iOSRouteSimulationExampleView::ToggleFollowCamera()
{
	InvokeAllHandlers(m_followCameraToggledHandlers);
}

void iOSRouteSimulationExampleView::AddFollowCameraDirectionChangedHandler(IUIActionHandler& handler)
{
	m_directionChangedHandlers.push_back(&handler);
}

void iOSRouteSimulationExampleView::RemoveFollowCameraDirectionChangedHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_directionChangedHandlers, &handler);
}

void iOSRouteSimulationExampleView::ToggleCameraDirection()
{
	InvokeAllHandlers(m_directionChangedHandlers);
}

void iOSRouteSimulationExampleView::AddIncreaseSpeedHandler(IUIActionHandler& handler)
{
	m_increaseSpeedHandlers.push_back(&handler);
}

void iOSRouteSimulationExampleView::RemoveIncreaseSpeedHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_increaseSpeedHandlers, &handler);
}

void iOSRouteSimulationExampleView::IncreaseSpeed()
{
	InvokeAllHandlers(m_increaseSpeedHandlers);
}

void iOSRouteSimulationExampleView::AddDecreaseSpeedHandler(IUIActionHandler& handler)
{
	m_decreaseSpeedHandlers.push_back(&handler);
}

void iOSRouteSimulationExampleView::RemoveDecreaseSpeedHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_decreaseSpeedHandlers, &handler);
}

void iOSRouteSimulationExampleView::DecreaseSpeed()
{
	InvokeAllHandlers(m_decreaseSpeedHandlers);
}

void iOSRouteSimulationExampleView::AddRotateToFollowToggledHandler(IUIActionHandler& handler)
{
	m_rotateToFollowToggledHandlers.push_back(&handler);
}

void iOSRouteSimulationExampleView::RemoveRotateToFollowToggledHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_rotateToFollowToggledHandlers, &handler);
}

void iOSRouteSimulationExampleView::ToggleRotateToFollow()
{
	InvokeAllHandlers(m_rotateToFollowToggledHandlers);
}

void iOSRouteSimulationExampleView::AddSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)
{
	m_roadSideChangedHandlers.push_back(&handler);
}

void iOSRouteSimulationExampleView::RemoveSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_roadSideChangedHandlers, &handler);
}

void iOSRouteSimulationExampleView::ChangeSideOfRoad()
{
	InvokeAllHandlers(m_roadSideChangedHandlers);
}
