// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "MenuViewInterop.h"
#include "CustomTableDataProvider.h"
#include "CellConstants.h"
#include "Circle.h"

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
    UIPanGestureRecognizer* _panGestureRecognizer;
    UITapGestureRecognizer* _tapGestureRecogniser;
    bool _dragging;
    bool _touchedDownInsideDragTab;
    
    ExampleApp::Helpers::UIAnimation::ViewPositionAnimator* m_currentAnimator;
    
    MenuState m_menuState;
}

@end

@implementation MenuView

- (void)initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
}

- (id) initWithParams:(float)width
    :(float)height
    :(float)pixelScale
    :(size_t)numberOfSections
    :(size_t)numberOfCells
    :(CustomTableDataProvider*)dataProvider
{
    if(self = [super init])
    {
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_pixelScale = 1.f;
        
        m_offscreenAnimator = NULL;
        m_closedAnimator = NULL;
        m_openAnimator = NULL;

        [self initialiseViews:numberOfSections numberOfCells:numberOfCells];
        
        [self initAnimators];

        _dragging = false;
        m_animating = false;
        self.hidden = true;
        m_isFirstAnimationCeremony = true;

        m_pDataProvider = dataProvider;
        [m_pDataProvider initWithParams:self];
        m_pInterop = Eegeo_NEW(ExampleApp::Menu::View::MenuViewInterop)(self, m_pDataProvider);

        _panGestureRecognizer = [[[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(dragTabGesture:)] autorelease];
        [_panGestureRecognizer setDelegate:self];

        _tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapTabGesture:)] autorelease];
        [_tapGestureRecogniser setDelegate:self];

        [[self pDragTab] addGestureRecognizer: _panGestureRecognizer];
        [[self pDragTab] addGestureRecognizer: _tapGestureRecogniser];

        if ([self.pTableview respondsToSelector:@selector(layoutMargins)])
        {
            self.pTableview.layoutMargins = UIEdgeInsetsZero;
        }

        if ([self.pTableview respondsToSelector:@selector(separatorInset)])
        {
            [self.pTableview setSeparatorInset:UIEdgeInsetsZero];
        }
        
        m_menuState = OFF_SCREEN;
        
        m_currentAnimator = NULL;
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_openAnimator;
    
    Eegeo_DELETE m_closedAnimator;
    
    Eegeo_DELETE m_offscreenAnimator;
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (ExampleApp::Menu::View::MenuViewInterop*) getInterop
{
    return m_pInterop;
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    self.pMenuContainer.hidden = hidden;
    self.pMenuHeaderStub.hidden = hidden;
    self.pTableview.hidden = hidden;
}

- (void) animateToRemovedFromScreen:(float)normalizedOffset
{
    [self startAnimationForState:OFF_SCREEN
                normalizedOffset:normalizedOffset
                        animator:m_offscreenAnimator];
}

- (void) animateToClosedOnScreen:(float)normalizedOffset
{
    [self startAnimationForState:CLOSED_ON_SCREEN
                normalizedOffset:normalizedOffset
                        animator:m_closedAnimator];
}

- (void) animateToOpenOnScreen:(float)normalizedOffset
{
    [self startAnimationForState:OPEN_ON_SCREEN
                normalizedOffset:normalizedOffset
                        animator:m_openAnimator];
}

- (void) startAnimationForState:(MenuState)state
               normalizedOffset:(float)normalizedOffset
                       animator:(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator*)animator
{
    if(m_menuState == state || [self isAnimating])
    {
        return;
    }
    
    m_menuState = ANIMATING;
    
    animator->PlayWithNormalizedOffset(normalizedOffset);
    
    m_currentAnimator = animator;
    
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
    
    float newX = m_offscreenX - ((m_offscreenX - m_closedX) * onScreenState);
    if(fabs(self.frame.origin.x - newX) < 0.01f)
    {
        return;
    }
    
    CGRect f = self.frame;
    f.origin.x = newX;
    self.frame = f;
}

- (void) setOpenStateToIntermediateValue:(float)openState
{
    if([self isAnimating])
    {
        return;
    }

    self.hidden = false;
    [self setOffscreenPartsHiddenState:false];

    float newX = m_closedX + (fabsf(m_openX - m_closedX) * openState);
    if(fabs(self.frame.origin.x - newX) < 0.01f)
    {
        return;
    }

    CGRect f = self.frame;
    f.origin.x = newX;
    self.frame = f;
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    CGPoint touchLocation = [touch locationInView:self];
    return CGRectContainsPoint(_pDragTab.frame, touchLocation)
           || CGRectContainsPoint(_pMenuContainer.frame, touchLocation);
}

- (void) initAnimators
{
    m_offscreenAnimator = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self,
                                                                                            Eegeo::v2(m_offscreenX, m_offscreenY),
                                                                                            m_stateChangeAnimationTimeSeconds,
                                                                                            Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Curves::CircleInOut)(),
                                                                                            ^(UIView* menuView)
                                                                                            {
                                                                                                [(MenuView*)menuView onOffScreenAnimationComplete];
                                                                                            });
    
    m_closedAnimator = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self,
                                                                                         Eegeo::v2(m_closedX, m_closedY),
                                                                                         m_stateChangeAnimationTimeSeconds,
                                                                                         Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Curves::CircleInOut)(),
                                                                                         ^(UIView* menuView)
                                                                                         {
                                                                                             [(MenuView*)menuView onClosedOnScreenAnimationComplete];
                                                                                         });
    
    m_openAnimator = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self,
                                                                                       Eegeo::v2(m_openX, m_openY),
                                                                                       m_stateChangeAnimationTimeSeconds,
                                                                                       Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Curves::CircleInOut)(),
                                                                                       ^(UIView* menuView)
                                                                                       {
                                                                                           [(MenuView*)menuView onOpenOnScreenAnimationComplete];
                                                                                       });
}

