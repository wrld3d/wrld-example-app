// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "MenuViewInterop.h"
#include "CustomTableDataProvider.h"
#include "CellConstants.h"
#include "ViewPositionAnimator.h"
#include "ViewFrameAnimator.h"
#include "CircleCurve.h"

enum MenuState
{
    DRAGGING,
    OFF_SCREEN,
    CLOSED_ON_SCREEN,
    OPEN_ON_SCREEN,
    ANIMATING
};

@interface MenuView()<UIGestureRecognizerDelegate>
{
    ExampleApp::Menu::View::MenuViewInterop* m_pInterop;
    
    UIPanGestureRecognizer* m_panGestureRecognizer;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    
    CGPoint m_dragStartPos;
    CGPoint m_controlStartPos;
    
    bool m_dragStartedClosed;
    bool m_touchedDownInsideDragTab;
    
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_currentAnimationController;
    
    MenuState m_menuState;
}

@end

@implementation MenuView

- (void)initializeViews
{
}

- (id) initWithParams:(float)width
    :(float)height
    :(float)pixelScale
    :(CustomTableDataProvider*)dataProvider
{
    if(self = [super init])
    {
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_pixelScale = 1.f;
        
        m_stateChangeAnimationTimeSeconds = 0.3f;
        
        m_onScreenAnimationController = NULL;
        m_openAnimationController = NULL;

        [self initializeViews];
        
        [self initializeAnimators];
        
        self.hidden = true;

        m_pDataProvider = dataProvider;
        [m_pDataProvider initWithParams:self];
        
        m_pInterop = Eegeo_NEW(ExampleApp::Menu::View::MenuViewInterop)(self);

        m_panGestureRecognizer = [[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(dragTabGesture:)] autorelease];
        [m_panGestureRecognizer setDelegate:self];

        m_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapTabGesture:)] autorelease];
        [m_tapGestureRecogniser setDelegate:self];

        [[self pDragTab] addGestureRecognizer: m_panGestureRecognizer];
        [[self pDragTab] addGestureRecognizer: m_tapGestureRecogniser];

        if ([self.pTableView respondsToSelector:@selector(layoutMargins)])
        {
            self.pTableView.layoutMargins = UIEdgeInsetsZero;
        }

        if ([self.pTableView respondsToSelector:@selector(separatorInset)])
        {
            [self.pTableView setSeparatorInset:UIEdgeInsetsZero];
        }
        
        m_dragStartedClosed = false;
        m_touchedDownInsideDragTab  = false;
        
        m_menuState = OFF_SCREEN;
        
        m_currentAnimationController = NULL;
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_openAnimationController;
    
    Eegeo_DELETE m_onScreenAnimationController;
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (ExampleApp::Menu::View::MenuViewInterop*) getInterop
{
    return m_pInterop;
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    self.pTableView.hidden = hidden;
}

- (void) animateToRemovedFromScreen
{
    [self startAnimationForState:OFF_SCREEN
                normalizedOffset:1.0f - [self onScreenState]
             animationController:m_onScreenAnimationController
                isPlayingForward:NO];
}

- (void) animateToClosedOnScreen
{
    if(m_menuState == OFF_SCREEN)
    {
        [self startAnimationForState:CLOSED_ON_SCREEN
                    normalizedOffset:[self onScreenState]
                 animationController:m_onScreenAnimationController
                    isPlayingForward:YES];
    }
    else if(m_menuState == OPEN_ON_SCREEN || m_menuState == DRAGGING)
    {
        [self startAnimationForState:CLOSED_ON_SCREEN
                    normalizedOffset:1.0f -[self openOnScreenState]
                 animationController:m_openAnimationController
                    isPlayingForward:NO];
    }
}

- (void) animateToOpenOnScreen
{
    [self startAnimationForState:OPEN_ON_SCREEN
                normalizedOffset:[self openOnScreenState]
             animationController:m_openAnimationController
                isPlayingForward:YES];
}

