// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterWorldHovercard.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "WorldPinOnMapViewInterop.h"

@implementation TwitterWorldHovercard

- (id)initWithParams:(float)pinDiameter :(float)pixelScale  :(ImageStore*)pImageStore :(ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*)interop
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
        [self.pMainControlShadowContainer setBackgroundColor: ExampleApp::Helpers::ColorPalette::GreyTone];
        [self addSubview: self.pMainControlShadowContainer];
        
        // main control container
        self.pMainControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pMainControlContainer setBackgroundColor: [UIColor clearColor]];
        [self addSubview: self.pMainControlContainer];
        
        // gold top strip
        self.pTopStrip = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pTopStrip setBackgroundColor: ExampleApp::Helpers::ColorPalette::TwitterBlue];
        [self.pMainControlContainer addSubview: self.pTopStrip];
        
        // label container
        self.pLabelBack = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pLabelBack setBackgroundColor: ExampleApp::Helpers::ColorPalette::MainHudColor];
        [self.pMainControlContainer addSubview: self.pLabelBack];
        
        // name label
        self.pNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pNameLabel.textColor = ExampleApp::Helpers::ColorPalette::TwitterDarkGrey;
        self.pNameLabel.textAlignment = NSTextAlignmentLeft;
        self.pNameLabel.font = [UIFont systemFontOfSize:16.0];
        self.pNameLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pNameLabel];
        
        // TwitterHandle label
        self.pTwitterHandle = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pTwitterHandle.textColor = ExampleApp::Helpers::ColorPalette::TwitterLightGrey;
        self.pTwitterHandle.textAlignment = NSTextAlignmentLeft;
        self.pTwitterHandle.font = [UIFont boldSystemFontOfSize:12.0];
        self.pTwitterHandle.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pTwitterHandle];
        
        // image container
        self.pImageDisplay = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        
        [self.pLabelBack addSubview: self.pImageDisplay];
        
        // poi arrow
        self.pArrowContainer = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage("arrow1")] autorelease];
        self.pArrowContainer.contentMode = UIViewContentModeScaleToFill;
        [self addSubview: self.pArrowContainer];
        
        self.pImageLoadingSpinner = [[[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge] autorelease];
        self.pImageLoadingSpinner.color = ExampleApp::Helpers::ColorPalette::TwitterBlue;
        self.pImageLoadingSpinner.hidden = YES;
        [self.pImageDisplay addSubview:self.pImageLoadingSpinner];
        
        self.frame.origin = CGPointMake(0, 0);
        
        m_pImageStore = pImageStore;
        m_profileImageUrl = "";
    }
    
    return self;
}

- (void)dealloc
{
    [self.pImageLoadingSpinner removeFromSuperview];
    [self.pImageLoadingSpinner release];
    
    [self.pNameLabel removeFromSuperview];
    [self.pNameLabel release];
    
    [self.pTwitterHandle removeFromSuperview];
    [self.pTwitterHandle release];
    
    [self.pLabelBack removeFromSuperview];
    [self.pLabelBack release];
    
    [self.pImageDisplay removeFromSuperview];
    [self.pImageDisplay release];
    
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
    
    const float labelVerticalSpaceMultiplier = 0.4f;
    const float labelVerticalSpace = h * labelVerticalSpaceMultiplier;
    const float labelSpacing = h*0.05f;
    const float labelOffsetX = 6.f;
    const float labelOffsetY = 6.f;
    
    const float imageSize = static_cast<float>(labelContainerHeight) - (2.f * labelOffsetX);
    const float textOffsetX = imageSize + (2.f * labelOffsetX);
    const float textWidth = w - labelOffsetX - textOffsetX;
    
    self.pNameLabel.frame = CGRectMake(textOffsetX,
                                       labelOffsetY,
                                       textWidth,
                                       labelVerticalSpace);
    
    
    self.pTwitterHandle.frame = CGRectMake(textOffsetX,
                                          labelVerticalSpace + labelSpacing,
                                          textWidth,
                                          labelVerticalSpace);
    
    self.pImageDisplay.frame = CGRectMake(labelOffsetX,
                                          labelOffsetY,
                                          imageSize,
                                          imageSize);
    
    [m_pImageStore releaseImageForView:self.pImageDisplay];
    [self.pImageLoadingSpinner startAnimating];
    
    if(!m_profileImageUrl.empty())
    {
        self.pImageDisplay.backgroundColor = [UIColor clearColor];
        [m_pImageStore loadImage:m_profileImageUrl
                                :self.pImageDisplay
                                :^(UIImage* image)
         {
             self.pImageDisplay.image = image;
             [self.pImageLoadingSpinner stopAnimating];
             
         }
                                :static_cast<float>(self.pImageDisplay.frame.size.width)];
    }
    else
    {
        self.pImageDisplay.backgroundColor = ExampleApp::Helpers::ColorPalette::TwitterBlue;
        [self.pImageLoadingSpinner stopAnimating];
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
    
    self.pTwitterHandle.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetSubtitle().c_str()];
    
    rapidjson::Document jsonData;
    jsonData.Parse<0>(worldPinsInFocusModel.GetJsonData().c_str());
    if(!jsonData.HasParseError())
    {
        Eegeo_ASSERT(jsonData.HasMember("twitter_image"));
        
        m_profileImageUrl = jsonData["twitter_image"].GetString();
    }
    
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
