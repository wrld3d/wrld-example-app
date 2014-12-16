// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultMenuView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "MenuViewControllerInterop.h"
#include "IconResources.h"

@implementation SearchResultMenuView

- (id)setController:(MenuViewController*)controller
{
	self = [super setController:controller];

	if(self)
	{
		m_pController = controller;
	}

	return self;
}

- (void) initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
	m_pColour = ExampleApp::Helpers::ColorPalette::WhiteTone;

	m_stateChangeAnimationTimeSeconds = 0.2f;

	m_mainContainerOffscreenOffsetX = (0.f * m_pixelScale);
	m_mainContainerOffscreenOffsetY = (0.f * m_pixelScale);
	m_mainContainerVisibleOnScreenWhenClosedX = (0.f * m_pixelScale);
	m_mainContainerVisibleOnScreenWhenClosedY = (0.f * m_pixelScale);
	m_mainContainerOnScreenWidth = (300.f * m_pixelScale);
	m_mainContainerOnScreenHeight = (420.f * m_pixelScale);
	m_mainContainerWidth = m_mainContainerOnScreenWidth;
	m_mainContainerHeight = m_mainContainerOnScreenHeight + m_mainContainerOffscreenOffsetY;
	m_mainContainerX = m_screenWidth/2.f - m_mainContainerOnScreenWidth/2.f;
	m_mainContainerY = m_screenHeight;

	self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_mainContainerX, m_mainContainerY, m_mainContainerWidth, m_mainContainerHeight)] autorelease];
	self.pMenuContainer.backgroundColor = m_pColour;

	m_dragTabHeight = (40.f * m_pixelScale);
	m_dragTabWidth = (m_mainContainerOnScreenWidth - (2.f * m_dragTabHeight));
	m_dragTabX = m_mainContainerX + (m_mainContainerWidth/2.f - m_dragTabWidth/2.f);
	m_dragTabY = m_mainContainerY - m_dragTabHeight;
	self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabX, m_dragTabY, m_dragTabWidth, m_dragTabHeight)] autorelease];
	self.pDragTab.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;

	m_tableOffsetIntoContainerX = (0.f * m_pixelScale);
	m_tableOffsetIntoContainerY = (0.f * m_pixelScale);
	m_tableX = m_tableOffsetIntoContainerX;
	m_tableY = m_tableOffsetIntoContainerY + m_mainContainerVisibleOnScreenWhenClosedY;
	m_tableWidth = m_mainContainerOnScreenWidth - (2 * m_tableOffsetIntoContainerX);
	m_tableHeight = m_mainContainerHeight - (2 * m_tableOffsetIntoContainerY) - m_tableOffsetIntoContainerY;
	self.pTableview = [[[CustomTableView alloc] initWithFrame:CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight) style:UITableViewStylePlain] autorelease];
	self.pTableview.backgroundColor = m_pColour;
	self.pTableview.separatorStyle = UITableViewCellSeparatorStyleNone;

	m_offscreenY = m_dragTabHeight;
	m_openY = -m_mainContainerOnScreenHeight;
	m_closedY = -m_mainContainerVisibleOnScreenWhenClosedY;
	m_offscreenX = (0.0f * m_pixelScale);

	//close
	const float closeButtonEdgeSize = m_dragTabHeight;
	self.pClearResults = [[[UIButton alloc] initWithFrame:CGRectMake(m_dragTabX + m_dragTabWidth, m_dragTabY, closeButtonEdgeSize, closeButtonEdgeSize)] autorelease];
	[self.pClearResults setBackgroundImage:[UIImage imageNamed:@"buttonsmall_close_off.png"] forState:UIControlStateNormal];
	[self.pClearResults setBackgroundImage:[UIImage imageNamed:@"buttonsmall_close_on.png"] forState:UIControlStateHighlighted];

	//category
	const float categoryIconEdgeSize = m_dragTabHeight;
	self.pCategory = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabX - categoryIconEdgeSize, m_dragTabY, categoryIconEdgeSize, categoryIconEdgeSize)] autorelease];

	//spinner
	const CGFloat spinnerSize = self.pDragTab.frame.size.height;
	const CGFloat spinnerX = self.pDragTab.frame.size.width - spinnerSize;
	CGRect spinnerFrame = CGRectMake(spinnerX, 0.f, spinnerSize, spinnerSize);
	self.pSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:spinnerFrame] autorelease];
	[self.pSpinner startAnimating];
	self.pSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;

	//results count
	CGRect resultsCountFrame = spinnerFrame;
	self.pResultsCount = [[[UILabel alloc] initWithFrame:resultsCountFrame] autorelease];
	self.pResultsCount.textColor = ExampleApp::Helpers::ColorPalette::GreyTone;
	self.pResultsCount.textAlignment = NSTextAlignmentCenter;

	//heading label
	const float headingMarginX = 5.f;
	CGRect headingFrame = CGRectMake(headingMarginX, 0.f, spinnerX, spinnerSize);
	self.pHeading = [[[UILabel alloc] initWithFrame:headingFrame] autorelease];
	self.pHeading.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
	self.pHeading.textAlignment = NSTextAlignmentLeft;
	self.pHeading.text = @"";
	UIFont* boldFont = [UIFont boldSystemFontOfSize:16];
	[self.pHeading setFont:boldFont];

	[self addSubview: self.pMenuContainer];
	[self addSubview: self.pDragTab];
	[self addSubview: self.pClearResults];
	[self addSubview: self.pCategory];
	[self.pDragTab addSubview: self.pHeading];
	[self.pDragTab addSubview: self.pSpinner];
	[self.pDragTab addSubview: self.pResultsCount];
	[self.pMenuContainer addSubview: self.pTableview];

	ExampleApp::Helpers::ImageHelpers::OffsetValue menuShadowOffset = ExampleApp::Helpers::ImageHelpers::Centre | ExampleApp::Helpers::ImageHelpers::Top;
	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pMenuContainer, "shadow_03", menuShadowOffset);
}

