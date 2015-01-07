// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include <algorithm>
#include <sstream>
#include "AboutPageView.h"
#include "AboutPageModel.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "App.h"

@implementation AboutPageView

- (id)initWithController:(AboutPageViewController*)controller
{
	self = [super init];

	if(self)
	{
		m_pController = controller;
		self.alpha = 0.f;
		m_stateChangeAnimationTimeSeconds = 0.2f;
        
        [self initNib];
	}

	return self;
}

- (void)dealloc
{
	[self removeFromSuperview];
	[super dealloc];
}

- (UIView*)findView:(NSArray*)objects
{
    for (id object in objects)
    {
        if ([object isKindOfClass:[UIView class]])
        {
            return object;
        }
    }
    return nil;
}

- (void)initNib
{
    NSArray *objects = [[NSBundle mainBundle] loadNibNamed:@"TestCustomView" owner:self options:nil];
    UIView *containerView = [self findView:objects];
    [self addSubview:containerView];
    
    self.translatesAutoresizingMaskIntoConstraints = NO;
    containerView.translatesAutoresizingMaskIntoConstraints = NO;
    
    
    NSDictionary *viewsDictionary = NSDictionaryOfVariableBindings(self, containerView);
    
    [self addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"H:|-0-[containerView]-0-|" options:0 metrics: 0 views:viewsDictionary]];
    [self addConstraints:[NSLayoutConstraint constraintsWithVisualFormat:@"V:|-0-[containerView]-0-|" options:0 metrics: 0 views:viewsDictionary]];
    
    [self setNeedsUpdateConstraints];
}


- (void)layoutSubviews
{
	self.alpha = 0.f;

	const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
	const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = App::IsDeviceSmall();
	const float boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
	const float boundsOccupyHeightMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f));
	const float mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
	const float mainWindowHeight = boundsHeight * boundsOccupyHeightMultiplier;
	const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
	const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.translatesAutoresizingMaskIntoConstraints = YES;

	self.frame = CGRectMake(mainWindowX,
	                        mainWindowY,
	                        mainWindowWidth,
	                        mainWindowHeight);
    
    [super layoutSubviews];
}

- (void) setContent:(const ExampleApp::AboutPage::IAboutPageModel*)pModel
{
	std::stringstream content;
	content << pModel->GetAboutText()
	        << "\n\nPlatform version: " + pModel->GetPlatformVersion()
	        << "\nPlatform hash: " + pModel->GetPlatformHash()
            << "\nPlatform runtime arch: " + pModel->GetPlatformArchitecture()
	        << "\n\n";

	self.pTextContent.text = [NSString stringWithUTF8String:content.str().c_str()];
    self.pTextContent.numberOfLines = 0;
	[self.pTextContent sizeToFit];
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
