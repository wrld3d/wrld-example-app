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

@interface DirectionsMenuView()<UITableViewDelegate, UITableViewDataSource, UITextFieldDelegate>
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
    DirectionsMenuStaticView *directionsMenuView;
    
}

@property (nonatomic, retain) UIView* pSearchMenuScrollButtonContainer;
@property (nonatomic, retain) UIButton* pSearchMenuScrollButton;
@property (nonatomic, retain) UIImageView* pSearchMenuFadeImage;

@property (nonatomic, retain) UITableView *wayPointsTableView;
@property (nonatomic, retain) UITextField *startRouteTextField;
@property (nonatomic, retain) UITextField *endRouteTextField;

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
    
    resultCount = 0;
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
    
    m_menuContainerWidth = m_screenWidth;
    //m_menuContainerHeight = m_maxScreenSpace;
    //m_menuContainerHeight = 260.0f;
    m_menuContainerOffScreenX = -m_menuContainerWidth;
    m_menuContainerOffScreenY = upperMargin;
    m_menuContainerClosedOnScreenX = m_menuContainerOffScreenX;
    m_menuContainerClosedOnScreenY = m_menuContainerOffScreenY;
    m_menuContainerOpenOnScreenX = 0.0f;
    m_menuContainerOpenOnScreenY = m_menuContainerOffScreenY;
    
     directionsMenuView = [[[NSBundle mainBundle] loadNibNamed:@"DirectionsMenuStaticView" owner:self options:nil] objectAtIndex:0];
    
    float estimatedHeight = [self getEstimatedHeight];

    m_menuContainerHeight = (estimatedHeight< m_maxScreenSpace) ? estimatedHeight : m_maxScreenSpace;
    
    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_menuContainerOffScreenX, m_menuContainerOffScreenY, m_menuContainerWidth, m_menuContainerHeight)] autorelease];
    
    [self addSubview: self.pDragTab];
    [self addSubview: self.pMenuContainer];
    
    [self.pMenuContainer setBackgroundColor:[UIColor clearColor]];
    

    [directionsMenuView setFrame:CGRectMake(0, 0, self.pMenuContainer.frame.size.width, self.pMenuContainer.frame.size.height)];
    
    _startRouteTextField = directionsMenuView.startRouteTextField;
    _endRouteTextField = directionsMenuView.endRouteTextField;
    
    _startRouteTextField.delegate = self;
    _endRouteTextField.delegate = self;
    
    self.wayPointsTableView = (UITableView *)[directionsMenuView viewWithTag:10];
    self.wayPointsTableView.delegate = self;
    self.wayPointsTableView.dataSource = self;

    
    UINib *wayPointsCellNib = [UINib nibWithNibName:@"DirectionsMenuWayPointViewCell" bundle: [NSBundle mainBundle]];
    [self.wayPointsTableView registerNib:wayPointsCellNib forCellReuseIdentifier:@"DirectionsMenuWayPointViewCell"];
    
    
    [directionsMenuView.exitDirectionsBtn addTarget:self action:@selector(ExitDirectionsClicked:) forControlEvents:UIControlEventTouchUpInside];
    
    [self.pMenuContainer addSubview:directionsMenuView];
    
    self.frame = CGRectMake(0, 0, m_screenWidth, m_screenHeight);
    
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

- (void) collapseAll
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

- (void) setSearchSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)searchSection
{

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

#define  UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return resultCount;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    DirectionsMenuWayPointViewCell *cell = (DirectionsMenuWayPointViewCell*)[self.wayPointsTableView dequeueReusableCellWithIdentifier:@"DirectionsMenuWayPointViewCell"];
        [cell.wayPointNumberlbl setText:[NSString stringWithFormat:@"%li",(long)indexPath.row+1]];
    if(indexPath.row == 0)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_RouteStart"]];
        [cell.wayPointMainTitlelbl setText:@"Westfield Valley Mall"];
        [cell.wayPointSubCategorylbl setText:@"South Entrance"];

    }
    else if (indexPath.row == 1)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_EnterMallSelected"]];
        [cell.wayPointMainTitlelbl setText:@"50 yd"];
        [cell.wayPointSubCategorylbl setText:@"Enter Mall"];


    }
    else if (indexPath.row == 2)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_StraightAhead"]];
        [cell.wayPointMainTitlelbl setText:@"40 yd"];
        [cell.wayPointSubCategorylbl setText:@"Turn left along main concourse"];

    }
    else if (indexPath.row == 3)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_TurnLeft"]];
        [cell.wayPointMainTitlelbl setText:@"Turn Left"];
        [cell.wayPointSubCategorylbl setText:@"Then 400 yd along main course"];

    }
    else if (indexPath.row == 4)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_ElevatorSelected"]];
        [cell.wayPointMainTitlelbl setText:@"Elevator to 2nd floor"];
        [cell.wayPointSubCategorylbl setText:@""];

    }
    else if (indexPath.row == 5)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_TurnRight"]];
        [cell.wayPointMainTitlelbl setText:@"Turn Right"];
        [cell.wayPointSubCategorylbl setText:@"Then 50 yd along main concourse"];

    }
    else if (indexPath.row == 6)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_VeerLeft.png"]];
        [cell.wayPointMainTitlelbl setText:@"Left"];
        [cell.wayPointSubCategorylbl setText:@"The 50 yd along main concourse"];

    }
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return 45;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {

    if(textField == _startRouteTextField)
    {
        [_endRouteTextField becomeFirstResponder];
    }
    else if(textField == _endRouteTextField)
    {
        [self EndRouteEntered];
        [_endRouteTextField resignFirstResponder];
        [_startRouteTextField resignFirstResponder];
    }
    return YES;
}

#define MenuViewCallbacks

-(void)ExitDirectionsClicked:(id)sender {
    
    if([self canInteract])
    {
        [self getInterop]->HandleViewClicked();
    }

}

-(void)EndRouteEntered  {
    
    m_pDirectionsMenuInterop->SearchPerformed("");

    NSLog(@"End Route Clicked");
    
    resultCount = 7;
    [self.wayPointsTableView reloadData];
    
    [self.pMenuContainer setFrame:CGRectMake(self.pMenuContainer.frame.origin.x, self.pMenuContainer.frame.origin.y, self.pMenuContainer.frame.size.width, [self getEstimatedHeight])];
    [directionsMenuView setFrame:CGRectMake(0,0, self.pMenuContainer.frame.size.width, [self getEstimatedHeight])];
        
        [UIView animateWithDuration:0.5
                         animations:^{
                             [self layoutIfNeeded];
                         }];
}

-(float)getEstimatedHeight  {

    return directionsMenuView.headerView.bounds.size.height + directionsMenuView.bottomBarView.bounds.size.height + (45 * m_pixelScale * resultCount) + (directionsMenuView.hideOptionsView.bounds.size.height);
}

@end
