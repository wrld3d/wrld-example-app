// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "WatermarkViewInterop.h"
#include "MathFunc.h"
#include "ImageHelpers.h"
#include "UIHelpers.h"
#include "WatermarkData.h"

const float InteriorStylingEnabledAlpha = 0.5f;
const float InteriorStylingDisabledAlpha = 0.8f;

@interface WatermarkView()

- (void) fitToSize:(CGSize)size withActivePosition:(bool)active;
- (void) updateYPositions;
@end

@implementation WatermarkView

- (ExampleApp::Watermark::View::WatermarkViewInterop *)getInterop
{
    return m_pInterop;
}


- (id) initWithScreenDimensions:(float)width
                               :(float)height
                               :(float)pixelScale
                               :(const ExampleApp::Watermark::View::WatermarkData&) watermarkData
{
    if(self = [super init])
    {
        m_pController = [UIViewController alloc];
        [m_pController setView:self];
        
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        
        m_pInterop = new ExampleApp::Watermark::View::WatermarkViewInterop(self);
        
        const float initialWidth = 140;
        const float initialHeight = 52;
        m_width = initialWidth*pixelScale;
        m_height = initialHeight*pixelScale;
        m_alignAlongBottom = !ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
        m_alignBelowFloorDisplay = false;
        [self updateYPositions];
        
        self.pButton = [[UIButton alloc] init];
        [self fitToSize:CGSizeMake(initialWidth, initialHeight) withActivePosition:false];
        self.pShadowGradient = [[UIView alloc] initWithFrame:CGRectMake(0, 0, m_screenWidth, m_height)];
        
        CAGradientLayer *gradient = [CAGradientLayer layer];
        gradient.frame =  CGRectMake(0, 0.f, m_screenWidth, m_screenHeight - m_yPosActive);
        
        UIColor *topColor = [UIColor clearColor];
        UIColor *bottomColor = [[UIColor blackColor] colorWithAlphaComponent:0.85];
        
        gradient.colors = [NSArray arrayWithObjects:(id)[topColor CGColor], (id)[bottomColor CGColor], nil];
        
        [self.pShadowGradient.layer insertSublayer:gradient atIndex:0];
        self.pShadowGradient.layer.shouldRasterize = YES;
        [self.pShadowGradient setAlpha:0.0];
        [self addSubview:self.pShadowGradient];
        
        m_stateChangeAnimationTimeSeconds = 0.2f;
        [self addSubview: self.pButton];
        
        [self.pButton addTarget:self action:@selector(onClick:) forControlEvents:UIControlEventTouchUpInside];
        [self updateWatermarkData: watermarkData];
        
        [self.pButton setAlpha:0.8];

#ifdef AUTOMATED_SCREENSHOTS
        // move offscreen
        m_yPosActive = -10000.f;
        m_yPosActive = -10000.f;
#endif
    }
    
    return self;
}

- (void)dealloc
{
    [self.pButton removeFromSuperview];
    [self.pButton release];
    
    [self.pShadowGradient removeFromSuperview];
    [self.pShadowGradient release];
    
    delete m_pInterop;
    [m_pController release];
    [super dealloc];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.pButton.frame, touchLocation);
}

- (void) onClick:(UIButton *)sender
{
    NSString* alertTitle = [NSString stringWithUTF8String: m_popupTitle.c_str()];
    NSString* alertMessage = [NSString stringWithUTF8String: m_popupBody.c_str()];
    NSString* cancelMessage = @"Later";
    NSString* goToSiteMessage = @"Find Out More";
    
    if([UIAlertController class])
    {
        UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle
                                                                       message:alertMessage
                                                                preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction* openSiteAction = [UIAlertAction actionWithTitle:goToSiteMessage
                                                                 style:UIAlertActionStyleDefault
                                                               handler:^(UIAlertAction * action) { [self goToWatermarkUrl]; }];
        
        UIAlertAction* cancelAction = [UIAlertAction actionWithTitle:cancelMessage
                                                               style:UIAlertActionStyleCancel
                                                             handler:^(UIAlertAction * action) {}];
        
        [alert addAction:openSiteAction];
        [alert addAction:cancelAction];
        [m_pController presentViewController:alert animated:YES completion:nil];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:self
                                              cancelButtonTitle:cancelMessage
                                              otherButtonTitles:goToSiteMessage, nil];
        
        
        
        [alert show];
        [alert release];
    }
    
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

- (void) goToWatermarkUrl
{
    NSString* urlString = [NSString stringWithUTF8String: m_webUrl.c_str()];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:urlString]];
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex == 1)
    {
        [self goToWatermarkUrl];
    }
}

