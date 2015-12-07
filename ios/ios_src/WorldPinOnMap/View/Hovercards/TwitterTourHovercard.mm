// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TwitterTourHovercard.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "WorldPinOnMapViewInterop.h"
#include "App.h"
#include "Document.h"
#include "ImageStore.h"
#include "TourDefines.h"

@implementation TwitterTourHovercard
{
    ExampleApp::WorldPins::View::WorldPinOnMapViewInterop* m_pInterop;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_stateChangeAnimationTimeSeconds;
    float m_pinOffset;
    float m_pixelScale;
    
    float m_cardHeight;
    float m_labelHeight;
    
    float m_previousX;
    float m_previousY;
    
    std::string m_imagePath;
    bool m_isVideo;
    ImageStore* m_pImageStore;
    
    ExampleApp::Helpers::ColorHelpers::Color m_baseColor;
    ExampleApp::Helpers::ColorHelpers::Color m_textColor;
}
- (id)initWithParams:(float)pinDiameter :(float)pixelScale :(ImageStore*)pImageStore :(ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*)interop
{
    self = [super init];
    
    if(self)
    {
        m_pImageStore = pImageStore;
        
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
        
        // poi arrow
        self.pArrowContainer = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage("arrow1")] autorelease];
        self.pArrowContainer.contentMode = UIViewContentModeScaleToFill;
        [self addSubview: self.pArrowContainer];
        
        // image/video
        self.pImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pImage.contentMode = UIViewContentModeScaleAspectFill;
        [self.pImage setClipsToBounds:YES];
        self.pVideoArrowImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        
        [self.pLabelBack addSubview: self.pImage];
        [self.pImage addSubview: self.pVideoArrowImage];
        
        m_pPlayIconImage = ExampleApp::Helpers::ImageHelpers::LoadImage("Tours/States/Twitter/play_icon");
        [m_pPlayIconImage retain];
        
        self.pImageLoadingSpinner = [[[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge] autorelease];
        self.pImageLoadingSpinner.color = ExampleApp::Helpers::ColorPalette::TwitterBlue;
        self.pImageLoadingSpinner.hidden = YES;
        CGRect spinnerFrame = self.pImageLoadingSpinner.frame;
        self.pImageLoadingSpinner.frame = CGRectMake((TourDefines::ProfileImageSize - spinnerFrame.size.width)/2,
                                                     (TourDefines::ProfileImageSize - spinnerFrame.size.height)/2,
                                                     spinnerFrame.size.width,
                                                     spinnerFrame.size.height);
        [self.pImage addSubview:self.pImageLoadingSpinner];
        
        self.frame.origin = CGPointMake(0, 0);
    }
    
    return self;
}

- (void)dealloc
{
    [self.pImageLoadingSpinner removeFromSuperview];
    [self.pImageLoadingSpinner release];
    
    [m_pPlayIconImage release];
    m_pPlayIconImage = nil;
    
    [self.pVideoArrowImage removeFromSuperview];
    [self.pVideoArrowImage release];
    
    [self.pImage removeFromSuperview];
    [self.pImage release];
    
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
    const float labelContainerOffsetY = 6.f;
    
    const float totalHeight = (labelContainerOffsetY *2.0f) + TourDefines::ProfileImageSize + labelContainerOffsetY;
    const float videoArrowSize = 68.f;
    
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, w, totalHeight);
    self.pMainControlShadowContainer.frame = CGRectMake(2.f, 2.f, w, totalHeight);
    
    
    const CGFloat labelContainerHeight = self.pMainControlContainer.frame.size.height - labelContainerOffsetY;
    
    self.pTopStrip.frame =  CGRectMake(0.f, 0.f, w, labelContainerOffsetY);
    self.pLabelBack.frame = CGRectMake(0.f, labelContainerOffsetY, w, labelContainerHeight);
    
    if(m_isVideo)
    {
        self.pVideoArrowImage.frame = CGRectMake((TourDefines::ProfileImageSize - videoArrowSize)/2,
                                                 (TourDefines::ProfileImageSize - videoArrowSize)/2,
                                                 videoArrowSize,
                                                 videoArrowSize);
        [self.pVideoArrowImage setImage:m_pPlayIconImage];
        self.pVideoArrowImage.hidden = NO;
    }
    else
    {
        self.pVideoArrowImage.image = nil;
        self.pVideoArrowImage.frame = CGRectMake(0, 0, 0, 0);
        self.pVideoArrowImage.hidden = YES;
    }
    
    self.pImage.hidden = NO;
    [m_pImageStore releaseImageForView:self.pImage];
    
    [self.pImageLoadingSpinner startAnimating];
    
    self.pImage.frame = CGRectMake((w - TourDefines::ProfileImageSize)/2,
                                   labelContainerOffsetY,
                                   TourDefines::ProfileImageSize,
                                   TourDefines::ProfileImageSize);;
    
    if(m_imagePath.find("http") != std::string::npos)
    {
        [m_pImageStore loadImage:m_imagePath
                                :self.pImage
                                :^(UIImage* image)
         {
             self.pImage.image = image;
             [self.pImageLoadingSpinner stopAnimating];
             
         }
                                :TourDefines::ProfileImageSize];
    }
    else
    {
        [self.pImage setBackgroundColor: ExampleApp::Helpers::ColorPalette::TwitterBlue];
        [self.pImageLoadingSpinner stopAnimating];
    }
    
    
    const float arrowWidth = 16.f;
    self.pArrowContainer.frame = CGRectMake(w/2.f - arrowWidth/2.f, totalHeight, arrowWidth, arrowWidth);
    
    float trueY = m_previousY/m_pixelScale - m_pinOffset/m_pixelScale;
    float trueX = m_previousX/m_pixelScale;
    self.frame = CGRectMake(trueX - w/2, trueY - (totalHeight + arrowWidth), w, totalHeight + arrowWidth);
    
    m_cardHeight = totalHeight + arrowWidth;
}

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel
{
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(worldPinsInFocusModel.GetSubtitle().c_str());
    if(jsonDocument.HasParseError())
    {
        m_imagePath = "";
        m_isVideo = false;
    }
    else
    {
        Eegeo_ASSERT(jsonDocument.HasMember("pinImageUrl") &&
                     jsonDocument.HasMember("isVideo"));
        
        m_imagePath = jsonDocument["pinImageUrl"].GetString();
        m_isVideo = jsonDocument["isVideo"].GetBool();
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