// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include <algorithm>
#include "SearchResultPoiView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"

@implementation SearchResultPoiView

- (id)initWithController:(SearchResultPoiViewController*)controller
{
	self = [super init];

	if(self)
	{
		m_pController = controller;
		self.alpha = 0.f;
		m_stateChangeAnimationTimeSeconds = 0.2;

		self.pShadowContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pShadowContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::BlackTone;
		self.pShadowContainer.alpha = 0.1f;
		[self addSubview: self.pShadowContainer];

		self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
		[self addSubview: self.pControlContainer];

		self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
		[self.pControlContainer addSubview: self.pCloseButtonContainer];

		self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		[self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_off.png"] forState:UIControlStateNormal];
		[self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_on.png"] forState:UIControlStateHighlighted];
		[self.pCloseButtonContainer addSubview: self.pCloseButton];

		self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
		[self.pControlContainer addSubview: self.pContentContainer];

		self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
		[self.pContentContainer addSubview: self.pLabelsContainer];

		self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
		[self.pControlContainer addSubview: self.pHeadlineContainer];

		self.pCategoryIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		[self.pHeadlineContainer addSubview: self.pCategoryIconContainer];

		self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
		self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
		[self.pHeadlineContainer addSubview: self.pTitleLabel];

		self.pAddressHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pAddressHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
		[self.pLabelsContainer addSubview: self.pAddressHeaderContainer];

		self.pAddressHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
		[self.pAddressHeaderContainer addSubview: self.pAddressHeaderLabel];

		self.pAddressContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
		self.pAddressContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
		[self.pLabelsContainer addSubview: self.pAddressContent];

		self.pPhoneHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pPhoneHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;

		[self.pLabelsContainer addSubview: self.pPhoneHeaderContainer];

		self.pPhoneHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
		[self.pPhoneHeaderContainer addSubview: self.pPhoneHeaderLabel];

		self.pPhoneContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
		self.pPhoneContent.textColor = ExampleApp::Helpers::ColorPalette::LinkTone;
		UITapGestureRecognizer* phoneTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnPhone:)];
		[self.pPhoneContent setUserInteractionEnabled:YES];
		[self.pPhoneContent addGestureRecognizer:phoneTappedGesture];

		[self.pLabelsContainer addSubview: self.pPhoneContent];

		self.pWebHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pWebHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
		[self.pLabelsContainer addSubview: self.pWebHeaderContainer];

		self.pWebHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
		[self.pWebHeaderContainer addSubview: self.pWebHeaderLabel];

		self.pWebContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
		self.pWebContent.textColor = ExampleApp::Helpers::ColorPalette::LinkTone;
		UITapGestureRecognizer* urlTappedGesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(userTappedOnLink:)];
		[self.pWebContent setUserInteractionEnabled:YES];
		[self.pWebContent addGestureRecognizer:urlTappedGesture];

		[self.pLabelsContainer addSubview: self.pWebContent];
        
        [self setTouchExclusivity: self];
	}

	return self;
}

- (void) setTouchExclusivity: (UIView*) view
{
    for (UIView *subView in [view subviews])
    {
        if ([subView subviews] != nil)
        {
            [self setTouchExclusivity: subView];
        }
        
        subView.exclusiveTouch = YES;
    }
}

- (void)dealloc
{
	[self.pCloseButton removeFromSuperview];
	[self.pCloseButton release];

	[self.pCloseButtonContainer removeFromSuperview];
	[self.pCloseButtonContainer release];

	[self.pShadowContainer removeFromSuperview];
	[self.pShadowContainer release];

	[self.pControlContainer removeFromSuperview];
	[self.pControlContainer release];

	[self.pHeadlineContainer removeFromSuperview];
	[self.pHeadlineContainer release];

	[self.pLabelsContainer removeFromSuperview];
	[self.pLabelsContainer release];

	[self.pContentContainer removeFromSuperview];
	[self.pContentContainer release];

	[self.pCategoryIconContainer removeFromSuperview];
	[self.pCategoryIconContainer release];

	[self.pTitleLabel removeFromSuperview];
	[self.pTitleLabel release];

	[self.pAddressHeaderLabel removeFromSuperview];
	[self.pAddressHeaderLabel release];

	[self.pAddressHeaderContainer removeFromSuperview];
	[self.pAddressHeaderContainer release];

	[self.pAddressContent removeFromSuperview];
	[self.pAddressContent release];

	[self.pPhoneHeaderLabel removeFromSuperview];
	[self.pPhoneHeaderLabel release];

	[self.pPhoneHeaderContainer removeFromSuperview];
	[self.pPhoneHeaderContainer release];

	[self.pPhoneContent removeFromSuperview];
	[self.pPhoneContent release];

	[self.pWebHeaderLabel removeFromSuperview];
	[self.pWebHeaderLabel release];

	[self.pWebHeaderContainer removeFromSuperview];
	[self.pWebHeaderContainer release];

	[self.pWebContent removeFromSuperview];
	[self.pWebContent release];

	[self removeFromSuperview];
	[super dealloc];
}

