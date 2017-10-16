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

        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];

        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];

        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pContentContainer];

        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentContainer addSubview: self.pLabelsContainer];

        self.pSwallowLogoImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pSwallowLogoImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage(@"swallow_logo_about");
        [self.pLabelsContainer addSubview: self.pSwallowLogoImage];

        self.pTextContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTextContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pLabelsContainer addSubview: self.pTextContent];

        self.pSeperator = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pSeperator.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview: self.pSeperator];

        self.pDevelopedByLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDevelopedByLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pLabelsContainer addSubview: self.pDevelopedByLabel];

        self.pWrldLogoImage = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pWrldLogoImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage(@"wrld_logo_about");
        [self.pLabelsContainer addSubview: self.pWrldLogoImage];

        self.pWrldLogoButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        UILongPressGestureRecognizer *longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(showHiddenText:)];
        [self.pWrldLogoButton addGestureRecognizer:longPress];
        [longPress autorelease];
        [self.pLabelsContainer addSubview: self.pWrldLogoButton];

        self.pLegalLink = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLegalLink.textColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        UITapGestureRecognizer* pLegalTapHandler = [[[UITapGestureRecognizer alloc]
                                                     initWithTarget:self
                                                     action:@selector(legalClickHandler:)] autorelease];
        [self.pLabelsContainer addSubview: self.pLegalLink];
        [self.pLegalLink addGestureRecognizer: pLegalTapHandler];
    }

    return self;
}

- (void)dealloc
{
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];

    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];

    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];

    [self.pHeadlineContainer removeFromSuperview];
    [self.pHeadlineContainer release];

    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];

    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];

    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];

    [self.pSwallowLogoImage removeFromSuperview];
    [self.pSwallowLogoImage release];

    [self.pTextContent removeFromSuperview];
    [self.pTextContent release];

    [self.pSeperator removeFromSuperview];
    [self.pSeperator release];

    [self.pDevelopedByLabel removeFromSuperview];
    [self.pDevelopedByLabel release];

    [self.pWrldLogoImage removeFromSuperview];
    [self.pWrldLogoImage release];

    [self.pWrldLogoButton removeFromSuperview];
    [self.pWrldLogoButton release];

    [self.pLegalLink removeFromSuperview];
    [self.pLegalLink release];

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

    const float separatorSize = 15.f;

    const float closeButtonSectionHeight = 64.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float headlineOffsetY = 2.f * separatorSize;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + 0.f);

    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                               headlineOffsetY,
                                               mainWindowWidth,
                                               0.f);

    self.pContentContainer.frame = CGRectMake(0.f,
                                              0.f,
                                              mainWindowWidth,
                                              contentSectionHeight);

    const float labelsContainerOffsetX = 2.f * separatorSize;
    const float labelsContainerWidth = mainWindowWidth - (2.f * labelsContainerOffsetX);

    self.pLabelsContainer.frame = CGRectMake(labelsContainerOffsetX,
                                             0.f,
                                             labelsContainerWidth,
                                             contentSectionHeight);

    const float currentLabelsContainerWidth = static_cast<float>(self.pLabelsContainer.frame.size.width);

    self.pCloseButtonContainer.frame = CGRectMake(0.f,
                                                  closeButtonSectionOffsetY,
                                                  mainWindowWidth,
                                                  closeButtonSectionHeight);

    self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight,
                                         0.f,
                                         closeButtonSectionHeight,
                                         closeButtonSectionHeight);


    const float swallowLogoX = 0.f;
    const float swallowLogoY = 2.f * separatorSize;
    const float swallowLogoWidth = self.pSwallowLogoImage.image.size.width;
    const float swallowLogoHeight = self.pSwallowLogoImage.image.size.height;

    self.pSwallowLogoImage.frame = CGRectMake(swallowLogoX, swallowLogoY, swallowLogoWidth, swallowLogoHeight);


    const float textContentX = 0.f;
    const float textContentY = swallowLogoY + swallowLogoHeight + separatorSize;
    const float textWidth = currentLabelsContainerWidth;
    const float textContentHeight = 0.f;

    self.pTextContent.frame = CGRectMake(textContentX, textContentY, textWidth, textContentHeight);
    self.pTextContent.numberOfLines = 0;
    self.pTextContent.adjustsFontSizeToFitWidth = NO;
    self.pTextContent.font = [UIFont systemFontOfSize:14.5f];
    self.pTextContent.lineBreakMode = NSLineBreakByWordWrapping;
    [self.pTextContent sizeToFit];


    const float seperatorX = 0.f;
    const float seperatorY = textContentY + self.pTextContent.frame.size.height + separatorSize * 2.f;
    const float seperatorWidth = currentLabelsContainerWidth;
    const float seperatorHeight = 1.f;

    self.pSeperator.frame = CGRectMake(seperatorX, seperatorY, seperatorWidth, seperatorHeight);


    const float developedByX = 0.f;
    const float developedByY = seperatorY + seperatorHeight + separatorSize * 2.f;
    const float developedByWidth = currentLabelsContainerWidth;
    const float developedByHeight = 16.f;

    self.pDevelopedByLabel.font = [UIFont systemFontOfSize:16.f];
    self.pDevelopedByLabel.text = @"Developed by Bloomberg L.P and";
    self.pDevelopedByLabel.frame = CGRectMake(developedByX, developedByY, developedByWidth, developedByHeight);
    [self.pDevelopedByLabel sizeToFit];


    const float wrldLogoWidth = self.pWrldLogoImage.image.size.width;
    const float wrldLogoHeight = self.pWrldLogoImage.image.size.height;
    const float wrldLogoX = 0.f;
    const float wrldLogoY = developedByY + wrldLogoHeight;

    self.pWrldLogoImage.frame = CGRectMake(wrldLogoX, wrldLogoY, wrldLogoWidth, wrldLogoHeight);
    self.pWrldLogoButton.frame = CGRectMake(wrldLogoX, wrldLogoY, wrldLogoWidth, wrldLogoHeight);


    const float legalLinkX = 0.f;
    const float legalLinkY = wrldLogoY + wrldLogoHeight * 2.f;
    const float legalLinkWidth = currentLabelsContainerWidth;
    const float legalLinkHeight = 0.f;

    self.pLegalLink.frame = CGRectMake(legalLinkX, legalLinkY, legalLinkWidth, legalLinkHeight);
    self.pLegalLink.userInteractionEnabled = YES;
    self.pLegalLink.text = @"Legal";
    self.pLegalLink.font = [UIFont boldSystemFontOfSize:16.f];
    [self.pLegalLink sizeToFit];


    CGRect contentRect = CGRectZero;
    for (UIView *view in self.self.pLabelsContainer.subviews)
    {
        contentRect = CGRectUnion(contentRect, view.frame);
    }
    contentRect.size.width = std::max(self.pTextContent.frame.size.width, self.pWrldLogoImage.frame.size.width);
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

- (void) legalClickHandler:(UITapGestureRecognizer *)recognizer
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/legal/"]];
}
@end
