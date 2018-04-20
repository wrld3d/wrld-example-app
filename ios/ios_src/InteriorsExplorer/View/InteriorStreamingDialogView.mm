// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorStreamingDialogView.h"
#include "InteriorStreamingDialogViewInterop.h"
#include "ImageHelpers.h"
#include "UIHelpers.h"
#include "UIColors.h"

@implementation InteriorStreamingDialogView

- (ExampleApp::InteriorsExplorer::View::InteriorStreamingDialogViewInterop*) getInterop
{
    return m_pInterop;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale
{
    if (self = [super init])
    {
        m_pixelScale = 1.0f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        
        m_pInterop = new ExampleApp::InteriorsExplorer::View::InteriorStreamingDialogViewInterop(self);
        
        self.pControlContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 0.0f, 0.0f)] autorelease];
        self.pControlContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        self.pControlContainer.layer.borderColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor.CGColor;
        self.pControlContainer.layer.borderWidth = 1.0f;
        [self addSubview: self.pControlContainer];
        
        self.pStreamingCompleteImage = [[[UIImageView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 62.0f, 62.0f)] autorelease];
        self.pStreamingCompleteImage.center = CGPointMake(0.0f, 0.0f);
        self.pStreamingCompleteImage.image = ExampleApp::Helpers::ImageHelpers::LoadImage(@"streaming_dialog_loaded");
        [self.pControlContainer addSubview: self.pStreamingCompleteImage];
        
        self.pSpinner = [[[InteriorStreamingDialogSpinner alloc] init] autorelease];
        self.pSpinner.center = CGPointMake(0.0f, 0.0f);
        [self.pControlContainer addSubview: self.pSpinner];
        
        self.pMainLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 0.0f, 0.0f)] autorelease];
        self.pMainLabel.textColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pMainLabel];
        
        self.pDescriptionLabel = [[[UILabel alloc] initWithFrame:CGRectMake(0.0f, 0.0f, 0.0f, 0.0f)] autorelease];
        self.pDescriptionLabel.textColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview: self.pDescriptionLabel];
        
        self.pDescriptionLabelSeparator = [[[UIView alloc] initWithFrame:CGRectMake(0.0f,0.0f,0.0f,0.0f)] autorelease];
        self.pDescriptionLabelSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
        [self.pControlContainer addSubview:self.pDescriptionLabelSeparator];
        
        [self setAlpha:0.0f];
        [self setHidden:YES];
    }
    return self;
}

- (void) dealloc
{
    delete m_pInterop;
    
    [self.pDescriptionLabelSeparator removeFromSuperview];
    [self.pDescriptionLabelSeparator dealloc];
    
    [self.pDescriptionLabel removeFromSuperview];
    [self.pDescriptionLabel dealloc];
    
    [self.pMainLabel removeFromSuperview];
    [self.pMainLabel dealloc];
    
    [self.pSpinner removeFromSuperview];
    [self.pSpinner release];
    
    [self.pStreamingCompleteImage removeFromSuperview];
    [self.pStreamingCompleteImage release];
    
    [self.pControlContainer removeFromSuperview];
    [self.pControlContainer dealloc];
    
    [self removeFromSuperview];
    [super dealloc];
}

