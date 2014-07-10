// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSRouteSimulationExampleView.h"
#include "UIHelpers.h"
#include "iOSUIHelpers.h"

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

namespace
{
    float ApplyPlatformScale(int position)
    {
        const float deviceSizeScale = IS_IPAD ? 1.f : 0.5f;
        return position*deviceSizeScale;
    }
    
    UIButton* CreateVerticalMenuButton(float screenY, NSString * title)
    {
        UIButton* button = [UIButton buttonWithType:BUTTON_TYPE];
        button.frame = CGRectMake(ApplyPlatformScale(10), screenY, ApplyPlatformScale(200), ApplyPlatformScale(50));
        [button setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0/255.0f alpha:0.6]];
        [button setTitle:title forState:UIControlStateNormal];
        
        if(!IS_IPAD) {
            button.titleLabel.font = [UIFont systemFontOfSize:10];
        }
        
        return button;
    }
}

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
    
    m_pToggleFollowButton = CreateVerticalMenuButton(screenHeight, @"Toggle Follow!");
	[m_pToggleFollowButton addTarget:m_pBinding action:@selector(toggleFollowCamera) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pToggleFollowButton];

	screenHeight -= ApplyPlatformScale(60.f);

    m_pIncreaseSpeedButton = CreateVerticalMenuButton(screenHeight, @"Increase Speed!");
	[m_pIncreaseSpeedButton addTarget:m_pBinding action:@selector(increaseSpeedFollowed) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pIncreaseSpeedButton];

	screenHeight -= ApplyPlatformScale(60.f);
    
    m_pDecreaseSpeedButton = CreateVerticalMenuButton(screenHeight, @"Decrease Speed!");
	[m_pDecreaseSpeedButton addTarget:m_pBinding action:@selector(increaseSpeedFollowed) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pDecreaseSpeedButton];
    
	screenHeight -= ApplyPlatformScale(60.f);
    
    m_pChangeDirectionButton = CreateVerticalMenuButton(screenHeight, @"Change Direction!");
	[m_pChangeDirectionButton addTarget:m_pBinding action:@selector(changeFollowDirection) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pChangeDirectionButton];
    
	screenHeight -= ApplyPlatformScale(60.f);

    m_pRotateToFollowButton = CreateVerticalMenuButton(screenHeight, @"Rotate to Follow!");
	[m_pRotateToFollowButton addTarget:m_pBinding action:@selector(rotateToFollow) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pRotateToFollowButton];
    

	//this one goes beside toggle follow as we can do it any time
	m_pToggleSideOfRoadToDriveOnButton = [UIButton buttonWithType:BUTTON_TYPE];
	m_pToggleSideOfRoadToDriveOnButton.frame = CGRectMake(m_pToggleFollowButton.frame.origin.x + m_pToggleFollowButton.frame.size.width + ApplyPlatformScale(10),
                                                          m_pToggleFollowButton.frame.origin.y, ApplyPlatformScale(200), ApplyPlatformScale(50));
    [m_pToggleSideOfRoadToDriveOnButton setBackgroundColor:[UIColor colorWithRed:0.0/255.0f green:0.0/255.0f blue:128.0/255.0f alpha:0.6]];
	[m_pToggleSideOfRoadToDriveOnButton setTitle:@"Toggle Road Side!" forState:UIControlStateNormal];
	[m_pToggleSideOfRoadToDriveOnButton addTarget:m_pBinding action:@selector(toggleSideOfRoadToDriveOn) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pToggleSideOfRoadToDriveOnButton];
    
    if (!IS_IPAD) {
        m_pToggleSideOfRoadToDriveOnButton.titleLabel.font = [UIFont systemFontOfSize:10];
    }

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
