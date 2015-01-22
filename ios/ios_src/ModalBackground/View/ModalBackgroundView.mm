// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalBackgroundView.h"
#include "MathFunc.h"
#include "UIColors.h"

@implementation ModalBackgroundView

- (id)initWithController:(ModalBackgroundViewController*)controller
{
	self = [super init];

	if(self)
	{
		m_pController = controller;
		[self setBackgroundColor: ExampleApp::Helpers::ColorPalette::ModalBackgroundColor];
		self.alpha = 0.f;
		m_stateChangeAnimationTimeSeconds = 0.2f;
	}

	return self;
}

- (void)dealloc
{
	[self removeFromSuperview];
	[super dealloc];
}

- (void)layoutSubviews
{
	self.alpha = 0.f;
	self.frame = self.superview.bounds;
}

- (void) setFullyActive
{
	if(self.alpha == 1.f)
	{
		return;
	}

	[self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
	if(self.alpha == 0.f)
	{
		return;
	}

	[self animateToAlpha:0.f];
}

- (void) setActiveStateToIntermediateValue:(float)openState
{
	self.alpha = openState;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
	return self.alpha > 0.f;
}

- (void) animateToAlpha:(float)alpha
{
	[UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
	 animations:^
	{
		self.alpha = alpha;
	}];
}

@end