- (void) updateWatermarkData: (const ExampleApp::Watermark::View::WatermarkData&) watermarkData
{
    m_popupTitle = watermarkData.PopupTitle();
    m_popupBody = watermarkData.PopupBody();
    m_webUrl = watermarkData.WebUrl();
    m_shouldShowShadow = watermarkData.ShouldShowShadow();
    
    const std::string& newImageAssetName = watermarkData.ImageAssetName();
    bool shouldTransitionImage = newImageAssetName != m_imageAssetName;
    
    if (shouldTransitionImage)
    {
        m_imageAssetName = newImageAssetName;
        [self transitionToNewImage];
    }
    
    if((self.frame.origin.y != m_yPosActive && self.frame.origin.y != m_yPosInactive) && !self.hidden)
    {
        [self transitionToNewPosition];
    }
}

- (void) transitionToNewImage
{
    NSString* assetString = [NSString stringWithUTF8String: m_imageAssetName.c_str()];
    UIImage* newImage = ExampleApp::Helpers::ImageHelpers::LoadImage(assetString);
    if (self.frame.origin.y == m_yPosInactive)
    {
        [self fitToSize:newImage.size withActivePosition:false];
    }
    
    CABasicAnimation *crossFade = [CABasicAnimation animationWithKeyPath:@"contents"];
    
    crossFade.duration = 0.2;
    crossFade.fromValue = (id)self.pButton.currentBackgroundImage.CGImage;
    crossFade.toValue = (id)newImage.CGImage;
    crossFade.removedOnCompletion = NO;
    crossFade.fillMode = kCAFillModeForwards;
    
    const float  fadeTo = m_shouldShowShadow ? 1.0f : 0.0f;
    const float fadeDelay = m_alignAlongBottom ? m_stateChangeAnimationTimeSeconds : 0.0f;
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds delay:fadeDelay options:UIViewAnimationOptionCurveEaseInOut
                     animations:^
     {
         [self.pShadowGradient setAlpha:fadeTo];
     }
                     completion:^(BOOL finished)
     {
     }];
    
    [CATransaction begin];
    {
        [CATransaction setCompletionBlock: ^
         {
             [self.pButton setBackgroundImage: self.pButton.imageView.image forState:UIControlStateNormal];
             [self.pButton setImage: nil forState: UIControlStateNormal];
         }];
        
        [self.pButton.imageView.layer addAnimation:crossFade forKey:@"animateContents"];
        [self.pButton setImage:newImage forState:UIControlStateNormal];
        [self.pButton setBackgroundImage: nil forState:UIControlStateNormal];
    }
    
    
    [CATransaction commit];
}

- (void) transitionToNewPosition
{
    float inactivePos = !m_alignAlongBottom ? (m_screenHeight + m_height) : (-m_height);
    
    if(self.frame.origin.y >= m_screenHeight * 0.5f && inactivePos < m_screenHeight * 0.5f)
    {
        inactivePos = (m_screenHeight + m_height);
    }
    else if(self.frame.origin.y < m_screenHeight * 0.5f && inactivePos >= m_screenHeight * 0.5f)
    {
        inactivePos = (-m_height);
    }
    
    CGRect f = self.frame;
    f.origin.y = inactivePos;
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^
     {
         self.frame = f;
     }
                     completion:^(BOOL finished)
     {
         [self fitToSize:self.pButton.currentBackgroundImage.size withActivePosition:false];
         [self animateToY:m_yPosActive];
     }
     ];
}

- (void) setWatermarkAlignmentState: (bool) alignAlongBottom
                                   : (bool) alignBelowFloorDisplay
{
    if (!ExampleApp::Helpers::UIHelpers::UsePhoneLayout())
    {
        return;
    }
    
    m_alignBelowFloorDisplay = alignBelowFloorDisplay;
    m_alignAlongBottom = alignAlongBottom;

    [self updateYPositions];
    
    CALayer* gradient = [self.pShadowGradient.layer.sublayers objectAtIndex:0];
    gradient.frame = CGRectMake(0, 0.f, m_screenWidth, m_screenHeight - m_yPosActive);
}

- (void) fitToSize:(CGSize)size withActivePosition:(bool)active
{
    m_width = size.width * m_pixelScale;
    m_height = size.height * m_pixelScale;
    
    float xPosition = ExampleApp::Helpers::UIHelpers::UsePhoneLayout()
      ? m_screenWidth*0.5f - m_width*0.5f
      : 30*m_pixelScale;
    
    [self updateYPositions];
    [self.pButton setFrame:CGRectMake(xPosition, 0, m_width, m_height)];
    [self setFrame:CGRectMake(0, active ? m_yPosActive : m_yPosInactive, m_screenWidth, m_height)];
}

- (void) setInteriorStylingState: (bool) shouldUseInteriorStyle
{
    self.pButton.alpha = shouldUseInteriorStyle ? InteriorStylingEnabledAlpha : InteriorStylingDisabledAlpha;
}

- (void) updateYPositions
{
    if (!m_alignAlongBottom)
    {
        m_yPosActive = m_alignBelowFloorDisplay
            ? m_height + 40*m_pixelScale
            : 20 * m_pixelScale;
        m_yPosInactive = -m_height;
    }
    else
    {
        m_yPosActive = m_screenHeight - m_height - (8 * m_pixelScale);
        m_yPosInactive = (m_screenHeight + m_height);
    }
}

@end
