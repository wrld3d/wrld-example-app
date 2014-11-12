// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PrimaryMenuView.h"
#include "MathFunc.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "CellConstants.h"

#include "MenuViewControllerInterop.h"

@implementation PrimaryMenuView

- (id)setController:(MenuViewController*)controller
{
	self = [super setController:controller];

	if(self)
	{
		m_pController = controller;
	}

	return self;
}

- (void)initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
    m_pColour = ExampleApp::Helpers::ColorPalette::WhiteTone;
    
    m_stateChangeAnimationTimeSeconds = 0.2;
    
    m_mainContainerOffscreenOffsetX = (0.f * m_pixelScale);
    m_mainContainerOffscreenOffsetY = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedX = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedY = (0.f * m_pixelScale);
    m_mainContainerX = (0.f * m_pixelScale) - m_mainContainerOffscreenOffsetX;
    m_mainContainerY = (50.f * m_pixelScale);
    m_mainContainerOnScreenWidth = (220.f * m_pixelScale);
    m_mainContainerOnScreenHeight = m_screenHeight - m_mainContainerY;
    m_mainContainerWidth = m_mainContainerOnScreenWidth + m_mainContainerOffscreenOffsetX;
    m_mainContainerHeight = m_mainContainerOnScreenHeight;
    
    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_mainContainerX, m_mainContainerY, m_mainContainerWidth, m_mainContainerHeight)] autorelease];
    self.pMenuContainer.backgroundColor = [UIColor clearColor];
    
    m_dragTabX = m_mainContainerOnScreenWidth;
    m_dragTabY = m_mainContainerY + (0.f * m_pixelScale);
    m_dragTabWidth = (64.f * m_pixelScale);
    m_dragTabHeight = (64.f * m_pixelScale);
    self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabX, m_dragTabY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    self.pDragTab.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
    
    const float menuHeaderStubX = m_mainContainerVisibleOnScreenWhenClosedX;
    const float menuHeaderStubY = m_mainContainerVisibleOnScreenWhenClosedY;
    const float menuHeaderStubWidth = m_mainContainerOnScreenWidth;
    const float menuHeaderStubHeight = 64 * m_pixelScale;
    self.pMenuHeaderStub = [[[UIView alloc] initWithFrame:CGRectMake(menuHeaderStubX, menuHeaderStubY, menuHeaderStubWidth, menuHeaderStubHeight)] autorelease];
    self.pMenuHeaderStub.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
    
    m_tableOffsetIntoContainerX = m_tableOffsetIntoContainerY = m_mainContainerVisibleOnScreenWhenClosedX;
    m_tableX = m_tableOffsetIntoContainerX + m_mainContainerOffscreenOffsetX;
    m_tableY = m_tableOffsetIntoContainerY + menuHeaderStubHeight;
    m_tableWidth = m_mainContainerOnScreenWidth - (2 * m_tableOffsetIntoContainerX);
    m_tableHeight = m_mainContainerHeight - m_tableOffsetIntoContainerY;
    self.pTableview = [[[CustomTableView alloc] initWithFrame:CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight) style:UITableViewStylePlain] autorelease];
    self.pTableview.backgroundColor = [UIColor clearColor];
    self.pTableview.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.pTableview.scrollEnabled = NO;
    self.pTableview.bounces = NO;
    
    m_offscreenX = -(m_mainContainerWidth + m_dragTabWidth);
    m_closedX = -(m_mainContainerOnScreenWidth - m_mainContainerVisibleOnScreenWhenClosedX);
    m_openX = (0.f * m_pixelScale);
    
    [self addSubview: self.pMenuContainer];
    [self addSubview: self.pDragTab];
    [self.pMenuContainer addSubview: self.pMenuHeaderStub];
    [self.pMenuContainer addSubview:self.pTableview];
    
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "icon0_me_icon", ExampleApp::Helpers::ImageHelpers::Centre);
    
    ExampleApp::Helpers::ImageHelpers::OffsetValue offset = ExampleApp::Helpers::ImageHelpers::Centre | ExampleApp::Helpers::ImageHelpers::Below;
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "shadow_01", offset);
    
    ExampleApp::Helpers::ImageHelpers::OffsetValue menuShadowOffset = ExampleApp::Helpers::ImageHelpers::Centre | ExampleApp::Helpers::ImageHelpers::Top;
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pTableview, "shadow_03", menuShadowOffset);
}

- (void)dealloc
{
	[self.pTableview removeFromSuperview];
	[self.pTableview release];

	[self.pDragTab removeFromSuperview];
	[self.pDragTab release];

	[self.pMenuHeaderStub removeFromSuperview];
	[self.pMenuHeaderStub release];

	[self.pMenuContainer removeFromSuperview];
	[self.pMenuContainer release];

	[self removeFromSuperview];
	[super dealloc];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
	if([self isAnimating])
	{
		return;
	}

	self.hidden = false;
	[self setOffscreenPartsHiddenState:false];

	float newX = m_offscreenX + ((m_closedX - m_offscreenX) * onScreenState);
	if(fabs(self.frame.origin.x - newX) < 0.01f)
	{
		return;
	}

	CGRect f = self.frame;
	f.origin.x = newX;
	self.frame = f;
}

- (void) updateDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
	CGRect f = self.frame;
	f.origin.x = m_controlStartPos.x + (absolutePosition.x - m_dragStartPos.x);

	if(f.origin.x > m_mainContainerOffscreenOffsetX)
	{
		f.origin.x = m_mainContainerOffscreenOffsetX;
	}

	if(f.origin.x < m_closedX)
	{
		f.origin.x = m_closedX;
	}

	float normalisedDragState = (self.frame.origin.x + (-m_closedX)) / (abs(m_openX - m_closedX));
	normalisedDragState = Eegeo::Clamp(normalisedDragState, 0.f, 1.f);

	[m_pMenuViewController handleDraggingViewInProgress:normalisedDragState];
	self.frame = f;

	[self.layer removeAllAnimations];
}

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
	const bool startedClosed = m_controlStartPos.x == m_closedX;
	const float minimumXValueToClose = startedClosed ? 0.35f : 0.65f;
	bool close = absolutePosition.x < ((m_dragTabWidth+m_mainContainerWidth) * minimumXValueToClose);

	const float velocityMagitude = abs(absoluteVelocity.x);
	if(velocityMagitude > (200 * m_pixelScale))
	{
		close = absoluteVelocity.x < 0 ? true : false;
	}

	[self animateToX:(close ? m_closedX : m_openX)];
}

@end

