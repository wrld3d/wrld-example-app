// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourExplorerView.h"
#include "MyPinCreationConfirmationViewInterop.h"
#include "TourExplorerViewInterop.h"
#include "iCarouselTourExplorerViewController.h"
#include "ColorHelpers.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "UIHelpers.h"

#import "UIButton+DefaultStates.h"
#import "UIView+TouchExclusivity.h"

@implementation TourExplorerView
{
    iCarouselTourExplorerViewController* m_viewController;
    ExampleApp::Tours::SdkModel::TourModel m_tour;
    ExampleApp::Tours::SdkModel::TourModel m_nextTour;
    bool m_isInterruptingTour;
    bool m_hasActiveTour;
    bool m_exitingTour;
    bool m_dismissingTour;
    
    CGPoint m_controlStartPos;
}

- (ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop*) getInterop
{
    return m_pInterop;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale :(ExampleApp::URLRequest::View::URLRequestHandler&) urlRequestHandler  :(ImageStore*)pImageStore
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    if (self = [super init])
    {
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_hasActiveTour = false;
        m_exitingTour = false;
        m_dismissingTour = false;
        
        m_pInterop = new ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop(self,urlRequestHandler);
        
        m_viewController = [[iCarouselTourExplorerViewController alloc] initWithParams
                            :m_screenWidth
                            :m_screenHeight
                            :m_pixelScale
                            :self
                            :@selector(onSelectionChanged)
                            :@selector(onCurrentSelectionTapped)
                            :@selector(onCurrentItemChanged)
                            :m_pInterop
                            :pImageStore];
        
        UIView* pViewImplementation = [self->m_viewController getView];
        
        
        // MB: TODO: viewImplementation's frame isn't actually a containing size - suspect nonsense with differing card sizes - will resolve when unify card theme sizes.
        // For now, just fix the size.
        const float carouselHeight = [m_viewController getItemHeight ];
        
        m_pCarouselContainer = [[UIView alloc] initWithFrame:CGRectMake(0, 0, m_screenWidth, carouselHeight)];
        
        [self addSubview:m_pCarouselContainer];
        [m_pCarouselContainer addSubview:pViewImplementation];
        
        // Set the carousel control as a subview inside main view, origin at 0.
        CGRect carouselFrame = m_pCarouselContainer.frame;
        carouselFrame.origin = CGPointMake(0.f, 0.f);
        m_pCarouselContainer.frame = carouselFrame;
        pViewImplementation.frame = carouselFrame;
        
        // Scott -- hack -- as determined below.
        const float textLineHeight = 58.f;
        const float textVerticalPadding = 8.f;
        const float textHeight = (textLineHeight) + (textVerticalPadding * 2.f);
        
        self.frame = CGRectMake(0,
                                0,
                                m_screenWidth,
                                m_screenHeight);
        
        const float labelContainerHeight = ([self controlHeight] * 0.25f) + textHeight;
        CGRect labelContainerFrame = CGRectMake(0.f,
                                                self.frame.size.height - labelContainerHeight,
                                                carouselFrame.size.width,
                                                labelContainerHeight);
        
        m_pTourItemLabelContainer = [[UIView alloc] initWithFrame:labelContainerFrame];
        [self insertSubview:m_pTourItemLabelContainer belowSubview:m_pCarouselContainer];
        
        const float textVerticalOffset = labelContainerHeight - textHeight;
        m_pTourItemLabel = [[UILabel alloc] initWithFrame:CGRectMake(labelContainerFrame.origin.x,
                                                                     textVerticalOffset,
                                                                     labelContainerFrame.size.width,
                                                                     textHeight)];
        m_pTourItemLabel.backgroundColor = [UIColor clearColor];
        m_pTourItemLabel.textAlignment = NSTextAlignmentCenter;
        m_pTourItemLabel.numberOfLines = 0;
        m_pTourItemLabel.font = [m_pTourItemLabel.font fontWithSize:16];
        [m_pTourItemLabelContainer addSubview:m_pTourItemLabel];
        
        // Scott quick hack to get label height for desired number lines (currently 3).
        //m_pTourItemLabel.text = @"1 \n 2 \n 3";
        //[m_pTourItemLabel sizeToFit];
        //printf("textLineHeight = %f\n", m_pTourItemLabel.frame.size.height);
        
        const float gradientHeight = 60.f;
        m_pTourItemLabelGradientContainer = [[UIView alloc] initWithFrame:CGRectMake(0.f,
                                                                                     labelContainerFrame.origin.y - gradientHeight,
                                                                                     labelContainerFrame.size.width,
                                                                                     gradientHeight)];
        [self insertSubview:m_pTourItemLabelGradientContainer belowSubview:m_pCarouselContainer];
        
        m_yPosInactive = m_screenHeight + [self controlHeight];
        m_yPosActive = m_screenHeight - [self controlHeight];
        
        [self setTouchExclusivity: self];
        
        const float upperMargin = isPhone ? 20.0f : 50.0f;
        float backButtonSize = 40.f;
        float exitButtonSize = 40.f;
        const float labelLength = isPhone? 150.f : 200.f;
        
        const float detailsPanelHeight = 40.0f;
        float totalPanelLength = backButtonSize + labelLength + exitButtonSize;
        
        float totalPanelHeight = detailsPanelHeight;
        
        self.pDetailsPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_screenWidth * 0.5f - totalPanelLength * 0.5f, upperMargin, totalPanelLength, totalPanelHeight)] autorelease];
        
        UIColor* backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
        
        self.pExitButtonBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(backgroundColor)] autorelease];
        self.pExitButtonBackground.frame = CGRectMake(totalPanelLength-exitButtonSize, 0.0f, exitButtonSize, exitButtonSize);
        
        [self.pDetailsPanel addSubview:self.pExitButtonBackground];
        
        self.pBackButtonBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::ImageFromColor(backgroundColor)] autorelease];
        self.pBackButtonBackground.frame = CGRectMake(0.0f, 0.0f, backButtonSize, backButtonSize);
        
        [self.pDetailsPanel addSubview:self.pBackButtonBackground];
        
        self.pExitButton = [[UIButton alloc]initWithFrame:CGRectMake(0.0f, 0.0f, exitButtonSize, exitButtonSize)];
        [self.pExitButton setDefaultStatesWithImageName:@"button_close_off"];
        [self.pExitButton addTarget:self action:@selector(handleExitButtonTap) forControlEvents:UIControlEventTouchUpInside];
        [self.pExitButtonBackground addSubview:self.pExitButton];
        
        self.pExitButtonBackground.userInteractionEnabled = YES;
        
        self.pBackButton = [[UIButton alloc]initWithFrame:CGRectMake(0.0f, 0.0f, backButtonSize, backButtonSize)];
        [self.pBackButton setDefaultStatesWithImageName:@"Arrow"];
        [self.pBackButton setImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"Arrow") forState:UIControlStateNormal];
        [self.pBackButton addTarget:self action:@selector(handleBackButtonTap) forControlEvents:UIControlEventTouchUpInside];
        [self.pBackButtonBackground addSubview:self.pBackButton];
        
        self.pBackButtonBackground.userInteractionEnabled = YES;
        
        self.pDetailsPanelBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"place_pin_background")] autorelease];
        
        self.pDetailsPanelBackground.frame = CGRectMake(backButtonSize, 0, labelLength, detailsPanelHeight);
        
        [self.pDetailsPanel addSubview:self.pDetailsPanelBackground];
        
        const float textPadding = 2.f;
        
        self.pTourNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake( textPadding + exitButtonSize, textPadding, labelLength - textPadding, detailsPanelHeight - textPadding)] autorelease];
        self.pTourNameLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColor;
        self.pTourNameLabel.textAlignment = NSTextAlignmentCenter;
        [self.pDetailsPanel addSubview:self.pTourNameLabel];
        
        
        [self addSubview:self.pDetailsPanel];
    }
    
    return self;
}

