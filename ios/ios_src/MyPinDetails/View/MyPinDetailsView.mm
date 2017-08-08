// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "MyPinDetailsView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#include "MyPinDetailsViewInterop.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@implementation MyPinDetailsView

- (id)initWithParams:(float)screenWidth :(float)screenHeight
{
    self = [super init];

    if(self)
    {
        m_pInterop = new ExampleApp::MyPinDetails::View::MyPinDetailsViewInterop(self);
        m_pController = [UIViewController alloc];
        [m_pController setView:self];

        self.alpha = 0.f;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_labelsSectionWidth = 0.f;
        m_maxContentSize = 0.f;
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview: self.pControlContainer];

        self.pCloseButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pCloseButtonContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pControlContainer addSubview: self.pCloseButtonContainer];

        self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
        [self.pCloseButton addTarget:self action:@selector(onCloseButtonPressed) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pCloseButton];

        self.pRemovePinButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pRemovePinButton setDefaultStatesWithImageNames:@"button_remove_pin_off" :@"button_remove_pin_on"];
        [self.pRemovePinButton addTarget:self action:@selector(onRemovePinButtonPressed) forControlEvents:UIControlEventTouchUpInside];
        [self.pCloseButtonContainer addSubview: self.pRemovePinButton];

        self.pContentContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pContentContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pContentContainer];

        self.pHeadlineContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pHeadlineContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pHeadlineContainer];

        self.pIconContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pHeadlineContainer addSubview: self.pIconContainer];

        self.pTitleLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextTitleColor :ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pHeadlineContainer addSubview: self.pTitleLabel];

        self.pLabelsContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pLabelsContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentContainer addSubview: self.pLabelsContainer];

        self.pDescriptionHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        [self.pLabelsContainer addSubview: self.pDescriptionHeaderContainer];

        self.pDescriptionHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextHeaderColor :ExampleApp::Helpers::ColorPalette::UiBorderColor];
        [self.pDescriptionHeaderContainer addSubview: self.pDescriptionHeaderLabel];

        self.pDescriptionContent = [[[UILabel alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDescriptionContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pLabelsContainer addSubview: self.pDescriptionContent];

        self.pImageHeaderContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pImageHeaderContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;

        [self.pLabelsContainer addSubview: self.pImageHeaderContainer];

        self.pImageHeaderLabel = [self createLabel :ExampleApp::Helpers::ColorPalette::UiTextHeaderColor :ExampleApp::Helpers::ColorPalette::UiBorderColor];
        [self.pImageHeaderContainer addSubview: self.pImageHeaderLabel];

        self.pImageContent = [[[UIImageView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        self.pImageContent.image = ExampleApp::Helpers::ImageHelpers::LoadImage(@"image_blank");

        [self.pLabelsContainer addSubview: self.pImageContent];
        
        [self setTouchExclusivity: self];
    }

    return self;
}

- (void)dealloc
{
    [self.pRemovePinButton removeFromSuperview];
    [self.pRemovePinButton release];

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

    [self.pIconContainer removeFromSuperview];
    [self.pIconContainer release];

    [self.pDescriptionHeaderLabel removeFromSuperview];
    [self.pDescriptionHeaderLabel release];

    [self.pDescriptionHeaderContainer removeFromSuperview];
    [self.pDescriptionHeaderContainer release];

    [self.pDescriptionContent removeFromSuperview];
    [self.pDescriptionContent release];

    [self.pImageHeaderLabel removeFromSuperview];
    [self.pImageHeaderLabel release];

    [self.pImageHeaderContainer removeFromSuperview];
    [self.pImageHeaderContainer release];

    [self.pImageContent removeFromSuperview];
    [self.pImageContent release];

    [m_pController release];
    delete m_pInterop;

    [self removeFromSuperview];
    [super dealloc];
}

- (ExampleApp::MyPinDetails::View::MyPinDetailsViewInterop*) getInterop
{
    return m_pInterop;
}

- (void)layoutSubviews
{
    self.alpha = 0.f;

    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const float boundsOccupyMultiplier = useFullScreenSize ? 0.9f : 0.5f;
    const float mainWindowWidth = boundsWidth * boundsOccupyMultiplier;
    const float mainWindowHeight = boundsHeight * boundsOccupyMultiplier;
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

    const float labelsSectionOffsetX = 12.f;
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

    self.pRemovePinButton.frame = CGRectMake(0.f,
                                  0.f,
                                  closeButtonSectionHeight,
                                  closeButtonSectionHeight);

    const float iconImageSize = 33.f;
    self.pIconContainer.frame = CGRectMake(labelsSectionOffsetX, labelsSectionOffsetX, iconImageSize, iconImageSize);
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pIconContainer, "button_create_poi_off", ExampleApp::Helpers::ImageHelpers::Centre);

    const float titlePadding = 23.0f;
    self.pTitleLabel.frame = CGRectMake(iconImageSize + titlePadding,
                                        0.f,
                                        mainWindowWidth - headlineHeight - titlePadding,
                                        headlineHeight);
    self.pTitleLabel.font = [UIFont systemFontOfSize:24.0f];

    m_headerLabelHeight = 20.f;
    m_labelYSpacing = 7.f;
    float currentLabelY = m_labelYSpacing;

    m_headerTextPadding = 3.0f;
    self.pDescriptionHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, m_headerLabelHeight + 2 * m_headerTextPadding);

    self.pDescriptionHeaderLabel.frame = CGRectMake(m_headerTextPadding, m_headerTextPadding, m_labelsSectionWidth - m_headerTextPadding, m_headerLabelHeight);
    self.pDescriptionHeaderLabel.text = @"Description";
    currentLabelY += m_labelYSpacing + self.pDescriptionHeaderContainer.frame.size.height;

    m_descriptionContentY = currentLabelY;
    self.pDescriptionContent.font = [UIFont systemFontOfSize: 16.f];
    self.pDescriptionContent.frame = CGRectMake(m_headerTextPadding, m_descriptionContentY, m_labelsSectionWidth - m_headerTextPadding, 0);
    self.pDescriptionContent.lineBreakMode = NSLineBreakByWordWrapping;
    self.pDescriptionContent.numberOfLines = 0;
    [self.pDescriptionContent sizeToFit];

    currentLabelY += m_labelYSpacing + self.pDescriptionContent.frame.size.height;


    self.pImageHeaderContainer.hidden = true;
    self.pImageContent.hidden = true;
    if(m_hasImage)
    {
        self.pImageHeaderContainer.hidden = false;
        self.pImageContent.hidden = false;

        self.pImageHeaderContainer.frame = CGRectMake(0.f, currentLabelY, m_labelsSectionWidth, m_headerLabelHeight + 2 * m_headerTextPadding);

        self.pImageHeaderLabel.frame = CGRectMake(m_headerTextPadding, m_headerTextPadding, m_labelsSectionWidth - m_headerTextPadding, m_headerLabelHeight);
        self.pImageHeaderLabel.text = @"Image";
        currentLabelY += m_labelYSpacing + self.pImageHeaderContainer.frame.size.height;

        m_maxImageWidth = m_labelsSectionWidth - m_headerTextPadding;

        const CGFloat widthRatio = m_maxImageWidth/self.pImageContent.image.size.width;
        const CGFloat height = self.pImageContent.image.size.height * widthRatio;

        self.pImageContent.frame = CGRectMake(0, currentLabelY, m_maxImageWidth, height);

        currentLabelY += m_labelYSpacing + height;
        m_scrollContentBottomMargin = 0;
    }

    m_scrollContentWidth = m_labelsSectionWidth;

    m_maxContentSize = currentLabelY;
    [self.pLabelsContainer setContentSize:CGSizeMake(m_labelsSectionWidth, m_maxContentSize)];
}

- (void) setContent:(const std::string&)title :(const std::string&)description :(const std::string&)imagePath
{
    self.pTitleLabel.text = [NSString stringWithUTF8String:title.c_str()];
    self.pDescriptionContent.text = [NSString stringWithUTF8String: description.c_str()];

    BOOL hideDescription = !(self.pDescriptionContent.text != nil && self.pDescriptionContent.text.length > 0);
    self.pDescriptionContent.hidden = hideDescription;
    self.pDescriptionHeaderContainer.hidden = hideDescription;

    m_hasImage = NO;

    if(!imagePath.empty())
    {
        NSArray* libraryPaths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
        NSString* libraryDirectory = [libraryPaths objectAtIndex:0];
        NSString* imageFilename = [NSString stringWithUTF8String: imagePath.c_str()];
        NSString* fullPathToImage  = [libraryDirectory stringByAppendingPathComponent: imageFilename];

        self.pImageContent.image = [UIImage imageWithContentsOfFile: fullPathToImage];
        Eegeo::TtyHandler::TtyEnabled = true;
        Eegeo_TTY("Image width is %f height is %f", self.pImageContent.image.size.width, self.pImageContent.image.size.height);

        m_hasImage = YES;
    }

    self.pLabelsContainer.contentOffset = CGPointMake(0, 0);

    [self setNeedsLayout];
    [self layoutIfNeeded];
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

- (UILabel*) createLabel:(UIColor*)textColor :(UIColor*)backgroundColor
{
    UILabel* pLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    pLabel.textColor = textColor;
    pLabel.backgroundColor = backgroundColor;
    pLabel.textAlignment = NSTextAlignmentLeft;
    return pLabel;
}

- (void) onCloseButtonPressed
{
    m_pInterop->OnDismiss();
}

- (void) onRemovePinButtonPressed
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
            m_pInterop->OnRemove();
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
        [alert release];
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    alertView.delegate = nil;

    if (buttonIndex == 1)
    {
        m_pInterop->OnRemove();
    }
}

@end
