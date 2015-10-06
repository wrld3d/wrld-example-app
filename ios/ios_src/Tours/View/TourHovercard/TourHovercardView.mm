// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourHovercardView.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "TourHovercardViewInterop.h"
#include "App.h"
#include "Document.h"
#include "ImageStore.h"
#include "TourDefines.h"

@implementation TourHovercardView
{
    ExampleApp::Tours::View::TourHovercard::TourHovercardViewInterop* m_pInterop;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_stateChangeAnimationTimeSeconds;
    float m_pinOffset;
    float m_pixelScale;
    
    float m_cardHeight;
    float m_labelHeight;
    
    float m_previousX;
    float m_previousY;
    
    ExampleApp::Helpers::ColorHelpers::Color m_baseColor;
    ExampleApp::Helpers::ColorHelpers::Color m_textColor;
}
- (id)initWithParams:(float)pinDiameter :(float)pixelScale
{
    self = [super init];
    
    if(self)
    {
        self.alpha = 0.f;
        m_pinOffset = (pinDiameter * pixelScale);
        m_pixelScale = pixelScale;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        
        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapped:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self addGestureRecognizer: m_tapGestureRecogniser];
        
        m_pInterop = new ExampleApp::Tours::View::TourHovercard::TourHovercardViewInterop(self);
        
        // shadow
        self.pMainControlShadowContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pMainControlShadowContainer setBackgroundColor: ExampleApp::Helpers::ColorPalette::GreyTone];
        [self addSubview: self.pMainControlShadowContainer];
        
        // main control container
        self.pMainControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pMainControlContainer setBackgroundColor: [UIColor clearColor]];
        [self addSubview: self.pMainControlContainer];
        
        // gold top strip
        self.pTopStrip = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pTopStrip setBackgroundColor: [UIColor colorWithRed:m_baseColor.GetRedF() green:m_baseColor.GetGreenF() blue:m_baseColor.GetBlueF() alpha:1.0f]];
        [self.pMainControlContainer addSubview: self.pTopStrip];
        
        // label container
        self.pLabelBack = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelBack setBackgroundColor: ExampleApp::Helpers::ColorPalette::MainHudColor];
        [self.pMainControlContainer addSubview: self.pLabelBack];
        
        // name label
        const float nameFontSize = 16.f;
        self.pNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pNameLabel.textColor = [UIColor colorWithRed:m_textColor.GetRedF() green:m_textColor.GetGreenF() blue:m_textColor.GetBlueF() alpha:1.0f];
        self.pNameLabel.textAlignment = NSTextAlignmentCenter;
        self.pNameLabel.font = [UIFont systemFontOfSize:nameFontSize];
        self.pNameLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pNameLabel];
        
        // info label
        const float infoFontSize = 12.f;
        self.pInfoLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pInfoLabel.textColor = TourDefines::LightTextColor;
        self.pInfoLabel.textAlignment = NSTextAlignmentCenter;
        self.pInfoLabel.font = [UIFont systemFontOfSize:infoFontSize];
        self.pInfoLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pInfoLabel];
        
        // poi arrow
        self.pArrowContainer = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage("arrow1")] autorelease];
        self.pArrowContainer.contentMode = UIViewContentModeScaleToFill;
        [self addSubview: self.pArrowContainer];
        
        self.frame.origin = CGPointMake(0, 0);
    }
    
    return self;
}

- (void)dealloc
{
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabel release];
    
    [self.pInfoLabel removeFromSuperview];
    [self.pInfoLabel release];
    
    [self.pLabelBack removeFromSuperview];
    [self.pLabelBack release];
    
    [self.pTopStrip removeFromSuperview];
    [self.pTopStrip release];
    
    [self.pMainControlContainer removeFromSuperview];
    [self.pMainControlContainer release];
    
    [self.pMainControlShadowContainer removeFromSuperview];
    [self.pMainControlShadowContainer release];
    
    [self.pArrowContainer removeFromSuperview];
    [self.pArrowContainer release];
    
    delete m_pInterop;
    
    [self removeFromSuperview];
    [super dealloc];
}

- (ExampleApp::Tours::View::TourHovercard::TourHovercardViewInterop*) getInterop
{
    return m_pInterop;
}

