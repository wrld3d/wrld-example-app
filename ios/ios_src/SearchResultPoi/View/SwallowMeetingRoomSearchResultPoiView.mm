// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "SearchResultPoiView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#import "UIView+TouchExclusivity.h"
#include "SwallowMeetingRoomSearchResultPoiView.h"
#include "SwallowSearchParser.h"
#include "App.h"

@interface SwallowMeetingRoomSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

const int DeletePinAlertViewTag = 1;

@implementation SwallowMeetingRoomSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;
{
    self = [super init];
    
    if(self)
    {
        m_pController = [UIViewController alloc];
        [m_pController setView:self];
        
        self->m_pRemovePinButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_remove_pin_off") retain];
        self->m_pAddPinButtonBackgroundImage = [ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_add_pin_off") retain];
        
        m_pInterop = pInterop;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
        [self addSubview: self.pControlContainer];
        
        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"button_close_off") forState:UIControlStateNormal];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];
        
        self.pPinButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pPinButton addTarget:self action:@selector(handlePinButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pPinButton];
        
        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pControlContainer addSubview: self.pContentContainer];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pContentContainer addSubview: self.pLabelsContainer];
        
        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pCategoryIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoryIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::WhiteTone;
        [self.pHeadlineContainer addSubview: self.pCategoryIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pPreviewImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImage.contentMode = UIViewContentModeScaleAspectFill;
        [self.pLabelsContainer addSubview: self.pPreviewImage];
        
        self.pPreviewImageSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImageSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        self.pPreviewImageSpinner.center = CGPointZero;
        [self.pPreviewImage addSubview: self.pPreviewImageSpinner];
        
        // available labels/title
        self.pAvailableHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAvailableHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pLabelsContainer addSubview: self.pAvailableHeaderContainer];
        
        self.pAvailableHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pAvailableHeaderContainer addSubview: self.pAvailableHeaderLabel];
        
        self.pAvailableContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pAvailableContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        [self.pLabelsContainer addSubview: self.pAvailableContent];
        
        self.pCategoriesHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoriesHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        [self.pLabelsContainer addSubview: self.pCategoriesHeaderContainer];
        
        self.pCategoriesHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::WhiteTone :ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pCategoriesHeaderContainer addSubview: self.pCategoriesHeaderLabel];
        
        self.pCategoriesContent = [self createLabel :ExampleApp::Helpers::ColorPalette::MainHudColor :ExampleApp::Helpers::ColorPalette::WhiteTone];
        self.pCategoriesContent.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        [self.pLabelsContainer addSubview: self.pCategoriesContent];
        
        
        [self setTouchExclusivity: self];
        
        self.alpha = 0.f;
    }
    
    return self;
}

- (void)dealloc
{
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pPinButton removeFromSuperview];
    [self.pPinButton release];
    
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
    
    [self.pCategoryIconContainer removeFromSuperview];
    [self.pCategoryIconContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pAvailableHeaderLabel removeFromSuperview];
    [self.pAvailableHeaderLabel release];
    
    [self.pAvailableHeaderContainer removeFromSuperview];
    [self.pAvailableHeaderContainer release];
    
    [self.pAvailableContent removeFromSuperview];
    [self.pAvailableContent release];
    
    [self.pCategoriesHeaderContainer removeFromSuperview];
    [self.pCategoriesHeaderContainer release];
    
    [self.pCategoriesHeaderLabel removeFromSuperview];
    [self.pCategoriesHeaderLabel release];
    
    [self.pCategoriesContent removeFromSuperview];
    [self.pCategoriesContent release];
    
    [self.pPreviewImage removeFromSuperview];
    [self.pPreviewImage release];
    
    [self.pPreviewImageSpinner removeFromSuperview];
    [self.pPreviewImageSpinner release];
    
    [self->m_pRemovePinButtonBackgroundImage release];
    [self->m_pRemovePinHighlightButtonBackgroundImage release];
    [self->m_pAddPinButtonBackgroundImage release];
    [self->m_pAddPinHighlightButtonBackgroundImage release];
    
    [m_pController release];
    [self removeFromSuperview];
    [super dealloc];
}

- (void) layoutSubviews
{
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const float boundsOccupyMultiplierHeight = 0.9f;
    const float mainWindowWidth = std::min(boundsWidth, 348.f);
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplierHeight;
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
    
    const float headlineHeight = 60.f;
    const float closeButtonSectionHeight = 64.f;
    const float closeButtonSectionOffsetY = mainWindowHeight - closeButtonSectionHeight;
    const float contentSectionHeight = mainWindowHeight - (closeButtonSectionHeight + headlineHeight);
    
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                               0.f,
                                               mainWindowWidth,
                                               headlineHeight);
    
    self.pContentContainer.frame = CGRectMake(0.f,
                                              headlineHeight,
                                              mainWindowWidth,
                                              contentSectionHeight);
    
    const float labelsSectionOffsetX = 0.f;
    m_labelsSectionWidth = mainWindowWidth - (2.f * labelsSectionOffsetX);
    
    self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                             0.f,
                                             m_labelsSectionWidth,
                                             contentSectionHeight);
    
    
    self.pCloseButtonContainer.frame = CGRectMake(0.f,
                                                  closeButtonSectionOffsetY,
                                                  mainWindowWidth,
                                                  closeButtonSectionHeight);
    
    self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight,
                                         0.f,
                                         closeButtonSectionHeight,
                                         closeButtonSectionHeight);
    
    self.pPinButton.frame = CGRectMake(0.f,
                                       0.f,
                                       closeButtonSectionHeight,
                                       closeButtonSectionHeight);
    
    self.pCategoryIconContainer.frame = CGRectMake(0.f, 0.f, headlineHeight, headlineHeight);
    
    const float titlePadding = 10.0f;
    
    const float titleHeight = headlineHeight * 0.6f;
    
    self.pTitleLabel.frame = CGRectMake(headlineHeight + titlePadding,
                                        0.f,
                                        mainWindowWidth - (headlineHeight + titlePadding),
                                        titleHeight);
    self.pTitleLabel.font = [UIFont systemFontOfSize:24.0f];
    
    m_imageWidth = mainWindowWidth;
    m_imageHeight = mainWindowWidth;
    
}

