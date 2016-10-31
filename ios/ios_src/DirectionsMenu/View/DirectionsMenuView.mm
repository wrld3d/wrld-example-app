// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuView.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "CellConstants.h"
#include "CustomTableDataProvider.h"
#include "MenuViewInterop.h"
#include "UIHelpers.h"
#include "BackCurve.h"
#include "CircleCurve.h"
#include "ViewAlphaAnimator.h"
#include "ViewFrameAnimator.h"
#include "ViewPositionAnimator.h"
#include "ViewSizeAnimator.h"

#import "UIButton+DefaultStates.h"

#include "DirectionsMenuWayPointViewCell.h"
#include "DirectionsMenuStaticView.h"
#include "DirectionsMenuViewInterop.h"
#include "MenuSectionViewModel.h"

#include "IMenuModel.h"
#include "Interiors.h"
#include "SearchResultItemModel.h"
#include "VectorMath.h"

@interface DirectionsMenuView()<UITextFieldDelegate>
{
    
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_pOnScreenResultsAnimationController;
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_pAnchorAnimationController;
    ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop* m_pDirectionsMenuInterop;
    
    bool m_resultsVisible;
    bool m_titleContainersRequireRefresh;
    bool m_resultsScrollable;
    
    float m_anchorAnimationDurationSeconds;
    
    float m_animationDelaySeconds;
    float m_animationDurationSeconds;
    
    float m_maxScreenSpace;
    DirectionsMenuStaticView *m_pDirectionsMenuView;
}

@property (nonatomic, retain) UIView* pSearchMenuScrollButtonContainer;
@property (nonatomic, retain) UIButton* pSearchMenuScrollButton;
@property (nonatomic, retain) UIImageView* pSearchMenuFadeImage;

@property (nonatomic, retain) UITextField *pStartRouteTextField;
@property (nonatomic, retain) UITextField *pEndRouteTextField;

@end

@implementation DirectionsMenuView

- (id)initWithParams:(float)width
                    :(float)height
                    :(float)pixelScale
{
    [super initWithParams:width
                         :height
                         :pixelScale
                         :NULL
                         :0];
    return self;
}

- (ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop*) getDirectionsMenuInterop
{
    return m_pDirectionsMenuInterop;
}

