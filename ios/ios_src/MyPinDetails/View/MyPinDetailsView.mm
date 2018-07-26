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
        
        self.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        
        [self setupHeader];
        [self setupBody];
        [self setupFooter];
        
        
        [self setTouchExclusivity: self];
    }

    return self;
}


-(void) setupHeader{
    self.pHeaderView = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    [self addSubview:self.pHeaderView];
    
    self.pPinIconImageView = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"ReportPinIcon"]] autorelease];
    [self.pHeaderView addSubview:self.pPinIconImageView];
    
    self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    self.pTitleLabel.textAlignment = NSTextAlignmentLeft;
    self.pTitleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
    
    self.pTitleLabel.font = [UIFont systemFontOfSize:24.f];
    [self.pHeaderView addSubview:self.pTitleLabel];
    
    self.pCloseButton = [[[UIButton alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    
    [self.pCloseButton setDefaultStatesWithImageNames:@"button_close_off" :@"button_close_on"];
    
    [self.pCloseButton addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
    
    [self.pHeaderView addSubview:self.pPinIconImageView];
    [self.pHeaderView addSubview:self.pCloseButton];
    
    self.pHeaderSeparator = [[[UIView alloc] init] autorelease];
    self.pHeaderSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
    [self addSubview:self.pHeaderSeparator];
}


-(void) setupBody{
    
    self.pContentScrollView = [[[UIScrollView alloc] init] autorelease];
    self.pContentScrollView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
    [self addSubview:self.pContentScrollView];
    
    self.pContentView = [[[UIView alloc] init] autorelease];
    self.pContentView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
    [self.pContentScrollView addSubview:self.pContentView];
    
    self.pPoiImageView = [[[UIImageView alloc] init] autorelease];
    [self.pContentView addSubview:self.pPoiImageView];
    
    self.pContentSeperator = [[[UIView alloc] init] autorelease];
    self.pContentSeperator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
    [self.pContentView addSubview:self.pContentSeperator];
    
    self.pDescriptionTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    self.pDescriptionTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
    
    self.pDescriptionTitleLabel.text = @"Description";
    
    [self.pContentView addSubview: self.pDescriptionTitleLabel];
    
    self.pDescriptionContentLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    self.pDescriptionContentLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
    self.pDescriptionContentLabel.text  = @"";
    
    [self.pContentView addSubview: self.pDescriptionContentLabel];
    
}

-(void)setupFooter{
    
    self.pFooterContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
    self.pFooterContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::TableSubCellColor;
    [self addSubview: self.pFooterContainer];
    
    self.pFooterSeperator= [[[UIView alloc] init] autorelease];
    self.pFooterSeperator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
    [self.pFooterContainer addSubview:self.pFooterSeperator];
    
    self.pDeleteButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
    [self.pFooterContainer addSubview: self.pDeleteButton];
    
    [self.pDeleteButton setDefaultStatesWithNormalImageName:@"BinButton"
                                          highlightImageName:@"BinButton_Down"
                                       normalBackgroundColor:UIColor.clearColor
                                    highlightBackgroundColor:ExampleApp::Helpers::ColorPalette::UiBorderColor];
    
    [self.pDeleteButton addTarget:self action:@selector(onRemovePinButtonPressed) forControlEvents:UIControlEventTouchUpInside];
    
}

- (void)dealloc
{
 
    [self.pCloseButton removeFromSuperview];
    [self.pCloseButton release];
    
    [self.pPinIconImageView removeFromSuperview];
    [self.pPinIconImageView release];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pHeaderSeparator removeFromSuperview];
    [self.pHeaderSeparator release];
    
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    
    [self.pPoiImageView removeFromSuperview];
    [self.pPoiImageView release];
    
    [self.pContentSeperator  removeFromSuperview];
    [self.pContentSeperator release];
    
    [self.pDescriptionTitleLabel removeFromSuperview];
    [self.pDescriptionTitleLabel release];
    
    [self.pDescriptionContentLabel removeFromSuperview];
    [self.pDescriptionContentLabel release];
    
    [self.pContentView removeFromSuperview];
    [self.pContentView release];
    
    [self.pContentScrollView removeFromSuperview];
    [self.pContentScrollView release];
    
    [self.pFooterSeperator removeFromSuperview];
    [self.pFooterSeperator release];
    
    [self.pDeleteButton removeFromSuperview];
    [self.pDeleteButton release];
    
    [self.pFooterContainer removeFromSuperview];
    [self.pFooterContainer release];

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
   
    const CGFloat boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const CGFloat boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const CGFloat boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    const CGFloat boundsOccupyHeightMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f));
    const CGFloat mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    const CGFloat mainWindowHeightMax = boundsHeight * boundsOccupyHeightMultiplier;
    
    
    UIEdgeInsets outerMargin = UIEdgeInsetsMake(8.0, 8.0, 8.0, 8.0);
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(20.0, 20.0, 16.0, 16.0);
    
    CGFloat outerMarginWidth = mainWindowWidth - outerMargin.left - outerMargin.right;
    CGFloat innerMarginWidth = mainWindowWidth - innerMargin.left - innerMargin.right;
    
    CGFloat headerHeight = 38;
    
    self.pHeaderView.frame = CGRectMake(innerMargin.left, outerMargin.top, innerMarginWidth,headerHeight );
    
    self.pPinIconImageView.frame = CGRectMake( -8.0, 0.0, 36, 36);
    [self.pPinIconImageView sizeToFit];
    
    CGFloat titleOffsetX = self.pPinIconImageView.frame.origin.x + self.pPinIconImageView.frame.size.width;
    CGFloat titleOffsetY = 4.0;
    self.pTitleLabel.frame = CGRectMake(titleOffsetX,titleOffsetY, innerMarginWidth - headerHeight-titleOffsetX,headerHeight);
    self.pCloseButton.frame = CGRectMake(innerMarginWidth - headerHeight,0.0, headerHeight,headerHeight);
    
    self.pHeaderSeparator.frame = CGRectMake(outerMargin.left, self.pHeaderView.frame.origin.y + self.pHeaderView.frame.size.height + outerMargin.top, outerMarginWidth,1.0);
    
    CGFloat scrollViewyOffset = self.pHeaderSeparator.frame.origin.y + self.pHeaderSeparator.frame.size.height + outerMargin.top;
    CGFloat footerHeight = 66;
    
    CGFloat contentHeight = 0.0;
    CGSize imageSize = self.pPoiImageView.image.size;
    CGFloat aspectRatio = 0.0;
    
    if (imageSize.width > 0.0){
        aspectRatio = imageSize.height/imageSize.width;
    }
    
    self.pPoiImageView.frame = CGRectMake(outerMargin.left,
                                          0.0 ,
                                          outerMarginWidth,
                                          outerMarginWidth*aspectRatio);
    
    contentHeight = outerMargin.top + self.pPoiImageView.frame.origin.y + self.pPoiImageView.frame.size.height;
    
    if(!self.pContentSeperator.hidden) {
        self.pContentSeperator.frame = CGRectMake(outerMargin.left,
                                                 contentHeight,
                                                 outerMarginWidth,
                                                 1);
        
        contentHeight += 2;
        contentHeight += outerMargin.top;
    }
    
    self.pDescriptionTitleLabel.frame = CGRectMake(innerMargin.left,
                                                  contentHeight,
                                                  innerMarginWidth,
                                                  20);
    
    contentHeight += self.pDescriptionTitleLabel.frame.size.height;
    
    self.pDescriptionContentLabel.frame = CGRectMake(innerMargin.left,
                                                   contentHeight,
                                                   innerMarginWidth,
                                                   200);
    
    self.pDescriptionContentLabel.numberOfLines = 0;
    
    [self.pDescriptionContentLabel sizeToFit];
    
    contentHeight += self.pDescriptionContentLabel.frame.size.height;
    contentHeight += innerMargin.top + innerMargin.bottom;
    
    self.pContentView.frame = CGRectMake(0.0, 0.0,mainWindowWidth,contentHeight);
    
    self.pContentScrollView.contentSize = self.pContentView.frame.size;
    
    
    CGFloat mainWindowHeight = MIN(scrollViewyOffset + contentHeight + footerHeight , mainWindowHeightMax);
    CGFloat scrollViewHeight = mainWindowHeight - scrollViewyOffset - footerHeight;
    
    
    self.pContentScrollView.frame = CGRectMake(0.0,
                                               scrollViewyOffset,
                                               mainWindowWidth,
                                               scrollViewHeight);
    
    const CGFloat mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const CGFloat mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pFooterContainer.frame = CGRectMake(0.0,
                                             self.pContentScrollView.frame.origin.y + self.pContentScrollView.frame.size.height,
                                             mainWindowWidth,
                                             footerHeight);
    
    self.pFooterSeperator.frame = CGRectMake(0.0,0.0,mainWindowWidth,1.0);
    
    CGFloat buttonHeight = self.pFooterContainer.frame.size.height - 1;
    CGFloat buttonWidth = buttonHeight;
    
    self.pDeleteButton.frame = CGRectMake(mainWindowWidth - buttonWidth , 1, buttonWidth, buttonHeight);
    
 
}