- (void)layoutSubviews
{
    
    self.layer.shouldRasterize = YES;
    self.layer.rasterizationScale = [[UIScreen mainScreen] scale];
    
    float maxH = 85.f;
    // figures from a proportional size of an iPad2 screen -- use const so not proportional to small screens on iPhones.
    float w = 162.f;
    float h = 56.f;
    
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, w, h);
    self.pMainControlShadowContainer.frame = CGRectMake(2.f, 2.f, w, h);
    
    const float labelContainerOffsetY = 6.f;
    const CGFloat labelContainerHeight = self.pMainControlContainer.frame.size.height - labelContainerOffsetY;
    
    self.pTopStrip.frame =  CGRectMake(0.f, 0.f, w, labelContainerOffsetY);
    self.pLabelBack.frame = CGRectMake(0.f, labelContainerOffsetY, w, labelContainerHeight);
    
    const float labelVerticalSpace = h*0.3f;
    const float labelSpacing = h*0.05f;
    const float labelOffsetX = 4.f;
    const float labelOffsetY = 2.f;
    
    self.pNameLabel.frame = CGRectMake(labelOffsetX,
                                       labelOffsetY,
                                       w - (labelOffsetX*2),
                                       labelVerticalSpace);
    
    
    self.pInfoLabel.frame = CGRectMake(labelOffsetX,
                                          labelVerticalSpace + labelSpacing,
                                          w - (labelOffsetX*2),
                                          labelVerticalSpace);
    
    
    const float arrowWidth = 16.f;
    self.pArrowContainer.frame = CGRectMake(w/2.f - arrowWidth/2.f, h, arrowWidth, arrowWidth);
    
    float trueY = m_previousY/m_pixelScale - m_pinOffset/m_pixelScale;
    float trueX = m_previousX/m_pixelScale;
    self.frame = CGRectMake(trueX - w/2, trueY - (h + arrowWidth), w, maxH + arrowWidth);
    
    m_cardHeight = h + arrowWidth;
}

- (void) setContent:(const std::string&)name :(const std::string&)subtitle;
{
    self.pNameLabel.text = [NSString stringWithUTF8String:name.c_str()];
    
    self.pInfoLabel.text = [NSString stringWithUTF8String:subtitle.c_str()];
    
    [self setNeedsLayout];
}

- (void) setFullyActive :(float)modality
{
    self.userInteractionEnabled = YES;
    [self animateToAlpha:(1.f - modality)];
}

- (void) setFullyInactive
{
    self.userInteractionEnabled = NO;
    [self animateToAlpha:0.f];
}

- (void) updatePosition:(float)x :(float)y
{
    float roundedX = roundf(x);
    float roundedY = roundf(y);
    
    if(m_previousX == roundedX && m_previousY == roundedY)
    {
        float trueY = roundedY/m_pixelScale - m_pinOffset/m_pixelScale;
        float trueX = roundedX/m_pixelScale;
        
        CGRect f = self.frame;
        f.origin.x = static_cast<int>(trueX - (f.size.width/2.f));
        f.origin.y = static_cast<int>(trueY - (m_cardHeight));
        self.frame = f;
    }
    else
    {
        float trueY = y/m_pixelScale - m_pinOffset/m_pixelScale;
        float trueX = x/m_pixelScale;
        
        CGRect f = self.frame;
        f.origin.x = trueX - (f.size.width/2.f);
        f.origin.y = trueY - (m_cardHeight);
        self.frame = f;
    }
    
    m_previousX = roundedX;
    m_previousY = roundedY;
}


- (void) setPresentationColors :(ExampleApp::Helpers::ColorHelpers::Color)baseColor :(ExampleApp::Helpers::ColorHelpers::Color)textColor
{
    m_baseColor = baseColor;
    m_textColor = textColor;
    
    [self.pTopStrip setBackgroundColor: [UIColor colorWithRed:m_baseColor.GetRedF() green:m_baseColor.GetGreenF() blue:m_baseColor.GetBlueF() alpha:1.0f]];
    self.pNameLabel.textColor = [UIColor colorWithRed:m_textColor.GetRedF() green:m_textColor.GetGreenF() blue:m_textColor.GetBlueF() alpha:1.0f];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    if(self.userInteractionEnabled)
    {
        CGPoint touchLocation = [touch locationInView:self];
        return CGRectContainsPoint(self.bounds, touchLocation);
    }
    
    return false;
}

- (void) animateToAlpha:(float)alpha
{
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.alpha = alpha;
     }];
}

- (void) onTapped:(UITapGestureRecognizer *)recognizer
{
    m_pInterop->OnSelected();
}

@end

