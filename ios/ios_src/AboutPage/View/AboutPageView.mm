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

        self.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        
        self.pHeaderView = [[[HeaderView alloc] initWithWidth:200 title:@"About"] autorelease];
        [self addSubview:self.pHeaderView];
        
        [self.pHeaderView addTarget:self action:@selector(onCloseButtonTapped) forControlEvents:UIControlEventTouchUpInside];
        
        self.pContentScrollView = [[[UIScrollView alloc] init] autorelease];
        self.pContentScrollView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self addSubview:self.pContentScrollView];
        
        self.pContentView = [[[UIView alloc] init] autorelease];
        self.pContentView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pContentScrollView addSubview:self.pContentView];
        
        self.pSwallowLogoImage = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"swallow_logo_about")] autorelease];
        [self.pContentView addSubview:self.pSwallowLogoImage];
        
        self.pTextContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTextContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pContentView addSubview: self.pTextContent];
        
        self.pContentSeperator = [[[UIView alloc] init] autorelease];
        self.pContentSeperator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
        [self.pContentView addSubview:self.pContentSeperator];
        
        self.pDevelopedByLabel  = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDevelopedByLabel.font = [UIFont systemFontOfSize:16.f];
        self.pDevelopedByLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pDevelopedByLabel.text = @"Developed by Bloomberg L.P and";
        [self.pContentView addSubview:self.pDevelopedByLabel];
        
        self.pWrldLogoImage = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"wrld_logo_about")] autorelease];
        self.pWrldLogoImage.userInteractionEnabled = true;
        UILongPressGestureRecognizer *longPress = [[UILongPressGestureRecognizer alloc] initWithTarget:self action:@selector(showHiddenText:)];
        [self.pWrldLogoImage addGestureRecognizer:longPress];
        [longPress autorelease];
        [self.pContentView addSubview:self.pWrldLogoImage];
        
        self.pLegalLink = [[[UIButton alloc] init] autorelease];
        [self.pLegalLink addTarget:self action:@selector(legalClickHandler:) forControlEvents:UIControlEventTouchUpInside];
        [self.pLegalLink setTitle:@"Legal" forState:UIControlStateNormal];
        [self.pLegalLink setTitleColor:ExampleApp::Helpers::ColorPalette::UiTextTitleColor forState:UIControlStateNormal];
        self.pLegalLink.titleLabel.font = [UIFont boldSystemFontOfSize:16.f];
        self.pLegalLink.titleLabel.textAlignment = NSTextAlignmentLeft;
    
        [self.pContentView addSubview:self.pLegalLink];
        
    }

    return self;
}

- (void)dealloc
{

    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    

    [self.pSwallowLogoImage removeFromSuperview];
    [self.pSwallowLogoImage release];

    [self.pTextContent removeFromSuperview];
    [self.pTextContent release];

    [self.pContentSeperator removeFromSuperview];
    [self.pContentSeperator release];
    
    [self.pDevelopedByLabel removeFromSuperview];
    [self.pDevelopedByLabel release];

    [self.pWrldLogoImage removeFromSuperview];
    [self.pWrldLogoImage release];

    [self.pLegalLink removeFromSuperview];
    [self.pLegalLink release];

    
    [self.pContentView removeFromSuperview];
    [self.pContentView release];
    
    [self.pContentScrollView removeFromSuperview];
    [self.pContentScrollView release];
    
    [self removeFromSuperview];
    [super dealloc];
    Eegeo_DELETE m_pInterop;
}

