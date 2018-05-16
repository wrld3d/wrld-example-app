// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AboutPageView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "AboutPageViewInterop.h"
#include "UIHelpers.h"
#include "ViewController.h"
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
        
        self.pTextContent = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTextContent.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        [self.pContentView addSubview: self.pTextContent];
        
        self.pContentSeperator = [[[UIView alloc] init] autorelease];
        self.pContentSeperator.backgroundColor = ExampleApp::Helpers::ColorPalette::UISeparatorColor;
        [self.pContentView addSubview:self.pContentSeperator];
        
        self.pDevelopedByLabel  = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pDevelopedByLabel.font = [UIFont systemFontOfSize:16.f];
        self.pDevelopedByLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pDevelopedByLabel.text = @"Developed by ";
        [self.pContentView addSubview:self.pDevelopedByLabel];
        
        
        self.pWrldLogoImage = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"eegeo_logo_about")] autorelease];
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
        
        self.pPrivacyLink = [[[UIButton alloc] init] autorelease];
        [self.pPrivacyLink addTarget:self action:@selector(privacyClickHandler:) forControlEvents:UIControlEventTouchUpInside];
        [self.pPrivacyLink setTitle:@"Privacy Policy" forState:UIControlStateNormal];
        [self.pPrivacyLink setTitleColor:ExampleApp::Helpers::ColorPalette::UiTextTitleColor forState:UIControlStateNormal];
        self.pPrivacyLink.titleLabel.font = [UIFont boldSystemFontOfSize:16.f];
        self.pPrivacyLink.titleLabel.textAlignment = NSTextAlignmentLeft;
        
        self.pEulaLink = [[[UIButton alloc] init] autorelease];
        [self.pEulaLink addTarget:self action:@selector(eulaClickHandler:) forControlEvents:UIControlEventTouchUpInside];
        [self.pEulaLink setTitle:@"EULA" forState:UIControlStateNormal];
        [self.pEulaLink setTitleColor:ExampleApp::Helpers::ColorPalette::UiTextTitleColor forState:UIControlStateNormal];
        self.pEulaLink.titleLabel.font = [UIFont boldSystemFontOfSize:16.f];
        self.pEulaLink.titleLabel.textAlignment = NSTextAlignmentLeft;
        
        self.pTeamLink = [[[UIButton alloc] init] autorelease];
        [self.pTeamLink addTarget:self action:@selector(teamClickHandler:) forControlEvents:UIControlEventTouchUpInside];
        [self.pTeamLink setTitle:@"Team" forState:UIControlStateNormal];
        [self.pTeamLink setTitleColor:ExampleApp::Helpers::ColorPalette::UiTextTitleColor forState:UIControlStateNormal];
        self.pTeamLink.titleLabel.font = [UIFont boldSystemFontOfSize:16.f];
        self.pTeamLink.titleLabel.textAlignment = NSTextAlignmentLeft;
        
        [self.pContentView addSubview:self.pLegalLink];
        [self.pContentView addSubview:self.pPrivacyLink];
        [self.pContentView addSubview:self.pEulaLink];
        [self.pContentView addSubview:self.pTeamLink];
        
    }

    return self;
}

- (void)dealloc
{
    [self.pHeaderView removeFromSuperview];
    [self.pHeaderView release];
    
    
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
    
    [self.pPrivacyLink removeFromSuperview];
    [self.pPrivacyLink release];
    
    [self.pEulaLink removeFromSuperview];
    [self.pEulaLink release];
    
    [self.pTeamLink removeFromSuperview];
    [self.pTeamLink release];
    
    [self removeFromSuperview];
    [super dealloc];
    
    Eegeo_DELETE m_pInterop;
    
}

