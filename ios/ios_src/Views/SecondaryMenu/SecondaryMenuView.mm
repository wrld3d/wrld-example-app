// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SecondaryMenuView.h"
#include "MathFunc.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "CellConstants.h"

#include "MenuViewControllerInterop.h"
#include "ScaleHelpers.h"

@implementation SecondaryMenuView

- (id)setController:(MenuViewController*)controller
{
	self = [super setController:controller];

	if (self)
	{
		m_pController = controller;
	}

	return self;
}

- (void) initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
	m_pColour = ExampleApp::Helpers::ColorPalette::WhiteTone;

	m_stateChangeAnimationTimeSeconds = 0.2;

	m_mainContainerOffscreenOffsetX = (0.f * m_pixelScale);
	m_mainContainerOffscreenOffsetY = (0.f * m_pixelScale);
	m_mainContainerVisibleOnScreenWhenClosedX = (0.f * m_pixelScale);
	m_mainContainerVisibleOnScreenWhenClosedY = (0.f * m_pixelScale);
	m_mainContainerX = m_screenWidth - m_mainContainerVisibleOnScreenWhenClosedX;
	m_mainContainerY = (50.f * m_pixelScale);
	m_mainContainerOnScreenWidth = (220.f * m_pixelScale);
	m_mainContainerOnScreenHeight = m_screenHeight - m_mainContainerY;
	m_mainContainerWidth = m_mainContainerOnScreenWidth + m_mainContainerOffscreenOffsetX;
	m_mainContainerHeight = m_mainContainerOnScreenHeight;

	self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_mainContainerX, m_mainContainerY, m_mainContainerWidth, m_mainContainerHeight)] autorelease];
	self.pMenuContainer.backgroundColor = [UIColor clearColor];

    float iphoneTweakScale = ExampleApp::Helpers::ScaleHelpers::GetScaleTweakValue();
    
	m_dragTabY = m_mainContainerY + (0.f * m_pixelScale);
	m_dragTabWidth = (64.f * m_pixelScale * iphoneTweakScale);
	m_dragTabX = m_mainContainerX - m_dragTabWidth;
	m_dragTabHeight = (64.f * m_pixelScale * iphoneTweakScale);
	self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabX, m_dragTabY, m_dragTabWidth, m_dragTabHeight)] autorelease];
	self.pDragTab.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;

	m_searchBoxContainerX = m_mainContainerVisibleOnScreenWhenClosedX;
	m_searchBoxContainerY = m_mainContainerVisibleOnScreenWhenClosedY;
	m_searchBoxContainerWidth = m_mainContainerOnScreenWidth;
	m_searchBoxContainerHeight = 64 * m_pixelScale * iphoneTweakScale;
	self.pSearchEditBoxContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_searchBoxContainerX, m_searchBoxContainerY, m_searchBoxContainerWidth, m_searchBoxContainerHeight)] autorelease];
	self.pSearchEditBoxContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;

	m_searchBoxOffsetIntoContainer = m_searchBoxContainerWidth*0.05f;
	m_searchBoxX = m_searchBoxOffsetIntoContainer;
	m_searchBoxY = m_searchBoxContainerHeight * 0.18f * m_pixelScale;
	m_searchBoxWidth = (m_searchBoxContainerWidth - (2 * m_searchBoxOffsetIntoContainer));
	m_searchBoxHeight = (m_searchBoxContainerHeight * 0.65f * m_pixelScale);
	self.pSearchEditBox = [[[UITextField alloc] initWithFrame:CGRectMake(m_searchBoxX, m_searchBoxY, m_searchBoxWidth, m_searchBoxHeight)] autorelease];
	self.pSearchEditBox.text = @"";
	self.pSearchEditBox.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;

	m_tableOffsetIntoContainerX = m_tableOffsetIntoContainerY = m_mainContainerVisibleOnScreenWhenClosedX;
	m_tableX = m_tableOffsetIntoContainerX;
	m_tableY = m_tableOffsetIntoContainerY + m_searchBoxContainerHeight;
	m_tableWidth = m_mainContainerOnScreenWidth - (2 * m_tableOffsetIntoContainerX);
	m_tableHeight = m_mainContainerHeight - m_searchBoxHeight;
	const float tableScreenY = m_mainContainerY + m_mainContainerOffscreenOffsetY + m_tableY;
	const float tableScreenSpace = m_screenHeight - tableScreenY;
	m_tableHeight = fmin(tableScreenSpace, m_tableHeight);

	const float realTableHeight =  (SECTION_HEADER_CELL_HEIGHT * numberOfSections) + (SUB_SECTION_CELL_HEIGHT * (numberOfCells));

	self.pTableviewContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight)] autorelease];
	self.pTableviewContainer.bounces = NO;
	self.pTableviewContainer.contentSize = CGSizeMake(m_tableWidth, realTableHeight);

	self.pTableview = [[[CustomTableView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_tableWidth, realTableHeight)
	                    style:UITableViewStylePlain
	                    container:self.pTableviewContainer
	                   ] autorelease];

	self.pTableview.backgroundColor = [UIColor clearColor];
	self.pTableview.separatorStyle = UITableViewCellSeparatorStyleNone;
	self.pTableview.bounces = NO;
	self.pTableview.scrollEnabled = NO;

	m_offscreenX = m_dragTabWidth + m_mainContainerVisibleOnScreenWhenClosedX;
	m_openX = -(m_mainContainerOnScreenWidth - m_mainContainerVisibleOnScreenWhenClosedX);
	m_closedX = (0.f * m_pixelScale);

	[self addSubview: self.pMenuContainer];
	[self addSubview: self.pDragTab];
	[self.pSearchEditBoxContainer addSubview:self.pSearchEditBox];
	[self.pMenuContainer addSubview:self.pSearchEditBoxContainer];

	[self.pTableviewContainer addSubview:self.pTableview];
	[self.pMenuContainer addSubview:self.pTableviewContainer];

	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "icon0_search_icon", ExampleApp::Helpers::ImageHelpers::Centre);

	ExampleApp::Helpers::ImageHelpers::OffsetValue tabShadowOffset = ExampleApp::Helpers::ImageHelpers::Centre | ExampleApp::Helpers::ImageHelpers::Below;
	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "shadow_01", tabShadowOffset);

	ExampleApp::Helpers::ImageHelpers::OffsetValue menuShadowOffset = ExampleApp::Helpers::ImageHelpers::Centre | ExampleApp::Helpers::ImageHelpers::Top;
	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pTableview, "shadow_03", menuShadowOffset);
}