- (void) startAnimationForState:(MenuState)state
               normalizedOffset:(float)normalizedOffset
            animationController:(ExampleApp::Helpers::UIAnimation::ViewAnimationController*)animationController
               isPlayingForward:(BOOL)isPlayingForward
{
    if(m_menuState == state || [self isAnimating])
    {
        return;
    }
    
    m_menuState = ANIMATING;
    
    if(isPlayingForward)
    {
        animationController->PlayWithNormalizedOffset(normalizedOffset);
    }
    else
    {
        animationController->PlayReverseWithNormalizedOffset(normalizedOffset);
    }
    
    m_currentAnimationController = animationController;
    
    self.hidden = NO;
    [self setOffscreenPartsHiddenState:false];
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    if([self isAnimating])
    {
        return;
    }
    
    self.hidden = false;
    [self setOffscreenPartsHiddenState:false];
    
    m_onScreenAnimationController->SetToNormalizedOffset(onScreenState);
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(self.pDragTab.frame, touchLocation)
           || CGRectContainsPoint(self.pTitleContainer.frame, touchLocation)
           || CGRectContainsPoint(self.pTableViewContainer.frame, touchLocation);
}

- (void) initializeAnimators
{
    // On/off screen animations
    m_onScreenAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                         ^(UIView* menuView)
                                                                                                         {
                                                                                                             [(MenuView*)menuView onClosedOnScreenAnimationComplete];
                                                                                                         },
                                                                                                         ^(UIView* menuView)
                                                                                                         {
                                                                                                             [(MenuView*)menuView onOffScreenAnimationComplete];
                                                                                                         });
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pDragTab,
                                                                                                      m_stateChangeAnimationTimeSeconds,
                                                                                                      0.0,
                                                                                                      Eegeo::v2(m_dragTabOffScreenX, m_dragTabOffScreenY),
                                                                                                      Eegeo::v2(m_dragTabClosedOnScreenX, m_dragTabClosedOnScreenY),
                                                                                                      Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pTitleContainer,
                                                                                                              m_stateChangeAnimationTimeSeconds,
                                                                                                              0.0,
                                                                                                              Eegeo::v2(m_titleContainerOffScreenX, m_titleContainerOffScreenY),
                                                                                                              Eegeo::v2(m_titleContainerClosedOnScreenX, m_titleContainerClosedOnScreenY),
                                                                                                              Eegeo::v2(m_titleContainerOffScreenWidth, m_titleContainerOffScreenHeight),
                                                                                                              Eegeo::v2(m_titleContainerClosedOnScreenWidth, m_titleContainerClosedOnScreenHeight),
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pMenuContainer,
                                                                                                                 m_stateChangeAnimationTimeSeconds,
                                                                                                                 0.0,
                                                                                                                 Eegeo::v2(m_menuContainerOffScreenX, m_menuContainerOffScreenY),
                                                                                                                 Eegeo::v2(m_menuContainerClosedOnScreenX, m_menuContainerClosedOnScreenY),
                                                                                                                 Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    // Open/closed on screen animations
    m_openAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                     ^(UIView* menuView)
                                                                                                     {
                                                                                                         [(MenuView*)menuView onOpenOnScreenAnimationComplete];
                                                                                                     },
                                                                                                     ^(UIView* menuView)
                                                                                                     {
                                                                                                         [(MenuView*)menuView onClosedOnScreenAnimationComplete];
                                                                                                     });
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pDragTab,
                                                                                                             m_stateChangeAnimationTimeSeconds,
                                                                                                             0.0,
                                                                                                             Eegeo::v2(m_dragTabClosedOnScreenX, m_dragTabClosedOnScreenY),
                                                                                                             Eegeo::v2(m_dragTabOpenOnScreenX, m_dragTabOpenOnScreenY),
                                                                                                             Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pTitleContainer,
                                                                                                          m_stateChangeAnimationTimeSeconds,
                                                                                                          0.0,
                                                                                                          Eegeo::v2(m_titleContainerClosedOnScreenX, m_titleContainerClosedOnScreenY),
                                                                                                          Eegeo::v2(m_titleContainerOpenOnScreenX, m_titleContainerOpenOnScreenY),
                                                                                                          Eegeo::v2(m_titleContainerClosedOnScreenWidth, m_titleContainerClosedOnScreenHeight),
                                                                                                          Eegeo::v2(m_titleContainerOpenOnScreenWidth, m_titleContainerOpenOnScreenHeight),
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pMenuContainer,
                                                                                                             m_stateChangeAnimationTimeSeconds,
                                                                                                             0.0,
                                                                                                             Eegeo::v2(m_menuContainerClosedOnScreenX, m_menuContainerClosedOnScreenY),
                                                                                                             Eegeo::v2(m_menuContainerOpenOnScreenX, m_menuContainerOpenOnScreenY),
                                                                                                             Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
}