- (void) layoutSubviews
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float seperatorSize = 15.0f;
    const float marginPadding = 28.0f;
    
    const float boundsWidth = static_cast<float>(self.superview.bounds.size.width);
    const float boundsHeight = static_cast<float>(self.superview.bounds.size.height);
    const float mainWindowWidth = isPhone ? boundsWidth - (2 * marginPadding) : 319.0f;
    const float mainWindowHeight = 240.0f;
    const float mainWindowX = isPhone ? marginPadding : (boundsWidth * 0.5f) - (mainWindowWidth * 0.5f);
    const float mainWindowY = (boundsHeight * 0.5f) - (mainWindowHeight * 0.5f);
    
    self.frame = CGRectMake(mainWindowX,
                            mainWindowY,
                            mainWindowWidth,
                            mainWindowHeight);
    
    const float controlContainerX = 0.0f;
    const float controlContainerY = 0.0f;
    const float controlContainerWidth = mainWindowWidth;
    const float controlContainerHeight = mainWindowHeight;
    
    self.pControlContainer.frame = CGRectMake(controlContainerX,
                                              controlContainerY,
                                              controlContainerWidth,
                                              controlContainerHeight);
    
    const float spinnerHeight = static_cast<float>(self.pSpinner.bounds.size.height);
    const float spinnerCenterX = controlContainerWidth / 2.0f;
    const float spinnerCenterY = (2 * seperatorSize) + (spinnerHeight / 2.0f);
    self.pSpinner.center = CGPointMake(spinnerCenterX,
                                       spinnerCenterY);
    
    self.pStreamingCompleteImage.center = CGPointMake(spinnerCenterX,
                                                      spinnerCenterY);
    
    const float mainLabelX = (2 * seperatorSize);
    const float mainLabelY = spinnerHeight + (3 * seperatorSize);
    const float mainLabelWidth = mainWindowWidth - (4 * seperatorSize);
    const float mainLabelHeight = (2 * seperatorSize);
    
    self.pMainLabel.font = [UIFont boldSystemFontOfSize:24.0f];
    self.pMainLabel.text = @"Loading Indoor Map";
    self.pMainLabel.frame = CGRectMake(mainLabelX,
                                       mainLabelY,
                                       mainLabelWidth,
                                       mainLabelHeight);
    self.pMainLabel.textAlignment = NSTextAlignmentCenter;
    
    const float descriptionLabelX = (2 * seperatorSize);
    const float descriptionLabelY = mainLabelY + mainLabelHeight + seperatorSize;
    const float descriptionLabelWidth = mainWindowWidth - (4 * seperatorSize);
    const float descriptionLabelHeight = 0.0f;
    const float descriptionPadding = 4.0f;
    const float descriptionUpperPadding = 8.0f;
    self.pDescriptionLabel.font = [UIFont systemFontOfSize:16.0f];
    self.pDescriptionLabel.text = @"We're saving this indoor map to your device, so your next visit is much faster.";
    self.pDescriptionLabel.numberOfLines = 0;
    self.pDescriptionLabel.frame = CGRectMake(descriptionLabelX+descriptionPadding,
                                             descriptionLabelY+descriptionPadding+descriptionUpperPadding,
                                             descriptionLabelWidth-(descriptionPadding*2),
                                             descriptionLabelHeight-(descriptionPadding*2));
    [self.pDescriptionLabel sizeToFit];
    
    self.pDescriptionLabelSeparator.frame = CGRectMake(descriptionLabelX,
                                                       descriptionLabelY,
                                                       descriptionLabelWidth,
                                                       1.0f);
    
    CGRect newControlContainerFrame = self.pControlContainer.frame;
    newControlContainerFrame.size.height =  descriptionLabelY + static_cast<float>(self.pDescriptionLabel.bounds.size.height) + (2 * seperatorSize);
    newControlContainerFrame.origin.y = (mainWindowHeight * 0.5f) - (newControlContainerFrame.size.height * 0.5f);
    
    [self.pControlContainer setFrame:newControlContainerFrame];
}

- (void) show
{
    if (self.hidden)
    {
        [self setHidden:NO];
        [self animateToAlpha:1.0f withFadeTime:0.5f thenSetHidden:NO withDelay:0.0f];
        
        [self.pSpinner setHidden:NO];
        [self.pSpinner startAnimating];
        
        [self.pStreamingCompleteImage setHidden:YES];
    }
}

- (void) hide
{
    if (!self.hidden)
    {
        [self.pSpinner stopAnimating];
        [self animateToAlpha:0.0f withFadeTime:0.5f thenSetHidden:YES withDelay:2.0f];
        
        [self.pSpinner setHidden:YES];
        [self.pSpinner stopAnimating];
        
        [self.pStreamingCompleteImage setHidden:NO];
    }
}

- (void) animateToAlpha:(float)fadeToAlpha
           withFadeTime:(float)fadeTime
          thenSetHidden:(bool)setHidden
              withDelay:(float)delayTime
{
    [UIView animateWithDuration:fadeTime
                          delay:delayTime
                        options:0
                     animations:^{self.alpha = fadeToAlpha;}
                     completion:^(BOOL finished) {
                         if (finished && setHidden)
                         {
                             [self setHidden:YES];
                         }
                     }];
}

@end