- (void)dealloc
{
    
    [self.pBackButton removeFromSuperview];
    [self.pBackButton release];
    self.pBackButton = nil;
    
    [self.pBackButtonBackground removeFromSuperview];
    [self.pBackButtonBackground release];
    self.pBackButtonBackground = nil;
    
    [self.pExitButton removeFromSuperview];
    [self.pExitButton release];
    self.pExitButton = nil;
    
    [self.pExitButtonBackground removeFromSuperview];
    [self.pExitButtonBackground release];
    self.pExitButtonBackground = nil;
    
    [self.pTourNameLabel removeFromSuperview];
    [self.pTourNameLabel release];
    self.pTourNameLabel = nil;
    
    [self.pDetailsPanelBackground removeFromSuperview];
    [self.pDetailsPanelBackground release];
    self.pDetailsPanelBackground = nil;
    
    [self.pDetailsPanel removeFromSuperview];
    [self.pDetailsPanel release];
    self.pDetailsPanel = nil;
    
    delete m_pInterop;
    
    [self removeFromSuperview];
    [super dealloc];
}

-(void) setPresentationColors :(ExampleApp::Helpers::ColorHelpers::Color)baseColor :(ExampleApp::Helpers::ColorHelpers::Color)textColor
{
    CAGradientLayer *gradient = [CAGradientLayer layer];
    gradient.frame =  CGRectMake(0.f, 0.f, m_pTourItemLabelGradientContainer.bounds.size.width, m_pTourItemLabelGradientContainer.bounds.size.height);
    
    UIColor* labelBackgroundColour = [UIColor colorWithRed:baseColor.GetRedF() green:baseColor.GetGreenF() blue:baseColor.GetBlueF() alpha:1.f];
    
    [m_pTourItemLabelContainer setBackgroundColor:labelBackgroundColour];
    m_pTourItemLabel.textColor = [UIColor colorWithRed:textColor.GetRedF() green:textColor.GetGreenF() blue:textColor.GetBlueF() alpha:1.f];
   
    UIColor *topColor = [UIColor colorWithRed:baseColor.GetRedF() green:baseColor.GetGreenF() blue:baseColor.GetBlueF() alpha:0.f];
    UIColor *bottomColor = labelBackgroundColour;
    gradient.colors = [NSArray arrayWithObjects:(id)[topColor CGColor], (id)[bottomColor CGColor], nil];
    
    for (CALayer *layer in [[m_pTourItemLabelGradientContainer.layer.sublayers copy] autorelease]) {
        [layer removeFromSuperlayer];
    }
    
    [m_pTourItemLabelGradientContainer.layer insertSublayer:gradient atIndex:0];
}