- (void)layoutSubviews
{
	self.alpha = 0.f;

	const float boundsWidth = self.superview.bounds.size.width;
	const float boundsHeight = self.superview.bounds.size.height;
	const bool useFullScreenSize = (boundsHeight < 600.f || boundsWidth < 400.f);
	const float boundsOccupyMultiplier = useFullScreenSize ? 0.9f : 0.5f;
	const float mainWindowWidth = boundsWidth * boundsOccupyMultiplier;
	const float mainWindowHeight = boundsHeight * boundsOccupyMultiplier;
	const float mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
	const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);

	self.frame = CGRectMake(mainWindowX,
	                        mainWindowY,
	                        mainWindowWidth,
	                        mainWindowHeight);

	self.pControlContainer.frame = CGRectMake(0.f,
	                               0.f,
	                               mainWindowWidth,
	                               mainWindowHeight);

	self.pShadowContainer.frame = CGRectMake(2.f,
	                              2.f,
	                              mainWindowWidth,
	                              mainWindowHeight);
	const float headlineHeight = 50.f;
	const float closeButtonSectionHeight = 80.f;
	const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
	const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
	const float shadowHeight = 10.f;

	self.pHeadlineContainer.frame = CGRectMake(0.f,
	                                0.f,
	                                mainWindowWidth,
	                                headlineHeight);

	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pHeadlineContainer, "shadow_03", 0.f, headlineHeight, mainWindowWidth, shadowHeight);


	self.pContentContainer.frame = CGRectMake(0.f,
	                               headlineHeight,
	                               mainWindowWidth,
	                               contentSectionHeight);

	const float labelsSectionOffsetX = 12.f;
	const float labelsSectionWidth = mainWindowWidth - (2.f * labelsSectionOffsetX);

	self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
	                              0.f,
	                              labelsSectionWidth,
	                              contentSectionHeight);


	self.pCloseButtonContainer.frame = CGRectMake(0.f,
	                                   closeButtonSectionOffsetY,
	                                   mainWindowWidth,
	                                   closeButtonSectionHeight);

	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pContentContainer, "shadow_03", 0.f, contentSectionHeight, mainWindowWidth, shadowHeight);

	self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight,
	                                     0.f,
	                                     closeButtonSectionHeight,
	                                     closeButtonSectionHeight);

	self.pCategoryIconContainer.frame = CGRectMake(0.f, 0.f, headlineHeight, headlineHeight);
	const float titlePadding = 10.0f;
	self.pTitleLabel.frame = CGRectMake(headlineHeight + titlePadding,
	                                    0.f,
	                                    mainWindowWidth - (headlineHeight + titlePadding),
	                                    headlineHeight);
	self.pTitleLabel.font = [UIFont systemFontOfSize:24.0f];
	self.pTitleLabel.text = @"";

	const float headerLabelHeight = 16.f;
	const float labelYSpacing = 8.f;
	float currentLabelY = labelYSpacing;

	const float headerTextPadding = 3.0f;
	self.pAddressHeaderContainer.frame = CGRectMake(0.f, currentLabelY, labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);

	self.pAddressHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, labelsSectionWidth - headerTextPadding, headerLabelHeight);
	self.pAddressHeaderLabel.text = @"Address";
	currentLabelY += labelYSpacing + self.pAddressHeaderContainer.frame.size.height;

	self.pAddressContent.frame = CGRectMake(headerTextPadding, currentLabelY, labelsSectionWidth - headerTextPadding, 85.f);
	self.pAddressContent.text = @"";
	self.pAddressContent.numberOfLines = 0;
	self.pAddressContent.adjustsFontSizeToFitWidth = NO;
	self.pAddressContent.lineBreakMode = NSLineBreakByTruncatingTail;
	currentLabelY += labelYSpacing + self.pAddressContent.frame.size.height;

	self.pPhoneHeaderContainer.frame = CGRectMake(0.f, currentLabelY, labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);

	self.pPhoneHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, labelsSectionWidth - headerTextPadding, headerLabelHeight);
	self.pPhoneHeaderLabel.text = @"Phone";
	currentLabelY += labelYSpacing + self.pPhoneHeaderContainer.frame.size.height;

	self.pPhoneContent.frame = CGRectMake(headerTextPadding, currentLabelY, labelsSectionWidth - headerTextPadding, 32.f);
	self.pPhoneContent.text = @"";
	currentLabelY += labelYSpacing + self.pPhoneContent.frame.size.height;

	self.pWebHeaderContainer.frame = CGRectMake(0.f, currentLabelY, labelsSectionWidth, headerLabelHeight + 2 * headerTextPadding);

	self.pWebHeaderLabel.frame = CGRectMake(headerTextPadding, headerTextPadding, labelsSectionWidth - headerTextPadding, headerLabelHeight);
	self.pWebHeaderLabel.text = @"Web";
	currentLabelY += labelYSpacing + self.pWebHeaderContainer.frame.size.height;

	self.pWebContent.frame = CGRectMake(headerTextPadding, currentLabelY, labelsSectionWidth - headerTextPadding, 32.f);
	self.pWebContent.text = @"";
	currentLabelY += labelYSpacing + self.pWebContent.frame.size.height;

	[self.pLabelsContainer setContentSize:CGSizeMake(labelsSectionWidth, currentLabelY)];
}