- (void) updateAnimation:(float)deltaSeconds
{
    Eegeo_ASSERT(m_currentAnimationController != NULL, "No animator set during updateAnimation, please call isAnimating before calling this function");
    
    m_currentAnimationController->Update(deltaSeconds);
    
    if(![self isAnimating])
    {
        m_currentAnimationController = NULL;
    }
}

- (void) updateTableAnimation:(float)deltaSeconds
{
    [self.pTableView updateAnimation:deltaSeconds];
}

- (void) onTableAnimationUpdated
{
    [self.pTableViewContainer setContentSize:CGSizeMake(self.pTableView.pBackgroundView.frame.size.width, self.pTableView.pBackgroundView.frame.size.height)];
}

- (void) onOffScreenAnimationComplete
{
    m_menuState = OFF_SCREEN;
    
    self.hidden = true;
}

- (void) onClosedOnScreenAnimationComplete
{
    m_menuState = CLOSED_ON_SCREEN;
    
    m_pInterop->HandleViewCloseCompleted();
    [self setOffscreenPartsHiddenState:true];
}

- (void) onOpenOnScreenAnimationComplete
{
    m_menuState = OPEN_ON_SCREEN;
    
    m_pInterop->HandleViewOpenCompleted();
}

- (BOOL) isAnimating
{
    return m_menuState == ANIMATING;
}

- (BOOL) isTableAnimating
{
    return [self.pTableView isAnimating];
}

- (float) openOnScreenState
{
    return m_openAnimationController->GetNormalizedLinearProgress();
}

- (float) onScreenState
{
    return m_onScreenAnimationController->GetNormalizedLinearProgress();
}

- (void) beginDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    m_dragStartedClosed = (m_menuState != OPEN_ON_SCREEN);
    
    m_menuState = DRAGGING;
    
    m_dragStartPos = absolutePosition;
    m_controlStartPos = self.pDragTab.frame.origin;
    
    [self setOffscreenPartsHiddenState:false];
    
    m_pInterop->HandleDraggingViewStarted();
}

- (void) updateDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    const float deltaX = absolutePosition.x - m_dragStartPos.x;
    
    float normalisedDragState;
    
    if(m_dragStartedClosed)
    {
        normalisedDragState = Eegeo::Math::Clamp(deltaX / (m_dragTabOpenOnScreenX - m_dragTabClosedOnScreenX), 0.0f, 1.0f);
    }
    else
    {
        normalisedDragState = Eegeo::Math::Clamp(deltaX / (m_dragTabClosedOnScreenX - m_dragTabOpenOnScreenX), 0.0f, 1.0f);
        normalisedDragState = 1.0f - normalisedDragState;
    }
    
    m_openAnimationController->SetToNormalizedOffset(normalisedDragState);
    
    m_pInterop->HandleDraggingViewInProgress(normalisedDragState);
}

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    const float deltaX = absolutePosition.x - m_dragStartPos.x;
    
    float normalisedDragState;
    
    if(m_dragStartedClosed)
    {
        normalisedDragState = Eegeo::Math::Clamp(deltaX / (m_dragTabOpenOnScreenX - m_dragTabClosedOnScreenX), 0.0f, 1.0f);
    }
    else
    {
        normalisedDragState = Eegeo::Math::Clamp(deltaX / (m_dragTabClosedOnScreenX - m_dragTabOpenOnScreenX), 0.0f, 1.0f);
    }
    
    const float stateChangeThreshold = 0.35f;
    
    bool stateChange = normalisedDragState > stateChangeThreshold;
    
    const float velocityThreshold = 200.0f * m_pixelScale;
    
    if(!stateChange && fabsf(absoluteVelocity.x) > velocityThreshold)
    {
        int stateChangeDirection;
        
        if(m_dragStartedClosed)
        {
            stateChangeDirection = (m_dragTabOpenOnScreenX - m_dragTabClosedOnScreenX) > 0.0f ? 1 : -1;
        }
        else
        {
            stateChangeDirection = (m_dragTabOpenOnScreenX - m_dragTabClosedOnScreenX) < 0.0f ? 1 : -1;
        }
        
        int velocityDirection = (absoluteVelocity.x > 0.0f) ? 1 : -1;
        
        stateChange = (velocityDirection == stateChangeDirection);
    }
    
    if((stateChange && m_dragStartedClosed) || (!stateChange && !m_dragStartedClosed))
    {
        [self animateToOpenOnScreen];
    }
    else
    {
        [self animateToClosedOnScreen];
    }
    
    m_pInterop->HandleDraggingViewCompleted();
}