- (void) configureViewForTour:(const ExampleApp::Tours::SdkModel::TourModel&) tour :(int)initialCard :(bool)showBackButton
{
    if(m_hasActiveTour)
    {
        // Exit current tour then join new tour.
        [self interruptCurrentTour:tour:showBackButton];
        return;
    }
    [self animateTo:1.0];
    
    m_tour = tour;
    m_hasActiveTour = true;
    m_exitingTour = false;
    m_dismissingTour = false;
    m_pTourItemLabel.text = @"";
    self.pTourNameLabel.text = [NSString stringWithUTF8String:m_tour.Name().c_str()];
    
    if(!showBackButton)
    {
        self.pBackButtonBackground.hidden = YES;
        self.pBackButtonBackground.userInteractionEnabled = NO;
    }
    else
    {
        self.pDetailsPanelBackground.layer.mask = nil;
        
        self.pBackButtonBackground.hidden = NO;
        self.pBackButtonBackground.userInteractionEnabled = YES;
    }
    
    [self->m_viewController configureTourStatesPresentation: tour];
    [m_viewController resetView:initialCard];
    if(tour.ShowGradientBase())
    {
        m_pTourItemLabelContainer.hidden = NO;
        m_pTourItemLabelGradientContainer.hidden = NO;
        [self setPresentationColors :tour.BaseColor() :tour.TextColor()];
    }
    else
    {
        m_pTourItemLabelContainer.hidden = YES;
        m_pTourItemLabelGradientContainer.hidden = YES;
    }
}

- (void) interruptCurrentTour:(const ExampleApp::Tours::SdkModel::TourModel&) tour :(bool)showBackButton
{
    m_isInterruptingTour = YES;
    m_nextTour = tour;
    
    CGRect offFrame = self->m_pCarouselContainer.frame;
    offFrame.origin.y = m_yPosInactive;

    [self.layer removeAllAnimations];
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                          delay:0.0
                        options:UIViewAnimationOptionBeginFromCurrentState
                     animations:^{
        self->m_pCarouselContainer.frame = offFrame;
        self.pDetailsPanel.alpha = 0.0f;
        
    } completion:^(BOOL finished) {
        if(finished)
        {
            m_hasActiveTour = NO;
            m_isInterruptingTour = NO;
            
            [self setNeedsLayout];
            [self layoutIfNeeded];

            [self configureViewForTour:m_nextTour :0 :showBackButton];
            [self animateTo:1.0];
        }
    }];
}

