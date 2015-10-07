// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourExplorerView.h"
#include "MyPinCreationConfirmationViewInterop.h"
#import "UIView+TouchExclusivity.h"
#include "TourExplorerViewInterop.h"
#include "iCarouselTourExplorerViewController.h"
#include "ColorHelpers.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "App.h"

@implementation TourExplorerView
{
    iCarouselTourExplorerViewController* m_viewController;
    ExampleApp::Tours::SdkModel::TourModel m_tour;
    ExampleApp::Tours::SdkModel::TourModel m_nextTour;
    bool m_isInterruptingTour;
    bool m_hasActiveTour;
    bool m_exitingTour;
    
    CGPoint m_controlStartPos;
}

- (ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop*) getInterop
{
    return m_pInterop;
}

- (id) initWithParams:(float)width :(float)height :(float)pixelScale :(ImageStore*)pImageStore
{
    const bool isPhone = App::IsDeviceSmall();
    
    if (self = [super init])
    {
        m_stateChangeAnimationTimeSeconds = 0.2f;
        m_pixelScale = 1.f;
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_hasActiveTour = false;
        m_exitingTour = false;
        
        m_pInterop = new ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop(self);
        
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
        float exitButtonSize = 40.f;
        const float labelLength = isPhone? 150.f : 200.f;
        
        const float detailsPanelHeight = 40.0f;
        float totalPanelLength = labelLength + exitButtonSize;
        
        float totalPanelHeight = detailsPanelHeight;
        
        self.pDetailsPanel = [[[UIView alloc] initWithFrame:CGRectMake(m_screenWidth * 0.5f - totalPanelLength * 0.5f, upperMargin, totalPanelLength, totalPanelHeight)] autorelease];
        
        self.pExitButtonBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"menu_button")] autorelease];
        self.pExitButtonBackground.frame = CGRectMake(0.0f, 0.0f, exitButtonSize, exitButtonSize);
        
        [self.pDetailsPanel addSubview:self.pExitButtonBackground];
    
        
        self.pExitButton = [[UIButton alloc]initWithFrame:CGRectMake(0.0f, 0.0f, exitButtonSize, exitButtonSize)];
        [self.pExitButton setImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"Arrow") forState:UIControlStateNormal];
        [self.pExitButton addTarget:self action:@selector(handleExitButtonTap) forControlEvents:UIControlEventTouchUpInside];
        [self.pExitButtonBackground addSubview:self.pExitButton];
        
        self.pExitButtonBackground.userInteractionEnabled = YES;
        
        self.pDetailsPanelBackground = [[[UIImageView alloc] initWithImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"place_pin_background")] autorelease];
        
        self.pDetailsPanelBackground.frame = CGRectMake(exitButtonSize, 0, labelLength, detailsPanelHeight);
        
        UIBezierPath* roundedShapePath = [UIBezierPath bezierPathWithRoundedRect:self.pDetailsPanelBackground.bounds byRoundingCorners:UIRectCornerTopRight | UIRectCornerBottomRight cornerRadii:CGSizeMake(7.0f, 7.0f)];
        
        CAShapeLayer* roundedShapeLayer = [CAShapeLayer layer];
        roundedShapeLayer.frame = self.pDetailsPanelBackground.bounds;
        roundedShapeLayer.path = roundedShapePath.CGPath;
        roundedShapeLayer.fillColor = [UIColor blackColor].CGColor;
        roundedShapeLayer.strokeColor = [UIColor blackColor].CGColor;
        roundedShapeLayer.lineWidth = 1.0f;
        
        self.pDetailsPanelBackground.layer.mask = roundedShapeLayer;
        
        [self.pDetailsPanel addSubview:self.pDetailsPanelBackground];
        
        const float textPadding = 2.f;
        
        self.pTourNameLabel = [[[UILabel alloc] initWithFrame:CGRectMake( textPadding + exitButtonSize, textPadding, labelLength - textPadding, detailsPanelHeight - textPadding)] autorelease];
        self.pTourNameLabel.textColor = ExampleApp::Helpers::ColorPalette::DarkGreyTone;
        self.pTourNameLabel.textAlignment = NSTextAlignmentCenter;
        [self.pDetailsPanel addSubview:self.pTourNameLabel];
        
        
        [self addSubview:self.pDetailsPanel];
    }
    
    return self;
}

