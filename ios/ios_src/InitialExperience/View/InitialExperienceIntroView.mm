// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroViewInterop.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "UIHelpers.h"

@implementation InitialExperienceIntroView

namespace
{
    namespace AlignHorizontal
    {
        enum AlignHorizontal
        {
            Left,
            Right,
            Centre
        };
    }
    
    namespace AlignVertical
    {
        enum AlignVertical
        {
            Top,
            Bottom,
            Centre
        };
    }
    
    namespace ArrowEdge
    {
        enum ArrowEdge
        {
            Left,
            Right,
            Top,
            Bottom
        };
    }
}

- (id) initView: (InitialExperienceIntroBackgroundView*)pBackground screenProperties:(const Eegeo::Rendering::ScreenProperties&)screenProperties;
{
    self = [super init];
    
    if(self)
    {
        const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
        
        m_animationTimeSeconds = 0.9f;
        
        m_pInterop = Eegeo_NEW(ExampleApp::InitialExperience::View::InitialExperienceIntroViewInterop)(self, pBackground);
        
        self.pBackgroundContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pBackgroundContainer];
        
        self.pBannerBarContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pBannerBarContainer];
        
        self.pBannerBarOutline = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pBannerBarOutline.backgroundColor = ExampleApp::Helpers::ColorPalette::White;
        self.pBannerBarOutline.alpha = 1.f;
        [self.pBannerBarContainer addSubview: self.pBannerBarOutline];
        
        self.pBannerBarBackground = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pBannerBarBackground.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pBannerBarContainer addSubview: self.pBannerBarBackground];
        
        self.pWelcomeText = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pWelcomeText.textColor = ExampleApp::Helpers::ColorPalette::White;
        self.pWelcomeText.text = @"Welcome";
        const float iPhone7PlusPixelScale = 2.60869575f;
        m_pixelScale = useSmallScreen ? iPhone7PlusPixelScale / screenProperties.GetPixelScale() : 1.0f;
        [self.pWelcomeText setFont:[UIFont fontWithName:@"HelveticaNeue-Thin" size:useSmallScreen ? 45.f/m_pixelScale : 58.0f/m_pixelScale]];
        [self.pBannerBarContainer addSubview:self.pWelcomeText];
        
        self.pWelcomeDescription = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pWelcomeDescription.textColor = ExampleApp::Helpers::ColorPalette::White;
        self.pWelcomeDescription.text = @"Design your maps at wrld3d.com";
        [self.pWelcomeDescription setFont:[UIFont fontWithName:@"Helvetica Neue" size:useSmallScreen ? 22.f/m_pixelScale : 30.0f/m_pixelScale]];
        [self.pBannerBarContainer addSubview:self.pWelcomeDescription];
        
        self.pSearchMenuDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pSearchMenuDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pSearchMenuDialogContainer];
        self.pSearchMenuDialogContent = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pSearchMenuDialogContent.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pSearchMenuDialogContainer addSubview:self.pSearchMenuDialogContent];
        self.pSearchMenuDialogArrowOutline = [self createDialogArrowOutline: self.pSearchMenuDialogContent arrowEdge: useSmallScreen ? ArrowEdge::Top : ArrowEdge::Left];
        self.pSearchMenuDialogArrow = [self createDialogArrow: self.pSearchMenuDialogContent arrowEdge: useSmallScreen ? ArrowEdge::Top : ArrowEdge::Left];
        self.pSearchMenuDialogIcon = [self createDialogIcon:self.pSearchMenuDialogContent];
        self.pSearchMenuDialogTitle = [self createDialogTitle:@"Search"];
        [self.pSearchMenuDialogContent addSubview:self.pSearchMenuDialogTitle];
        self.pSearchMenuDialogDescription = [self createDialogDescription:@"Find places fast or just\nstart exploring."];
        [self.pSearchMenuDialogContent addSubview:self.pSearchMenuDialogDescription];
        
        self.pCompassDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pCompassDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pCompassDialogContainer];
        self.pCompassDialogContent = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pCompassDialogContent.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pCompassDialogContainer addSubview:self.pCompassDialogContent];
        self.pCompassDialogArrowOutline = [self createDialogArrowOutline: self.pCompassDialogContent arrowEdge: ArrowEdge::Bottom];
        self.pCompassDialogArrow = [self createDialogArrow: self.pCompassDialogContent arrowEdge: ArrowEdge::Bottom];
        self.pCompassDialogIcon = [self createDialogIcon:self.pCompassDialogContent];
        self.pCompassDialogTitle = [self createDialogTitle:@"Compass"];
        [self.pCompassDialogContent addSubview:self.pCompassDialogTitle];
        self.pCompassDialogDescription = [self createDialogDescription:useSmallScreen ? @"Locate me.\nLock rotation\nto compass." : @"Locate me.\nLock rotation to compass."];
        [self.pCompassDialogContent addSubview:self.pCompassDialogDescription];
        
        self.pMapModeDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pMapModeDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pMapModeDialogContainer];
        self.pMapModeDialogContent = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pMapModeDialogContent.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pMapModeDialogContainer addSubview:self.pMapModeDialogContent];
        self.pMapModeDialogArrowOutline = [self createDialogArrowOutline: self.pMapModeDialogContent arrowEdge: useSmallScreen ? ArrowEdge::Bottom : ArrowEdge::Right];
        self.pMapModeDialogArrow = [self createDialogArrow: self.pMapModeDialogContent arrowEdge: useSmallScreen ? ArrowEdge::Bottom : ArrowEdge::Right];
        self.pMapModeDialogIcon = [self createDialogIcon:self.pMapModeDialogContent];
        self.pMapModeDialogTitle = [self createDialogTitle:@"Map Mode"];
        [self.pMapModeDialogContent addSubview:self.pMapModeDialogTitle];
        self.pMapModeDialogDescription = [self createDialogDescription:@"Simple 2D View."];
        [self.pMapModeDialogContent addSubview:self.pMapModeDialogDescription];
        
        self.pPinCreationDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pPinCreationDialogContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self addSubview: self.pPinCreationDialogContainer];
        self.pPinCreationDialogContent = [[[UIView alloc] initWithFrame:CGRectMake(0.f, 0.f, 0.f, 0.f)] autorelease];
        self.pPinCreationDialogContent.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pPinCreationDialogContainer addSubview:self.pPinCreationDialogContent];
        self.pPinCreationDialogArrowOutline = [self createDialogArrowOutline: self.pPinCreationDialogContent arrowEdge: useSmallScreen ? ArrowEdge::Bottom : ArrowEdge::Left];
        self.pPinCreationDialogArrow = [self createDialogArrow: self.pPinCreationDialogContent arrowEdge: useSmallScreen ? ArrowEdge::Bottom : ArrowEdge::Left];
        self.pPinCreationDialogIcon = [self createDialogIcon:self.pPinCreationDialogContent];
        self.pPinCreationDialogTitle = [self createDialogTitle:@"Drop Pin"];
        [self.pPinCreationDialogContent addSubview:self.pPinCreationDialogTitle];
        self.pPinCreationDialogDescription = [self createDialogDescription:useSmallScreen
                                              ? @"Drop a pin on map\nto bookmark a place."
                                              : @"Drop a pin to bookmark\na place on the map."];
        [self.pPinCreationDialogContent addSubview:self.pPinCreationDialogDescription];
        
        m_awaitingInput = false;
        
        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self addGestureRecognizer:m_tapGestureRecogniser];
        
        [self setHidden:YES];
    }
    
    return self;
}

