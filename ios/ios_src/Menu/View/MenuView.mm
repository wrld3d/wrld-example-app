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

@interface MenuView()<UIGestureRecognizerDelegate>
{
    ExampleApp::Menu::View::MenuViewInterop* m_pInterop;
    
    UITapGestureRecognizer* m_tapGestureRecogniser;
    
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_currentAnimationController;
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
                     :(int)tableCount
{
    if(self = [super init])
    {
        m_screenWidth = width/pixelScale;
        m_screenHeight = height/pixelScale;
        m_pixelScale = 1.f;
        
        m_stateChangeAnimationTimeSeconds = 0.3f;
        
        m_onScreenAnimationController = NULL;
        m_openAnimationController = NULL;
        
        self.pTableViewMap = [[[NSMutableDictionary alloc] init] autorelease];
        
        for(int i = 0; i < tableCount; ++i)
        {
            CustomTableView* customTableView = [[CustomTableView alloc] autorelease];
            self.pTableViewMap[@(i)] = [customTableView retain];
        }

        [self initializeViews];
        
        [self initializeAnimators];
        
        self.hidden = true;

        m_pDataProvider = dataProvider;
        [m_pDataProvider initWithParams:self
                                       :self.pTableViewMap];
        
        m_pInterop = Eegeo_NEW(ExampleApp::Menu::View::MenuViewInterop)(self);
        
        m_tapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(tapTabGesture:)] autorelease];
        [m_tapGestureRecogniser setDelegate:self];
        
        [[self pDragTab] addGestureRecognizer: m_tapGestureRecogniser];
        
        m_menuState = OFF_SCREEN;
        
        m_currentAnimationController = NULL;
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_openAnimationController;
    
    Eegeo_DELETE m_onScreenAnimationController;
    
    for(int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        CustomTableView* customTableView = (CustomTableView*)self.pTableViewMap[@(i)];
        
        self.pTableViewMap[@(i)] = nil;
        
        [customTableView removeFromSuperview];
        [customTableView release];
    }
    
