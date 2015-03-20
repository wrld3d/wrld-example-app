// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsView.h"
#include "InitialExperienceDialogsViewInterop.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "App.h"

@implementation InitialExperienceDialogsView

const float arrowWidth = 10;

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
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pDialogContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"buttonsmall_close_off") forState:UIControlStateNormal];
        [self.pCloseButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"buttonsmall_close_on") forState:UIControlStateHighlighted];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];
        
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
    
    m_borderMarginX = useSmallScreen ? 20 : 64;
    m_borderMarginY = useSmallScreen ? 30 : 64;
    m_arrowLength = useSmallScreen ?  20 : 70;

    const float closeButtonSectionHeight = 20.f;
    
    const float dialogHeight = 110;
    float dialogWidth = (m_screenWidth - 2 * (m_arrowLength + m_borderMarginX));
    if(!useSmallScreen)
    {
        dialogWidth /= 2;
    }
    
    m_dialogContainerWidth = dialogWidth + 2 * m_arrowLength;
    m_dialogContainerHeight = dialogHeight + closeButtonSectionHeight + (2 * m_arrowLength);
    
    [self.pDialogContainer setFrame:CGRectMake(m_dialogPosition.x, m_dialogPosition.y, m_dialogContainerWidth, m_dialogContainerHeight)];
    
    [self.pDialogContainer setAlpha:m_visible ? 1.0f : 0.0f];
    [self.pDialogTextboxContainer setFrame:CGRectMake(m_arrowLength, m_arrowLength, dialogWidth, dialogHeight)];
    self.pTitleLabel.font = [UIFont systemFontOfSize:20.f];
    self.pTitleLabel.numberOfLines = 1;
    self.pTitleLabel.frame = CGRectMake(10, 10, dialogWidth - 10, 20);
    self.pDescriptionLabel.font = useSmallScreen ? [UIFont systemFontOfSize:12.f] : [UIFont systemFontOfSize:15.f];
    self.pDescriptionLabel.frame = CGRectMake(10, 30, dialogWidth - 20, 70);
    self.pDescriptionLabel.dataDetectorTypes = UIDataDetectorTypeLink;
    
    self.pCloseButtonContainer.frame = CGRectMake(m_arrowLength, m_arrowLength+dialogHeight, dialogWidth, closeButtonSectionHeight);
    self.pCloseButton.frame = CGRectMake(dialogWidth-closeButtonSectionHeight, 0, closeButtonSectionHeight, closeButtonSectionHeight);
}

- (BOOL) consumesTouch:(UITouch *)touch
{
    return m_modalBackgroundActive;
}

- (void) showDialog:(const ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Values)dialogType
                   :(const std::string *)title
                   :(const std::string *)description
{
    [self.pArrowLeft setFrame:CGRectMake(0, m_dialogContainerHeight/2 - arrowWidth/2, m_arrowLength, arrowWidth)];
    [self.pArrowRight setFrame:CGRectMake(m_dialogContainerWidth-m_arrowLength, m_dialogContainerHeight/2 - arrowWidth/2, m_arrowLength, arrowWidth)];
    [self.pArrowUp setFrame:CGRectMake(m_dialogContainerWidth/2 - arrowWidth/2, 0, arrowWidth, m_arrowLength)];
    [self.pArrowDown setFrame:CGRectMake(m_dialogContainerWidth/2 - arrowWidth/2, m_dialogContainerHeight-m_arrowLength, arrowWidth, m_arrowLength)];
    
    [self.pArrowLeft setHidden:YES];
    [self.pArrowRight setHidden:YES];
    [self.pArrowUp setHidden:YES];
    [self.pArrowDown setHidden:YES];
    
    const bool useSmallScreen = App::IsDeviceSmall();
    
    CGPoint anchor = CGPointMake(0.5f, 0.5f);

    // half-compass + spacing + half-control
    const float bottomButtonCentreOffsets(40.f + 8.f + 32.f);
    
    switch(dialogType)
    {
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::MainMenu:
            [self.pArrowRight setHidden:NO];
            anchor = CGPointMake(1.0f, 0.5f);
            m_dialogPosition = useSmallScreen
                ? CGPointMake(-m_arrowLength, 0)
                : CGPointMake(m_screenWidth - (m_dialogContainerWidth + m_borderMarginY), m_borderMarginY - m_arrowLength*1.5f);
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::SearchResultMenu:
            [self.pArrowLeft setHidden:NO];
            anchor = CGPointMake(0.0f, 0.5f);
            m_dialogPosition = useSmallScreen
                ? CGPointMake(m_screenWidth - m_dialogContainerWidth + m_arrowLength, 0)
                : CGPointMake(m_borderMarginY, m_borderMarginY - m_arrowLength*1.5f);
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Compass:
            [self.pArrowDown setHidden:NO];
            anchor = CGPointMake(0.5f, 1.0f);
            
            m_dialogPosition = useSmallScreen
                ? CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2,
                              m_screenHeight - (m_dialogContainerHeight + (m_borderMarginY*3.0f)))
                : CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2,
                              m_screenHeight - (m_dialogContainerHeight + (m_borderMarginY*1.5f)));
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::PinCreation:
            [self.pArrowDown setHidden:NO];
            anchor = CGPointMake(0.5f, 1.0f);
            
            if(useSmallScreen)
            {
                m_dialogPosition = CGPointMake((m_screenWidth/2 - m_dialogContainerWidth/2),
                                               m_screenHeight - (m_dialogContainerHeight + (m_borderMarginY*3.0f)));
                
                [self.pArrowDown setFrame:CGRectMake((m_dialogContainerWidth/2 - arrowWidth/2) + bottomButtonCentreOffsets,
                                                     m_dialogContainerHeight-m_arrowLength, arrowWidth, m_arrowLength)];
            }
            else
            {
                m_dialogPosition = CGPointMake((m_screenWidth/2 - m_dialogContainerWidth/2) + bottomButtonCentreOffsets,
                                               m_screenHeight - (m_dialogContainerHeight + (m_borderMarginY*1.5f)));
                
            }
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Flatten:
            [self.pArrowDown setHidden:NO];
            anchor = CGPointMake(0.5f, 1.0f);
            
            if(useSmallScreen)
            {
                m_dialogPosition = CGPointMake((m_screenWidth/2 - m_dialogContainerWidth/2),
                                               m_screenHeight - (m_dialogContainerHeight + (m_borderMarginY*3.0f)));
                
                [self.pArrowDown setFrame:CGRectMake((m_dialogContainerWidth/2 - arrowWidth/2) - bottomButtonCentreOffsets,
                                                     m_dialogContainerHeight-m_arrowLength, arrowWidth, m_arrowLength)];
            }
            else
            {
                m_dialogPosition = CGPointMake((m_screenWidth/2 - m_dialogContainerWidth/2) - bottomButtonCentreOffsets,
                                               m_screenHeight - (m_dialogContainerHeight + (m_borderMarginY*1.5f)));
                
            }
            break;
            
        case ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::SourceCode:
            m_dialogPosition = CGPointMake(m_screenWidth/2 - m_dialogContainerWidth/2,
                                           m_screenHeight/2 - m_dialogContainerHeight/2);
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