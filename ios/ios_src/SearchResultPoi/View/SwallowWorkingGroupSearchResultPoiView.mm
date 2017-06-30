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
#include "SwallowWorkingGroupSearchResultPoiView.h"
#include "SwallowSearchParser.h"
#include "App.h"
#import "UIButton+DefaultStates.h"

@interface SwallowWorkingGroupSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

@implementation SwallowWorkingGroupSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;
{
    self = [super init];
    
    if(self)
    {
        m_pController = [UIViewController alloc];
        [m_pController setView:self];
        
        m_pInterop = pInterop;
        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pControlContainer];
        
        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pContentContainer];
        
        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentContainer addSubview: self.pLabelsContainer];
        
        self.pDescriptionIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionIconContainer.image = [UIImage imageNamed:@"detail_icon_description"];
        [self.pLabelsContainer addSubview: self.pDescriptionIconContainer];
        
        self.pDescriptionContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pDescriptionContent];
        
        self.pDescriptionDivider = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionDivider.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pDescriptionDivider];
        
        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pCategoryIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoryIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pHeadlineContainer addSubview: self.pCategoryIconContainer];
        
        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pHeadlineContainer addSubview: self.pTitleLabel];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setDefaultStatesWithImageNames:@"exit_blue_x_button" :@"exit_dark_blue_x_button"];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pHeadlineContainer addSubview: self.pCloseButton];
        
        self.pPreviewImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImage.contentMode = UIViewContentModeScaleAspectFill;
        [self.pLabelsContainer addSubview: self.pPreviewImage];
        
        self.pPreviewImageSpinner = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pPreviewImageSpinner.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        self.pPreviewImageSpinner.center = CGPointZero;
        [self.pPreviewImage addSubview: self.pPreviewImageSpinner];
        
        self.pPlaceholderImage = [UIImage imageNamed: @"poi_placeholder.png"];
        
        self.pImageDivider = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pImageDivider.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pImageDivider];
        
        self.pCategoriesIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoriesIconContainer.image = [UIImage imageNamed:@"poi_tag"];
        [self.pLabelsContainer addSubview: self.pCategoriesIconContainer];
        
        self.pCategoriesContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pCategoriesContent];
        
        self.pCategoriesDivider = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoriesDivider.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pCategoriesDivider];
        
        [self setTouchExclusivity: self];
        
        self.alpha = 0.f;
    }
    
    return self;
}

- (void)dealloc
{
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
    [self.pHeadlineContainer removeFromSuperview];
    [self.pHeadlineContainer release];
    
    [self.pDescriptionIconContainer removeFromSuperview];
    [self.pDescriptionIconContainer release];
    
    [self.pDescriptionContent removeFromSuperview];
    [self.pDescriptionContent release];
    
    [self.pDescriptionDivider removeFromSuperview];
    [self.pDescriptionDivider release];
    
    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];
    
    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];
    
    [self.pCategoryIconContainer removeFromSuperview];
    [self.pCategoryIconContainer release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pCategoriesContent removeFromSuperview];
    [self.pCategoriesContent release];
    
    [self.pCategoriesIconContainer removeFromSuperview];
    [self.pCategoriesIconContainer release];
    
    [self.pCategoriesDivider removeFromSuperview];
    [self.pCategoriesDivider release];
    
    [self.pPlaceholderImage release];
    
    [self.pPreviewImage removeFromSuperview];
    [self.pPreviewImage release];
    
    [self.pPreviewImageSpinner removeFromSuperview];
    [self.pPreviewImageSpinner release];
    
    [self.pImageDivider removeFromSuperview];
    [self.pImageDivider release];
    
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
    const float sideMargin = 15.0f;
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pControlContainer.frame = CGRectMake(0.f,
                                              0.f,
                                              mainWindowWidth,
                                              mainWindowHeight);
    
    const float headlineHeight = 60.f;
    const float closeButtonSectionHeight = 36.f;
    const float contentSectionHeight = mainWindowHeight - headlineHeight;
    const float contentSectionWidth = mainWindowWidth - (2 * sideMargin);
    
    self.pHeadlineContainer.frame = CGRectMake(0.f,
                                               0.f,
                                               mainWindowWidth,
                                               headlineHeight);
    
    self.pContentContainer.frame = CGRectMake(sideMargin,
                                              headlineHeight,
                                              contentSectionWidth,
                                              contentSectionHeight);
    
    const float labelsSectionOffsetX = 0.f;
    m_labelsSectionWidth = contentSectionWidth - (2.f * labelsSectionOffsetX);
    
    self.pLabelsContainer.frame = CGRectMake(labelsSectionOffsetX,
                                             0.f,
                                             m_labelsSectionWidth,
                                             contentSectionHeight);
    
    const float closeButtonMarginTop = 12.0f;
    self.pCloseButton.frame = CGRectMake(mainWindowWidth - closeButtonSectionHeight - sideMargin,
                                         closeButtonMarginTop,
                                         closeButtonSectionHeight,
                                         closeButtonSectionHeight);
    
    self.pCategoryIconContainer.frame = CGRectMake(0.f, 0.f, headlineHeight, headlineHeight);
    
    const float titlePadding = 10.0f;
    
    const float titleHeight = headlineHeight;
    
    self.pTitleLabel.frame = CGRectMake(headlineHeight + titlePadding,
                                        0,
                                        mainWindowWidth - (headlineHeight + titlePadding) - closeButtonSectionHeight - sideMargin,
                                        titleHeight);
    self.pTitleLabel.font = [UIFont systemFontOfSize:24.0f];
    
    m_imageWidth = contentSectionWidth;
    m_imageHeight = contentSectionWidth;
    
}

