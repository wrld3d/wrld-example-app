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
    self = [super initWithParams:pinDiameter :pixelScale :interop :14];
    if(self)
    {
        self.pSubtitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pSubtitleLabel.textColor = ExampleApp::Helpers::ColorPalette::TwitterDarkGrey;
        self.pSubtitleLabel.textAlignment = NSTextAlignmentCenter;
        self.pSubtitleLabel.numberOfLines = 1;
        self.pSubtitleLabel.lineBreakMode = NSLineBreakByTruncatingTail;
        self.pSubtitleLabel.font = [UIFont systemFontOfSize:12.0];
        self.pSubtitleLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pSubtitleLabel];
    }
    return self;
}

- (void)dealloc
{
    [self.pSubtitleLabel removeFromSuperview];
    [self.pSubtitleLabel release];
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    self.layer.shouldRasterize = YES;
    self.layer.rasterizationScale = [[UIScreen mainScreen] scale];
    
    self.pNameLabel.frame = CGRectMake(labelMarginX, labelMarginTop, maxLabelWidth, 0.f);
    
    [self.pNameLabel sizeToFit];
    
    const float w = Eegeo::Math::Clamp(static_cast<float>(self.pNameLabel.frame.size.width) + 2*labelMarginX, minWidth, maxWidth);
    const float h = self.pNameLabel.frame.size.height + topStripHeight + labelMarginTop + labelMarginBottom;

    CGRect labelFrame = self.pNameLabel.frame;
    labelFrame.origin = CGPointMake((w - labelFrame.size.width) / 2, labelMarginTop);
    self.pNameLabel.frame = labelFrame;
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, w, h);
    self.pMainControlShadowContainer.frame = CGRectMake(2.f, 2.f, w, h);

    self.pTopStrip.frame =  CGRectMake(0.f, 0.f, w, topStripHeight);
    self.pLabelBack.frame = CGRectMake(0.f, topStripHeight, w, h - topStripHeight);

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
    self.frame = CGRectMake(trueX - w/2, trueY - (h + arrowWidth), w, h + arrowWidth);
    
    m_cardHeight = self.frame.size.height;
}

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel
{
    self.pNameLabel.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetTitle().c_str()];
    self.pSubtitleLabel.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetSubtitle().c_str()];
    [self setNeedsLayout];
}
@end
