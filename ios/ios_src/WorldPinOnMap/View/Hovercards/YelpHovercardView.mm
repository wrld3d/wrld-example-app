// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpHovercardView.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "WorldPinOnMapViewInterop.h"

@implementation YelpHovercardView

- (id)initWithParams:(float)pinDiameter :(float)pixelScale :(ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*)interop
{
    self = [super initWithParams:pinDiameter :pixelScale :interop :16];
    if(self)
    {
        m_enlarged = NO;
        
        // address label
        self.pAddressLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pAddressLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pAddressLabel.textAlignment = NSTextAlignmentCenter;
        self.pAddressLabel.font = [UIFont systemFontOfSize:12.0];
        self.pAddressLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pAddressLabel];
        
        // image container
        self.pImageDisplay = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 115, 25)] autorelease];
        [self.pLabelBack addSubview: self.pImageDisplay];
        
        // review count
        self.pReviewCountLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewCountLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pReviewCountLabel.textAlignment = NSTextAlignmentLeft;
        self.pReviewCountLabel.font = [UIFont systemFontOfSize:12.0];
        self.pReviewCountLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pReviewCountLabel];
        
        // accreditation image (Only Yelp for now for reviews/ratings)
        self.pAccreditationImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 51, 27)] autorelease];
        self.pAccreditationImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage("yelp_logo");
        [self.pLabelBack addSubview: self.pAccreditationImage];
        
        self.frame.origin = CGPointMake(0, 0);
    }
    return self;
}

- (void)dealloc
{
    [self.pAddressLabel removeFromSuperview];
    [self.pAddressLabel release];
    
    [self.pReviewCountLabel removeFromSuperview];
    [self.pReviewCountLabel release];
    
    [self.pAccreditationImage removeFromSuperview];
    [self.pAccreditationImage release];

    [self.pImageDisplay removeFromSuperview];
    [self.pImageDisplay release];
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    
    self.layer.shouldRasterize = YES;
    self.layer.rasterizationScale = [[UIScreen mainScreen] scale];
    
    float maxH = 85.f;
    // figures from a proportional size of an iPad2 screen -- use const so not proportional to small screens on iPhones.
    float w = 162.f; //self.superview.bounds.size.width/6;
    float h = m_enlarged ? maxH : 56.f; //self.superview.bounds.size.height/16;
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, w, h);
    self.pMainControlShadowContainer.frame = CGRectMake(2.f, 2.f, w, h);
    
    const float labelContainerOffsetY = 6.f;
    const CGFloat labelContainerHeight = self.pMainControlContainer.frame.size.height - labelContainerOffsetY;
    
    self.pTopStrip.frame =  CGRectMake(0.f, 0.f, w, labelContainerOffsetY);
    self.pLabelBack.frame = CGRectMake(0.f, labelContainerOffsetY, w, labelContainerHeight);
    
    const float labelVerticalSpaceMultiplier = m_enlarged ? 0.3f : 0.4f;
    const float labelVerticalSpace = h * labelVerticalSpaceMultiplier;
    const float labelSpacing = h*0.05f;
    const float labelOffsetX = 4.f;
    const float labelOffsetY = 2.f;
    
    self.pNameLabel.frame = CGRectMake(labelOffsetX,
                                       labelOffsetY,
                                       w - (labelOffsetX*2),
                                       labelVerticalSpace);
    
    
    self.pAddressLabel.frame = CGRectMake(labelOffsetX,
                                          labelVerticalSpace + labelSpacing,
                                          w - (labelOffsetX*2),
                                          labelVerticalSpace);
    
    if(m_enlarged)
    {
        float textWidth = [self.pReviewCountLabel.text sizeWithAttributes:@{NSFontAttributeName: self.pReviewCountLabel.font}].width;
        float totalWidth = self.pImageDisplay.frame.size.width + textWidth + labelOffsetX;
        self.pImageDisplay.frame = CGRectMake(w/2 - totalWidth/2,
                                              labelVerticalSpace + labelSpacing,
                                              self.pImageDisplay.frame.size.width,
                                              self.pImageDisplay.frame.size.height);
        self.pReviewCountLabel.frame = CGRectMake(labelOffsetX, labelVerticalSpace + labelSpacing, 0, 0);
        self.pReviewCountLabel.frame = CGRectMake(self.pImageDisplay.frame.origin.x + self.pImageDisplay.frame.size.width + labelOffsetX,
                                                  self.pImageDisplay.frame.origin.y,
                                                  textWidth,
                                                  self.pImageDisplay.frame.size.height);
        
        [self.pAccreditationImage setHidden:NO];
        self.pAccreditationImage.frame = CGRectMake(w/2 - self.pAccreditationImage.bounds.size.width/2, (labelVerticalSpace *2) - labelOffsetY, 51, 27);
    }
    
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
    const bool hasRatingsImage = !worldPinsInFocusModel.GetRatingsImage().empty();
    bool usedImage = false;
    m_enlarged = hasRatingsImage;
    
    [self.pReviewCountLabel setHidden:YES];
    
    if(hasRatingsImage && worldPinsInFocusModel.GetReviewCount() > 0)
    {
        UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(worldPinsInFocusModel.GetRatingsImage());
        if(image != nil)
        {
            self.pAddressLabel.text = @"";
            [self.pImageDisplay setImage:image];
            [self.pImageDisplay setHidden:NO];
            
            CGRect frame = self.pImageDisplay.frame;
            frame.size = image.size;
            self.pImageDisplay.frame = frame;
            
            // Include review count.
            self.pReviewCountLabel.text = [NSString stringWithFormat:@"(%d)", worldPinsInFocusModel.GetReviewCount()];
            [self.pReviewCountLabel setHidden:NO];
            
            usedImage = true;
        }
    }
    
    if(!usedImage)
    {
        self.pAddressLabel.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetSubtitle().c_str()];
        [self.pImageDisplay setImage:nil];
        [self.pImageDisplay setHidden:YES];
        [self.pReviewCountLabel setHidden:YES];
        [self.pAccreditationImage setHidden:YES];
    }
    [self setNeedsLayout];
}
@end
