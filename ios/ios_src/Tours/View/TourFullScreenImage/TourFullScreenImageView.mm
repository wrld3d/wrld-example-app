// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageView.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "TourFullScreenImageViewInterop.h"
#include "UIHelpers.h"

@implementation TourFullScreenImageView
{
    ExampleApp::Tours::View::TourFullScreenImage::TourFullScreenImageViewInterop* m_pInterop;
    float m_pixelScale;
    float m_width;
    float m_height;
    std::string m_imagePath;
    std::string m_message;
    bool m_enabled;
}

- (id)initWithParams:(float)width :(float)height :(float)pixelScale;
{
    self = [super init];
    
    if(self)
    {
        m_width = width / pixelScale;
        m_height = height / pixelScale;
        m_enabled = false;
        
        self.alpha = 0.f;
        
        m_pixelScale = pixelScale;
        
        m_pInterop = new ExampleApp::Tours::View::TourFullScreenImage::TourFullScreenImageViewInterop(self);
        
        self.pMainControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0, 0, m_width, m_height)] autorelease];
        self.pBackgroundImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0, 0, m_width, m_height)] autorelease];
        
        self.pMessage = [[UILabel alloc] initWithFrame:CGRectMake(0, 0, m_width, 0)];
        self.pMessage.backgroundColor = [UIColor clearColor];
        self.pMessage.textColor = [UIColor whiteColor];
        self.pMessage.textAlignment = NSTextAlignmentCenter;
        self.pMessage.numberOfLines = 0;
        self.pMessage.font = [self.pMessage.font fontWithSize: (ExampleApp::Helpers::UIHelpers::UsePhoneLayout() ? 24 : 36)];
        self.pMessage.layer.shadowColor = [[UIColor blackColor] CGColor];
        self.pMessage.layer.shadowOffset = CGSizeMake(0.0f, 1.0f);
        self.pMessage.layer.shadowOpacity = 1.0f;
        self.pMessage.layer.shadowRadius = 1.0f;
        
        [self.pBackgroundImage addSubview:self.pMessage];
        
        [self addSubview: self.pMainControlContainer];
    }
    
    return self;
}

- (void)dealloc
{
    [self.pMessage removeFromSuperview];
    [self.pMessage release];
    
    [self.pBackgroundImage removeFromSuperview];
    [self.pBackgroundImage release];
    
    [self.pMainControlContainer removeFromSuperview];
    [self.pMainControlContainer release];
    
    delete m_pInterop;
    
    [self removeFromSuperview];
    [super dealloc];
}

-(void)layoutSubviews
{
    [super layoutSubviews];
    
    const float screenMessageVerticalOffsetPercent = ExampleApp::Helpers::UIHelpers::UsePhoneLayout() ? 0.50f : 0.65f;
    
    self.pMessage.text = [NSString stringWithUTF8String:m_message.c_str()];
    [self.pMessage sizeToFit];
    self.pMessage.frame = CGRectMake((m_width * 0.5f) - (self.pMessage.frame.size.width * 0.5f),
                                     (m_height * screenMessageVerticalOffsetPercent) - (self.pMessage.frame.size.height * 0.5f),
                                     self.pMessage.frame.size.width,
                                     self.pMessage.frame.size.height);
    
    UIImage* image = ExampleApp::Helpers::ImageHelpers::LoadImage(m_imagePath);
    const bool hasImage = image != nil;
    
    self.frame = CGRectMake(self.frame.origin.x,
                            self.frame.origin.y,
                            m_width,
                            m_height);
    
    self.pMainControlContainer.frame = CGRectMake(0, 0, m_width, m_height);
    
    self.pBackgroundImage.frame = CGRectMake(0, 0, m_width, m_height);
    
    [self.pMainControlContainer setBackgroundColor:[UIColor clearColor]];
    
    [self.pBackgroundImage removeFromSuperview];
    
    if(hasImage)
    {
        [self.pBackgroundImage setImage:image];
        self.pBackgroundImage.contentMode = UIViewContentModeScaleAspectFill;
        [self.pMainControlContainer addSubview: self.pBackgroundImage];
        self.alpha = 1.f;
        [self playShowCeremony :1.f];
        m_enabled = true;
    }
}

- (ExampleApp::Tours::View::TourFullScreenImage::TourFullScreenImageViewInterop*) getInterop
{
    return m_pInterop;
}

- (void) beginCeremony:(const std::string&)asset :(const std::string&)message
{
    m_imagePath = asset;
    m_message = message;
    
    [self setNeedsLayout];
}

- (void) endCeremony
{
    m_imagePath = "";
    m_message = "";
    m_enabled = false;
    
    [self playHideCeremony :1.f];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    if(m_enabled && self.userInteractionEnabled)
    {
        CGPoint touchLocation = [touch locationInView:self];
        return CGRectContainsPoint(self.bounds, touchLocation);
    }
    
    return false;
}

- (void) playShowCeremony:(float)transitionTimeSeconds
{
    self.userInteractionEnabled = true;
    self.pBackgroundImage.alpha = 0.f;
    self.pMessage.alpha = 0.f;
    self.pBackgroundImage.frame = CGRectMake((m_width * 0.5f) - (m_width * 0.1f),
                                             (m_height * 0.5f) - (m_height * 0.1f),
                                             (m_width * 0.2f),
                                             (m_height * 0.2f));
    
    [UIView animateWithDuration:transitionTimeSeconds
                     animations:^
     {
         self.pBackgroundImage.alpha = 1.f;
         self.pBackgroundImage.frame = CGRectMake(0, 0, m_width, m_height);
     }
                    completion:^(BOOL finished)
     {
         if(finished)
         {
             [UIView animateWithDuration:transitionTimeSeconds animations:^ {
                 self.pMessage.alpha = 1.f;
             }];
         }
     }];
}


- (void) playHideCeremony:(float)transitionTimeSeconds
{
    [UIView animateWithDuration:transitionTimeSeconds
                     animations:^
     {
         self.pBackgroundImage.alpha = 0.f;
         [self.pBackgroundImage removeFromSuperview];
         self.userInteractionEnabled = false;
     }];
}

@end
