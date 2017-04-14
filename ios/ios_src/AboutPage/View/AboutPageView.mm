// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "AboutPageViewInterop.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"

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
        [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pCloseButton addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
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
        [self.pLabelsContainer addSubview: self.pDevelopedByLabel];

        self.pLogoImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLogoImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage(@"eegeo_logo_about");
        [self.pLabelsContainer addSubview: self.pLogoImage];
        
        self.pLogoButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UILongPressGestureRecognizer *longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(showHiddenText:)];
        [self.pLogoButton addGestureRecognizer:longPress];
        [longPress autorelease];
        [self.pLabelsContainer addSubview: self.pLogoButton];

        self.pTextContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTextContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
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
        
        UITapGestureRecognizer* pLegalTapHandler = [[[UITapGestureRecognizer alloc]
                                                    initWithTarget:self
                                                    action:@selector(legalClickHandler:)] autorelease];
        self.pLegalLink = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLegalLink.textColor = ExampleApp::Helpers::ColorPalette::UiTextLinkColor;
        [self.pLegalLink addGestureRecognizer: pLegalTapHandler];
        [self.pLabelsContainer addSubview: self.pLegalLink];
        
        UITapGestureRecognizer* pTeamTapHandler = [[[UITapGestureRecognizer alloc]
                                                     initWithTarget:self
                                                     action:@selector(teamClickHandler:)] autorelease];
        self.pTeamLink = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTeamLink.textColor = ExampleApp::Helpers::ColorPalette::UiTextLinkColor;
        [self.pTeamLink addGestureRecognizer: pTeamTapHandler];
        [self.pLabelsContainer addSubview: self.pTeamLink];
    }

    return self;
}

- (void)dealloc
{
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
    
    [self.pLogoButton removeFromSuperview];
    [self.pLogoButton release];

    [self.pLogoImage removeFromSuperview];
    [self.pLogoImage release];

    [self.pTextContent removeFromSuperview];
    [self.pTextContent release];
    
    [self.pPrivacyLink removeFromSuperview];
    [self.pPrivacyLink release];
    
    [self.pEulaLink removeFromSuperview];
    [self.pEulaLink release];
    
    [self.pLegalLink removeFromSuperview];
    [self.pLegalLink release];
    
    [self.pTeamLink removeFromSuperview];
    [self.pTeamLink release];

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

    const float closeButtonSectionHeight = 64.f;
    const float headlineOffsetY = 10.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + 0.f);
   
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                    headlineOffsetY,
                                    mainWindowWidth,
                                    0.f);

    self.pContentContainer.frame = CGRectMake(0.f,
                                   0.f,
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


    const float textWidth = static_cast<float>(self.pLabelsContainer.frame.size.width) * 0.8f;
    const float textContentX = ((static_cast<float>(self.pLabelsContainer.frame.size.width) / 2) - (textWidth / 2));
    const float developedByY = 50.f;
    const float developedByHeight = 16.f;
    const float developedByTopPadding = 45.f;

    self.pDevelopedByLabel.font = [UIFont systemFontOfSize:14.f];
    self.pDevelopedByLabel.text = @"Developed by";
    self.pDevelopedByLabel.frame = CGRectMake(textContentX, developedByY, textWidth, developedByHeight);

    const float logoWidth = self.pLogoImage.image.size.width;
    const float logoHeight = self.pLogoImage.image.size.height;
    const float logoY = developedByY + developedByHeight + developedByTopPadding;
    const float logoX = self.pTextContent.frame.origin.x;

    self.pLogoImage.frame = CGRectMake(logoX, logoY, logoWidth, logoHeight);
    self.pLogoButton.frame = CGRectMake(logoX, logoY, logoWidth, logoHeight);

    const float textContentY = logoY + logoHeight;
    self.pTextContent.frame = CGRectMake(textContentX, textContentY + self.pLegalLink.frame.size.height, textWidth, contentSectionHeight - 300.f);
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
    eulaFrame.origin.x = self.pTextContent.frame.origin.x;
    eulaFrame.origin.y = roundf(textContentY + self.pTextContent.frame.size.height + 16.f);
    self.pEulaLink.frame = eulaFrame;
    
    self.pPrivacyLink.text = @"Privacy Policy";
    self.pPrivacyLink.font = [UIFont systemFontOfSize:14.f];
    [self.pPrivacyLink sizeToFit];
    self.pPrivacyLink.userInteractionEnabled = YES;
    CGRect privacyFrame = self.pPrivacyLink.frame;
    privacyFrame.origin.x = self.pTextContent.frame.origin.x;
    privacyFrame.origin.y = roundf(eulaFrame.origin.y + self.pEulaLink.frame.size.height + 16.f);
    self.pPrivacyLink.frame = privacyFrame;
    
    self.pLegalLink.text = @"Legal";
    self.pLegalLink.font = [UIFont systemFontOfSize:14.f];
    [self.pLegalLink sizeToFit];
    self.pLegalLink.userInteractionEnabled = YES;
    CGRect legalFrame = self.pLegalLink.frame;
    legalFrame.origin.x = self.pTextContent.frame.origin.x;
    legalFrame.origin.y = roundf(privacyFrame.origin.y + self.pPrivacyLink.frame.size.height + 16.f);
    self.pLegalLink.frame = legalFrame;
    
    self.pTeamLink.text = @"Team";
    self.pTeamLink.font = [UIFont systemFontOfSize:14.f];
    [self.pTeamLink sizeToFit];
    self.pTeamLink.userInteractionEnabled = YES;
    CGRect teamFrame = self.pTeamLink.frame;
    teamFrame.origin.x = roundf(self.pLabelsContainer.frame.size.width/2.f - self.pTeamLink.frame.size.width/2.f);
    teamFrame.origin.x = self.pTextContent.frame.origin.x;
    teamFrame.origin.y = roundf(legalFrame.origin.y + self.pLegalLink.frame.size.height + 16.f);
    self.pTeamLink.frame = teamFrame;
    
    CGRect contentRect = CGRectZero;
    for (UIView *view in self.self.pLabelsContainer.subviews)
    {
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
    }
     completion:^(BOOL finished) {
         // Stop scrolling
         CGPoint offset = self.pLabelsContainer.contentOffset;
         [self.pLabelsContainer setContentOffset:offset animated:NO];
     }];
}

- (void)onCloseButtonTapped
{
    m_pInterop->CloseTapped();
}

- (void)showHiddenText:(UILongPressGestureRecognizer*)gesture
{
    if ( gesture.state == UIGestureRecognizerStateEnded )
    {
        m_pInterop->ShowHiddenText();
    }
}

- (void) privacyClickHandler:(UITapGestureRecognizer *)recognizer
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/privacy/"]];
}

- (void) eulaClickHandler:(UITapGestureRecognizer *)recognizer
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/tos/"]];
}

- (void) legalClickHandler:(UITapGestureRecognizer *)recognizer
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/legal/"]];
}

- (void) teamClickHandler:(UITapGestureRecognizer *)recognizer
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/team/"]];
}

@end