- (void) initializeViews
{
    m_pDirectionsMenuInterop = Eegeo_NEW(ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop)(self);
    
    m_pOnScreenResultsAnimationController = NULL;
    m_pAnchorAnimationController = NULL;
    
    m_resultsVisible = false;
    m_titleContainersRequireRefresh = false;
    m_resultsScrollable = false;
    
    m_anchorAnimationDurationSeconds = 0.1f;
    
    m_animationDelaySeconds = 0.2f;
    m_animationDurationSeconds = 0.1f;
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float upperMargin = (isPhone ? 20.0f : 50.0f) * m_pixelScale;
    
    const float dragTabOffsetX = 0.0f;
    const float dragTabSize = 25.0f * m_pixelScale;
    
    m_dragTabOffsetX = dragTabOffsetX;
    m_dragTabWidth = dragTabSize;
    m_dragTabHeight = dragTabSize;
    m_dragTabOffScreenX = -m_dragTabWidth;
    m_dragTabOffScreenY = upperMargin * m_pixelScale;
    m_dragTabClosedOnScreenX = m_dragTabOffsetX;
    m_dragTabClosedOnScreenY = m_dragTabOffScreenY;
    m_dragTabOpenOnScreenX = m_screenWidth;
    m_dragTabOpenOnScreenY = m_dragTabOffScreenY;
    
    self.pDragTab = [[[UIButton alloc] initWithFrame:CGRectMake(m_dragTabOffScreenX, m_dragTabOffScreenY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    [self.pDragTab setDefaultStatesWithImageNames:@"direction_card_close_arrow" :@"direction_card_close_arrow_down"];
    [self.pDragTab setHidden:YES];
    self.pTitleContainer = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 0, 0)];
    
    m_maxScreenSpace = m_screenHeight - (upperMargin + m_tableSpacing + m_screenHeight/6);

    if(isPhone)
        m_menuContainerWidth = m_screenWidth;
    else
        m_menuContainerWidth = m_screenWidth / 3;

    m_menuContainerOffScreenX = -m_menuContainerWidth;
    m_menuContainerOffScreenY = upperMargin;
    m_menuContainerClosedOnScreenX = m_menuContainerOffScreenX;
    m_menuContainerClosedOnScreenY = m_menuContainerOffScreenY;
    m_menuContainerOpenOnScreenX = 0.0f;
    m_menuContainerOpenOnScreenY = m_menuContainerOffScreenY;
    
     m_pDirectionsMenuView = [[[NSBundle mainBundle] loadNibNamed:@"DirectionsMenuStaticView" owner:self options:nil] objectAtIndex:0];
    
    float estimatedHeight = [m_pDirectionsMenuView getEstimatedHeight];
    [m_pDirectionsMenuView SetSearchMenuView:self];

    m_menuContainerHeight = (estimatedHeight< m_maxScreenSpace) ? estimatedHeight : m_maxScreenSpace;
    
    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_menuContainerOffScreenX, m_menuContainerOffScreenY, m_menuContainerWidth, m_menuContainerHeight)] autorelease];
    
    [self addSubview: self.pDragTab];
    [self addSubview: self.pMenuContainer];
    
    [self.pMenuContainer setBackgroundColor:[UIColor clearColor]];
    

    [m_pDirectionsMenuView setFrame:CGRectMake(0, 0, self.pMenuContainer.frame.size.width, self.pMenuContainer.frame.size.height)];
    
    _pStartRouteTextField = m_pDirectionsMenuView.startRouteTextField;
    _pEndRouteTextField = m_pDirectionsMenuView.endRouteTextField;
    
    _pEndRouteTextField.delegate = self;
    
    [_pStartRouteTextField addTarget:self action:@selector(StartLocationTextFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    
    [_pEndRouteTextField addTarget:self action:@selector(EndLocationTextFieldDidChange:) forControlEvents:UIControlEventEditingChanged];
    
    [m_pDirectionsMenuView.exitDirectionsBtn addTarget:self action:@selector(ExitDirectionsClicked) forControlEvents:UIControlEventTouchUpInside];
    
    [self.pMenuContainer addSubview:m_pDirectionsMenuView];
    
    self.frame = CGRectMake(0, 0, m_screenWidth, m_screenHeight);
    
}

- (void)HighlightItemIndex:(int)itemIndex   {
    
    [m_pDirectionsMenuView SetHighlightItem:itemIndex];
}

- (void)dealloc
{
    [self.pSearchResultsTableContainerView removeFromSuperview];
    [self.pSearchResultsTableContainerView release];

    [self.pTableViewContainer removeFromSuperview];
    [self.pTableViewContainer release];
    
    [self.pTopTableSeparator removeFromSuperview];
    [self.pTopTableSeparator release];
    
    [self.pMenuContainer removeFromSuperview];
    [self.pMenuContainer release];
    
    [self.pTitleContainer removeFromSuperview];
    [self.pTitleContainer release];

    [self.pDragTab removeFromSuperview];
    [self.pDragTab release];
    
    [self.pSearchMenuFadeImage removeFromSuperview];
    [self.pSearchMenuFadeImage release];
    
    [self.pSearchMenuScrollButton removeFromSuperview];
    [self.pSearchMenuScrollButton release];
    
    [self.pSearchMenuScrollButtonContainer removeFromSuperview];
    [self.pSearchMenuScrollButtonContainer release];

    Eegeo_DELETE m_pAnchorAnimationController;
    
    Eegeo_DELETE m_pDirectionsMenuInterop;
    
    [self removeFromSuperview];
    
    [super dealloc];
}

- (void)initializeAnimators
{
    [super initializeAnimators];
    
    // On screen results received animations
    m_pOnScreenResultsAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                                 nil,
                                                                                                                 nil);
    
    // Anchor arrow animations
    m_pAnchorAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                        nil,
                                                                                                        nil);
}



- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    [super setOffscreenPartsHiddenState:hidden];

}

- (void) CollapseAll
{
    [m_pDataProvider collapseAll];
}

- (void) updateAnimation:(float)deltaSeconds
{
    Eegeo_ASSERT([self isAnimating], "updateTableAnimation called when table is not animating, please call isTableAnimating to check that animation is running before calling updateTableAnimation");
    
    if([super isAnimating])
    {
        [super updateAnimation:deltaSeconds];
    }
    
    if(m_pAnchorAnimationController->IsActive())
    {
        m_pAnchorAnimationController->Update(deltaSeconds);
    }
    
    if(m_pOnScreenResultsAnimationController->IsActive())
    {
        m_pOnScreenResultsAnimationController->Update(deltaSeconds);
    }
}

- (void) updateTableAnimation:(float)deltaSeconds
{
    if([super isTableAnimating])
    {
        [super updateTableAnimation:deltaSeconds];
    }
}

- (void) onTableAnimationUpdated
{
    [self refreshTableHeights];
}

- (BOOL) isAnimating
{
    return [super isAnimating] || m_pAnchorAnimationController->IsActive() || m_pOnScreenResultsAnimationController->IsActive();
}

- (BOOL) isTableAnimating
{
    return false;
}

- (void)refreshTableHeights
{
    
}

- (float) getHeightForTable:(CustomTableView*)tableView
{
    return 200;
}

- (void) SetSearchSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)searchSection
{
    [m_pDirectionsMenuView updateSearchResultsSection:searchSection];
    
    [self updateContainerFrame];
}

- (void)onSectionExpanded
{

}

- (void)onSectionContracted
{
    
}

- (void)onRowSelected
{

}

-(void)scrollViewDidScroll:(UIScrollView *)sender
{
        if(self.pSearchResultsTableContainerView.contentOffset.y + self.pSearchResultsTableContainerView.frame.size.height == self.pSearchResultsTableContainerView.contentSize.height)
        {
            _pSearchMenuScrollButtonContainer.hidden = true;
            _pSearchMenuFadeImage.hidden = true;
        }
        else
        {
            _pSearchMenuScrollButtonContainer.hidden = false;
            _pSearchMenuFadeImage.hidden = false;
        }
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{

    if(textField == _pStartRouteTextField)
    {
        [_pEndRouteTextField becomeFirstResponder];
    }
    else if(textField == _pEndRouteTextField)
    {
        [self EndRouteEntered];
        [_pEndRouteTextField resignFirstResponder];
        [_pStartRouteTextField resignFirstResponder];
    }
    return YES;
}

-(void)StartLocationTextFieldDidChange:(UITextField *)textField
{
    m_pDirectionsMenuInterop->HandleStartLocationChanged(std::string([textField.text UTF8String]));
}

-(void)EndLocationTextFieldDidChange:(UITextField *)textField
{
    m_pDirectionsMenuInterop->HandleEndLocationChanged(std::string([textField.text UTF8String]));
}

#define MenuViewCallbacks

-(void)ExitDirectionsClicked {
    
    if([self canInteract])
    {
        m_pDirectionsMenuInterop->OnExitDirectionsClicked();
    }

}


-(void)EndRouteEntered  {
    
    m_pDirectionsMenuInterop->SearchPerformed("");  
}

-(void)updateContainerFrame {
    
    float updatedEstimatedHeight = [m_pDirectionsMenuView getEstimatedHeight];
    
    [self.pMenuContainer setFrame:CGRectMake(self.pMenuContainer.frame.origin.x, self.pMenuContainer.frame.origin.y, self.pMenuContainer.frame.size.width, updatedEstimatedHeight)];
    
    [m_pDirectionsMenuView setFrame:CGRectMake(0,0, self.pMenuContainer.frame.size.width, updatedEstimatedHeight)];
    
    [UIView animateWithDuration:0.5
                     animations:^{
                         [self layoutIfNeeded];
                     }];

}

@end