- (BOOL)pointInside:(CGPoint)point withEvent:(UIEvent *)event
{
    return NO;
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    if (self.hidden || !self.userInteractionEnabled || self.alpha < 0.01 || ![self canInteract])
    {
        return nil;
    }

    __block UIView *hitView = nil;

    [self.subviews enumerateObjectsUsingBlock:^(UIView *obj, NSUInteger idx, BOOL *stop)
    {

        CGPoint thePoint = [self convertPoint:point toView:obj];
        UIView *theSubHitView = [obj hitTest:thePoint withEvent:event];

        if (theSubHitView != nil)
        {
            hitView = theSubHitView;
            *stop = YES;
        }
    }];

    return hitView;
}

- (void)dragTabGesture:(UIPanGestureRecognizer *)recognizer
{
    if (!m_pInterop->CallBeginDrag())
    {
        return;
    }

    CGPoint positionAbs = [recognizer locationInView:[self superview]];
    CGPoint velocity = [recognizer velocityInView:[self superview]];

    switch(recognizer.state)
    {
    case UIGestureRecognizerStateBegan:
        [self beginDrag:positionAbs velocity:velocity];
        break;

    case UIGestureRecognizerStateChanged:
        [self updateDrag:positionAbs velocity:velocity];
        break;

    case UIGestureRecognizerStateEnded:
        m_touchedDownInsideDragTab = false;
        [self completeDrag:positionAbs velocity:velocity];
        break;

    case UIGestureRecognizerStateCancelled:
        m_touchedDownInsideDragTab = false;
        [self completeDrag:positionAbs velocity:velocity];
        break;

    default:
        break;
    }
}

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    UITouch *touch = [[event allTouches] anyObject];
    CGPoint touchLocation = [touch locationInView:self];
    
    if(CGRectContainsPoint(_pDragTab.frame, touchLocation))
    {
        m_touchedDownInsideDragTab = true;
    }
    else
    {
        m_touchedDownInsideDragTab = false;
    }
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    if([gestureRecognizer isKindOfClass:[UITapGestureRecognizer class]])
    {
        return true;
    }
    
    if(m_touchedDownInsideDragTab && [self canInteract])
    {
        return m_pInterop->CallBeginDrag();
    }
    return false;
}

- (void)tapTabGesture:(UITapGestureRecognizer *)recognizer
{
    if([self canInteract])
    {
        m_pInterop->HandleViewClicked();
    }
}

- (void) refreshTableHeights
{
    const float tableHeight = [m_pDataProvider getRealTableHeight];
    
    const float tableViewContainerHeight = fminf(m_screenHeight - self.pTableViewContainer.frame.origin.y, tableHeight);
    
    CGRect frame = self.pTableView.frame;
    frame.size.height = tableHeight;
    self.pTableView.frame = frame;
    
    frame = self.pTableView.pBackgroundView.frame;
    frame.size.height = tableHeight;
    self.pTableView.pBackgroundView.frame = frame;
    
    frame = self.pTableViewContainer.frame;
    frame.size.height = tableViewContainerHeight;
    self.pTableViewContainer.frame = frame;
    
    [self.pTableViewContainer setContentSize:CGSizeMake(self.pTableViewContainer.frame.size.width, tableHeight)];
}

- (void) refreshHeightForTable:(CustomTableView*)tableView
{
    Eegeo_ASSERT(tableView == self.pTableView, "Can't refresh height for a table view not owned by this view");
    
    [self refreshTableHeights];
}

- (float) getHeightForTable:(CustomTableView*)tableView
{
    Eegeo_ASSERT(tableView == self.pTableView, "Can't get height for a table view not owned by this view");
    
    return [m_pDataProvider getRealTableHeight];
}

- (void) setTableCanInteract:(BOOL)canInteract
{
    [self.pTableView setUserInteractionEnabled:canInteract];
}

- (BOOL) canInteract
{
    return (m_menuState == CLOSED_ON_SCREEN || m_menuState == OPEN_ON_SCREEN);
}

- (void) updateMenuSections:(ExampleApp::Menu::View::TSections*)sections
{
    [m_pDataProvider updateMenuSections:sections];
}

@end
