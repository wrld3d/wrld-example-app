// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapView.h"
#include <algorithm>
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
        m_pinOffset = (pinDiameter * pixelScale);
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
        
        // image container
        self.pImageDisplay = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 115, 25)] autorelease];
        [self.pLabelBack addSubview: self.pImageDisplay];
        
        // review count
        self.pReviewCountLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0, 0, 0, 0)] autorelease];
        self.pReviewCountLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pReviewCountLabel.textAlignment = NSTextAlignmentLeft;
        self.pReviewCountLabel.font = [UIFont systemFontOfSize:12.0];
        self.pReviewCountLabel.backgroundColor = [UIColor clearColor];
        [self.pLabelBack addSubview: self.pReviewCountLabel];
        
        // accreditation image (Only Yelp for now for reviews/ratings)
        self.pAccreditationImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, 51, 27)] autorelease];
        self.pAccreditationImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage("yelp_logo");
        [self.pLabelBack addSubview: self.pAccreditationImage];
        
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
    
    [self.pReviewCountLabel removeFromSuperview];
    [self.pReviewCountLabel release];
    
    [self.pAccreditationImage removeFromSuperview];
    [self.pAccreditationImage release];

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
    float w = 190.f; //self.superview.bounds.size.width/6;
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
    
    self.pImageDisplay.frame = CGRectMake(labelOffsetX,
                                          labelVerticalSpace + labelSpacing,
                                          0.f,
                                          0.f);
    self.pReviewCountLabel.frame = CGRectMake(labelOffsetX, labelVerticalSpace + labelSpacing, 0, 0);

    const float arrowWidth = 16.f;
    self.pArrowContainer.frame = CGRectMake(w/2.f - arrowWidth/2.f, h, arrowWidth, arrowWidth);

    self.frame = CGRectMake(x, y, w, h + arrowWidth);
}

- (void) setContent:(const std::string&)name :(const std::string&)subtitle :(const std::string&)ratingsImage :(const int)reviewCount;
{
    self.pNameLabel.text = [NSString stringWithUTF8String:name.c_str()];
    
    const bool hasRatingsImage = !ratingsImage.empty();
    
    bool usedImage = false;
    
    if(hasRatingsImage)
    {
        UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(ratingsImage);
        if(image != nil)
        {
            self.pAddressLabel.text = @"";
            
            [self.pImageDisplay setImage:image];
            [self.pImageDisplay setHidden:NO];
            
            CGRect frame = self.pImageDisplay.frame;
            frame.size = image.size;
            self.pImageDisplay.frame = frame;
            
            // Include review count.
            [self.pReviewCountLabel setHidden:NO];
            self.pReviewCountLabel.text = [NSString stringWithFormat:@"(%d)", reviewCount];
            self.pReviewCountLabel.frame = CGRectMake(frame.origin.x + frame.size.width + 4.0f,
                                                      frame.origin.y,
                                                      self.pLabelBack.frame.size.width - (frame.size.width + self.pAccreditationImage.frame.size.width),
                                                      frame.size.height);
            
            [self.pAccreditationImage setHidden:NO];
            self.pAccreditationImage.frame = CGRectMake(self.pLabelBack.frame.size.width - 51, self.pLabelBack.frame.size.height-27, 51, 27);
            
            usedImage = true;
        }
    }
    
    if(!usedImage)
    {
        self.pAddressLabel.text = [NSString stringWithUTF8String:subtitle.c_str()];
        [self.pImageDisplay setImage:nil];
        [self.pImageDisplay setHidden:YES];
        [self.pReviewCountLabel setHidden:YES];
        [self.pAccreditationImage setHidden:YES];
    }
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
        f.origin.y = static_cast<int>(trueY - (f.size.height));
        self.frame = f;
    }
    else
    {
        float trueY = y/m_pixelScale - m_pinOffset/m_pixelScale;
        float trueX = x/m_pixelScale;
        
        CGRect f = self.frame;
        f.origin.x = trueX - (f.size.width/2.f);
        f.origin.y = trueY - (f.size.height);
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