- (void) performDynamicContentLayout
{
    const float headerLabelHeight = 20.f;
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    
    float currentLabelY = 8.f;
    if(!m_meetingRoomModel.GetImageUrl().empty())
    {
        currentLabelY = 0.f;
        
        self.pPreviewImage.frame = CGRectMake(0, currentLabelY, m_imageWidth, m_imageHeight);
        [self.pPreviewImage setClipsToBounds:YES];
        self.pPreviewImageSpinner.center = [self.pPreviewImage convertPoint:self.pPreviewImage.center fromView:self.pPreviewImage.superview];
        const CGFloat imageBottomPadding = 8.0;
        currentLabelY += (m_imageHeight + imageBottomPadding);
        self.pPreviewImage.hidden = false;
    }
    
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    m_meetingRoomModel = ExampleApp::Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(m_model);
    m_isPinned = isPinned;
    [self updatePinnedButtonState];
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self.pCategoryIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string categoryIcon = ExampleApp::Helpers::IconResources::GetSmallIconForCategory(pModel->GetCategory());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategoryIconContainer, categoryIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pAvailableHeaderContainer.hidden = true;
    self.pAvailableHeaderLabel.hidden = true;
    self.pAvailableContent.hidden = true;
    self.pPreviewImage.hidden = true;
    self.pCategoriesHeaderContainer.hidden = true;
    self.pCategoriesContent.hidden = true;
    
    [self performDynamicContentLayout];
    
    if(!m_meetingRoomModel.GetImageUrl().empty())
    {
        [self.pPreviewImage setImage:nil];
        [self.pPreviewImageSpinner startAnimating];
    }
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    if(url == m_meetingRoomModel.GetImageUrl())
    {
        [self.pPreviewImageSpinner stopAnimating];
        
        if(success)
        {
            NSData* imageData = [NSData dataWithBytes:&bytes->at(0) length:bytes->size()];
            UIImage *image = [UIImage imageWithData:imageData];
            [self.pPreviewImage setImage:image];
            
            [self.pPreviewImage.layer removeAllAnimations];
            self.pPreviewImage.hidden = false;
            
            [self performDynamicContentLayout];
        }
        else
        {
            
            [self performDynamicContentLayout];
        }
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

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)getInterop
{
    return m_pInterop;
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

-(void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    switch (alertView.tag)
    {
        case DeletePinAlertViewTag:
        {
            alertView.delegate = nil;
            
            if (buttonIndex == 1)
            {
                [self togglePinState];
            }
        }break;
        default:
            break;
    }
}

- (void) handleClosedButtonSelected
{
    m_pInterop->HandleCloseClicked();
}

- (void) handlePinButtonSelected
{
    if(m_isPinned)
    {
        [self performPinRemoveWarningCeremony];
    }
    else
    {
        [self togglePinState];
    }
}

- (void) togglePinState
{
    m_isPinned = !m_isPinned;
    m_pInterop->HandlePinToggleClicked(m_model);
    [self updatePinnedButtonState];
}

- (void) updatePinnedButtonState
{
    if(m_isPinned)
    {
        [self.pPinButton setBackgroundImage:self->m_pRemovePinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setBackgroundImage:self->m_pRemovePinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
    }
    else
    {
        [self.pPinButton setBackgroundImage:self->m_pAddPinButtonBackgroundImage forState:UIControlStateNormal];
        [self.pPinButton setBackgroundImage:self->m_pAddPinHighlightButtonBackgroundImage forState:UIControlStateHighlighted];
    }
}

- (void) performPinRemoveWarningCeremony
{
    NSString* alertTitle = @"Remove Pin";
    NSString* alertMessage = @"Are you sure you want to remove this pin?";
    NSString* keepButtonText = @"No, keep it";
    NSString* deleteButtonText = @"Yes, delete it";
    
    if([UIAlertController class])
    {
        UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle
                                                                       message:alertMessage
                                                                preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction* defaultAction = [UIAlertAction actionWithTitle:keepButtonText
                                                                style:UIAlertActionStyleDefault
                                                              handler:^(UIAlertAction * action) {}];
        
        UIAlertAction* removePinAction = [UIAlertAction actionWithTitle:deleteButtonText
                                                                  style:UIAlertActionStyleDefault
                                                                handler: ^(UIAlertAction * action)
                                          {
                                              [self togglePinState];
                                          }];
        
        [alert addAction:defaultAction];
        [alert addAction:removePinAction];
        [m_pController presentViewController:alert animated:YES completion:nil];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:self
                                              cancelButtonTitle:keepButtonText
                                              otherButtonTitles:deleteButtonText, nil];
        
        [alert show];
        alert.tag = DeletePinAlertViewTag;
        [alert release];
    }
}

@end