    [self.pTableViewMap release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (ExampleApp::Menu::View::MenuViewInterop*) getInterop
{
    return m_pInterop;
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    self.pTableViewContainer.hidden = hidden;
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
    if(m_menuState == OFF_SCREEN || m_menuState == ANIMATING)
    {
        [self startAnimationForState:CLOSED_ON_SCREEN
                    normalizedOffset:[self onScreenState]
                 animationController:m_onScreenAnimationController
                    isPlayingForward:YES];
    }
    else if(m_menuState == OPEN_ON_SCREEN)
    {
        [self startAnimationForState:CLOSED_ON_SCREEN
                    normalizedOffset:1.0f - [self openOnScreenState]
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
    if(m_menuState == state)
    {
        return;
    }
    
    bool overridingAnimation = false;
    
    if(m_currentAnimationController != NULL)
    {
        m_currentAnimationController->SetToEnd();
        overridingAnimation = true;
    }
    
    m_menuState = ANIMATING;
    
    if(isPlayingForward)
    {
        if(overridingAnimation)
        {
            animationController->PlayFromCurrent();
        }
        else
        {
            animationController->PlayWithNormalizedOffset(normalizedOffset);
        }
    }
    else
    {
        if(overridingAnimation)
        {
            animationController->PlayReverseFromCurrent();
        }
        else
        {
            animationController->PlayReverseWithNormalizedOffset(normalizedOffset);
        }
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
           || CGRectContainsPoint(self.pMenuContainer.frame, touchLocation);
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
    for(int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        CustomTableView* customTableView = (CustomTableView*)self.pTableViewMap[@(i)];
        
        if([customTableView isAnimating])
        {
            [customTableView updateAnimation:deltaSeconds];
        }
    }
}

- (void) onTableAnimationUpdated
{
    [self refreshTableHeights];
}

- (void) onOffScreenAnimationComplete
{
    m_menuState = OFF_SCREEN;
    
    self.hidden = true;
    
    [self onMenuStateUpdated];
}

- (void) onClosedOnScreenAnimationComplete
{
    m_menuState = CLOSED_ON_SCREEN;
    
    m_pInterop->HandleViewCloseCompleted();
    [self setOffscreenPartsHiddenState:true];
    
    [self onMenuStateUpdated];
}

- (void) onOpenOnScreenAnimationComplete
{
    m_menuState = OPEN_ON_SCREEN;
    
    m_pInterop->HandleViewOpenCompleted();
    
    [self onMenuStateUpdated];
}

- (void) onMenuStateUpdated
{
    // handled in sub classes
}

- (BOOL) isAnimating
{
    return m_menuState == ANIMATING;
}

- (BOOL) isTableAnimating
{
    for(int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        CustomTableView* customTableView = (CustomTableView*)self.pTableViewMap[@(i)];
        
        if([customTableView isAnimating])
        {
            return true;
        }
    }
    
    return false;
}

- (float) openOnScreenState
{
    return m_openAnimationController->GetNormalizedLinearProgress();
}

- (float) onScreenState
{
    return m_onScreenAnimationController->GetNormalizedLinearProgress();
}

- (UIView *)hitTest:(CGPoint)point withEvent:(UIEvent *)event
{
    if (self.hidden || !self.userInteractionEnabled || self.alpha < 0.01 || ![self canInteract])
    {
        return nil;
    }
    
    UIView *hitView = [super hitTest:point withEvent:event];
    if (hitView == self) return nil;
    return hitView;
}

- (BOOL)gestureRecognizerShouldBegin:(UIGestureRecognizer *)gestureRecognizer
{
    if([gestureRecognizer isKindOfClass:[UITapGestureRecognizer class]])
    {
        return true;
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
    CGFloat totalTableHeight = 0.0f;
    
    for(int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        CustomTableView* customTableView = self.pTableViewMap[@(i)];
        
        const CGFloat tableHeight = [customTableView refreshHeight:[m_pDataProvider getRealHeightForTable:customTableView]];
        
        CGRect frame = customTableView.frame;
        frame.origin.y = totalTableHeight;
        customTableView.frame = frame;
        
        totalTableHeight += tableHeight;
    }

    const CGFloat tableY = self.pTableViewContainer.frame.origin.y + self.pMenuContainer.frame.origin.y;
    const CGFloat tableViewContainerHeight = MIN(m_screenHeight - tableY, totalTableHeight);
    
    CGRect frame = self.pTableViewContainer.frame;
    frame.size.height = tableViewContainerHeight;
    self.pTableViewContainer.frame = frame;
    
    [self.pTableViewContainer setContentSize:CGSizeMake(self.pTableViewContainer.frame.size.width, totalTableHeight)];
    
    frame = self.pMenuContainer.frame;
    frame.size.height = tableViewContainerHeight + m_tableSpacing;
    self.pMenuContainer.frame = frame;
}

- (float) getHeightForTable:(CustomTableView*)tableView
{
    return [m_pDataProvider getRealHeightForTable:tableView];
}

- (void) setTableCanInteract:(BOOL)canInteract
{
    for(int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        [self.pTableViewMap[@(i)] setUserInteractionEnabled:canInteract];
    }
}

- (BOOL) canInteract
{
    return (m_menuState == CLOSED_ON_SCREEN || m_menuState == OPEN_ON_SCREEN);
}

- (void) updateMenuSections:(ExampleApp::Menu::View::TSections*)sections
{
    [m_pDataProvider updateMenuSections:sections];
}

- (void) toggleSection:(int)sectionIndex
{
    [m_pDataProvider tableView:self.pTableViewMap[@(sectionIndex)]
       didSelectRowAtIndexPath:[NSIndexPath indexPathForRow:0
                                                  inSection:sectionIndex]];
}

@end
