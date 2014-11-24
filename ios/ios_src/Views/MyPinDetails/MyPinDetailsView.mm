// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include <algorithm>
#include "MyPinDetailsView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#include "MyPinDetailsViewController.h"

@implementation MyPinDetailsView

- (id)initWithController:(MyPinDetailsViewController*)controller
{
	self = [super init];

	if(self)
	{
		m_pController = controller;
		self.alpha = 0.f;
		m_stateChangeAnimationTimeSeconds = 0.2;
        m_labelsSectionWidth = 0.f;
        m_maxContentSize = 0.f;

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
        [self.pCloseButton addTarget:self action:@selector(onCloseButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
		[self.pCloseButtonContainer addSubview: self.pCloseButton];
        
        self.pRemovePinButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pRemovePinButton setBackgroundImage:[UIImage imageNamed:@"button_remove_pin_off.png"] forState:UIControlStateNormal];
        [self.pRemovePinButton setBackgroundImage:[UIImage imageNamed:@"button_remove_pin_on.png"] forState:UIControlStateHighlighted];
        [self.pRemovePinButton addTarget:self action:@selector(onRemovePinButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pRemovePinButton];

		self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
		[self.pControlContainer addSubview: self.pContentContainer];

		self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
		[self.pControlContainer addSubview: self.pHeadlineContainer];

		self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
		self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
		[self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pContentContainer addSubview: self.pLabelsContainer];
        
		self.pDescriptionHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pDescriptionHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
		[self.pLabelsContainer addSubview: self.pDescriptionHeaderContainer];

		self.pDescriptionHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
		[self.pDescriptionHeaderContainer addSubview: self.pDescriptionHeaderLabel];

        self.pDescriptionContent = [[[UITextView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
		self.pDescriptionContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pDescriptionContent.editable = NO;
		[self.pLabelsContainer addSubview: self.pDescriptionContent];

		self.pImageHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
		self.pImageHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;

		[self.pLabelsContainer addSubview: self.pImageHeaderContainer];

		self.pImageHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
		[self.pImageHeaderContainer addSubview: self.pImageHeaderLabel];

        self.pImageContent = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pImageContent.image = [UIImage imageNamed: @"image_blank.png"];

		[self.pLabelsContainer addSubview: self.pImageContent];
	}

	return self;
}

- (void)dealloc
{
    [self.pRemovePinButton removeFromSuperview];
    [self.pRemovePinButton release];
    
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

	[self.pTitleLabel removeFromSuperview];
	[self.pTitleLabel release];

	[self.pDescriptionHeaderLabel removeFromSuperview];
	[self.pDescriptionHeaderLabel release];

	[self.pDescriptionHeaderContainer removeFromSuperview];
	[self.pDescriptionHeaderContainer release];

	[self.pDescriptionContent removeFromSuperview];
	[self.pDescriptionContent release];

	[self.pImageHeaderLabel removeFromSuperview];
	[self.pImageHeaderLabel release];

	[self.pImageHeaderContainer removeFromSuperview];
	[self.pImageHeaderContainer release];

	[self.pImageContent removeFromSuperview];
	[self.pImageContent release];

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
	m_labelsSectionWidth = mainWindowWidth - (2.f * labelsSectionOffsetX);

    self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                             0.f,
                                             m_labelsSectionWidth,
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
    
    self.pRemovePinButton.frame = CGRectMake(0.f,
                                             0.f,
                                             closeButtonSectionHeight,
                                             closeButtonSectionHeight);

	const float titlePadding = 10.0f;
	self.pTitleLabel.frame = CGRectMake(titlePadding,
	                                    0.f,
	                                    mainWindowWidth - titlePadding,
	                                    headlineHeight);
	self.pTitleLabel.font = [UIFont systemFontOfSize:24.0f];
	self.pTitleLabel.text = @"";

	m_headerLabelHeight = 20.f;
	m_labelYSpacing = 8.f;
	float currentLabelY = m_labelYSpacing;

	m_headerTextPadding = 3.0f;
	self.pDescriptionHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, m_headerLabelHeight + 2 * m_headerTextPadding);

	self.pDescriptionHeaderLabel.frame = CGRectMake(m_headerTextPadding, m_headerTextPadding, m_labelsSectionWidth - m_headerTextPadding, m_headerLabelHeight);
	self.pDescriptionHeaderLabel.text = @"Description";
	currentLabelY += m_labelYSpacing + self.pDescriptionHeaderContainer.frame.size.height;

    m_descriptionContentY = currentLabelY;
	self.pDescriptionContent.frame = CGRectMake(m_headerTextPadding, currentLabelY, m_labelsSectionWidth - m_headerTextPadding, 60.f);
	self.pDescriptionContent.text = @"";
    self.pDescriptionContent.font = [UIFont systemFontOfSize: 16.f];
    self.pDescriptionContent.contentInset = UIEdgeInsetsMake(-4,-8,0,0);
	currentLabelY += m_labelYSpacing + self.pDescriptionContent.frame.size.height;

	self.pImageHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, m_headerLabelHeight + 2 * m_headerTextPadding);

	self.pImageHeaderLabel.frame = CGRectMake(m_headerTextPadding, m_headerTextPadding, m_labelsSectionWidth - m_headerTextPadding, m_headerLabelHeight);
	self.pImageHeaderLabel.text = @"Image";
	currentLabelY += m_labelYSpacing + self.pImageHeaderContainer.frame.size.height;

    m_maxImageWidth = m_labelsSectionWidth - m_headerTextPadding;
	self.pImageContent.frame = CGRectMake(m_headerTextPadding, currentLabelY, m_maxImageWidth, m_labelsSectionWidth * 0.75f);
    currentLabelY += m_labelYSpacing + self.pImageContent.frame.size.height;
    m_scrollContentBottomMargin = 0;
    m_scrollContentWidth = m_labelsSectionWidth;
    
	[self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
    m_maxContentSize = currentLabelY;
}

- (void) setContent:(const ExampleApp::MyPins::MyPinModel*)pModel
{
	self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];

	self.pDescriptionHeaderContainer.hidden = true;
	self.pDescriptionContent.hidden = true;
	self.pImageHeaderContainer.hidden = true;
	self.pImageContent.hidden = true;
    
    self.pDescriptionHeaderContainer.hidden = false;
    self.pDescriptionContent.hidden = false;
    self.pDescriptionContent.text = [NSString stringWithUTF8String: pModel->GetDescription().c_str()];
    
    float textContentSize = self.pDescriptionHeaderContainer.bounds.size.height + self.pDescriptionContent.contentSize.height;
    
    self.pDescriptionContent.frame = CGRectMake(m_headerTextPadding, m_descriptionContentY, m_labelsSectionWidth - m_headerTextPadding, m_maxContentSize);
    self.pLabelsContainer.contentSize = CGSizeMake(m_labelsSectionWidth, textContentSize);
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];

	if(!pModel->GetImagePath().empty())
	{
        NSArray* libraryPaths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
        NSString* libraryDirectory = [libraryPaths objectAtIndex:0];
        NSString* imageFilename = [NSString stringWithUTF8String: pModel->GetImagePath().c_str()];
        NSString* fullPathToImage  = [libraryDirectory stringByAppendingPathComponent: imageFilename];
        
        float imageContentHeaderOriginY = m_descriptionContentY + textContentSize;
        
        self.pImageContent.image = [UIImage imageWithContentsOfFile: fullPathToImage];
		self.pImageHeaderContainer.hidden = false;
        self.pImageHeaderContainer.frame = CGRectMake(m_headerTextPadding, imageContentHeaderOriginY, m_labelsSectionWidth, 20.0f + 2 * m_headerTextPadding);
        self.pImageContent.frame = CGRectMake(m_headerTextPadding, imageContentHeaderOriginY + m_headerLabelHeight + m_labelYSpacing, 0, 0);
		self.pImageContent.hidden = false;
        
        [self resizeImageViewToFit:self.pImageContent.image.size.width :self.pImageContent.image.size.height];
	}
    
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

- (void) onCloseButtonPressed:(UIButton *)sender
{
    [m_pController handleCloseButtonPressed];
}

- (void) onRemovePinButtonPressed:(UIButton *)sender
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Remove Pin"
                                                    message:@"Are you sure you want to remove this pin?"
                                                   delegate:self
                                          cancelButtonTitle:@"No, keep it"
                                          otherButtonTitles:@"Yes, delete it", nil];
    
    [alert show];
    [alert release];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1)
    {
        [m_pController handleRemovePinButtonPressed];
    }
}

- (void) resizeImageViewToFit:(float)sourceImageWidth :(float)sourceImageHeight
{
    const float widthRatio = m_maxImageWidth/sourceImageWidth;
    const float height = sourceImageHeight * widthRatio;
    
    CGRect frame = self.pImageContent.frame;
    self.pImageContent.frame = CGRectMake(frame.origin.x, frame.origin.y, m_maxImageWidth, height);
    
    self.pLabelsContainer.contentSize = CGSizeMake(m_scrollContentWidth, self.pImageContent.frame.origin.y + self.pImageContent.frame.size.height + m_scrollContentBottomMargin);
}

@end
