// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CompassView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "ScaleHelpers.h"

@implementation CompassView

- (id) initWithParams:(CompassViewController*)controller :(float)width :(float)height :(float)pixelScale
{
	if(self = [super init])
	{
        float iphoneTweakScale = ExampleApp::Helpers::ScaleHelpers::GetScaleTweakValue();
		m_pController = controller;
		m_stateChangeAnimationTimeSeconds = 0.2f;
		m_pixelScale = 1.f;
		m_screenWidth = width/pixelScale;
		m_screenHeight = height/pixelScale;
		m_darkColour = ExampleApp::Helpers::ColorPalette::GoldTone;
		m_lightColour = ExampleApp::Helpers::ColorPalette::WhiteTone;

		//control positioning
		m_width = 64 * m_pixelScale * iphoneTweakScale;
		m_height = m_width;
		m_yPosActive = 16 * m_pixelScale;
		m_yPosInactive = -m_height;
		self.frame = CGRectMake(((m_screenWidth * 0.5f) - (m_width * 0.5f)), m_yPosActive, m_width, m_height);

		//outer shape shadow
		self.pOuterShadowContainer = [[[UIView alloc] init] autorelease];
		[self addSubview: self.pOuterShadowContainer];
		ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pOuterShadowContainer, "compass_shadow", 8*iphoneTweakScale, 8*iphoneTweakScale, m_width, m_height);

		//outer shape
		self.pOuterShape = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_width, m_height)] autorelease];
		self.pOuterShape.layer.cornerRadius = m_width * 0.5;
		self.pOuterShape.backgroundColor = m_lightColour;
		[self addSubview: self.pOuterShape];

		//inner shape
		const float innerWidth = 54 * m_pixelScale * iphoneTweakScale;
		const float innerHeight = innerWidth;
		self.pInnerShape = [[[UIView alloc] initWithFrame:CGRectMake(5.f * iphoneTweakScale, 5.f * iphoneTweakScale, innerWidth, innerHeight)] autorelease];
		self.pInnerShape.layer.cornerRadius = innerWidth * 0.5;
		self.pInnerShape.backgroundColor = m_darkColour;
		[self addSubview: self.pInnerShape];

		//compass point shadow
		self.pPointShadowContainer = [[[UIView alloc] init] autorelease];
		[self addSubview: self.pPointShadowContainer];
		ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pPointShadowContainer, "compass_shadow", 0, 0, 12 * iphoneTweakScale, 12 * iphoneTweakScale);

		//compass point
		float pointWidth = (12.f * m_pixelScale) * iphoneTweakScale;
		float pointHeight = pointWidth;
		self.pPoint = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, pointWidth, pointHeight)] autorelease];
		self.pPoint.backgroundColor = m_lightColour;
		self.pPoint.layer.cornerRadius = pointWidth * 0.5;
		[self addSubview: self.pPoint];

		//lock icon
		self.pLockIconContainer = [[[UIView alloc] init] autorelease];
		[self addSubview: self.pLockIconContainer];
		ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pLockIconContainer, "compass_lock", 54 * iphoneTweakScale, 0, 25 * iphoneTweakScale, 25 * iphoneTweakScale);
		self.pLockIconContainer.alpha = 0.f;

		m_compassPointNaturalOffsetX = (m_width / 2.f) - (pointWidth / 2.f);
		m_compassPointNaturalOffsetY = (m_width / 2.f) - (pointWidth / 2.f);
	}

	return self;
}

- (void)dealloc
{
	[self.pOuterShape removeFromSuperview];
	[self.pOuterShape release];

	[self.pOuterShadowContainer removeFromSuperview];
	[self.pOuterShadowContainer release];

	[self.pInnerShape removeFromSuperview];
	[self.pInnerShape release];

	[self.pPoint removeFromSuperview];
	[self.pPoint release];

	[self.pPointShadowContainer removeFromSuperview];
	[self.pPointShadowContainer release];

	[self.pLockIconContainer removeFromSuperview];
	[self.pLockIconContainer release];

	[super dealloc];
}

- (void)layoutSubviews
{

}

- (void) showGpsDisabledView
{
	[self.pOuterShape setBackgroundColor: m_lightColour];
	[self.pInnerShape setBackgroundColor: m_darkColour];
	[self.pPoint setBackgroundColor: m_lightColour];

	[UIView animateWithDuration:m_stateChangeAnimationTimeSeconds animations:^ {self.pLockIconContainer.alpha = 0.f;}];
}

- (void) showGpsFollowView
{
	[self.pOuterShape setBackgroundColor: m_darkColour];
	[self.pInnerShape setBackgroundColor: m_lightColour];
	[self.pPoint setBackgroundColor: m_darkColour];

	[UIView animateWithDuration:m_stateChangeAnimationTimeSeconds animations:^ {self.pLockIconContainer.alpha = 0.f;}];
}

- (void) showGpsCompassModeView
{
	[self.pOuterShape setBackgroundColor: m_darkColour];
	[self.pInnerShape setBackgroundColor: m_lightColour];
	[self.pPoint setBackgroundColor: m_darkColour];

	[UIView animateWithDuration:m_stateChangeAnimationTimeSeconds animations:^ {self.pLockIconContainer.alpha = 1.f;}];
}

- (void) updateHeading:(float)angleRadians
{
	const float theta = -angleRadians;
	const float sinTheta = (float)sin(theta);
	const float cosTheta = (float)cos(theta);
	const float x = 0.f;
    const float y = -15.f * ExampleApp::Helpers::ScaleHelpers::GetScaleTweakValue();
	const float newX = (x*cosTheta - y*sinTheta) + m_compassPointNaturalOffsetX;
	const float newY = (y*cosTheta + x*sinTheta) + m_compassPointNaturalOffsetY;

	CGRect frame = self.pPoint.frame;
	frame.origin.x = newX;
	frame.origin.y = newY;
	self.pPoint.frame = frame;

	CGRect shadowFrame = self.pPointShadowContainer.frame;
	shadowFrame.origin.x = newX + 2.f;
	shadowFrame.origin.y = newY + 2.f;
	self.pPointShadowContainer.frame = shadowFrame;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
	CGPoint touchLocation = [touch locationInView:self];
	return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) setFullyOnScreen
{
	if(self.frame.origin.y == m_yPosActive)
	{
		return;
	}

	[self animateToY:m_yPosActive];
}

- (void) setFullyOffScreen
{
	if(self.frame.origin.y == m_yPosInactive)
	{
		return;
	}

	[self animateToY:m_yPosInactive];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
	float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;

	self.hidden = false;
	CGRect f = self.frame;
	f.origin.y = newY;
	self.frame = f;
}

- (void) animateToY:(float)y
{
	CGRect f = self.frame;
	f.origin.y = y;

	if(y != m_yPosInactive)
	{
		self.hidden = false;
	}

	[UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
	 animations:^
	{
		self.frame = f;
	}
	completion:^(BOOL finished)
	{
		self.hidden = (y == m_yPosInactive);
	}
	];
}

@end