- (void) setContent:(const std::string&)title
         :(const std::string&)description
         :(const std::string&)imagePath
{
    self.pTitleLabel.text = [NSString stringWithUTF8String:title.c_str()];
    self.pDescriptionContentLabel.text = [NSString stringWithUTF8String: description.c_str()];

    m_hasImage = NO;

    if(!imagePath.empty())
    {
        NSArray* libraryPaths = NSSearchPathForDirectoriesInDomains(NSLibraryDirectory, NSUserDomainMask, YES);
        NSString* libraryDirectory = [libraryPaths objectAtIndex:0];
        NSString* imageFilename = [NSString stringWithUTF8String: imagePath.c_str()];
        NSString* fullPathToImage  = [libraryDirectory stringByAppendingPathComponent: imageFilename];
        UIImage *image = [UIImage imageWithContentsOfFile: fullPathToImage];
        self.pPoiImageView.image = image;
        Eegeo::TtyHandler::TtyEnabled = true;
        Eegeo_TTY("Image width is %f height is %f", self.pPoiImageView.image.size.width, self.pPoiImageView.image.size.height);
        
        if(image) {
            m_hasImage = YES;
        }
        
    }
    else {
        self.pPoiImageView.image = nil;
    }
    
    self.pContentSeperator.hidden = !m_hasImage;
   
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

- (void) onCloseButtonTapped
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
}

@end
