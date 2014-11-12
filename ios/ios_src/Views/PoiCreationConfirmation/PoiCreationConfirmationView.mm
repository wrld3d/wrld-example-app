// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PoiCreationConfirmationView.h"
#include "UIColors.h"
#include "ImageHelpers.h"

@implementation PoiCreationConfirmationView

- (id) initWithParams:(PoiCreationConfirmationViewController *)controller :(float)width :(float)height :(float)pixelScale
{
    if (self = [super init])
    {
        m_pController = controller;
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        
        const float containerWidth = m_screenWidth;
        const float containerHeight = 90.f;
        
        m_yPosInactive = m_screenHeight + containerHeight;
        m_yPosActive = m_screenHeight - containerHeight;

        self.frame = CGRectMake(0, m_screenHeight - containerHeight, m_screenWidth, containerHeight);
        
        self.pTitleBar = [[[UIView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pTitleBar];
        const float titleBarHeight = 20.f;
        self.pTitleBar.frame = CGRectMake(0, 0, m_screenWidth, titleBarHeight);
        [self.pTitleBar setBackgroundColor: [UIColor whiteColor]];
        
        const float textPadding = 2.f;
        self.pTitleBarText = [[[UILabel alloc] initWithFrame: self.pTitleBar.frame] autorelease];
        self.pTitleBarText.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        [self.pTitleBar addSubview: self.pTitleBarText];
        
        self.pTitleBarText.frame = CGRectMake(textPadding, textPadding, containerWidth - textPadding, titleBarHeight - textPadding);
        self.pTitleBarText.center =  self.pTitleBar.center;
        
        self.pTitleBarText.font = [UIFont systemFontOfSize:13.0f];
        self.pTitleBarText.text = @"Drag the marker to place your pin";
        self.pTitleBarText.textAlignment = UITextAlignmentCenter;
        
        self.pMainSection = [[[UIView alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self addSubview: self.pMainSection];
        self.pMainSection.frame = CGRectMake(0.f, titleBarHeight, containerWidth, containerHeight - titleBarHeight);
        [self.pMainSection setBackgroundColor: ExampleApp::Helpers::ColorPalette::GoldTone];
        
        const float shadowHeight = 10.f;
        ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self, "shadow_03", 0.f, titleBarHeight, containerWidth, shadowHeight);
        
        const float buttonSize = containerHeight - titleBarHeight;

        self.pCancelButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pMainSection addSubview: self.pCancelButton];
    
        self.pCancelButton.frame = CGRectMake(0, 0, buttonSize, buttonSize);
        [self.pCancelButton setBackgroundImage:[UIImage imageNamed:@"button_close_off.png"] forState:UIControlStateNormal];
        [self.pCancelButton addTarget:self action:@selector(onCancelButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
        
        self.pConfirmButton = [[[UIButton alloc] initWithFrame: CGRectMake(0, 0, 0, 0)] autorelease];
        [self.pMainSection addSubview: self.pConfirmButton];
        
        self.pConfirmButton.frame = CGRectMake(containerWidth - buttonSize, 0, buttonSize, buttonSize);
        [self.pConfirmButton setBackgroundImage:[UIImage imageNamed:@"button_ok.png"] forState:UIControlStateNormal];
        [self.pConfirmButton addTarget:self action:@selector(onOkayButtonPressed:) forControlEvents:UIControlEventTouchUpInside];
    }
    
    return self;
}

- (void) onCancelButtonPressed:(UIButton *)sender
{
    [sender setSelected:!sender.selected];
    [m_pController handleCloseButtonSelected];
}

- (void) onOkayButtonPressed:(UIButton *)sender
{
    [sender setSelected:!sender.selected];
    [m_pController handleConfirmButtonSelected];
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.bounds, touchLocation);
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;
    
    self.hidden = false;
    CGRect f = self.frame;
    f.origin.y = newY;
    self.frame = f;
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

- (void) animateToY:(float)y
{
    CGRect f = self.frame;
    f.origin.y = y;
    
    if(y != m_yPosInactive)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                     animations:^{
                         self.frame = f;
                     }
                     completion:^(BOOL finished){
                         self.hidden = (y == m_yPosInactive);
                     }
     ];
}

@end