- (void)dealloc
{
	[self.pSearchEditBox removeFromSuperview];
	[self.pSearchEditBox release];

	[self.pSearchEditBoxContainer removeFromSuperview];
	[self.pSearchEditBoxContainer release];

	[self.pTableview removeFromSuperview];
	[self.pTableview release];

	[self.pTableviewContainer removeFromSuperview];
	[self.pTableviewContainer release];

	[self.pDragTab removeFromSuperview];
	[self.pDragTab release];

	[self.pMenuContainer removeFromSuperview];
	[self.pMenuContainer release];

	[self removeFromSuperview];
	[super dealloc];
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
	[super setOffscreenPartsHiddenState:hidden];
	self.pSearchEditBox.hidden = hidden;
	self.pSearchEditBoxContainer.hidden = hidden;
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
	if([self isAnimating])
	{
		return;
	}

	self.hidden = false;
	[self setOffscreenPartsHiddenState:false];

	float newX = m_offscreenX - ((m_offscreenX - m_closedX) * onScreenState);
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

	if(f.origin.x < -m_mainContainerOnScreenWidth)
	{
		f.origin.x = (-m_mainContainerOnScreenWidth);
	}

	if(f.origin.x > m_closedX)
	{
		f.origin.x = m_closedX;
	}

	float normalisedDragState = -((self.frame.origin.x + (-m_closedX)) / (abs(m_openX - m_closedX)));
	normalisedDragState = Eegeo::Clamp(normalisedDragState, 0.f, 1.f);

	[m_pMenuViewController handleDraggingViewInProgress:normalisedDragState];
	self.frame = f;

	[self.layer removeAllAnimations];
}

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
	const bool startedClosed = m_controlStartPos.x == m_closedX;
	const float xRatioForStateChange = startedClosed ? 0.35f : 0.65f;
	const float threshold = (m_screenWidth - (m_mainContainerOnScreenWidth * xRatioForStateChange));
	bool open = absolutePosition.x < threshold;

	const float velocityMagitude = abs(absoluteVelocity.x);
	if(velocityMagitude > (200 * m_pixelScale))
	{
		open = absoluteVelocity.x < 0 ? true : false;
	}

	[super animateToX:(open ? m_openX : m_closedX)];
}

@end
