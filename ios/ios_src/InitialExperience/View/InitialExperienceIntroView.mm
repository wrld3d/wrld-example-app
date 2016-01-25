// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroViewInterop.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "UIHelpers.h"

@implementation InitialExperienceIntroView

const float arrowWidth = 10;

- (id) initView: (InitialExperienceIntroBackgroundView*)pBackground;
{
    self = [super init];
    
    if(self)
    {
        m_animationTimeSeconds = 0.9f;
        
        m_pInterop = Eegeo_NEW(ExampleApp::InitialExperience::View::InitialExperienceIntroViewInterop)(self, pBackground);
        
        self.pBackgroundContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pBackgroundContainer];
        
        self.pBannerBarContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pBannerBarContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pBannerBarContainer];
        
        self.pWelcomeImage = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 320.0f, 90.0f)] autorelease];
        self.pWelcomeImage.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"banner_logo")];
        [self.pBannerBarContainer addSubview:self.pWelcomeImage];
        
        self.pSettingsMenuDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pSettingsMenuDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pSettingsMenuDialogContainer];
        self.pSettingsMenuDialogArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pSettingsMenuDialogContainer, "arrow3_up", 0.f, 0.f, 0, 0);
        self.pSettingsMenuDialogTitle = [self createDialogTitle:@"Settings"];
        [self.pSettingsMenuDialogContainer addSubview:self.pSettingsMenuDialogTitle];
        self.pSettingsMenuDialogDescription = [self createDialogDescription:@"Change your settings here"];
        [self.pSettingsMenuDialogContainer addSubview:self.pSettingsMenuDialogDescription];
        
        self.pSearchMenuDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pSearchMenuDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pSearchMenuDialogContainer];
        self.pSearchMenuDialogArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pSearchMenuDialogContainer, "arrow3_up", 0.f, 0.f, 0, 0);
        self.pSearchMenuDialogTitle = [self createDialogTitle:@"Search Menu"];
        [self.pSearchMenuDialogContainer addSubview:self.pSearchMenuDialogTitle];
        self.pSearchMenuDialogDescription = [self createDialogDescription:@"Start exploring here"];
        [self.pSearchMenuDialogContainer addSubview:self.pSearchMenuDialogDescription];
        
        self.pCompassDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pCompassDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pCompassDialogContainer];
        self.pCompassDialogArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCompassDialogContainer, "arrow3_down", 0.f, 0.f, 0, 0);
        self.pCompassDialogTitle = [self createDialogTitle:@"Compass"];
        [self.pCompassDialogContainer addSubview:self.pCompassDialogTitle];
        self.pCompassDialogDescription = [self createDialogDescription:@"Find me\nLock rotation"];
        [self.pCompassDialogContainer addSubview:self.pCompassDialogDescription];
        
        self.pMapModeDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pMapModeDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pMapModeDialogContainer];
        self.pMapModeDialogArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pMapModeDialogContainer, "arrow3_down", 0.f, 0.f, 0, 0);
        self.pMapModeDialogTitle = [self createDialogTitle:@"Map Mode"];
        [self.pMapModeDialogContainer addSubview:self.pMapModeDialogTitle];
        self.pMapModeDialogDescription = [self createDialogDescription:@"Simple 2D View"];
        [self.pMapModeDialogContainer addSubview:self.pMapModeDialogDescription];
        
        self.pPinCreationDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pPinCreationDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pPinCreationDialogContainer];
        self.pPinCreationDialogArrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pPinCreationDialogContainer, "arrow3_down", 0.f, 0.f, 0, 0);
        self.pPinCreationDialogTitle = [self createDialogTitle:@"My Pin"];
        [self.pPinCreationDialogContainer addSubview:self.pPinCreationDialogTitle];
        self.pPinCreationDialogDescription = [self createDialogDescription:@"Create your own pins"];
        [self.pPinCreationDialogContainer addSubview:self.pPinCreationDialogDescription];
        
        m_awaitingInput = false;
        
        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self addGestureRecognizer:m_tapGestureRecogniser];
        
        [self setHidden:YES];
    }
    
    return self;
}