-(UIView*)createDialogArrowOutline: (UIView*) parent
                         arrowEdge: (ArrowEdge::ArrowEdge) arrowEdge
{
    std::string arrowImageFilename;
    switch(arrowEdge)
    {
        case ArrowEdge::Left: arrowImageFilename = "arrow3_left_blue"; break;
        case ArrowEdge::Right: arrowImageFilename = "arrow3_right_blue"; break;
        case ArrowEdge::Top: arrowImageFilename = "arrow3_up_blue"; break;
        case ArrowEdge::Bottom: arrowImageFilename = "arrow3_down_blue"; break;
    }
    
    UIView* arrowOutline = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(parent, arrowImageFilename, 0.f, 0.f, 0, 0);
    return arrowOutline;
}

-(UIView*)createDialogArrow: (UIView*) parent
                  arrowEdge: (ArrowEdge::ArrowEdge) arrowEdge
{
    std::string arrowImageFilename;
    switch(arrowEdge)
    {
        case ArrowEdge::Left: arrowImageFilename = "arrow3_left"; break;
        case ArrowEdge::Right: arrowImageFilename = "arrow3_right"; break;
        case ArrowEdge::Top: arrowImageFilename = "arrow3_up"; break;
        case ArrowEdge::Bottom: arrowImageFilename = "arrow3_down"; break;
    }
    
    UIView* arrow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(parent, arrowImageFilename, 0.f, 0.f, 0, 0);
    return arrow;
}