-(void) onSelectionChanged
{
    // Nothing to do, change states when animation finishes (onCurrentItemChanged).
}

-(void) onCurrentSelectionTapped
{
    m_pInterop->OnCurrentTourCardTapped();
}

-(void) onCurrentItemChanged
{
    if(m_hasActiveTour)
    {
        [self dispatchStateSelectionChanged];
    }
}

-(void) dispatchStateSelectionChanged
{
    if(m_hasActiveTour && [self->m_viewController getSelectionIndex] < m_tour.StateCount())
    {
        int selectionIndex = [self->m_viewController getSelectionIndex];
        m_pInterop->OnStateSelected(selectionIndex);
        if(m_tour.ShowGradientBase())
        {
            [self setBaseTextLabel:[NSString stringWithUTF8String:m_tour.States()[selectionIndex].Description().c_str()]];
        }
    }
}

-(void)exitTour
{
    if(m_hasActiveTour)
    {
        m_hasActiveTour = false;
        m_pInterop->OnExited();
    }
}

-(void)dismissTour
{
    if(m_hasActiveTour)
    {
        m_hasActiveTour = false;
        m_pInterop->OnDismissed();
    }
}

-(void) setBaseTextLabel:(NSString*) text
{
    CATransition *animation = [CATransition animation];
    animation.duration = 0.5f;
    animation.type = kCATransitionFade;
    animation.timingFunction = [CAMediaTimingFunction functionWithName:kCAMediaTimingFunctionEaseInEaseOut];
    
    [m_pTourItemLabelContainer.layer removeAnimationForKey:@"changeTextTransition"];
    [m_pTourItemLabel.layer addAnimation:animation forKey:@"changeTextTransition"];
    
    m_pTourItemLabel.text = text;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return (self.pDetailsPanel.alpha > 0.0 && CGRectContainsPoint(self.pDetailsPanel.frame, touchLocation)) ||
            CGRectContainsPoint(m_pCarouselContainer.frame, touchLocation);
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    UIView *hitView = [super hitTest:point withEvent:event];
    if (hitView == self) return nil;
    return hitView;
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;
    
    self.hidden = onScreenState == 0.0f;
    
    CGRect f = self->m_pCarouselContainer.frame;
    f.origin.y = newY;
    self->m_pCarouselContainer.frame = f;
    
    self.pDetailsPanel.alpha = onScreenState;
}

- (void) setFullyOnScreen
{
    if(m_isInterruptingTour)
    {
        return;
    }
    
    [self animateTo:1.0f];
}

- (void) setFullyOffScreen
{
    if(self.frame.origin.y == m_yPosInactive)
    {
        return;
    }
    
    [self animateTo:0.0f];
}

- (void) animateTo:(float)t
{
    float y = m_yPosInactive + (m_yPosActive - m_yPosInactive) * t;
    
    CGRect f = self->m_pCarouselContainer.frame;
    f.origin.y = y;
    
    if(t > 0.0f)
    {
        self.hidden = false;
    }
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds
                          delay:0.0f
                        options:UIViewAnimationOptionBeginFromCurrentState
                     animations:^
     {
         self->m_pCarouselContainer.frame = f;
         self.pDetailsPanel.alpha = t;
     }
                     completion:^(BOOL finished)
     {
         self.hidden = (t == 0.0f);
         
         if(self.hidden)
         {
             if(m_exitingTour)
             {
                 [self exitTour];
             }
             if(m_dismissingTour)
             {
                 [self dismissTour];
             }
         }
     }
     ];
}

- (void)handleExitButtonTap
{
    m_exitingTour = true;
    [self animateTo:0.0f];
}

- (void)handleBackButtonTap
{
    m_dismissingTour = true;
    [self animateTo:0.0f];
}

-(float) controlHeight
{
    return static_cast<float>(m_pCarouselContainer.frame.size.height);
}

@end