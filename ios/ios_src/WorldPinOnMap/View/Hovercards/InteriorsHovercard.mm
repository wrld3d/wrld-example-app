// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsHovercard.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "WorldPinOnMapViewInterop.h"

@implementation InteriorsHovercard

- (id)initWithParams:(float)pinDiameter :(float)pixelScale :(ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*)interop
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
        
        m_pInterop = interop;
        
        // shadow
        self.pMainControlShadowContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pMainControlShadowContainer setBackgroundColor: ExampleApp::Helpers::ColorPalette::UiShadowColor];
        [self addSubview: self.pMainControlShadowContainer];
        
        // main control container
        self.pMainControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pMainControlContainer setBackgroundColor: [UIColor clearColor]];
        [self addSubview: self.pMainControlContainer];
        
        // top strip
        self.pTopStrip = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pTopStrip setBackgroundColor: ExampleApp::Helpers::ColorPalette::UiBorderColor];
        [self.pMainControlContainer addSubview: self.pTopStrip];
        
        // label container
        self.pLabelBack = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelBack setBackgroundColor: ExampleApp::Helpers::ColorPalette::UiBackgroundColor];
        [self.pMainControlContainer addSubview: self.pLabelBack];
        
        // name label
        self.pNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pNameLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextTitleColor;
        self.pNameLabel.textAlignment = NSTextAlignmentCenter;
        self.pNameLabel.numberOfLines = 1;
        self.pNameLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pNameLabel.font = [UIFont systemFontOfSize:14.0];
        self.pNameLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pNameLabel];
        
        self.pSubtitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pSubtitleLabel.textColor = ExampleApp::Helpers::ColorPalette::TwitterDarkGrey;
        self.pSubtitleLabel.textAlignment = NSTextAlignmentCenter;
        self.pSubtitleLabel.numberOfLines = 1;
        self.pSubtitleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pSubtitleLabel.font = [UIFont systemFontOfSize:12.0];
        self.pSubtitleLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pSubtitleLabel];
        
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
    
    [self.pSubtitleLabel removeFromSuperview];
    [self.pSubtitleLabel release];
    
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
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    
    self.layer.shouldRasterize = YES;
    self.layer.rasterizationScale = [[UIScreen mainScreen] scale];
    
    // figures from a proportional size of an iPad2 screen -- use const so not proportional to small screens on iPhones.
    const float w = 162.f;
    const float h =  56.f;
    const float maxH = 85.f;
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, w, h);
    self.pMainControlShadowContainer.frame = CGRectMake(2.f, 2.f, w, h);
    
    const float labelContainerOffsetY = 6.f;
    const CGFloat labelContainerHeight = self.pMainControlContainer.frame.size.height - labelContainerOffsetY;
    
    self.pTopStrip.frame =  CGRectMake(0.f, 0.f, w, labelContainerOffsetY);
    self.pLabelBack.frame = CGRectMake(0.f, labelContainerOffsetY, w, labelContainerHeight);
    
    const float labelOffsetX = 4.f;
    const float labelOffsetY = 1.5f;
    const float nameHeight = h - labelContainerOffsetY;
    
    if(self.pSubtitleLabel.text.length == 0)
    {
        self.pNameLabel.frame = CGRectMake(labelOffsetX,
                                           labelOffsetY,
                                           w - (labelOffsetX*2),
                                           nameHeight);
        self.pNameLabel.font = [UIFont systemFontOfSize:18.0];
        self.pSubtitleLabel.hidden = YES;
    }
    else
    {
        self.pNameLabel.frame = CGRectMake(labelOffsetX,
                                           labelOffsetY - 10,
                                           w - (labelOffsetX*2),
                                           nameHeight);
        self.pNameLabel.font = [UIFont systemFontOfSize:14.0];
        self.pSubtitleLabel.hidden = NO;
    }
    self.pSubtitleLabel.frame = CGRectMake(labelOffsetX,
                                       labelOffsetY + 10,
                                       w - (labelOffsetX*2),
                                       nameHeight);
    
    const float arrowWidth = 16.f;
    self.pArrowContainer.frame = CGRectMake(w/2.f - arrowWidth/2.f, h, arrowWidth, arrowWidth);
    
    float trueY = m_previousY/m_pixelScale - m_pinOffset/m_pixelScale;
    float trueX = m_previousX/m_pixelScale;
    self.frame = CGRectMake(trueX - w/2, trueY - (h + arrowWidth), w, maxH + arrowWidth);
    
    m_cardHeight = h + arrowWidth;
}

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel
{
    self.pNameLabel.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetTitle().c_str()];
    self.pSubtitleLabel.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetSubtitle().c_str()];
    
    
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
