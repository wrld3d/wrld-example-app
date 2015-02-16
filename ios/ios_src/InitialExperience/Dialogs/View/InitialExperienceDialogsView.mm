// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsView.h"
#include "InitialExperienceDialogsViewInterop.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "App.h"

@implementation InitialExperienceDialogsView

- (id) initView
{
    self = [super init];
    
    if(self)
    {
        m_animationTimeSeconds = 0.4f;
        
        m_pInterop = Eegeo_NEW(ExampleApp::InitialExperience::Dialogs::View::InitialExperienceDialogsViewInterop)(self);

        self.pBackgroundContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pBackgroundContainer];
        
        self.pDialogContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pBackgroundContainer addSubview: self.pDialogContainer];
        
        self.pArrowLeft = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDialogContainer, "arrow3_left", 0.f, 0.f, 0, 0);
        self.pArrowRight = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDialogContainer, "arrow3_right", 0.f, 0.f, 0, 0);
        self.pArrowUp = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDialogContainer, "arrow3_up", 0.f, 0.f, 0, 0);
        self.pArrowDown = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDialogContainer, "arrow3_down", 0.f, 0.f, 0, 0);
        
        self.pDialogTextboxContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDialogTextboxContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pDialogContainer addSubview: self.pDialogTextboxContainer];
        
        self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pDialogTextboxContainer addSubview: self.pTitleLabel];
        
        self.pDescriptionLabel = [[[UITextView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pDescriptionLabel.editable = NO;
        self.pDescriptionLabel.scrollEnabled = NO;
        [self.pDialogTextboxContainer addSubview: self.pDescriptionLabel];
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pDialogContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_off.png"] forState:UIControlStateNormal];
        [self.pCloseButton setBackgroundImage:[UIImage imageNamed:@"button_close_on.png"] forState:UIControlStateHighlighted];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];
        
        self.pCloseButtonContainerShadow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDialogContainer, "shadow_03", 0.f, 0.f, 0, 0);
        
        self.pDialogShadow = ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDialogContainer, "shadow_01", 0.f, 0.f, 0, 0);
        
        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(_tapTabGesture:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self.pCloseButton addGestureRecognizer: m_tapGestureRecogniser];
        
        m_visible = NO;
        m_modalBackgroundActive = NO;
        
        [self setModalBackgroundActive: NO];
    }
    
    return self;
}

- (void)dealloc
{
    [m_tapGestureRecogniser release];
    
    [self.pDialogShadow removeFromSuperview];
    [self.pDialogShadow release];
    
    [self.pCloseButtonContainerShadow removeFromSuperview];
    [self.pCloseButtonContainerShadow release];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pCloseButtonContainer removeFromSuperview];
    [self.pCloseButtonContainer release];
    
    [self.pDescriptionLabel removeFromSuperview];
    [self.pDescriptionLabel release];
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pDialogTextboxContainer removeFromSuperview];
    [self.pDialogTextboxContainer release];
    
    [self.pArrowLeft removeFromSuperview];
    [self.pArrowLeft release];
    [self.pArrowRight removeFromSuperview];
    [self.pArrowRight release];
    [self.pArrowUp removeFromSuperview];
    [self.pArrowUp release];
    [self.pArrowDown removeFromSuperview];
    [self.pArrowDown release];
    
    [self.pDialogContainer removeFromSuperview];
    [self.pDialogContainer release];
    [self.pBackgroundContainer removeFromSuperview];
    [self.pBackgroundContainer release];
    
    m_dialogPosition = CGPointMake(0, 0);
    
    Eegeo_DELETE m_pInterop;

    [super dealloc];
}

- (ExampleApp::InitialExperience::Dialogs::View::InitialExperienceDialogsViewInterop*) getInterop
{
    return m_pInterop;
}

- (void) layoutSubviews
{
    m_screenWidth = self.superview.bounds.size.width;
    m_screenHeight = self.superview.bounds.size.height;
    [self setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];
    [self.pBackgroundContainer setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];
    
    const bool useSmallScreen = App::IsDeviceSmall();
    
    m_borderMargin = useSmallScreen ? 20 : 64;
    const float arrowWidth = 10;
    m_arrowLength = useSmallScreen ?  20 : 70;

    const float closeButtonSectionHeight = 50.f;
    const float shadowHeight = 10.f;
    
    const float dialogHeight = 90;
    float dialogWidth = (m_screenWidth - 2 * (m_arrowLength + m_borderMargin));
    if(!useSmallScreen)
    {
        dialogWidth /= 2;
    }
    
    m_dialogContainerWidth = dialogWidth + 2 * m_arrowLength;
    m_dialogContainerHeight = dialogHeight + closeButtonSectionHeight + (2 * m_arrowLength);
    
    [self.pDialogContainer setFrame:CGRectMake(m_dialogPosition.x, m_dialogPosition.y, m_dialogContainerWidth, m_dialogContainerHeight)];
    
    [self.pArrowLeft setFrame:CGRectMake(0, m_dialogContainerHeight/2 - arrowWidth/2, m_arrowLength, arrowWidth)];
    [self.pArrowRight setFrame:CGRectMake(m_dialogContainerWidth-m_arrowLength, m_dialogContainerHeight/2 - arrowWidth/2, m_arrowLength, arrowWidth)];
    [self.pArrowUp setFrame:CGRectMake(m_dialogContainerWidth/2 - arrowWidth/2, 0, arrowWidth, m_arrowLength)];
    [self.pArrowDown setFrame:CGRectMake(m_dialogContainerWidth/2 - arrowWidth/2, m_dialogContainerHeight-m_arrowLength, arrowWidth, m_arrowLength)];
    
    [self.pDialogContainer setAlpha:m_visible ? 1.0f : 0.0f];
    [self.pDialogTextboxContainer setFrame:CGRectMake(m_arrowLength, m_arrowLength, dialogWidth, dialogHeight)];
    self.pTitleLabel.font = [UIFont systemFontOfSize:20.f];
    self.pTitleLabel.numberOfLines = 1;
    self.pTitleLabel.frame = CGRectMake(10, 10, dialogWidth - 10, 20);
    self.pDescriptionLabel.font = useSmallScreen ? [UIFont systemFontOfSize:12.f] : [UIFont systemFontOfSize:15.f];
    self.pDescriptionLabel.frame = CGRectMake(10, 30, dialogWidth - 20, 50);
    self.pDescriptionLabel.dataDetectorTypes = UIDataDetectorTypeLink;
    
    self.pCloseButtonContainer.frame = CGRectMake(m_arrowLength, m_arrowLength+dialogHeight, dialogWidth, closeButtonSectionHeight);
    self.pCloseButtonContainerShadow.frame = CGRectMake(m_arrowLength, m_arrowLength + dialogHeight, dialogWidth, shadowHeight);
    self.pCloseButton.frame = CGRectMake(dialogWidth-closeButtonSectionHeight, 0, closeButtonSectionHeight, closeButtonSectionHeight);
    
    self.pDialogShadow.frame = CGRectMake(m_arrowLength, m_arrowLength+dialogHeight+closeButtonSectionHeight, dialogWidth, shadowHeight);
}