-(UIView*)createDialogIcon: (UIView*) parent
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    std::string dialogIconFilename = useSmallScreen ? "Alert_Tutorial_icon_phone" : "Alert_Tutorial_icon";
    UIView* icon = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(parent, dialogIconFilename, 0.f, 0.f, 0, 0);
    return icon;
}

- (UILabel*)createDialogTitle: (NSString*)text
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    UILabel* pLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    pLabel.text = text;
    pLabel.font = useSmallScreen ? [UIFont systemFontOfSize:10.5f] : [UIFont systemFontOfSize:18.0f];
    return pLabel;
}

- (UITextView*)createDialogDescription: (NSString*)text
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    UITextView* pTextView = [[[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pTextView.textColor = ExampleApp::Helpers::ColorPalette::Black;
    pTextView.editable = NO;
    pTextView.scrollEnabled = NO;
    pTextView.font = useSmallScreen ? [UIFont systemFontOfSize:9.0f] : [UIFont systemFontOfSize:16.0f];
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
    [self.pPinCreationDialogArrowOutline removeFromSuperview];
    [self.pPinCreationDialogArrowOutline release];
    [self.pPinCreationDialogIcon removeFromSuperview];
    [self.pPinCreationDialogIcon release];
    [self.pPinCreationDialogContent removeFromSuperview];
    [self.pPinCreationDialogContent release];
    [self.pPinCreationDialogContainer removeFromSuperview];
    [self.pPinCreationDialogContainer release];

    [self.pCompassDialogDescription removeFromSuperview];
    [self.pCompassDialogDescription release];
    [self.pCompassDialogTitle removeFromSuperview];
    [self.pCompassDialogTitle release];
    [self.pCompassDialogArrow removeFromSuperview];
    [self.pCompassDialogArrow release];
    [self.pCompassDialogArrowOutline removeFromSuperview];
    [self.pCompassDialogArrowOutline release];
    [self.pCompassDialogIcon removeFromSuperview];
    [self.pCompassDialogIcon release];
    [self.pCompassDialogContent removeFromSuperview];
    [self.pCompassDialogContent release];
    [self.pCompassDialogContainer removeFromSuperview];
    [self.pCompassDialogContainer release];
    
    [self.pMapModeDialogDescription removeFromSuperview];
    [self.pMapModeDialogDescription release];
    [self.pMapModeDialogTitle removeFromSuperview];
    [self.pMapModeDialogTitle release];
    [self.pMapModeDialogArrow removeFromSuperview];
    [self.pMapModeDialogArrow release];
    [self.pMapModeDialogArrowOutline removeFromSuperview];
    [self.pMapModeDialogArrowOutline release];
    [self.pMapModeDialogIcon removeFromSuperview];
    [self.pMapModeDialogIcon release];
    [self.pMapModeDialogContent removeFromSuperview];
    [self.pMapModeDialogContent release];
    [self.pMapModeDialogContainer removeFromSuperview];
    [self.pMapModeDialogContainer release];
    
    [self.pSearchMenuDialogDescription removeFromSuperview];
    [self.pSearchMenuDialogDescription release];
    [self.pSearchMenuDialogTitle removeFromSuperview];
    [self.pSearchMenuDialogTitle release];
    [self.pSearchMenuDialogArrow removeFromSuperview];
    [self.pSearchMenuDialogArrow release];
    [self.pSearchMenuDialogArrowOutline removeFromSuperview];
    [self.pSearchMenuDialogArrowOutline release];
    [self.pSearchMenuDialogIcon removeFromSuperview];
    [self.pSearchMenuDialogIcon release];
    [self.pSearchMenuDialogContent removeFromSuperview];
    [self.pSearchMenuDialogContent release];
    [self.pSearchMenuDialogContainer removeFromSuperview];
    [self.pSearchMenuDialogContainer release];

    [self.pWelcomeText removeFromSuperview];
    [self.pWelcomeText release];
    
    [self.pWelcomeDescription removeFromSuperview];
    [self.pWelcomeDescription release];
    
    [self.pBannerBarBackground removeFromSuperview];
    [self.pBannerBarBackground release];
    
    [self.pBannerBarOutline removeFromSuperview];
    [self.pBannerBarOutline release];
    
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
    
    const int bannerOutlineSize = 2;
    const int bannerHeight = (useSmallScreen ? 130.f : 145.f)/m_pixelScale;
    const int bannerHeightWithOutline = bannerHeight + ((bannerOutlineSize * 2))/m_pixelScale;
    const int welcomeTextYOffset =  (useSmallScreen ? -16.f : -18.f)/m_pixelScale;
    const int welcomeDescriptionYOffset = (useSmallScreen ? 24.f : 32.f)/m_pixelScale;
    int bannerYOffset = (int)(m_screenHeight/2 - bannerHeightWithOutline/2);
    [self.pBannerBarContainer setFrame:CGRectMake(0, bannerYOffset, m_screenWidth, bannerHeightWithOutline)];
    
    [self.pBannerBarOutline setFrame:CGRectMake(0, 0, m_screenWidth, bannerHeightWithOutline)];
    [self.pBannerBarBackground setFrame:CGRectMake(0, bannerOutlineSize/m_pixelScale, m_screenWidth, bannerHeight)];
    float welcomeTextWidth = [self.pWelcomeText.text boundingRectWithSize:self.pWelcomeText.frame.size options:NSStringDrawingUsesLineFragmentOrigin attributes:@{ NSFontAttributeName:self.pWelcomeText.font } context:nil].size.width;
    [self.pWelcomeText setFrame:CGRectMake((m_screenWidth - welcomeTextWidth)/2, welcomeTextYOffset, m_screenWidth, bannerHeightWithOutline)];
    float welcomeDescriptionWidth = [self.pWelcomeDescription.text boundingRectWithSize:self.pWelcomeDescription.frame.size options:NSStringDrawingUsesLineFragmentOrigin attributes:@{ NSFontAttributeName:self.pWelcomeDescription.font } context:nil].size.width;
    [self.pWelcomeDescription setFrame:CGRectMake((m_screenWidth - welcomeDescriptionWidth)/2, welcomeDescriptionYOffset, m_screenWidth, bannerHeightWithOutline)];
    
    [self layoutDialogSubview: self.pSearchMenuDialogContainer
                      content: self.pSearchMenuDialogContent
                         icon: self.pSearchMenuDialogIcon
                        title: self.pSearchMenuDialogTitle
                  description: self.pSearchMenuDialogDescription
                        arrow: self.pSearchMenuDialogArrow
                 arrowOutline: self.pSearchMenuDialogArrowOutline
                            x: useSmallScreen ? 30 : 100
                            y: useSmallScreen ? 90 : 52
              alignHorizontal: AlignHorizontal::Left
                alignVertical: AlignVertical::Top
                    arrowEdge: useSmallScreen ? ArrowEdge::Top : ArrowEdge::Left
            arrowEdgeLocation: useSmallScreen ? 0.21f : 0.25f];
    
    [self layoutDialogSubview: self.pCompassDialogContainer
                      content: self.pCompassDialogContent
                         icon: self.pCompassDialogIcon
                        title: self.pCompassDialogTitle
                  description: self.pCompassDialogDescription
                        arrow: self.pCompassDialogArrow
                 arrowOutline: self.pCompassDialogArrowOutline
                            x: m_screenWidth/2
                            y: m_screenHeight - (useSmallScreen ? 108 : 125)
              alignHorizontal: AlignHorizontal::Centre
                alignVertical: AlignVertical::Bottom
                    arrowEdge: ArrowEdge::Bottom
            arrowEdgeLocation: 0.5f];
    
    [self layoutDialogSubview: self.pMapModeDialogContainer
                      content: self.pMapModeDialogContent
                         icon: self.pMapModeDialogIcon
                        title: self.pMapModeDialogTitle
                  description: self.pMapModeDialogDescription
                        arrow: self.pMapModeDialogArrow
                 arrowOutline: self.pMapModeDialogArrowOutline
                            x: m_screenWidth/2 - (useSmallScreen ? 45 : 150)
                            y: m_screenHeight - (useSmallScreen ? 92 : 10)
              alignHorizontal: AlignHorizontal::Right
                alignVertical: AlignVertical::Bottom
                    arrowEdge: useSmallScreen ? ArrowEdge::Bottom : ArrowEdge::Right
            arrowEdgeLocation: useSmallScreen ? 0.6f : 0.65f];
    
    [self layoutDialogSubview: self.pPinCreationDialogContainer
                      content: self.pPinCreationDialogContent
                         icon: self.pPinCreationDialogIcon
                        title: self.pPinCreationDialogTitle
                  description: self.pPinCreationDialogDescription
                        arrow: self.pPinCreationDialogArrow
                 arrowOutline: self.pPinCreationDialogArrowOutline
                            x: m_screenWidth/2 + (useSmallScreen ? 45 : 150)
                            y: m_screenHeight - (useSmallScreen ? 92 : 10)
              alignHorizontal: AlignHorizontal::Left
                alignVertical: AlignVertical::Bottom
                    arrowEdge: useSmallScreen ? ArrowEdge::Bottom : ArrowEdge::Left
            arrowEdgeLocation: useSmallScreen ? 0.315f : 0.7f];
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

    float stepAnimationTimeSeconds = m_animationTimeSeconds / 5;
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pSearchMenuDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds * 2
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pMapModeDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds * 3
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pCompassDialogContainer.alpha = 1.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds * 4
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
    
    float stepAnimationTimeSeconds = m_animationTimeSeconds / 5;
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pSearchMenuDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds * 2
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pMapModeDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds * 3
                        options:UIViewAnimationOptionCurveEaseOut
                     animations:^{
                         self.pCompassDialogContainer.alpha = 0.0f;
                     }
                     completion:nil];
    
    [UIView animateWithDuration:stepAnimationTimeSeconds
                          delay:stepAnimationTimeSeconds * 4
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

-(void)layoutDialogSubview: (UIView*) container
                   content: (UIView*) content
                      icon: (UIView*) icon
                     title: (UILabel*) title
               description: (UITextView*) description
                     arrow: (UIView*) arrow
              arrowOutline: (UIView*) arrowOutline
                         x: (int) x
                         y: (int) y
           alignHorizontal: (AlignHorizontal::AlignHorizontal) alignHorizontal
             alignVertical: (AlignVertical::AlignVertical) alignVertical
                 arrowEdge: (ArrowEdge::ArrowEdge) arrowEdge
         arrowEdgeLocation: (float) arrowEdgeLocation
{
    const bool useSmallScreen = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const int arrowSize = useSmallScreen ? 8 : 12;
    
    const int iconSize = useSmallScreen ? 16 : 26;
    const int iconPaddingTop = useSmallScreen ? 6 : 13;
    const int iconPaddingLeft = useSmallScreen ? 6 : 18;
    
    const int textPadding = useSmallScreen ? 8 : 17;
    const int titlePaddingLeft = (iconPaddingLeft * 1.5f) + iconSize;
    const int descriptionPaddingLeft = useSmallScreen ? iconPaddingLeft : titlePaddingLeft;
    const int descriptionPaddingTop = useSmallScreen ? 6 : 4;
    
    CGSize titleTextSize = [title sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
    CGRect titleRect = CGRectMake(titlePaddingLeft, textPadding, titleTextSize.width, titleTextSize.height);
    [title setFrame:titleRect];
    
    CGSize descriptionTextSize = [description sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
    CGRect descriptionRect = CGRectMake(descriptionPaddingLeft,
                                        titleTextSize.height + textPadding + descriptionPaddingTop,
                                        descriptionTextSize.width,
                                        descriptionTextSize.height);
    [description setFrame:descriptionRect];
    
    const int titleRightPosition = titlePaddingLeft + titleTextSize.width;
    const int descriptionRightPosition = descriptionPaddingLeft + descriptionTextSize.width;
    const int textWidth = titleRightPosition > descriptionRightPosition ? titleRightPosition : descriptionRightPosition;
    const int dialogWidth = textWidth + textPadding;
    const int dialogHeight = descriptionRect.origin.y + descriptionRect.size.height + textPadding;
    
    int dialogX = x;
    if(alignHorizontal == AlignHorizontal::Right)
    {
        dialogX -= dialogWidth;
    }
    else if(alignHorizontal == AlignHorizontal::Centre)
    {
        dialogX -= dialogWidth * 0.5f;
    }
    
    int dialogY = y;
    if(alignVertical == AlignVertical::Bottom)
    {
        dialogY -= dialogHeight;
    }
    else if(alignVertical == AlignVertical::Centre)
    {
        dialogY -= dialogHeight * 0.5f;
    }
    
    const int dialogOutlineSize = 2;
    
    [container setFrame:CGRectMake(dialogX - dialogOutlineSize,
                                   dialogY - dialogOutlineSize,
                                   dialogWidth + (dialogOutlineSize * 2),
                                   dialogHeight + (dialogOutlineSize * 2))];
    [content setFrame:CGRectMake(dialogOutlineSize,
                                 dialogOutlineSize,
                                 dialogWidth,
                                 dialogHeight)];
    
    int arrowX = dialogWidth * arrowEdgeLocation - arrowSize/2;
    int arrowOutlineX = dialogWidth * arrowEdgeLocation - (arrowSize + (dialogOutlineSize * 2))/2;
    if(arrowEdge == ArrowEdge::Left)
    {
        arrowX = -arrowSize;
        arrowOutlineX = -arrowSize - dialogOutlineSize * 2;
    }
    else if(arrowEdge == ArrowEdge::Right)
    {
        arrowX = dialogWidth;
        arrowOutlineX = dialogWidth;
    }
    
    int arrowY = dialogHeight * arrowEdgeLocation - arrowSize/2;
    int arrowOutlineY = dialogHeight * arrowEdgeLocation - (arrowSize + (dialogOutlineSize * 2))/2;
    if(arrowEdge == ArrowEdge::Top)
    {
        arrowY = -arrowSize;
        arrowOutlineY = -arrowSize - dialogOutlineSize * 2;
    }
    else if(arrowEdge == ArrowEdge::Bottom)
    {
        arrowY = dialogHeight;
        arrowOutlineY = dialogHeight;
    }
    
    [arrowOutline setFrame:CGRectMake(arrowOutlineX,
                                      arrowOutlineY,
                                      arrowSize + (dialogOutlineSize * 2),
                                      arrowSize + (dialogOutlineSize * 2))];
    [arrow setFrame:CGRectMake(arrowX,
                               arrowY,
                               arrowSize,
                               arrowSize)];
    
    [icon setFrame:CGRectMake(iconPaddingLeft,
                              iconPaddingTop,
                              iconSize,
                              iconSize)];
}

@end
