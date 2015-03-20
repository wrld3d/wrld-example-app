// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "WatermarkViewInterop.h"
#include "MathFunc.h"
#include "ImageHelpers.h"
#include "App.h"

@implementation WatermarkView

- (ExampleApp::Watermark::View::WatermarkViewInterop *)getInterop
{
    return m_pInterop;
}

- (id) initWithDimensions:(float)width :(float)height :(float)pixelScale
{
    if(self = [super init])
    {
        [self setAlpha:0.8f];
        
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;

        m_pInterop = new ExampleApp::Watermark::View::WatermarkViewInterop(self);
        [self addTarget:self action:@selector(onClick:) forControlEvents:UIControlEventTouchUpInside];
        [self setBackgroundImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"eegeo_logo") forState:UIControlStateNormal];
        
        m_width = 140 * m_pixelScale;
        m_height = 52 * m_pixelScale;
        
        if(App::IsDeviceSmall())
        {
            m_yPosActive = (20 * m_pixelScale);
            m_yPosInactive = (-m_height);
            
            self.frame = CGRectMake(((m_screenWidth * 0.5f) - (m_width * 0.5f)),
                                    m_yPosInactive,
                                    m_width,
                                    m_height);
        }
        else
        {
            m_yPosActive = m_screenHeight - m_height - (8 * m_pixelScale);
            m_yPosInactive = (m_screenWidth + m_height);
            
            self.frame = CGRectMake(((m_screenWidth) - (m_width) - (8 * m_pixelScale)),
                                    m_yPosInactive,
                                    m_width,
                                    m_height);
        }
        
        m_stateChangeAnimationTimeSeconds = 0.2f;
    }

    return self;
}

- (void)dealloc
{
    delete m_pInterop;
    [super dealloc];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) onClick:(UIButton *)sender
{   
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Maps by eeGeo"
                                                    message:@"This application is built using the eeGeo SDK, a cross-platform API for building immersive, engaging maps. Click 'Yes' to visit eeGeo SDK website and find out more."
                                                   delegate:self
                                          cancelButtonTitle:@"Later"
                                          otherButtonTitles:@"Yes", nil];
    
    
    [alert show];
    [alert release];
    
    m_pInterop->OnSelected();
}

- (void) setFullyOnScreen
{
    if(self.frame.origin.y == m_yPosActive)
    {
        return;
    }
    
    [self animateToY:m_yPosActive];
}

- (void) setFullyOffScreen
{
    if(self.frame.origin.y == m_yPosInactive)
    {
        return;
    }
    
    [self animateToY:m_yPosInactive];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;
    
    self.hidden = false;
    CGRect f = self.frame;
    f.origin.y = newY;
    self.frame = f;
}

- (void) animateToY:(float)y
{
    CGRect f = self.frame;
    f.origin.y = y;
    
    if(y != m_yPosInactive)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.frame = f;
     }
                     completion:^(BOOL finished)
     {
         self.hidden = (y == m_yPosInactive);
     }
     ];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1)
    {
        [[UIApplication sharedApplication] openURL:[NSURL URLWithString:@"http://sdk.eegeo.com"]];
    }
}

@end

