// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "WorldPinOnMapViewInterop.h"

@implementation WorldPinOnMapView

- (id)initWithParams:(float)pinDiameter :(float)pixelScale
{
    self = [super init];

    if(self)
    {
        self.alpha = 0.f;
        m_pinOffset = pinDiameter * 0.75f;
        m_pixelScale = pixelScale;
        m_stateChangeAnimationTimeSeconds = 0.2f;

        m_tapGestureRecogniser = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(onTapped:)];
        [m_tapGestureRecogniser setDelegate:self];
        [self addGestureRecognizer: m_tapGestureRecogniser];

        m_pInterop = new ExampleApp::WorldPins::View::WorldPinOnMapViewInterop(self);

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
        [self.pTopStrip setBackgroundColor: ExampleApp::Helpers::ColorPalette::GoldTone];
        [self.pMainControlContainer addSubview: self.pTopStrip];

        // label container
        self.pLabelBack = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelBack setBackgroundColor: ExampleApp::Helpers::ColorPalette::MainHudColor];
        [self.pMainControlContainer addSubview: self.pLabelBack];

        // name label
        self.pNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pNameLabel.textColor = ExampleApp::Helpers::ColorPalette::GoldTone;
        self.pNameLabel.textAlignment = NSTextAlignmentLeft;
        self.pNameLabel.font = [UIFont systemFontOfSize:16.0];
        self.pNameLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pNameLabel];

        // address label
        self.pAddressLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAddressLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pAddressLabel.textAlignment = NSTextAlignmentLeft;
        self.pAddressLabel.font = [UIFont systemFontOfSize:12.0];
        self.pAddressLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pAddressLabel];

        // poi arrow
        self.pArrowContainer = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage("arrow1")] autorelease];
        self.pArrowContainer.contentMode = UIViewContentModeScaleToFill;
        [self addSubview: self.pArrowContainer];
    }

    return self;
}

- (void)dealloc
{
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabel release];

    [self.pAddressLabel removeFromSuperview];
    [self.pAddressLabel release];

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

- (ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*) getInterop
{
    return m_pInterop;
}

- (void)layoutSubviews
{
    self.alpha = 0.f;
    self.layer.shouldRasterize = YES;
    self.layer.rasterizationScale = [[UIScreen mainScreen] scale];

    // figures from a proportional size of an iPad2 screen -- use const so not proportional to small screens on iPhones.
    float w = 172.f; //self.superview.bounds.size.width/6;
    float h = 56.f; //self.superview.bounds.size.height/16;
    float x = 0.f;
    float y = 0.f;

    self.pMainControlContainer.frame = CGRectMake(x, y, w, h);
    self.pMainControlShadowContainer.frame = CGRectMake(x + 2.f, y + 2.f, w, h);

    const float labelContainerOffsetY = 6.f;
    const CGFloat labelContainerHeight = self.pMainControlContainer.frame.size.height - labelContainerOffsetY;

    self.pTopStrip.frame =  CGRectMake(0.f, 0.f, w, labelContainerOffsetY);
    self.pLabelBack.frame = CGRectMake(0.f, labelContainerOffsetY, w, labelContainerHeight);

    const float labelVerticalSpace = h*0.4f;
    const float labelSpacing = h*0.05f;
    const float labelOffsetX = 4.f;
    const float labelOffsetY = 4.f;

    self.pNameLabel.frame = CGRectMake(labelOffsetX,
                                       labelOffsetY,
                                       w - labelOffsetX,
                                       labelVerticalSpace);


    self.pAddressLabel.frame = CGRectMake(labelOffsetX,
                                          labelVerticalSpace + labelSpacing,
                                          w - labelOffsetX,
                                          labelVerticalSpace);

    const float arrowWidth = 16.f;
    self.pArrowContainer.frame = CGRectMake(w/2.f - arrowWidth/2.f, h, arrowWidth, arrowWidth);

    self.frame = CGRectMake(x, y, w, h + arrowWidth);
}

- (void) setLabel:(std::string)name :(std::string)detail
{
    self.pNameLabel.text = [NSString stringWithUTF8String:name.c_str()];
    self.pAddressLabel.text = [NSString stringWithUTF8String:detail.c_str()];
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
    float trueY = y/m_pixelScale - m_pinOffset;
    float trueX = x/m_pixelScale;

    CGRect f = self.frame;
    f.origin.x = trueX - (f.size.width/2.f);
    f.origin.y = trueY - (f.size.height);
    self.frame = f;
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