- (UILabel*)createDialogTitle: (NSString*)text
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    UILabel* pLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    pLabel.text = text;
    pLabel.font = useSmallScreen ? [UIFont systemFontOfSize:14.5f] : [UIFont systemFontOfSize:18.0f];
    return pLabel;
}

- (UITextView*)createDialogDescription: (NSString*)text
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    UITextView* pTextView = [[[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pTextView.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
    pTextView.editable = NO;
    pTextView.scrollEnabled = NO;
    pTextView.font = useSmallScreen ? [UIFont systemFontOfSize:13.0f] : [UIFont systemFontOfSize:16.0f];
    pTextView.textContainer.lineFragmentPadding = 0;
    pTextView.textContainerInset = UIEdgeInsetsZero;
    pTextView.text = text;
    return pTextView;
}

- (void)dealloc
{
    [m_tapGestureRecogniser release];
    
    Eegeo_DELETE m_pInterop;
    
    [self.pPinCreationDialogDescription removeFromSuperview];
    [self.pPinCreationDialogDescription release];
    [self.pPinCreationDialogTitle removeFromSuperview];
    [self.pPinCreationDialogTitle release];
    [self.pPinCreationDialogArrow removeFromSuperview];
    [self.pPinCreationDialogArrow release];
    [self.pPinCreationDialogContainer removeFromSuperview];
    [self.pPinCreationDialogContainer release];

    [self.pCompassDialogDescription removeFromSuperview];
    [self.pCompassDialogDescription release];
    [self.pCompassDialogTitle removeFromSuperview];
    [self.pCompassDialogTitle release];
    [self.pCompassDialogArrow removeFromSuperview];
    [self.pCompassDialogArrow release];
    [self.pCompassDialogContainer removeFromSuperview];
    [self.pCompassDialogContainer release];
    
    [self.pMapModeDialogDescription removeFromSuperview];
    [self.pMapModeDialogDescription release];
    [self.pMapModeDialogTitle removeFromSuperview];
    [self.pMapModeDialogTitle release];
    [self.pMapModeDialogArrow removeFromSuperview];
    [self.pMapModeDialogArrow release];
    [self.pMapModeDialogContainer removeFromSuperview];
    [self.pMapModeDialogContainer release];
    
    [self.pSettingsMenuDialogDescription removeFromSuperview];
    [self.pSettingsMenuDialogDescription release];
    [self.pSettingsMenuDialogTitle removeFromSuperview];
    [self.pSettingsMenuDialogTitle release];
    [self.pSettingsMenuDialogArrow removeFromSuperview];
    [self.pSettingsMenuDialogArrow release];
    [self.pSettingsMenuDialogContainer removeFromSuperview];
    [self.pSettingsMenuDialogContainer release];
    
    [self.pSearchMenuDialogDescription removeFromSuperview];
    [self.pSearchMenuDialogDescription release];
    [self.pSearchMenuDialogTitle removeFromSuperview];
    [self.pSearchMenuDialogTitle release];
    [self.pSearchMenuDialogArrow removeFromSuperview];
    [self.pSearchMenuDialogArrow release];
    [self.pSearchMenuDialogContainer removeFromSuperview];
    [self.pSearchMenuDialogContainer release];

    [self.pWelcomeImage removeFromSuperview];
    [self.pWelcomeImage release];
    
    [self.pBannerBarContainer removeFromSuperview];
    [self.pBannerBarContainer release];
    
    [self.pBackgroundContainer removeFromSuperview];
    [self.pBackgroundContainer release];
    
    [super removeFromSuperview];
    [super dealloc];
}

- (ExampleApp::InitialExperience::View::InitialExperienceIntroViewInterop*) getInterop
{
    return m_pInterop;
}

- (void) layoutSubviews
{
    m_screenWidth = self.superview.bounds.size.width;
    m_screenHeight = self.superview.bounds.size.height;
    [self setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];
    [self.pBackgroundContainer setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];
    
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const int dialogWidth = useSmallScreen ? 100 : 120;
    const int dialogHeight = useSmallScreen ? 64 : 97;
    const int arrowLength = useSmallScreen ? 20 : 30;
    const int dialogMargin = 50;
    const int dialogSpacing = useSmallScreen ? 10 : 20;
    const int textPadding = 5;
    const int menuDialogOffsetX = 28;
    const int upperMargin = (useSmallScreen ? 20 : 50);
    
    const int bannerHeight = 90;
    
    const float leftDialogArrowOffset = useSmallScreen ? 0.8f : 0.9f;
    const float rightDialogArrowOffset = useSmallScreen ? 0.2f : 0.1f;
    
    int bannerYOffset = (int)(m_screenHeight/2 - bannerHeight/2);
    [self.pBannerBarContainer setFrame:CGRectMake(0, bannerYOffset, m_screenWidth, bannerHeight)];
    
    [self.pWelcomeImage setCenter:CGPointMake(m_screenWidth/2, bannerHeight/2)];
    
    [self.pSettingsMenuDialogContainer setFrame:CGRectMake(m_screenWidth - (menuDialogOffsetX + dialogWidth),
                                                   upperMargin + dialogMargin + arrowLength + dialogSpacing,
                                                   dialogWidth,
                                                   dialogHeight)];
    [self.pSettingsMenuDialogArrow setFrame:CGRectMake(dialogWidth * 0.75f, -arrowLength, arrowWidth, arrowLength)];
    
    [self.pSearchMenuDialogContainer setFrame:CGRectMake(menuDialogOffsetX,
                                                   upperMargin + dialogMargin + arrowLength + dialogSpacing,
                                                   dialogWidth,
                                                   dialogHeight)];
    [self.pSearchMenuDialogArrow setFrame:CGRectMake(dialogWidth * 0.25f, -arrowLength, arrowWidth, arrowLength)];
    
    
    int centerDialogPositionX = (int)(m_screenWidth/2 - dialogWidth/2);
    int centerDialogPositionY = (int)(m_screenHeight - (dialogHeight + arrowLength + dialogMargin*2));
    [self.pCompassDialogContainer setFrame:CGRectMake(centerDialogPositionX,
                                                      centerDialogPositionY,
                                                      dialogWidth,
                                                      dialogHeight)];
    [self.pCompassDialogArrow setFrame:CGRectMake(dialogWidth/2 - arrowWidth/2, dialogHeight, arrowWidth, arrowLength)];
    
    [self.pMapModeDialogContainer setFrame:CGRectMake(centerDialogPositionX - (dialogSpacing + dialogWidth),
                                                      centerDialogPositionY + dialogSpacing,
                                                      dialogWidth,
                                                      dialogHeight)];
    [self.pMapModeDialogArrow setFrame:CGRectMake(dialogWidth*leftDialogArrowOffset - arrowWidth/2, dialogHeight, arrowWidth, arrowLength)];
    
    [self.pPinCreationDialogContainer setFrame:CGRectMake(centerDialogPositionX + (dialogSpacing + dialogWidth),
                                                          centerDialogPositionY + dialogSpacing,
                                                          dialogWidth,
                                                          dialogHeight)];
    [self.pPinCreationDialogArrow setFrame:CGRectMake(dialogWidth*rightDialogArrowOffset - arrowWidth/2, dialogHeight, arrowWidth, arrowLength)];
    
    [self.pSettingsMenuDialogTitle setFrame:CGRectMake(textPadding, textPadding, dialogWidth-(2*textPadding), 18.0f )];
    [self.pSettingsMenuDialogDescription setFrame:CGRectMake(textPadding, 18.0f + textPadding, dialogWidth-(2*textPadding), dialogHeight-18.0f -2*textPadding)];
    [self.pSearchMenuDialogTitle setFrame:CGRectMake(textPadding, textPadding, dialogWidth-(2*textPadding), 18.0f )];
    [self.pSearchMenuDialogDescription setFrame:CGRectMake(textPadding, 18.0f + textPadding, dialogWidth-(2*textPadding), dialogHeight-18.0f -2*textPadding)];
    [self.pCompassDialogTitle setFrame:CGRectMake(textPadding, textPadding, dialogWidth-(2*textPadding), 18.0f )];
    [self.pCompassDialogDescription setFrame:CGRectMake(textPadding, 18.0f + textPadding, dialogWidth-(2*textPadding), dialogHeight-18.0f -2*textPadding)];
    [self.pMapModeDialogTitle setFrame:CGRectMake(textPadding, textPadding, dialogWidth-(2*textPadding), 18.0f )];
    [self.pMapModeDialogDescription setFrame:CGRectMake(textPadding, 18.0f + textPadding, dialogWidth-(2*textPadding), dialogHeight-18.0f -2*textPadding)];
    [self.pPinCreationDialogTitle setFrame:CGRectMake(textPadding, textPadding, dialogWidth-(2*textPadding), 18.0f )];
    [self.pPinCreationDialogDescription setFrame:CGRectMake(textPadding, 18.0f + textPadding, dialogWidth-(2*textPadding), dialogHeight-18.0f -2*textPadding)];
}

- (BOOL) consumesTouch:(UITouch *)touch
{
    return m_awaitingInput;
}

- (void) show
{
    [self setHidden:NO];
    
    m_awaitingInput = true;
    
    [self.pBannerBarContainer setCenter:CGPointMake(m_screenWidth/2 - m_screenWidth, m_screenHeight/2)];
    self.pSettingsMenuDialogContainer.alpha = 0.0f;
    self.pSearchMenuDialogContainer.alpha = 0.0f;
    self.pCompassDialogContainer.alpha = 0.0f;
    self.pMapModeDialogContainer.alpha = 0.0f;
    self.pPinCreationDialogContainer.alpha = 0.0f;
    
    [UIView animateWithDuration:m_animationTimeSeconds
                          delay:0.0
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         [self.pBannerBarContainer setCenter:CGPointMake(m_screenWidth/2, m_screenHeight/2)];
                     }
                     completion:nil];

    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 1
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pSettingsMenuDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 2
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pSearchMenuDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 3
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pMapModeDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 4
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pCompassDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 5
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pPinCreationDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];

    
    [self setNeedsLayout];
    [self layoutIfNeeded];

}