- (void)dealloc
{
	[self.pTableview removeFromSuperview];
	[self.pTableview release];

	[self.pSpinner removeFromSuperview];
	[self.pSpinner release];

	[self.pResultsCount removeFromSuperview];
	[self.pResultsCount release];

	[self.pDragTab removeFromSuperview];
	[self.pDragTab release];

	[self.pMenuContainer removeFromSuperview];
	[self.pMenuContainer release];

	[self.pHeading removeFromSuperview];
	[self.pHeading release];

	[self.pClearResults removeFromSuperview];
	[self.pClearResults release];

	[self.pCategory removeFromSuperview];
	[self.pCategory release];

	[self removeFromSuperview];
	[super dealloc];
}

- (void) updateViewForQuery:(std::string)searchText :(bool)queryPending :(size_t)numResults
{
	if(queryPending)
	{
		[self.pSpinner startAnimating];
		self.pResultsCount.hidden = true;
	}
	else
	{
		[self.pSpinner stopAnimating];
		self.pResultsCount.text = [NSString stringWithFormat:@"%lu", numResults];
		self.pResultsCount.hidden = false;
	}

	self.pHeading.text = [NSString stringWithUTF8String: searchText.c_str()];
	[self.pCategory.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];

	std::string categoryIcon = ExampleApp::Helpers::IconResources::GetSmallIconForCategory(searchText);
	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategory, categoryIcon, ExampleApp::Helpers::ImageHelpers::Centre);
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
	if([self isAnimating])
	{
		return;
	}

	self.hidden = false;
	[self setOffscreenPartsHiddenState:false];

	float newY = m_offscreenY + ((m_closedY - m_offscreenY) * onScreenState);
	if(fabs(self.frame.origin.y - newY) < 0.01f)
	{
		return;
	}

	CGRect f = self.frame;
	f.origin.y = newY;
	self.frame = f;
}

- (void) updateDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
	CGRect f = self.frame;
	f.origin.y = m_controlStartPos.y + (absolutePosition.y - m_dragStartPos.y);

	if(f.origin.y < -m_mainContainerHeight)
	{
		f.origin.y = -m_mainContainerHeight;
	}

	if(f.origin.y > m_closedX)
	{
		f.origin.y = m_closedX;
	}

	float normalisedDragState = -((static_cast<float>(self.frame.origin.y) + (-m_closedY)) / (std::abs(m_openY - m_closedY)));
	normalisedDragState = Eegeo::Clamp(normalisedDragState, 0.f, 1.f);

	[m_pMenuViewController handleDraggingViewInProgress:normalisedDragState];
	self.frame = f;

	[self.layer removeAllAnimations];
}

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
	const bool startedClosed = m_controlStartPos.y == 0.f;
	const float yRatioForStateChange = startedClosed ? 0.35f : 0.65f;
	const float threshold = (m_screenHeight - (m_mainContainerOnScreenHeight * yRatioForStateChange));
	bool open = absolutePosition.y < threshold;

	const float velocityMagitude = std::abs(static_cast<float>(absoluteVelocity.y));
	if(velocityMagitude > (200 * m_pixelScale))
	{
		open = absoluteVelocity.y < 0 ? true : false;
	}

	[super animateToY:(open ? m_openY : m_closedY)];
}

- (bool) useSizeToFit
{
    return true;
}

@end