- (void) setContent:(const ExampleApp::Search::SearchResultModel*)pModel
{
	self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];

	[self.pCategoryIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
	std::string categoryIcon = ExampleApp::Helpers::IconResources::GetSmallIconForCategory(pModel->GetCategory());
	ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategoryIconContainer, categoryIcon, ExampleApp::Helpers::ImageHelpers::Centre);

	self.pAddressHeaderContainer.hidden = true;
	self.pAddressContent.hidden = true;
	self.pPhoneHeaderContainer.hidden = true;
	self.pPhoneContent.hidden = true;
	self.pWebHeaderContainer.hidden = true;
	self.pWebContent.hidden = true;

	if(!pModel->GetAddress().empty())
	{
		self.pAddressHeaderContainer.hidden = false;
		self.pAddressContent.hidden = false;
		std::string addressText = pModel->GetAddress();
		Eegeo::Helpers::SearchReplace(addressText,", ", "\n");
		self.pAddressContent.text = [NSString stringWithUTF8String:addressText.c_str()];
	}

	if(!pModel->GetPhone().empty())
	{
		self.pPhoneHeaderContainer.hidden = false;
		self.pPhoneContent.hidden = false;
		self.pPhoneContent.text = [NSString stringWithUTF8String:pModel->GetPhone().c_str()];
		[self.pWebContent sizeToFit];
	}

	if(!pModel->GetWebUrl().empty())
	{
		self.pWebHeaderContainer.hidden = false;
		self.pWebContent.hidden = false;
		self.pWebContent.text = [NSString stringWithUTF8String:pModel->GetWebUrl().c_str()];
		[self.pWebContent sizeToFit];
	}

	[self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
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

- (UILabel*) createLabel:(UIColor*)textColor :(UIColor*)backgroundColor
{
	UILabel* pLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
	pLabel.textColor = textColor;
	pLabel.backgroundColor = backgroundColor;
	pLabel.textAlignment = NSTextAlignmentLeft;
	return pLabel;
}

- (void) userTappedOnLink:(UITapGestureRecognizer *)recognizer
{
	NSString * webUrlString = [NSString stringWithFormat:@"http://%@", self.pWebContent.text];
	NSURL *url = [NSURL URLWithString:webUrlString];
	if (![[UIApplication sharedApplication] openURL:url])
	{
		NSLog(@"%@%@",@"Failed to open url:",[url description]);
	}
}

-(void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
	switch (alertView.tag)
	{
	case 1:
		if (buttonIndex == 1)
		{
			NSString * phoneUrlString = [NSString stringWithFormat:@"tel://%@", self.pPhoneContent.text];
			NSURL *url = [NSURL URLWithString:phoneUrlString];
			if (![[UIApplication sharedApplication] openURL:url])
			{
				NSLog(@"%@%@",@"Failed to open phone link:",[url description]);
			}
		}
		break;
	default:
		break;
	}
}

- (void) userTappedOnPhone:(UITapGestureRecognizer *)recognizer
{
	UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil message:[NSString stringWithFormat:@"Call %@?", self.pPhoneContent.text] delegate:self cancelButtonTitle:@"Cancel" otherButtonTitles:@"Call", nil];
	[alert show];
	alert.tag = 1;
	[alert release];
}

@end
