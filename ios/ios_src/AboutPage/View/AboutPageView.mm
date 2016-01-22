// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "AboutPageView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "AboutPageViewInterop.h"
#include "UIHelpers.h"

@implementation AboutPageView

- (id)initView
{
    self = [super init];

    if(self)
    {
        m_pInterop = Eegeo_NEW(ExampleApp::AboutPage::View::AboutPageViewInterop)(self);
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;


        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pControlContainer];

        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];

        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_close_off") forState:UIControlStateNormal];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];

        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pContentContainer];

        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentContainer addSubview: self.pLabelsContainer];

        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];

        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];

        self.pDevelopedByLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDevelopedByLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pDevelopedByLabel.textAlignment = NSTextAlignmentCenter;
        [self.pLabelsContainer addSubview: self.pDevelopedByLabel];

        self.pLogoImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLogoImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage(@"eegeo_logo");
        [self.pLabelsContainer addSubview: self.pLogoImage];

        self.pTextContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTextContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pTextContent.textAlignment = NSTextAlignmentCenter;
        [self.pLabelsContainer addSubview: self.pTextContent];
        
        UITapGestureRecognizer* pPrivacyTapHandler = [[[UITapGestureRecognizer alloc]
                                                          initWithTarget:self
                                                          action:@selector(privacyClickHandler:)] autorelease];
        self.pPrivacyLink = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPrivacyLink.textColor = ExampleApp::Helpers::ColorPalette::UiTextLinkColor;
        [self.pPrivacyLink addGestureRecognizer: pPrivacyTapHandler];
        [self.pLabelsContainer addSubview: self.pPrivacyLink];
        
        UITapGestureRecognizer* pEulaTapHandler = [[[UITapGestureRecognizer alloc]
                                                    initWithTarget:self
                                                    action:@selector(eulaClickHandler:)] autorelease];
        self.pEulaLink = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pEulaLink.textColor = ExampleApp::Helpers::ColorPalette::UiTextLinkColor;
        [self.pEulaLink addGestureRecognizer: pEulaTapHandler];
        [self.pLabelsContainer addSubview: self.pEulaLink];

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

    [self.pDevelopedByLabel removeFromSuperview];
    [self.pDevelopedByLabel release];

    [self.pLogoImage removeFromSuperview];
    [self.pLogoImage release];

    [self.pTextContent removeFromSuperview];
    [self.pTextContent release];
    
    [self.pPrivacyLink removeFromSuperview];
    [self.pPrivacyLink release];
    
    [self.pEulaLink removeFromSuperview];
    [self.pEulaLink release];

    [self removeFromSuperview];
    [super dealloc];
    Eegeo_DELETE m_pInterop;
}

- (void)layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
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

    const float headlineHeight = 50.f;
    const float headlineMargin = 10.f;
    const float closeButtonSectionHeight = 64.f;
    const float headlineOffsetY = 10.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSectionOffsetY = headlineOffsetY + headlineHeight;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + contentSectionOffsetY);
   
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                    headlineOffsetY,
                                    mainWindowWidth,
                                    headlineHeight);

    self.pContentContainer.frame = CGRectMake(0.f,
                                   contentSectionOffsetY,
                                   mainWindowWidth,
                                   contentSectionHeight);

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
    self.pTextContent.numberOfLines = 0;
    self.pTextContent.adjustsFontSizeToFitWidth = NO;
    self.pTextContent.font = [UIFont systemFontOfSize:14.0f];
    self.pTextContent.lineBreakMode = NSLineBreakByWordWrapping;
    [self.pTextContent sizeToFit];
    
    self.pEulaLink.text = @"EULA";
    self.pEulaLink.font = [UIFont systemFontOfSize:14.f];
    [self.pEulaLink sizeToFit];
    self.pEulaLink.userInteractionEnabled = YES;
    CGRect eulaFrame = self.pPrivacyLink.frame;
    eulaFrame.origin.x = roundf(mainWindowWidth/2.f - self.pEulaLink.frame.size.width/2.f);
    eulaFrame.origin.y = roundf(textContentY + self.pTextContent.frame.size.height);
    self.pEulaLink.frame = eulaFrame;
    
    self.pPrivacyLink.text = @"Privacy Policy";
    self.pPrivacyLink.font = [UIFont systemFontOfSize:14.f];
    [self.pPrivacyLink sizeToFit];
    self.pPrivacyLink.userInteractionEnabled = YES;
    CGRect privacyFrame = self.pPrivacyLink.frame;
    privacyFrame.origin.x = roundf(mainWindowWidth/2.f - self.pEulaLink.frame.size.width/2.f);
    privacyFrame.origin.y = roundf(eulaFrame.origin.y + self.pEulaLink.frame.size.height + 16.f);
    self.pPrivacyLink.frame = privacyFrame;
    
    CGRect contentRect = CGRectZero;
    for (UIView *view in self.self.pLabelsContainer.subviews) {
        contentRect = CGRectUnion(contentRect, view.frame);
    }
    
    contentRect.size.width = std::max(self.pTextContent.frame.size.width, self.pLogoImage.frame.size.width);
    self.pLabelsContainer.contentSize = contentRect.size;
    
    self.pLabelsContainer.userInteractionEnabled = YES;
    
}

- (ExampleApp::AboutPage::View::AboutPageViewInterop*)getInterop
{
    return m_pInterop;
}

- (void) setContent:(const std::string*)content
{
    self.pTextContent.text = [NSString stringWithUTF8String:content->c_str()];
    [self setNeedsLayout];
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

- (void) privacyClickHandler:(UITapGestureRecognizer *)recognizer
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.eegeo.com/privacy/"]];
}

- (void) eulaClickHandler:(UITapGestureRecognizer *)recognizer
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.eegeo.com/tos/"]];
}

@end