- (BOOL) consumesTouch:(UITouch *)touch
{
    return m_modalBackgroundActive;
}

- (void) showDialog:(const ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Values)dialogType
                   :(const std::string *)title
                   :(const std::string *)description
{
    [self.pArrowLeft setHidden:YES];
    [self.pArrowRight setHidden:YES];
    [self.pArrowUp setHidden:YES];
    [self.pArrowDown setHidden:YES];
    
    const bool useSmallScreen = App::IsDeviceSmall();
    
    CGPoint anchor = CGPointMake(0.5f, 0.5f);
    
    switch(dialogType)
    {
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::SearchMenu:
            [self.pArrowRight setHidden:NO];
            anchor = CGPointMake(1.0f, 0.5f);
            m_dialogPosition = useSmallScreen
                ? CGPointMake(-m_arrowLength, 0)
                : CGPointMake(m_screenWidth - (m_dialogContainerWidth + m_borderMargin), m_borderMargin - m_arrowLength*1.5f);
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::PrimaryMenu:
            [self.pArrowLeft setHidden:NO];
            anchor = CGPointMake(0.0f, 0.5f);
            m_dialogPosition = useSmallScreen
                ? CGPointMake(m_screenWidth - m_dialogContainerWidth + m_arrowLength, 0)
                : CGPointMake(m_borderMargin, m_borderMargin - m_arrowLength*1.5f);
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Compass:
            [self.pArrowUp setHidden:NO];
            anchor = CGPointMake(0.5f, 0.0f);
            m_dialogPosition = useSmallScreen
                ? CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2, m_borderMargin*3.0f)
                : CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2, m_borderMargin*1.5f);
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::PinCreation:
            [self.pArrowDown setHidden:NO];
            anchor = CGPointMake(0.5f, 1.0f);
            
            m_dialogPosition = useSmallScreen
                ? CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2, m_screenHeight - (m_dialogContainerHeight + (m_borderMargin*3.0f)))
                : CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2, m_screenHeight - (m_dialogContainerHeight + (m_borderMargin*1.5f)));
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Flatten:
            [self.pArrowLeft setHidden:NO];
            anchor = CGPointMake(0.0f, 0.5f);
            m_dialogPosition = useSmallScreen
                ? CGPointMake(m_screenWidth - m_dialogContainerWidth + m_arrowLength, m_screenHeight/2 - m_dialogContainerHeight*0.5f)
                : CGPointMake(m_borderMargin, m_screenHeight/2 - m_dialogContainerHeight*0.5f);
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::SourceCode:
            m_dialogPosition = CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2, m_screenHeight/2 - m_dialogContainerHeight/2);
            break;
            
        default:
            break;
    }
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:title->c_str()];
    self.pDescriptionLabel.text = [NSString stringWithUTF8String:description->c_str()];;
    
    m_visible = YES;
    
    self.pDialogContainer.transform = CGAffineTransformMakeScale(0.1f, 0.1f);
    self.pDialogContainer.layer.anchorPoint = anchor;
    
    [UIView animateWithDuration:m_animationTimeSeconds
                     animations:^(){
                         self.pDialogContainer.transform = CGAffineTransformMakeScale(1.0f, 1.0f);
                     }completion:nil];
    
    
    [self setNeedsLayout];
    [self layoutIfNeeded];
}

- (void) closeCurrentDialog
{
    self.pDialogContainer.transform = CGAffineTransformMakeScale(1.0f, 1.0f);
    
    [UIView animateWithDuration:m_animationTimeSeconds
                     animations:^(){
                         self.pDialogContainer.transform = CGAffineTransformMakeScale(0.01f, 0.01f);
                     }
                     completion:^(BOOL finished) {
                         if(finished)
                         {
                             m_visible = false;
                             [self setNeedsLayout];
                             [self layoutIfNeeded];
                         }
                     }];
}

- (void) setModalBackgroundActive:(BOOL)active
{
    m_modalBackgroundActive = active;
    self.opaque = !active;
    self.userInteractionEnabled = active;
    [self.pBackgroundContainer setHidden:!active];
    [self setHidden:!active];
}

- (void)_tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    m_pInterop->CloseButtonTapped();
}

@end