- (void)dealloc
{
    
    [self.pDetailsPanel removeFromSuperview];
    [self.pDetailsPanel release];
    self.pDetailsPanel = nil;
    
    [self.pDetailsPanelBackground removeFromSuperview];
    [self.pDetailsPanelBackground release];
    self.pDetailsPanelBackground = nil;
    
    [self.pExitButtonBackground removeFromSuperview];
    [self.pExitButtonBackground release];
    self.pExitButtonBackground = nil;
    
    [self.pExitButton removeFromSuperview];
    [self.pExitButton release];
    self.pExitButton = nil;
    
    [self.pTourNameLabel removeFromSuperview];
    [self.pTourNameLabel release];
    self.pTourNameLabel = nil;
    
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

- (void) configureViewForTour:(const ExampleApp::Tours::SdkModel::TourModel&) tour :(int)initialCard
{
    if(m_hasActiveTour)
    {
        // Exit current tour then join new tour.
        [self interruptCurrentTour:tour];
        return;
    }
    const float carouselHeight = [m_viewController getItemHeight];
    
    CGRect f = m_pCarouselContainer.frame;
    f.origin.y = m_screenHeight - carouselHeight;
    m_pCarouselContainer.frame = f;
    
    m_tour = tour;
    m_hasActiveTour = true;
    m_exitingTour = false;
    m_pTourItemLabel.text = @"";
    self.pTourNameLabel.text = [NSString stringWithUTF8String:m_tour.Name().c_str()];
    
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

- (void) interruptCurrentTour:(const ExampleApp::Tours::SdkModel::TourModel&) tour
{
    m_isInterruptingTour = YES;
    m_nextTour = tour;
    
    CGRect offFrame = self.frame;
    offFrame.origin.y = m_yPosInactive;
    
    CGRect onFrame = self.frame;
    onFrame.origin.y = m_yPosActive;

    [self.layer removeAllAnimations];
    
    [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds animations:^{
        self.frame = offFrame;
        
    } completion:^(BOOL finished) {
        if(finished)
        {
            m_hasActiveTour = NO;
            m_isInterruptingTour = NO;
            
            [self setNeedsLayout];
            [self layoutIfNeeded];

            [self configureViewForTour:m_nextTour :0];
            
            [UIView animateWithDuration:m_stateChangeAnimationTimeSeconds animations:^{
                self.frame = onFrame;
            } completion:^(BOOL finished) {
            }];
        }
    }];
}

-(void) onSelectionChanged
{
    // Nothing to do, change states when animation finishes (onCurrentItemChanged).
}

-(void) onCurrentSelectionTapped
{
    // display the POI view.
    NSLog(@"Tapped carousel thing");
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
    return CGRectContainsPoint(self.pDetailsPanel.frame, touchLocation) || CGRectContainsPoint(m_pCarouselContainer.frame, touchLocation);
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    float newY = m_yPosInactive + (m_yPosActive - m_yPosInactive) * onScreenState;
    
    self.hidden = onScreenState == 0.0f;
    CGRect f = self.frame;
    f.origin.y = newY;
    self.frame = f;
}

- (void) setFullyOnScreen
{
    if(m_isInterruptingTour)
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
                     animations:^
     {
         self.frame = f;
     }
                     completion:^(BOOL finished)
     {
         self.hidden = (y == m_yPosInactive);
         
         if(self.hidden && m_exitingTour)
         {
             [self exitTour];
         }
     }
     ];
}

- (void)handleExitButtonTap
{
    m_exitingTour = true;
    [self animateToY:m_yPosInactive];
}

-(float) controlHeight
{
    return static_cast<float>(self.frame.size.height);
}

@end