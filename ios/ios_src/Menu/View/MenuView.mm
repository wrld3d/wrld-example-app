// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "MenuViewInterop.h"
#include "CustomTableDataProvider.h"
#include "CellConstants.h"


@interface MenuView()<UIGestureRecognizerDelegate>
{
    UIPanGestureRecognizer* _panGestureRecognizer;
    UITapGestureRecognizer* _tapGestureRecogniser;
    bool _dragging;
    bool _touchedDownInsideDragTab;
}

@end

@implementation MenuView
- (void)initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
}

- (id) initWithParams:(float)width
    :(float)height
    :(float)pixelScale
    :(bool)rightMenu
    :(size_t)numberOfSections
    :(size_t)numberOfCells
    :(CustomTableDataProvider*)dataProvider
{
    if(self = [super init])
    {
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_pixelScale = 1.f;

        [self initialiseViews:numberOfSections numberOfCells:numberOfCells];

        _dragging = false;
        m_animating = false;
        self.hidden = true;
        m_isFirstAnimationCeremony = true;
        m_rightMenu = rightMenu;

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
    }

    return self;
}

- (BOOL)isRightMenu
{
    return m_rightMenu;
}

- (void)dealloc
{
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (ExampleApp::Menu::View::MenuViewInterop*) getInterop
{
    return m_pInterop;
}

- (void)layoutSubviews
{
    CGRect f = self.frame;
    f.origin.x = m_offscreenX;
    f.origin.y = m_offscreenY;
    self.frame = f;
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    self.pMenuContainer.hidden = hidden;
    self.pMenuHeaderStub.hidden = hidden;
    self.pTableview.hidden = hidden;
}

- (void) animateToRemovedFromScreen
{
    if(self.frame.origin.x != m_offscreenX || (m_animating && m_animationEndPos.x != m_offscreenX))
    {
        [self animateToX:m_offscreenX];
    }

    if(self.frame.origin.y != m_offscreenY || (m_animating && m_animationEndPos.y != m_offscreenY))
    {
        [self animateToY:m_offscreenY];
    }
}

- (void) animateToClosedOnScreen
{
    if(self.frame.origin.x != m_closedX || (m_animating && m_animationEndPos.x != m_closedX))
    {
        [self animateToX:m_closedX];
    }

    if(self.frame.origin.y != m_closedY || (m_animating && m_animationEndPos.y != m_closedY))
    {
        [self animateToY:m_closedY];
    }
}

- (void) animateToOpenOnScreen
{
    if(self.frame.origin.x != m_openX || (m_animating && m_animationEndPos.x != m_openX))
    {
        [self animateToX:m_openX];
    }

    if(self.frame.origin.y != m_openY || (m_animating && m_animationEndPos.y != m_openY))
    {
        [self animateToY:m_openY];
    }
}

- (void) setOnScreenStateToIntermediateValue:(float)onScreenState
{
    Eegeo_ASSERT(false, "Derived views should implement 'setOnScreenStateToIntermediateValue'.\n");
}

- (void) setOpenStateToIntermediateValue:(float)openState
{
    if([self isAnimating])
    {
        return;
    }

    self.hidden = false;
    [self setOffscreenPartsHiddenState:false];

    float newX = m_closedX + (std::abs(m_openX - m_closedX) * openState);
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

- (void) updateAnimation:(float)deltaSeconds
{
    if (!m_animating)
    {
        return;
    }

    bool done = false;
    CGRect f = self.frame;
    const Eegeo::v2 totalDelta = (m_animationEndPos - m_animationStartPos);
    const float totalDeltaLen = totalDelta.Length();
    if(totalDeltaLen != 0.f)
    {
        const float animationUnitsPerSecond = totalDeltaLen / m_stateChangeAnimationTimeSeconds;
        const float frameDeltaUnits = animationUnitsPerSecond * deltaSeconds;
        const Eegeo::v2 norm = totalDelta.Norm();
        const Eegeo::v2 delta = norm * frameDeltaUnits;
        m_animationCurrentPos += delta;
        
        f.origin.x = m_animationCurrentPos.x;
        f.origin.y = m_animationCurrentPos.y;
        
        const Eegeo::v2 currentPosDirToEnd = (m_animationEndPos - m_animationCurrentPos).Norm();
        const float dp = Eegeo::v2::Dot(currentPosDirToEnd, norm);
        done = dp < 0.f;
    }
    else
    {
        done = true;
    }

    if(done)
    {
        f.origin.x = m_animationEndPos.x;
        f.origin.y = m_animationEndPos.y;
        self.frame = f;
        m_animationCurrentPos = m_animationEndPos;

        const bool closed =
            (f.origin.x == m_closedX && m_animationStartPos.x != m_animationEndPos.x) ||
            (f.origin.y == m_closedY && m_animationStartPos.y != m_animationEndPos.y);

        const bool open =
            (f.origin.x == m_openX && m_animationStartPos.x != m_animationEndPos.x) ||
            (f.origin.y == m_openY && m_animationStartPos.y != m_animationEndPos.y);

        const bool offScreen =
            (f.origin.x == m_offscreenX && m_animationStartPos.x != m_animationEndPos.x) ||
            (f.origin.y == m_offscreenY && m_animationStartPos.y != m_animationEndPos.y);

        if(closed)
        {
            m_pInterop->HandleViewCloseCompleted();
            [self setOffscreenPartsHiddenState:true];
        }
        else if(open)
        {
            m_pInterop->HandleViewOpenCompleted();
        }
        else if(offScreen)
        {
            self.hidden = true;
        }

        m_animating = false;
    }
    else
    {
        self.frame = f;
    }
}

- (BOOL) isAnimating
{
    return m_animating;
}

- (float) animationValue
{
    CGFloat totalDistance = (m_animationEndPos - m_animationStartPos).Length();
    CGFloat currentDistance = (m_animationEndPos - m_animationCurrentPos).Length();
    float result = currentDistance/totalDistance;
    result = Eegeo::Math::Clamp(result, 0.f, 1.f);

    if(m_animationEndPos.x != m_animationStartPos.x)
    {
        if(m_animationEndPos.x == m_openX)
        {
            return 1.f - result;
        }
        else
        {
            return result;
        }
    }
    else if(m_animationEndPos.y != m_animationStartPos.y)
    {
        if(m_animationEndPos.y == m_openY)
        {
            return 1.f - result;
        }
        else
        {
            return result;
        }
    }

    return 0.f;
}

- (void) beginDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    m_dragStartPos = absolutePosition;
    m_controlStartPos = self.frame.origin;
    [self setOffscreenPartsHiddenState:false];
    m_pInterop->HandleDraggingViewStarted();
}

- (void) animateToX:(float)x
{
    self.hidden = false;
    [self setOffscreenPartsHiddenState:false];
    CGRect f = self.frame;

    if(x == m_offscreenX || x == m_closedX)
    {
        m_animationStartPos.x = m_isFirstAnimationCeremony && x == m_closedX ? m_offscreenX : m_openX;
    }
    else if(x == m_openX)
    {
        m_animationStartPos.x = m_closedX;
    }
    else
    {
        Eegeo_ASSERT(false, "Invalid animation target.\n");
    }
    
    m_isFirstAnimationCeremony = false;

    m_animationStartPos.y =
        m_animationCurrentPos.y =
            m_animationEndPos.y = f.origin.y;

    m_animationCurrentPos.x = f.origin.x;
    m_animationEndPos.x = x;

    m_animating = true;
}

- (void) animateToY:(float)y
{
    self.hidden = false;
    [self setOffscreenPartsHiddenState:false];
    CGRect f = self.frame;

    if(y == m_offscreenY || y == m_closedY)
    {
        m_animationStartPos.y = m_isFirstAnimationCeremony && y == m_closedY ? m_offscreenY : m_openY;
    }
    else if(y == m_openY)
    {
        m_animationStartPos.y = m_closedY;
    }
    else
    {
        Eegeo_ASSERT(false, "Invalid animation target.\n");
    }


    m_isFirstAnimationCeremony = false;

    m_animationStartPos.x =
        m_animationCurrentPos.x =
            m_animationEndPos.x = f.origin.x;

    m_animationCurrentPos.y = f.origin.y;
    m_animationEndPos.y = y;

    m_animating = true;
}

- (void) updateDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    Eegeo_ASSERT(false, "Derived views should implement 'updateDrag'.\n");
}

- (void) completeDrag:(CGPoint)absolutePosition velocity:(CGPoint)absoluteVelocity
{
    Eegeo_ASSERT(false, "Derived views should implement 'completeDrag'.\n");
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

- (void) refreshTableHeights: (size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
    const float tableScreenY = m_mainContainerY + m_mainContainerOffscreenOffsetY + m_tableY;
    const float tableScreenSpace = m_screenHeight - tableScreenY;
    m_tableHeight = fmin(tableScreenSpace, m_tableHeight);
    
    const float realTableHeight =  (SECTION_HEADER_CELL_HEIGHT * numberOfSections) + (SUB_SECTION_CELL_HEIGHT * (numberOfCells));
    self.pTableviewContainer.frame = CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight);
    self.pTableviewContainer.bounces = NO;
    self.pTableviewContainer.contentSize = CGSizeMake(m_tableWidth, realTableHeight);
    self.pTableview.frame = CGRectMake(0.f, 0.f, m_tableWidth, realTableHeight);
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