- (void)layoutSubviews
{
    UIViewController *viewController = [UIApplication sharedApplication].delegate.window.rootViewController;
    self.frame = [viewController largePopoverFrame];
    
    self.pHeaderView.width = self.frame.size.width;
    [self.pHeaderView layoutIfNeeded];
    CGFloat seperatorMargin = self.pHeaderView.pHeaderSeparator.frame.origin.x;
    UIEdgeInsets outerMargin = UIEdgeInsetsMake(seperatorMargin, seperatorMargin, seperatorMargin, seperatorMargin);
    UIEdgeInsets innerMargin = UIEdgeInsetsMake(self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin,self.pHeaderView.margin);
    CGFloat innerMarginWidth = self.frame.size.width - innerMargin.left - innerMargin.right;
    CGFloat outerMarginWidth = self.frame.size.width - outerMargin.left - outerMargin.right;
    CGFloat contentY = self.pHeaderView.frame.origin.y +  self.pHeaderView.frame.size.height;
    
    self.pContentScrollView.frame = CGRectMake(0.0,
                                               contentY,
                                               self.frame.size.width,
                                               self.frame.size.height - contentY);
    
    const CGFloat textMarginY  = 14.f;
    const CGFloat textContentY = textMarginY;
    
    self.pTextContent.frame = CGRectMake(innerMargin.left, textContentY, innerMarginWidth, 0.0);
    self.pTextContent.numberOfLines = 0;
    self.pTextContent.adjustsFontSizeToFitWidth = NO;
    self.pTextContent.font = [UIFont systemFontOfSize:14.5f];
    self.pTextContent.lineBreakMode = NSLineBreakByWordWrapping;
    
    [self.pTextContent sizeToFit];
    
    CGFloat contentSeperatorY = self.pTextContent.frame.origin.y + self.pTextContent.frame.size.height + textMarginY + 1.f;
    self.pContentSeperator.frame = CGRectMake(outerMargin.left, contentSeperatorY, outerMarginWidth,1.0);
    
    const CGFloat developedByY = self.pContentSeperator.frame.origin.y + self.pContentSeperator.frame.size.height + innerMargin.top;
    const CGFloat developedByHeight = 16.f;
    
    self.pDevelopedByLabel.frame = CGRectMake(innerMargin.left, developedByY, innerMarginWidth, developedByHeight);
    [self.pDevelopedByLabel sizeToFit];
    
    const float wrldLogoWidth = self.pWrldLogoImage.image.size.width;
    const float wrldLogoHeight = self.pWrldLogoImage.image.size.height;
    const float wrldLogoX = innerMargin.left;
    const float wrldLogoY = developedByY + wrldLogoHeight;
    
    self.pWrldLogoImage.frame = CGRectMake(wrldLogoX, wrldLogoY, wrldLogoWidth, wrldLogoHeight);
    
    contentY = wrldLogoY + wrldLogoHeight + innerMargin.bottom;
    
    UIEdgeInsets linkMargin = innerMargin;
    linkMargin.bottom = 0;
    
    contentY = [self layoutLinks:self.pEulaLink atY:contentY margin:linkMargin width:innerMarginWidth];
    contentY = [self layoutLinks:self.pPrivacyLink atY:contentY margin:linkMargin width:innerMarginWidth];
    contentY = [self layoutLinks:self.pLegalLink atY:contentY margin:linkMargin width:innerMarginWidth];
    contentY = [self layoutLinks:self.pTeamLink atY:contentY margin:linkMargin width:innerMarginWidth];
    
    self.pContentView.frame = CGRectMake(0.0, 0.0,self.frame.size.width,contentY);
    
    self.pContentScrollView.contentSize = self.pContentView.frame.size;
    
}

-(CGFloat ) layoutLinks:(UIButton *)link atY:(CGFloat) linkY margin:(UIEdgeInsets)margin width:(CGFloat)width
{
    link.frame = CGRectMake(margin.left, linkY, width, 16);
    link.titleLabel.textAlignment = NSTextAlignmentLeft;
    
    [link.titleLabel sizeToFit];
    [link sizeToFit];
    
    return link.frame.origin.y + link.frame.size.height + margin.bottom;
}

- (ExampleApp::AboutPage::View::AboutPageViewInterop*)getInterop
{
    return m_pInterop;
}

- (void) setContent:(const std::string*)content
{
    self.pTextContent.text = [[NSString stringWithUTF8String:content->c_str()]
                              stringByTrimmingCharactersInSet:
                              [NSCharacterSet whitespaceAndNewlineCharacterSet]];
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

- (void) privacyClickHandler:(id) sender
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/privacy/"]];
}

- (void) eulaClickHandler:(id) sender
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/tos/"]];
}

- (void) legalClickHandler:(id) sender
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/legal/"]];
}

- (void) teamClickHandler:(id) sender
{
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://www.wrld3d.com/team/"]];
}

@end