- (void) performDynamicContentLayout
{
    const float labelYSpacing = 8.f;
    const float headerTextPadding = 3.0f;
    const float dividerHeight = 1.0f;
    const float detailsImageSize = 18.f;
    const float detailsImageToTextMargin = 6.f;
    
    float currentLabelY = 8.f;
    if(!m_workingGroupModel.GetImageUrl().empty())
    {
        currentLabelY = 0.f;
        const CGFloat imagePadding = 10.0;
        
        self.pImageDivider.frame = CGRectMake(0,
                                              currentLabelY,
                                              m_labelsSectionWidth,
                                              dividerHeight);
        self.pImageDivider.hidden = false;
        
        currentLabelY += dividerHeight + imagePadding;
        
        self.pPreviewImage.frame = CGRectMake(0, currentLabelY, m_imageWidth, m_imageHeight);
        [self.pPreviewImage setClipsToBounds:YES];
        self.pPreviewImageSpinner.center = [self.pPreviewImage convertPoint:self.pPreviewImage.center fromView:self.pPreviewImage.superview];
        currentLabelY += (m_imageHeight + imagePadding);
        self.pPreviewImage.hidden = false;
    }
    
    if(m_model.GetHumanReadableTags().size() > 0)
    {
        self.pCategoriesDivider.frame = CGRectMake(0,
                                                   currentLabelY,
                                                   m_labelsSectionWidth,
                                                   dividerHeight);
        self.pCategoriesDivider.hidden = false;
        
        currentLabelY += labelYSpacing + dividerHeight;
        
        self.pCategoriesIconContainer.frame = CGRectMake(headerTextPadding,
                                                         currentLabelY,
                                                         detailsImageSize,
                                                         detailsImageSize);
        self.pCategoriesIconContainer.hidden = false;
        
        self.pCategoriesContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                                   currentLabelY,
                                                   m_labelsSectionWidth - (2 * headerTextPadding) - (detailsImageSize + detailsImageToTextMargin),
                                                   32.f);
        
        std::vector<std::string> tagVector = m_model.GetHumanReadableTags();
        std::string tags = "";
        for(int i = 0; i < tagVector.size(); ++i)
        {
            tags += tagVector[i];
        }
        self.pCategoriesContent.text = [NSString stringWithUTF8String:tags.c_str()];
        
        self.pCategoriesContent.numberOfLines = 0;
        self.pCategoriesContent.adjustsFontSizeToFitWidth = NO;
        self.pCategoriesContent.lineBreakMode = NSLineBreakByWordWrapping;
        
        self.pCategoriesContent.hidden = false;
        [self.pCategoriesContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pCategoriesContent.frame.size.height;
    }
    
    if(!m_workingGroupModel.GetDescription().empty())
    {
        self.pDescriptionDivider.frame = CGRectMake(0,
                                                    currentLabelY,
                                                    m_labelsSectionWidth,
                                                    dividerHeight);
        self.pDescriptionDivider.hidden = false;
        
        currentLabelY += labelYSpacing + dividerHeight;
        
        self.pDescriptionIconContainer.frame = CGRectMake(headerTextPadding,
                                                          currentLabelY,
                                                          detailsImageSize,
                                                          detailsImageSize);
        self.pDescriptionIconContainer.hidden = false;
        
        self.pDescriptionContent.frame = CGRectMake(headerTextPadding + detailsImageSize + detailsImageToTextMargin,
                                                    currentLabelY,
                                                    m_labelsSectionWidth - (2 * headerTextPadding) - (detailsImageSize + detailsImageToTextMargin),
                                                    32.f);
        self.pDescriptionContent.text = [NSString stringWithUTF8String:m_workingGroupModel.GetDescription().c_str()];
        
        self.pDescriptionContent.numberOfLines = 0;
        self.pDescriptionContent.adjustsFontSizeToFitWidth = NO;
        self.pDescriptionContent.lineBreakMode = NSLineBreakByWordWrapping;
        
        self.pDescriptionContent.hidden = false;
        [self.pDescriptionContent sizeToFit];
        
        currentLabelY += labelYSpacing + self.pDescriptionContent.frame.size.height;
    }
    
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    m_workingGroupModel = ExampleApp::Search::Swallow::SdkModel::SearchParser::TransformToSwallowWorkingGroupResult(m_model);
    
    self.pTitleLabel.text = [NSString stringWithUTF8String:pModel->GetTitle().c_str()];
    
    [self.pCategoryIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string tagIcon = ExampleApp::Helpers::IconResources::GetSmallIconForTag(pModel->GetPrimaryTag());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategoryIconContainer, tagIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pImageDivider.hidden = true;
    self.pPreviewImage.hidden = true;
    self.pCategoriesDivider.hidden = true;
    self.pCategoriesIconContainer.hidden = true;
    self.pCategoriesContent.hidden = true;
    self.pDescriptionDivider.hidden = true;
    self.pDescriptionIconContainer.hidden = true;
    self.pDescriptionContent.hidden = true;
    
    [self performDynamicContentLayout];
    
    if(!m_workingGroupModel.GetImageUrl().empty())
    {
        [self.pPreviewImage setImage:self.pPlaceholderImage];
        [self.pPreviewImageSpinner startAnimating];
    }
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    if(url == m_workingGroupModel.GetImageUrl())
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
    [m_pController setView:self];
    if(self.alpha == 1.f)
    {
        return;
    }
    
    [self animateToAlpha:1.f];
}

- (void) setFullyInactive
{
    [m_pController setView:nil];
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

- (void) handleClosedButtonSelected
{
    m_pInterop->HandleCloseClicked();
}

@end
