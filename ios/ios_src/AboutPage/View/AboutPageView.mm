// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "AboutPageView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "AboutPageViewInterop.h"
#include "App.h"

@implementation AboutPageView

- (id)initView
{
    self = [super init];

    if(self)
    {
        m_pInterop = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageViewInterop)(self);
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;

        self.pShadowContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pShadowContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::BlackTone;
        self.pShadowContainer.alpha = 0.1f;
        [self addSubview: self.pShadowContainer];

        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self addSubview: self.pControlContainer];

        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];

        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_off.png"] forState:UIControlStateNormal];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_on.png"] forState:UIControlStateHighlighted];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];

        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
        [self.pControlContainer addSubview: self.pContentContainer];

        self.pContainerShadowBottom = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pContentContainer, "shadow_03", 0.f, 0.f, 0, 0);

        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pContentContainer addSubview: self.pLabelsContainer];

        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pControlContainer addSubview: self.pHeadlineContainer];

        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];

        self.pContainerShadowTop = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pContentContainer, "shadow_03", 0.f, 0.f, 0, 0);

        self.pDevelopedByLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDevelopedByLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pDevelopedByLabel.textAlignment = NSTextAlignmentCenter;
        [self.pLabelsContainer addSubview: self.pDevelopedByLabel];

        self.pLogoImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLogoImage.image = [UIImage imageNamed: @"eegeo_logo@ipho.png"];
        [self.pLabelsContainer addSubview: self.pLogoImage];

        self.pTextContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTextContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pTextContent.textAlignment = NSTextAlignmentCenter;
        [self.pLabelsContainer addSubview: self.pTextContent];

        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self.pCloseButton addGestureRecognizer: m_tapGestureRecogniser];
    }

    return self;
}

- (void)dealloc
{
    [m_tapGestureRecogniser release];
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

    [self.pContainerShadowTop removeFromSuperview];
    [self.pContainerShadowTop release];
    [self.pContainerShadowBottom removeFromSuperview];
    [self.pContainerShadowBottom release];

    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];

    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];

    [self.pDevelopedByLabel removeFromSuperview];
    [self.pDevelopedByLabel release];

    [self.pLogoImage removeFromSuperview];
    [self.pLogoImage release];

    [self.pTextContent removeFromSuperview];
    [self.pTextContent release];

    [self removeFromSuperview];
    [super dealloc];
    Eegeo_DELETE m_pInterop;
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
    const float headlineMargin = 10.f;
    const float closeButtonSectionHeight = 80.f;
    const float headlineOffsetY = 10.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSectionOffsetY = headlineOffsetY + headlineHeight;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
    const float shadowHeight = 10.f;

    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                    headlineOffsetY,
                                    mainWindowWidth,
                                    headlineHeight);



    self.pContentContainer.frame = CGRectMake(0.f,
                                   contentSectionOffsetY,
                                   mainWindowWidth,
                                   contentSectionHeight);

    self.pContainerShadowTop.frame = CGRectMake(0.f, 0.f, mainWindowWidth, shadowHeight);

    const float labelsSectionOffsetX = 8.f;
    const float labelsSectionWidth = mainWindowWidth - (2.f * labelsSectionOffsetX);

    self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                  0.f,
                                  labelsSectionWidth,
                                  contentSectionHeight);


    self.pCloseButtonContainer.frame = CGRectMake(0.f,
                                       closeButtonSectionOffsetY,
                                       mainWindowWidth,
                                       closeButtonSectionHeight);

    self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight,
                                         0.f,
                                         closeButtonSectionHeight,
                                         closeButtonSectionHeight);

    self.pContainerShadowBottom.frame = CGRectMake(0.f, contentSectionHeight, mainWindowWidth, shadowHeight);

    const float headlineWidth = mainWindowWidth - headlineMargin;

    self.pTitleLabel.frame = CGRectMake(headlineMargin,
                                        0.f,
                                        headlineWidth,
                                        headlineHeight);
    self.pTitleLabel.font = [UIFont systemFontOfSize:18.0f];

    self.pTitleLabel.text = @"About this app...";

    const float textWidth = static_cast<float>(self.pLabelsContainer.frame.size.width) * 0.8f;
    const float textContentX = ((static_cast<float>(self.pLabelsContainer.frame.size.width) / 2) - (textWidth / 2)) + labelsSectionOffsetX;
    const float developedByY = 10.f;
    const float developedByHeight = 16.f;

    self.pDevelopedByLabel.font = [UIFont systemFontOfSize:14.f];
    self.pDevelopedByLabel.text = @"Developed by eeGeo";
    self.pDevelopedByLabel.frame = CGRectMake(textContentX, developedByY, textWidth, developedByHeight);

    const float logoWidth = 140.f;
    const float logoHeight = 52.f;
    const float logoY = developedByY + developedByHeight;
    const float logoX = (static_cast<float>(self.pLabelsContainer.frame.size.width) / 2) - (logoWidth/2) + labelsSectionOffsetX;

    self.pLogoImage.frame = CGRectMake(logoX, logoY, logoWidth, logoHeight);

    const float textContentY = logoY + logoHeight;
    self.pTextContent.frame = CGRectMake(textContentX, textContentY, textWidth, contentSectionHeight - 300.f);
    self.pTextContent.text = @"";
    self.pTextContent.numberOfLines = 0;
    self.pTextContent.adjustsFontSizeToFitWidth = NO;
    self.pTextContent.font = [UIFont systemFontOfSize:14.0f];
    self.pTextContent.lineBreakMode = NSLineBreakByWordWrapping;
}

- (ExampleApp::AboutPage::View::AboutPageViewInterop*)getInterop
{
    return m_pInterop;
}

- (void) setContent:(const std::string*)content
{
    self.pTextContent.text = [NSString stringWithUTF8String:content->c_str()];
    [self.pTextContent sizeToFit];
    self.pLabelsContainer.contentSize = CGSizeMake(std::max(self.pTextContent.frame.size.width, self.pLogoImage.frame.size.width),
                                        self.pTextContent.frame.size.height + self.pLogoImage.frame.size.height + self.pDevelopedByLabel.frame.size.height);
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

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    m_pInterop->CloseTapped();
}

@end
