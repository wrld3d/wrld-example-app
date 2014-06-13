// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSRouteMatchingExampleView.h"
#include "UIHelpers.h"

using namespace Examples;

@implementation IRouteMatchingExampleBinding

Examples::iOSRouteMatchingExampleView* m_pRouteMatchingExample;
UIButton* m_pToggleMatching;

-(void) setExampleInstance:(iOSRouteMatchingExampleView*)pExample :(UIButton*)pToggleMatching
{
	m_pRouteMatchingExample = pExample;
	m_pToggleMatching = pToggleMatching;
}

-(void) toggleMatching
{
	m_pRouteMatchingExample->ToggleMatching();
}

@end

namespace Examples
{
iOSRouteMatchingExampleView::iOSRouteMatchingExampleView(UIView* pView)
	: m_pView(pView)
{
	m_pBinding = [[IRouteMatchingExampleBinding alloc] init];

	// Grab the window frame and adjust it for orientation
	UIView *rootView = [[[UIApplication sharedApplication] keyWindow]
	                    rootViewController].view;
	CGRect originalFrame = [[UIScreen mainScreen] bounds];
	CGRect adjustedFrame = [rootView convertRect:originalFrame fromView:nil];

	float screenHeight = adjustedFrame.size.height - 80.f;

	m_pToggleMatchingButton = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	m_pToggleMatchingButton.frame = CGRectMake(10, screenHeight, 200, 50);
	[m_pToggleMatchingButton setTitle:@"Toggle Match!" forState:UIControlStateNormal];
	[m_pToggleMatchingButton addTarget:m_pBinding action:@selector(toggleMatching) forControlEvents:UIControlEventTouchDown];
	[m_pView addSubview:m_pToggleMatchingButton];

	[m_pBinding setExampleInstance:this :m_pToggleMatchingButton];
}

iOSRouteMatchingExampleView::~iOSRouteMatchingExampleView()
{
	[m_pToggleMatchingButton removeFromSuperview];
	m_pToggleMatchingButton = nil;

	[m_pBinding release];
	m_pBinding = nil;
}

void iOSRouteMatchingExampleView::AddMatchingToggledHandler(IUIActionHandler& handler)
{
	m_matchingToggledHandlers.push_back(&handler);
}

void iOSRouteMatchingExampleView::RemoveMatchingToggledHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_matchingToggledHandlers, &handler);
}

void iOSRouteMatchingExampleView::ToggleMatching()
{
	InvokeAllHandlers(m_matchingToggledHandlers);
}
}
