// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourHovercardView.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "WorldPinOnMapViewInterop.h"
#include "App.h"
#include "Document.h"
#include "ImageStore.h"
#include "TourDefines.h"

@implementation TourHovercardView
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
        
        // image/video
        self.pImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pImage.contentMode = UIViewContentModeScaleAspectFit;
        self.pVideoArrowImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pImage];
        [self.pImage addSubview: self.pVideoArrowImage];
        
        m_pPlayIconImage = ExampleApp::Helpers::ImageHelpers::LoadImage("Tours/States/Twitter/play_icon");
        [m_pPlayIconImage retain];
        
        self.pImageLoadingSpinner = [[[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleWhiteLarge] autorelease];
        self.pImageLoadingSpinner.color = [UIColor colorWithRed:m_baseColor.GetRedF() green:m_baseColor.GetGreenF() blue:m_baseColor.GetBlueF() alpha:1.0f];
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
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void)layoutSubviews
{
    
    self.layer.shouldRasterize = YES;
    self.layer.rasterizationScale = [[UIScreen mainScreen] scale];
    
    // figures from a proportional size of an iPad2 screen -- use const so not proportional to small screens on iPhones.
    const float w = 162.f;
    const float h = 56.f;
    const float imageOffsetY = 4;
    const float labelContainerOffsetY = 6.f;
    const float labelVerticalSpace = h*0.4f;
    const float labelSpacing = h*0.05f;
    const float labelOffsetX = 4.f;
    const float labelOffsetY = 2.f;
    float heightWithImage = labelContainerOffsetY + labelOffsetY + labelVerticalSpace + imageOffsetY + TourDefines::ProfileImageSize;
    const float videoArrowSize = 68.f;
    
    bool hasImage = m_imagePath != "";
    float totalHeight = hasImage ? heightWithImage : h;
    
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, w, totalHeight);
    self.pMainControlShadowContainer.frame = CGRectMake(2.f, 2.f, w, totalHeight);
    
    
    const CGFloat labelContainerHeight = self.pMainControlContainer.frame.size.height - labelContainerOffsetY;
    
    self.pTopStrip.frame =  CGRectMake(0.f, 0.f, w, labelContainerOffsetY);
    self.pLabelBack.frame = CGRectMake(0.f, labelContainerOffsetY, w, labelContainerHeight);
    
    self.pNameLabel.frame = CGRectMake(labelOffsetX,
                                       labelOffsetY,
                                       w - (labelOffsetX*2),
                                       labelVerticalSpace);
    
    self.pInfoLabel.frame = CGRectMake(labelOffsetX,
                                          labelVerticalSpace + labelSpacing,
                                          w - (labelOffsetX*2),
                                          labelVerticalSpace);
    
    if(hasImage)
    {
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
                                       totalHeight - (TourDefines::ProfileImageSize + (imageOffsetY/2)),
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
            UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(m_imagePath);
            [self.pImage setImage:image];
            [self.pImageLoadingSpinner stopAnimating];
        }
    }
    else
    {
        CGRect zeroFrame = CGRectMake(0, 0, 0, 0);
        self.pImage.frame = zeroFrame;
        self.pImage.hidden = YES;
        self.pVideoArrowImage.image = nil;
        self.pVideoArrowImage.frame = zeroFrame;
        self.pVideoArrowImage.hidden = YES;
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
    self.pNameLabel.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetTitle().c_str()];
    
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(worldPinsInFocusModel.GetSubtitle().c_str());
    if(jsonDocument.HasParseError())
    {
        self.pInfoLabel.text = [NSString stringWithUTF8String:worldPinsInFocusModel.GetSubtitle().c_str()];
        m_imagePath = "";
        m_isVideo = false;
    }
    else
    {
        Eegeo_ASSERT(jsonDocument.HasMember("pinImageUrl") &&
                     jsonDocument.HasMember("isVideo"));
        self.pInfoLabel.text = @"";
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


- (void) setPresentationColors :(ExampleApp::Helpers::ColorHelpers::Color)baseColor :(ExampleApp::Helpers::ColorHelpers::Color)textColor
{
    m_baseColor = baseColor;
    m_textColor = textColor;
    
    [self.pTopStrip setBackgroundColor: [UIColor colorWithRed:m_baseColor.GetRedF() green:m_baseColor.GetGreenF() blue:m_baseColor.GetBlueF() alpha:1.0f]];
    self.pImageLoadingSpinner.color = [UIColor colorWithRed:m_baseColor.GetRedF() green:m_baseColor.GetGreenF() blue:m_baseColor.GetBlueF() alpha:1.0f];
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