- (void) dismiss
{
    m_awaitingInput = false;
    
    [self.pBannerBarContainer setCenter:CGPointMake(m_screenWidth/2, m_screenHeight/2)];
    self.pSettingsMenuDialogContainer.alpha = 1.0f;
    self.pSearchMenuDialogContainer.alpha = 1.0f;
    self.pCompassDialogContainer.alpha = 1.0f;
    self.pMapModeDialogContainer.alpha = 1.0f;
    self.pPinCreationDialogContainer.alpha = 1.0f;
    
    [UIView animateWithDuration:m_animationTimeSeconds
                          delay:0.0
                        options:UIViewAnimationOptionCurveEaseIn
                     animations:^{
                         [self.pBannerBarContainer setCenter:CGPointMake(m_screenWidth/2 + m_screenWidth, m_screenHeight/2)];
                     }
                     completion:^(BOOL finished){
                         if(finished)
                         {
                             [self setHidden:YES];
                             [self setNeedsLayout];
                             [self layoutIfNeeded];
                         }
                     }];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 1
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pSettingsMenuDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 2
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pSearchMenuDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 3
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pMapModeDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 4
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pCompassDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:m_animationTimeSeconds/6
                          delay:m_animationTimeSeconds/6 * 5
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pPinCreationDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    if(m_awaitingInput)
    {
        m_pInterop->OnDismiss();
    }
}

@end