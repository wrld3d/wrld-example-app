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
#include "SwallowPersonSearchResultPoiView.h"
#include "App.h"
#include "SwallowSearchParser.h"
#import "UIButton+DefaultStates.h"

@interface SwallowPersonSearchResultPoiView()<UIGestureRecognizerDelegate>
{
}
@end

@implementation SwallowPersonSearchResultPoiView

- (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop
{
    self = [super init];
    
    if(self)
    {
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
        
        self.pJobTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pJobTitleLabel];
        
        self.pWorkingGroupLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pWorkingGroupLabel];
        
        self.pOfficeLocationLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pOfficeLocationLabel];
        
        self.pDeskCodeLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pLabelsContainer addSubview: self.pDeskCodeLabel];
        
        self.pDescriptionIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionIconContainer.image = [UIImage imageNamed:@"detail_icon_description"];
        [self.pLabelsContainer addSubview: self.pDescriptionIconContainer];
        
        self.pDescriptionDivider = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionDivider.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pDescriptionDivider];
        
        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];
        
        self.pCategoryIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoryIconContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pHeadlineContainer addSubview: self.pCategoryIconContainer];
        
        self.pProfileImageContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelsContainer addSubview: self.pProfileImageContainer];
        
        self.pProfileImageActivityIndicator = [[[UIActivityIndicatorView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pProfileImageActivityIndicator.activityIndicatorViewStyle = UIActivityIndicatorViewStyleGray;
        [self.pProfileImageContainer addSubview:self.pProfileImageActivityIndicator];
        
        self.pPlaceholderImage = [UIImage imageNamed: @"poi_placeholder.png"];
        
        self.pImageDivider = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pImageDivider.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview:self.pImageDivider];
        
        self.pNameLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextCopyColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        self.pNameLabel.textColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pHeadlineContainer addSubview: self.pNameLabel];
        
        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setDefaultStatesWithImageNames:@"exit_blue_x_button" :@"exit_dark_blue_x_button"];
        [self.pCloseButton addTarget:self action:@selector(handleClosedButtonSelected) forControlEvents:UIControlEventTouchUpInside];
        [self.pHeadlineContainer addSubview: self.pCloseButton];
        
        self.pCategoriesIconContainer = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCategoriesIconContainer.image = [UIImage imageNamed:@"poi_tag"];
        [self.pLabelsContainer addSubview: self.pCategoriesIconContainer];
        
        self.pCategoriesContent = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextLinkColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        self.pCategoriesContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
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
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabel release];
    
    [self.pProfileImageActivityIndicator removeFromSuperview];
    [self.pProfileImageActivityIndicator release];
    
    [self.pPlaceholderImage release];
    
    [self.pProfileImageContainer removeFromSuperview];
    [self.pProfileImageContainer release];
    
    [self.pImageDivider removeFromSuperview];
    [self.pImageDivider release];
    
    [self.pCategoryIconContainer removeFromSuperview];
    [self.pCategoryIconContainer release];
    
    [self.pHeadlineContainer removeFromSuperview];
    [self.pHeadlineContainer release];
    
    [self.pCategoriesContent removeFromSuperview];
    [self.pCategoriesContent release];
    
    [self.pCategoriesIconContainer removeFromSuperview];
    [self.pCategoriesIconContainer release];
    
    [self.pCategoriesDivider removeFromSuperview];
    [self.pCategoriesDivider release];
    
    [self.pDescriptionIconContainer removeFromSuperview];
    [self.pDescriptionIconContainer release];
    
    [self.pDescriptionDivider removeFromSuperview];
    [self.pDescriptionDivider release];
    
    [self.pDeskCodeLabel removeFromSuperview];
    [self.pDeskCodeLabel release];
    
    [self.pOfficeLocationLabel removeFromSuperview];
    [self.pOfficeLocationLabel release];
    
    [self.pWorkingGroupLabel removeFromSuperview];
    [self.pWorkingGroupLabel release];
    
    [self.pJobTitleLabel removeFromSuperview];
    [self.pJobTitleLabel release];
    
    [self.pLabelsContainer removeFromSuperview];
    [self.pLabelsContainer release];
    
    [self.pContentContainer removeFromSuperview];
    [self.pContentContainer release];
    
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer release];
    
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
    
    const float categoryIconContainerLeftMargin = 5.0f;
    self.pCategoryIconContainer.frame = CGRectMake(categoryIconContainerLeftMargin, 0.f, headlineHeight, headlineHeight);
    
    const float titlePadding = 10.0f;
    self.pNameLabel.frame = CGRectMake(headlineHeight + titlePadding,
                                        0.f,
                                        mainWindowWidth - (headlineHeight + titlePadding) - closeButtonSectionHeight - sideMargin,
                                        headlineHeight);
    self.pNameLabel.font = [UIFont systemFontOfSize:24.0f];
    
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
    
    float currentLabelY = 0.f;
    const CGFloat imagePadding = 10.0f;
    
    self.pImageDivider.frame = CGRectMake(0,
                                          currentLabelY,
                                          m_labelsSectionWidth,
                                          dividerHeight);
    
    currentLabelY += dividerHeight + imagePadding;
    
    self.pProfileImageContainer.frame = CGRectMake(0.f, currentLabelY, m_imageWidth, m_imageHeight);
    
    self.pProfileImageActivityIndicator.center = CGPointMake(m_imageWidth / 2.0f, m_imageHeight / 2.0f);
    
    currentLabelY += (m_imageHeight + imagePadding);
    
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
    
    if(m_swallowPersonModel.GetJobTitle() != ""
       || m_swallowPersonModel.GetWorkingGroup() != ""
       || m_swallowPersonModel.GetOfficeLocation() != ""
       || m_swallowPersonModel.GetDeskCode() != "")
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
        
        const float labelLeftMargin = headerTextPadding + detailsImageSize + detailsImageToTextMargin;
        const float labelWidth = m_labelsSectionWidth - labelLeftMargin - headerTextPadding;
        const float labelHeight = 18.0f;
        
        if(m_swallowPersonModel.GetJobTitle() != "")
        {
            self.pJobTitleLabel.frame = CGRectMake(labelLeftMargin,
                                                   currentLabelY,
                                                   labelWidth,
                                                   labelHeight);
            self.pJobTitleLabel.hidden = false;
            currentLabelY += labelHeight + labelYSpacing;
        }
        
        if(m_swallowPersonModel.GetWorkingGroup() != "")
        {
            self.pWorkingGroupLabel.frame = CGRectMake(labelLeftMargin,
                                                       currentLabelY,
                                                       labelWidth,
                                                       labelHeight);
            self.pWorkingGroupLabel.hidden = false;
            currentLabelY += labelHeight + labelYSpacing;
        }
        
        if(m_swallowPersonModel.GetOfficeLocation() != "")
        {
            self.pOfficeLocationLabel.frame = CGRectMake(labelLeftMargin,
                                                         currentLabelY,
                                                         labelWidth,
                                                         labelHeight);
            self.pOfficeLocationLabel.hidden = false;
            currentLabelY += labelHeight + labelYSpacing;
        }
        
        if(m_swallowPersonModel.GetDeskCode() != "")
        {
            self.pDeskCodeLabel.frame = CGRectMake(labelLeftMargin,
                                                   currentLabelY,
                                                   labelWidth,
                                                   labelHeight);
            self.pDeskCodeLabel.hidden = false;
            currentLabelY += labelHeight + labelYSpacing;
        }
        
        [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, currentLabelY)];
    }
}

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel
{
    Eegeo_ASSERT(pModel != NULL);
    
    m_model = *pModel;
    
    m_swallowPersonModel = ExampleApp::Search::Swallow::SdkModel::SearchParser::TransformToSwallowPersonResult(m_model);
    
    [self.pProfileImageActivityIndicator startAnimating];
    
    [self.pCategoryIconContainer.subviews makeObjectsPerformSelector: @selector(removeFromSuperview)];
    std::string tagIcon = ExampleApp::Helpers::IconResources::GetSmallIconForTag(pModel->GetPrimaryTag());
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pCategoryIconContainer, tagIcon, ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.pNameLabel.text = [NSString stringWithUTF8String:m_swallowPersonModel.GetName().c_str()];
    
    const std::string jobTitlePrefix = "Job Title: ";
    const std::string workingGroupPrefix = "Working Group: ";
    const std::string officeLocationPrefix = "Location: ";
    const std::string deskCodePrefix = "Desk: ";
    
    self.pJobTitleLabel.text = [NSString stringWithUTF8String:(jobTitlePrefix + m_swallowPersonModel.GetJobTitle()).c_str()];
    self.pWorkingGroupLabel.text = [NSString stringWithUTF8String:(workingGroupPrefix + m_swallowPersonModel.GetWorkingGroup()).c_str()];
    self.pOfficeLocationLabel.text = [NSString stringWithUTF8String:(officeLocationPrefix + m_swallowPersonModel.GetOfficeLocation()).c_str()];
    self.pDeskCodeLabel.text = [NSString stringWithUTF8String:(deskCodePrefix + m_swallowPersonModel.GetDeskCode()).c_str()];
    
    [self.pLabelsContainer setContentOffset:CGPointMake(0,0) animated:NO];
    
    [self.pProfileImageContainer setImage:self.pPlaceholderImage];
    
    self.pCategoriesDivider.hidden = true;
    self.pCategoriesIconContainer.hidden = true;
    self.pCategoriesContent.hidden = true;
    self.pDescriptionDivider.hidden = true;
    self.pDescriptionIconContainer.hidden = true;
    self.pJobTitleLabel.hidden = true;
    self.pWorkingGroupLabel.hidden = true;
    self.pOfficeLocationLabel.hidden = true;
    self.pDeskCodeLabel.hidden = true;
    
    [self performDynamicContentLayout];
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
//    if(url == m_swallowPersonModel.GetImageUrl())
//    {
        [self.pProfileImageActivityIndicator stopAnimating];
        
        if(success)
        {
            NSData* imageData = [NSData dataWithBytes:&bytes->at(0) length:bytes->size()];
            UIImage *image = [UIImage imageWithData:imageData];
            [self.pProfileImageContainer setImage:image];
            
            [self.pProfileImageContainer.layer removeAllAnimations];
            self.pProfileImageContainer.hidden = false;
            
            [self performDynamicContentLayout];
        }
//    }
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

- (void) handleClosedButtonSelected
{
    m_pInterop->HandleCloseClicked();
}

@end