- (void) updateAnimation:(float)deltaSeconds
{
    Eegeo_ASSERT(m_currentAnimator != NULL, "No animator set during updateAnimation, please call isAnimating before calling this function");
    
    m_currentAnimator->Update(deltaSeconds);
    
    if(![self isAnimating])
    {
        m_currentAnimator = NULL;
    }
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

- (float) onScreenOpenState
{
    return Eegeo::Math::Clamp((self.frame.origin.x - m_closedX) / (m_openX - m_closedX), 0.0f, 1.0f);
}

- (void) beginDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    m_menuState = DRAGGING;
    m_dragStartPos = absolutePosition;
    m_controlStartPos = self.frame.origin;
    [self setOffscreenPartsHiddenState:false];
    m_pInterop->HandleDraggingViewStarted();
}

- (void) updateDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    CGRect f = self.frame;
    f.origin.x = m_controlStartPos.x + (absolutePosition.x - m_dragStartPos.x);
    
    if(f.origin.x < -m_mainContainerOnScreenWidth)
    {
        f.origin.x = (-m_mainContainerOnScreenWidth);
    }
    
    if(f.origin.x > m_closedX)
    {
        f.origin.x = m_closedX;
    }
    
    float normalisedDragState = -((static_cast<float>(self.frame.origin.x) + (-m_closedX)) / (std::abs(m_openX - m_closedX)));
    normalisedDragState = Eegeo::Clamp(normalisedDragState, 0.f, 1.f);
    
    m_pInterop->HandleDraggingViewInProgress(normalisedDragState);
    self.frame = f;
    
    [self.layer removeAllAnimations];
}

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    const bool startedClosed = m_controlStartPos.x == m_closedX;
    const float xRatioForStateChange = startedClosed ? 0.35f : 0.65f;
    const float threshold = (m_screenWidth - (m_mainContainerOnScreenWidth * xRatioForStateChange));
    bool open = absolutePosition.x < threshold;
    
    const float velocityMagitude = std::abs(static_cast<float>(absoluteVelocity.x));
    if(velocityMagitude > (200 * m_pixelScale))
    {
        open = absoluteVelocity.x < 0 ? true : false;
    }
    
    float normalizedOffset = Eegeo::Math::Clamp((m_dragStartPos.x - absolutePosition.x) / (m_closedX - m_openX), 0.0f, 1.0f);
    
    if(open)
    {
        [self animateToOpenOnScreen:normalizedOffset];
    }
    else
    {
        [self animateToClosedOnScreen:(1.0f - normalizedOffset)];
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
        _dragging = true;
        [self beginDrag:positionAbs velocity:velocity];
        break;

    case UIGestureRecognizerStateChanged:
        [self updateDrag:positionAbs velocity:velocity];
        break;

    case UIGestureRecognizerStateEnded:
        _dragging = false;
        _touchedDownInsideDragTab = false;
        [self completeDrag:positionAbs velocity:velocity];
        break;

    case UIGestureRecognizerStateCancelled:
        _dragging = false;
        _touchedDownInsideDragTab = false;
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
        _touchedDownInsideDragTab = true;
    }
    else
    {
        _touchedDownInsideDragTab = false;
    }
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    if([gestureRecognizer isKindOfClass:[UITapGestureRecognizer class]])
    {
        return true;
    }
    
    if(_touchedDownInsideDragTab && [self canInteract])
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
    const float tableScreenY = m_mainContainerY + m_mainContainerOffscreenOffsetY + m_tableY;
    const float tableScreenSpace = m_screenHeight - tableScreenY;
    m_tableHeight = fmaxf(tableScreenSpace, m_tableHeight);
    
    const float realTableHeight = [m_pDataProvider getRealTableHeight];
    self.pTableviewContainer.frame = CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight);
    self.pTableviewContainer.bounces = NO;
    self.pTableviewContainer.contentSize = CGSizeMake(m_tableWidth, realTableHeight);
    self.pTableview.frame = CGRectMake(0.f, 0.f, m_tableWidth, realTableHeight);
    
    m_mainContainerHeight = m_dragTabHeight + realTableHeight;
    self.pMenuContainer.frame = CGRectMake(m_mainContainerX, m_mainContainerY, m_mainContainerWidth, m_mainContainerHeight);
}

- (void) setCanInteract:(BOOL)canInteract
{
    [self.pTableview setUserInteractionEnabled:canInteract];
}

- (BOOL) canInteract
{
    const bool closed = self.frame.origin.x == m_closedX || self.frame.origin.y == m_closedY;
    const bool open = self.frame.origin.x == m_openX || self.frame.origin.y == m_openY;

    return !_dragging && (closed || open);
}

@end