- (void)layoutSubviews
{
    const CGFloat boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const CGFloat boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const bool useFullScreenSize = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    const CGFloat boundsOccupyWidthMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f) * 0.6f);
    const CGFloat boundsOccupyHeightMultiplier = useFullScreenSize ? 0.9f : ((2.f/3.f));
    const CGFloat mainWindowWidth = boundsWidth * boundsOccupyWidthMultiplier;
    const CGFloat mainWindowHeight = boundsHeight * boundsOccupyHeightMultiplier;
    const CGFloat mainWindowX = (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const CGFloat mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    self.pHeaderView.width = mainWindowWidth;
    [self.pHeaderView layoutIfNeeded];
    CGFloat seperatorMargin = self.pHeaderView.pHeaderSeparator.frame.origin.x;
    UIEdgeInsets outerMargin = UIEdgeInsetsMake(seperatorMargin, seperatorMargin, seperatorMargin, seperatorMargin);
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin);
    CGFloat innerMarginWidth = mainWindowWidth - innerMargin.left - innerMargin.right;
    CGFloat outerMarginWidth = mainWindowWidth - outerMargin.left - outerMargin.right;
    CGFloat contentY = self.pHeaderView.frame.origin.y +  self.pHeaderView.frame.size.height;

    self.pContentScrollView.frame = CGRectMake(0.0,
                                               contentY,
                                               mainWindowWidth,
                                               mainWindowHeight - contentY);
    
    self.pSwallowLogoImage.frame = CGRectMake(innerMargin.left,
                                              innerMargin.top,
                                              self.pSwallowLogoImage.image.size.width,
                                              self.pSwallowLogoImage.image.size.height);
    
    const CGFloat textContentY =  self.pSwallowLogoImage.image.size.height + innerMargin.top + innerMargin.bottom;
   
    self.pTextContent.frame = CGRectMake(innerMargin.left, textContentY, innerMarginWidth, 0.0);
    self.pTextContent.numberOfLines = 0;
    self.pTextContent.adjustsFontSizeToFitWidth = NO;
    self.pTextContent.font = [UIFont systemFontOfSize:14.5f];
    self.pTextContent.lineBreakMode = NSLineBreakByWordWrapping;
    
    [self.pTextContent sizeToFit];
    
    CGFloat contentSeperatorY = self.pTextContent.frame.origin.y + self.pTextContent.frame.size.height + innerMargin.top;
    self.pContentSeperator.frame = CGRectMake(outerMargin.left, contentSeperatorY, outerMarginWidth,2.0);
    
    const CGFloat developedByY = self.pContentSeperator.frame.origin.y + self.pContentSeperator.frame.size.height + innerMargin.top;
    const CGFloat developedByHeight = 16.f;
    
    self.pDevelopedByLabel.frame = CGRectMake(innerMargin.left, developedByY, innerMarginWidth, developedByHeight);
    [self.pDevelopedByLabel sizeToFit];
    
    const float wrldLogoWidth = self.pWrldLogoImage.image.size.width;
    const float wrldLogoHeight = self.pWrldLogoImage.image.size.height;
    const float wrldLogoX = innerMargin.left;
    const float wrldLogoY = developedByY + wrldLogoHeight;
    
    self.pWrldLogoImage.frame = CGRectMake(wrldLogoX, wrldLogoY, wrldLogoWidth, wrldLogoHeight);
    
    const CGFloat legalLinkY = wrldLogoY + wrldLogoHeight + innerMargin.bottom;
    self.pLegalLink.frame = CGRectMake(innerMargin.left, legalLinkY, innerMarginWidth, 16);
    self.pLegalLink.titleLabel.textAlignment = NSTextAlignmentLeft;
    
    [self.pLegalLink.titleLabel sizeToFit];
    [self.pLegalLink sizeToFit];
  
    CGFloat contentHeight = self.pLegalLink.frame.origin.y + self.pLegalLink.frame.size.height + innerMargin.bottom;
    
    self.pContentView.frame = CGRectMake(0.0, 0.0,mainWindowWidth,contentHeight);
    
    self.pContentScrollView.contentSize = self.pContentView.frame.size;
    
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
         CGPoint offset = self.pContentScrollView.contentOffset;
         [self.pContentScrollView setContentOffset:offset animated:NO];
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
