// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "CellConstants.h"
#include "CustomTableDataProvider.h"
#include "SearchResultsTableDataProvider.h"
#include "SearchMenuViewInterop.h"
#include "MenuViewInterop.h"
#include "UIHelpers.h"
#include "BackCurve.h"
#include "CircleCurve.h"
#include "ViewAlphaAnimator.h"
#include "ViewFrameAnimator.h"
#include "ViewPositionAnimator.h"

@interface SearchMenuView()
{
    SearchResultsTableDataProvider* m_pSearchResultsDataProvider;
    ExampleApp::SearchMenu::View::SearchMenuViewInterop* m_pSearchMenuInterop;
    
    float m_animationDelaySeconds;
    float m_animationDurationSeconds;
    
    float m_maxScreenSpace;
    
    float m_searchCountLabelWidth;
    float m_searchCountLabelHeight;
    float m_searchCountLabelOffScreenAlpha;
    float m_searchCountLabelOffScreenX;
    float m_searchCountLabelOffScreenY;
    float m_searchCountLabelClosedOnScreenAlpha;
    float m_searchCountLabelClosedOnScreenX;
    float m_searchCountLabelClosedOnScreenY;
    float m_searchCountLabelOpenOnScreenAlpha;
    float m_searchCountLabelOpenOnScreenX;
    float m_searchCountLabelOpenOnScreenY;
    
    float m_searchEditBoxBackgroundOffScreenWidth;
    float m_searchEditBoxBackgroundOffScreenHeight;
    float m_searchEditBoxBackgroundOffScreenX;
    float m_searchEditBoxBackgroundOffScreenY;
    float m_searchEditBoxBackgroundClosedOnScreenWidth;
    float m_searchEditBoxBackgroundClosedOnScreenHeight;
    float m_searchEditBoxBackgroundClosedOnScreenX;
    float m_searchEditBoxBackgroundClosedOnScreenY;
    float m_searchEditBoxBackgroundOpenOnScreenWidth;
    float m_searchEditBoxBackgroundOpenOnScreenHeight;
    float m_searchEditBoxBackgroundOpenOnScreenX;
    float m_searchEditBoxBackgroundOpenOnScreenY;
    
    float m_searchEditBoxWidth;
    float m_searchEditBoxHeight;
    float m_searchEditBoxOffScreenAlpha;
    float m_searchEditBoxOffScreenX;
    float m_searchEditBoxOffScreenY;
    float m_searchEditBoxClosedOnScreenAlpha;
    float m_searchEditBoxClosedOnScreenX;
    float m_searchEditBoxClosedOnScreenY;
    float m_searchEditBoxOpenOnScreenAlpha;
    float m_searchEditBoxOpenOnScreenX;
    float m_searchEditBoxOpenOnScreenY;
}

@property (nonatomic, retain) UILabel* pSearchCountLabel;
@property (nonatomic, retain) UIView* pSearchEditBoxBackground;
@property (nonatomic, retain) UITextField* pSearchEditBox;
@property (nonatomic, retain) UIView* pSearchTableSeparator;

@end

@implementation SearchMenuView

- (id)initWithParams:(float)width
                    :(float)height
                    :(float)pixelScale
                    :(CustomTableDataProvider*)dataProvider
                    :(SearchResultsTableDataProvider*)searchResultsDataProvider
{
    [super initWithParams:width
                         :height
                         :pixelScale
                         :dataProvider];
    
    dataProvider.rowSelectionDelegate = self;
    
    m_pSearchResultsDataProvider = searchResultsDataProvider;
    [m_pSearchResultsDataProvider initWithParams:self];
    
    return self;
}

- (ExampleApp::SearchMenu::View::SearchMenuViewInterop*) getSearchMenuInterop
{
    return m_pSearchMenuInterop;
}

- (void) initializeViews
{
    m_pSearchMenuInterop = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchMenuViewInterop)(self);
    
    m_animationDelaySeconds = 0.2f;
    m_animationDurationSeconds = 0.1f;
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float upperMargin = (isPhone ? 20.0f : 50.0f) * m_pixelScale;
    const float tableCellWidth = 295.0f * m_pixelScale;
    const float searchCountLabelWidth = 32.0f * m_pixelScale;
    const float dragTabOffsetX = searchCountLabelWidth;
    const float dragTabSize = 50.0f * m_pixelScale;
    const float tableSpacing = 6.0f * m_pixelScale;
    
    const float tableCellRightInset = 5.0f * m_pixelScale;
    
    const float searchEditBoxLeftInset = 8.0f * m_pixelScale;
    const float searchEditBoxInsetY = 8.0f * m_pixelScale;
    
    m_tableSpacing = tableSpacing;
    
    m_dragTabOffsetX = dragTabOffsetX;
    m_dragTabWidth = dragTabSize;
    m_dragTabHeight = dragTabSize;
    m_dragTabOffScreenX = -m_dragTabWidth;
    m_dragTabOffScreenY = upperMargin * m_pixelScale;
    m_dragTabClosedOnScreenX = m_dragTabOffsetX;
    m_dragTabClosedOnScreenY = m_dragTabOffScreenY;
    m_dragTabOpenOnScreenX = tableCellWidth + searchCountLabelWidth + tableCellRightInset;
    m_dragTabOpenOnScreenY = m_dragTabOffScreenY;
    
    self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabOffScreenX, m_dragTabOffScreenY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    self.pDragTab.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;
    
    m_titleContainerOffScreenWidth = 0.0f;
    m_titleContainerOffScreenHeight = m_dragTabHeight;
    m_titleContainerOffScreenX = m_dragTabOffScreenX;
    m_titleContainerOffScreenY = upperMargin;
    
    m_titleContainerClosedOnScreenWidth = 0.0f;
    m_titleContainerClosedOnScreenHeight = m_titleContainerOffScreenHeight;
    m_titleContainerClosedOnScreenX = m_dragTabClosedOnScreenX;
    m_titleContainerClosedOnScreenY = m_titleContainerOffScreenY;
    
    m_titleContainerOpenOnScreenWidth = tableCellWidth + searchCountLabelWidth + tableCellRightInset;
    m_titleContainerOpenOnScreenHeight = m_titleContainerOffScreenHeight;
    m_titleContainerOpenOnScreenX = 0.0f;
    m_titleContainerOpenOnScreenY = m_titleContainerOffScreenY;
    
    self.pTitleContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_titleContainerOffScreenX, m_titleContainerOffScreenY, m_titleContainerOffScreenWidth, m_titleContainerOffScreenHeight)] autorelease];
    self.pTitleContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;
    
    m_searchCountLabelWidth = searchCountLabelWidth;
    m_searchCountLabelHeight = dragTabSize;
    m_searchCountLabelOffScreenAlpha = 0.0f;
    m_searchCountLabelOffScreenX = 0.0f;
    m_searchCountLabelOffScreenY = -dragTabSize;
    m_searchCountLabelClosedOnScreenAlpha = 0.0f;
    m_searchCountLabelClosedOnScreenX = 0.0f;
    m_searchCountLabelClosedOnScreenY = -dragTabSize;
    m_searchCountLabelOpenOnScreenAlpha = 1.0f;
    m_searchCountLabelOpenOnScreenX = 0.0f;
    m_searchCountLabelOpenOnScreenY = 0.0f;
    
    self.pSearchCountLabel = [[[UILabel alloc] initWithFrame:CGRectMake(m_searchCountLabelOffScreenX, m_searchCountLabelOffScreenY, m_searchCountLabelWidth, m_searchCountLabelHeight)] autorelease];
    [self.pSearchCountLabel setBackgroundColor:[UIColor clearColor]];
    [self.pSearchCountLabel setFont:[UIFont systemFontOfSize:16.0f]];
    [self.pSearchCountLabel setTextColor:ExampleApp::Helpers::ColorPalette::UiTextHeaderColour];
    [self.pSearchCountLabel setAlpha:m_searchCountLabelOffScreenAlpha];
    [self.pSearchCountLabel setTextAlignment:NSTextAlignmentCenter];
    [self.pSearchCountLabel setHidden:YES];
    
    m_searchEditBoxBackgroundOffScreenWidth = tableCellWidth;
    m_searchEditBoxBackgroundOffScreenHeight = 0.0f;
    m_searchEditBoxBackgroundOffScreenX = searchCountLabelWidth;
    m_searchEditBoxBackgroundOffScreenY = searchEditBoxInsetY;
    m_searchEditBoxBackgroundClosedOnScreenWidth = m_searchEditBoxBackgroundOffScreenWidth;
    m_searchEditBoxBackgroundClosedOnScreenHeight = 0.0f;
    m_searchEditBoxBackgroundClosedOnScreenX = m_searchEditBoxBackgroundOffScreenX;
    m_searchEditBoxBackgroundClosedOnScreenY = searchEditBoxInsetY;
    m_searchEditBoxBackgroundOpenOnScreenWidth = m_searchEditBoxBackgroundOffScreenWidth;
    m_searchEditBoxBackgroundOpenOnScreenHeight = dragTabSize - (searchEditBoxInsetY * 2.0f);
    m_searchEditBoxBackgroundOpenOnScreenX = m_searchEditBoxBackgroundOffScreenX;
    m_searchEditBoxBackgroundOpenOnScreenY = searchEditBoxInsetY;
    
    self.pSearchEditBoxBackground = [[[UIView alloc] initWithFrame:CGRectMake(m_searchEditBoxBackgroundOffScreenX, m_searchEditBoxBackgroundOpenOnScreenY, m_searchEditBoxBackgroundOffScreenWidth, m_searchEditBoxBackgroundOpenOnScreenHeight)] autorelease];
    self.pSearchEditBoxBackground.backgroundColor = ExampleApp::Helpers::ColorPalette::MainHudColor;
    self.pSearchEditBoxBackground.layer.cornerRadius = 5.0f;
    self.pSearchEditBoxBackground.layer.masksToBounds = YES;
    
    m_searchEditBoxWidth = tableCellWidth - searchEditBoxLeftInset;
    m_searchEditBoxHeight = dragTabSize - (searchEditBoxInsetY * 2.0f);
    m_searchEditBoxOffScreenAlpha = 0.0f;
    m_searchEditBoxOffScreenX = searchCountLabelWidth + searchEditBoxLeftInset;
    m_searchEditBoxOffScreenY = -dragTabSize + searchEditBoxInsetY;
    m_searchEditBoxClosedOnScreenAlpha = 0.0f;
    m_searchEditBoxClosedOnScreenX = m_searchEditBoxOffScreenX;
    m_searchEditBoxClosedOnScreenY = m_searchEditBoxOffScreenY;
    m_searchEditBoxOpenOnScreenAlpha = 1.0f;
    m_searchEditBoxOpenOnScreenX = m_searchEditBoxOffScreenX;
    m_searchEditBoxOpenOnScreenY = searchEditBoxInsetY;
    
    self.pSearchEditBox = [[[UITextField alloc] initWithFrame:CGRectMake(m_searchEditBoxOffScreenX, m_searchEditBoxOffScreenY, m_searchEditBoxWidth, m_searchEditBoxHeight)] autorelease];
    self.pSearchEditBox.text = @"";
    self.pSearchEditBox.textColor = ExampleApp::Helpers::ColorPalette::UiTextCopyColour;
    self.pSearchEditBox.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.pSearchEditBox.clearButtonMode = UITextFieldViewModeAlways;
    self.pSearchEditBox.backgroundColor = [UIColor clearColor];
    self.pSearchEditBox.borderStyle = UITextBorderStyleNone;
    self.pSearchEditBox.returnKeyType = UIReturnKeySearch;
    self.pSearchEditBox.placeholder = @"Enter search term";
    
    m_maxScreenSpace = m_screenHeight - (upperMargin + dragTabSize);
    
    m_menuContainerWidth = tableCellWidth + searchCountLabelWidth + tableCellRightInset;
    m_menuContainerHeight = m_maxScreenSpace;
    m_menuContainerOffScreenX = -m_menuContainerWidth;
    m_menuContainerOffScreenY = upperMargin + dragTabSize;
    m_menuContainerClosedOnScreenX = m_menuContainerOffScreenX;
    m_menuContainerClosedOnScreenY = m_menuContainerOffScreenY;
    m_menuContainerOpenOnScreenX = 0.0f;
    m_menuContainerOpenOnScreenY = m_menuContainerOffScreenY;
    
    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_menuContainerOffScreenX, m_menuContainerOffScreenY, m_menuContainerWidth, m_menuContainerHeight)] autorelease];
    
    self.pTopTableSeparator = [[[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, m_menuContainerWidth, m_tableSpacing)] autorelease];
    self.pTopTableSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::TableSeparatorColor;
    
    self.pSearchTableSeparator = [[[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, m_menuContainerWidth, m_tableSpacing)] autorelease];
    self.pSearchTableSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::TableSeparatorColor;
    
    self.pTableViewContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0.0f, m_tableSpacing, m_menuContainerWidth, 0.0f)] autorelease];
    self.pTableViewContainer.bounces = NO;
    self.pTableViewContainer.contentSize = CGSizeMake(m_menuContainerWidth, 0.0f);
    self.pTableViewContainer.backgroundColor = [UIColor clearColor];
    self.pTableViewContainer.scrollEnabled = YES;
    self.pTableViewContainer.userInteractionEnabled = YES;
    
    self.pSearchResultsTableContainerView = [[[UIScrollView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, m_menuContainerWidth, 0.0f)] autorelease];
    self.pSearchResultsTableContainerView.bounces = NO;
    self.pSearchResultsTableContainerView.contentSize = CGSizeMake(m_menuContainerWidth, 0.0f);
    self.pSearchResultsTableContainerView.backgroundColor = [UIColor clearColor];
    self.pSearchResultsTableContainerView.scrollEnabled = YES;
    self.pSearchResultsTableContainerView.userInteractionEnabled = YES;
    
    const float tableX = 0.0f;
    const float tableY = 0.0f;
    const float tableWidth = m_menuContainerWidth;
    const float tableHeight = 0.0f;
    
    self.pTableView = [[[CustomTableView alloc] initWithFrame:CGRectMake(tableX, tableY, tableWidth, tableHeight)
                                                        style:UITableViewStylePlain
                                                     menuView:self
                                                  hasSubMenus:true
                                                    cellWidth:tableCellWidth
                                                    cellInset:searchCountLabelWidth
                        ] autorelease];
    self.pTableView.backgroundColor = [UIColor clearColor];
    self.pTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.pTableView.bounces = NO;
    self.pTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    self.pTableView.pBackgroundView.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;
    
    self.pSearchResultsTableView = [[[CustomTableView alloc] initWithFrame:CGRectMake(tableX, tableY, tableWidth, tableHeight)
                                                                     style:UITableViewStylePlain
                                                                  menuView:self
                                                               hasSubMenus:true
                                                                 cellWidth:tableCellWidth
                                                                 cellInset:searchCountLabelWidth
                                     ] autorelease];
    self.pSearchResultsTableView.backgroundColor = [UIColor clearColor];
    self.pSearchResultsTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.pSearchResultsTableView.bounces = NO;
    self.pSearchResultsTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    self.pSearchResultsTableView.pBackgroundView.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;
    
    [self addSubview: self.pDragTab];
    [self addSubview: self.pTitleContainer];
    [self.pTitleContainer addSubview: self.pSearchCountLabel];
    [self.pTitleContainer addSubview: self.pSearchEditBoxBackground];
    [self.pTitleContainer addSubview: self.pSearchEditBox];
    [self addSubview: self.pMenuContainer];
    [self.pMenuContainer addSubview: self.pTopTableSeparator];
    [self.pMenuContainer addSubview: self.pSearchTableSeparator];
    [self.pMenuContainer addSubview: self.pTableViewContainer];
    [self.pTableViewContainer addSubview:self.pTableView];
    [self.pTableViewContainer addSubview:self.pSearchResultsTableContainerView];
    [self.pSearchResultsTableContainerView addSubview:self.pSearchResultsTableView];
    
    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "search_magglass", ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.frame = CGRectZero;
    
    self.pInputDelegate = [[[SearchMenuInputDelegate alloc] initWithTextField:self.pSearchEditBox interop:m_pSearchMenuInterop] autorelease];
}

- (void)dealloc
{
    [self.pInputDelegate release];
    
    [self.pSearchResultsTableView removeFromSuperview];
    [self.pSearchResultsTableView release];
    
    [self.pTableView removeFromSuperview];
    [self.pTableView release];
    
    [self.pSearchResultsTableContainerView removeFromSuperview];
    [self.pSearchResultsTableContainerView release];

    [self.pTableViewContainer removeFromSuperview];
    [self.pTableViewContainer release];
    
    [self.pSearchTableSeparator removeFromSuperview];
    [self.pSearchTableSeparator release];
    
    [self.pTopTableSeparator removeFromSuperview];
    [self.pTopTableSeparator release];
    
    [self.pMenuContainer removeFromSuperview];
    [self.pMenuContainer release];
    
    [self.pSearchEditBox removeFromSuperview];
    [self.pSearchEditBox release];
    
    [self.pSearchEditBoxBackground removeFromSuperview];
    [self.pSearchEditBoxBackground release];
    
    [self.pSearchCountLabel removeFromSuperview];
    [self.pSearchCountLabel release];
    
    [self.pTitleContainer removeFromSuperview];
    [self.pTitleContainer release];

    [self.pDragTab removeFromSuperview];
    [self.pDragTab release];

    Eegeo_DELETE m_pSearchMenuInterop;
    [self removeFromSuperview];
    [super dealloc];
}

- (void)initializeAnimators
{
    [super initializeAnimators];
    
    // On/off screen animations
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pSearchEditBoxBackground,
                                                                                                              m_animationDurationSeconds,
                                                                                                              0.0,
                                                                                                              Eegeo::v2(m_searchEditBoxBackgroundOffScreenX, m_searchEditBoxBackgroundOffScreenY),
                                                                                                              Eegeo::v2(m_searchEditBoxBackgroundClosedOnScreenX, m_searchEditBoxBackgroundClosedOnScreenY),
                                                                                                              Eegeo::v2(m_searchEditBoxBackgroundOffScreenWidth, m_searchEditBoxBackgroundOffScreenHeight),
                                                                                                              Eegeo::v2(m_searchEditBoxBackgroundClosedOnScreenWidth, m_searchEditBoxBackgroundClosedOnScreenHeight),
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::BackOut<Eegeo::v2>)()));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAlphaAnimator)(self.pSearchCountLabel,
                                                                                                              m_animationDurationSeconds,
                                                                                                              0.0f,
                                                                                                              m_searchCountLabelOffScreenAlpha,
                                                                                                              m_searchCountLabelClosedOnScreenAlpha,
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchCountLabel,
                                                                                                                 m_animationDurationSeconds,
                                                                                                                 0.0f,
                                                                                                                 Eegeo::v2(m_searchCountLabelOffScreenX, m_searchCountLabelOffScreenY),
                                                                                                                 Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenY),
                                                                                                                 Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAlphaAnimator)(self.pSearchEditBox,
                                                                                                              m_animationDurationSeconds,
                                                                                                              0.0f,
                                                                                                              m_searchEditBoxOffScreenAlpha,
                                                                                                              m_searchEditBoxClosedOnScreenAlpha,
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchEditBox,
                                                                                                                 m_animationDurationSeconds,
                                                                                                                 0.0f,
                                                                                                                 Eegeo::v2(m_searchEditBoxOffScreenX, m_searchEditBoxOffScreenY),
                                                                                                                 Eegeo::v2(m_searchEditBoxClosedOnScreenX, m_searchEditBoxClosedOnScreenY),
                                                                                                                 Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
    
    // Open/closed on screen animations
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pSearchEditBoxBackground,
                                                                                                          m_animationDurationSeconds,
                                                                                                          m_animationDelaySeconds,
                                                                                                          Eegeo::v2(m_searchEditBoxBackgroundClosedOnScreenX, m_searchEditBoxBackgroundClosedOnScreenY),
                                                                                                          Eegeo::v2(m_searchEditBoxBackgroundOpenOnScreenX, m_searchEditBoxBackgroundOpenOnScreenY),
                                                                                                          Eegeo::v2(m_searchEditBoxBackgroundClosedOnScreenWidth, m_searchEditBoxBackgroundClosedOnScreenHeight),
                                                                                                          Eegeo::v2(m_searchEditBoxBackgroundOpenOnScreenWidth, m_searchEditBoxBackgroundOpenOnScreenHeight),
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::BackOut<Eegeo::v2>)()));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAlphaAnimator)(self.pSearchCountLabel,
                                                                                                          m_animationDurationSeconds,
                                                                                                          m_animationDelaySeconds,
                                                                                                          m_searchCountLabelClosedOnScreenAlpha,
                                                                                                          m_searchCountLabelOpenOnScreenAlpha,
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchCountLabel,
                                                                                                             m_animationDurationSeconds,
                                                                                                             m_animationDelaySeconds,
                                                                                                             Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenY),
                                                                                                             Eegeo::v2(m_searchCountLabelOpenOnScreenX, m_searchCountLabelOpenOnScreenY),
                                                                                                             Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAlphaAnimator)(self.pSearchEditBox,
                                                                                                          m_animationDurationSeconds,
                                                                                                          m_animationDelaySeconds,
                                                                                                          m_searchEditBoxClosedOnScreenAlpha,
                                                                                                          m_searchEditBoxOpenOnScreenAlpha,
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchEditBox,
                                                                                                             m_animationDurationSeconds,
                                                                                                             m_animationDelaySeconds,
                                                                                                             Eegeo::v2(m_searchEditBoxClosedOnScreenX, m_searchEditBoxClosedOnScreenY),
                                                                                                             Eegeo::v2(m_searchEditBoxOpenOnScreenX, m_searchEditBoxOpenOnScreenY),
                                                                                                             Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    [super setOffscreenPartsHiddenState:hidden];
    self.pSearchEditBox.hidden = hidden;
    self.pSearchEditBoxBackground.hidden = hidden;
    self.pSearchCountLabel.hidden = hidden;
}

- (void) setSearchResultCount:(int)searchResultCount
{
    if(searchResultCount == 0)
    {
        [self.pSearchCountLabel setText:@""];
    }
    else
    {
        [self.pSearchCountLabel setText:[NSString stringWithFormat:@"%d", searchResultCount]];
    }
}

- (void) collapseAll
{
    [m_pDataProvider collapseAll];
}

- (void) updateTableAnimation:(float)deltaSeconds
{
    Eegeo_ASSERT([self.pTableView isAnimating] || [self.pSearchResultsTableView isAnimating], "updateTableAnimation called when table is not animating, please call isTableAnimating to check that animation is running before calling updateTableAnimation");
    
    if([self.pTableView isAnimating])
    {
        [self.pTableView updateAnimation:deltaSeconds];
    }
    
    if([self.pSearchResultsTableView isAnimating])
    {
        [self.pSearchResultsTableView updateAnimation:deltaSeconds];
    }
}

- (void) onTableAnimationUpdated
{
    const float tableContentHeight = self.pTableView.pBackgroundView.frame.size.height;
    const float searchResultsTableContentHeight = self.pSearchResultsTableView.pBackgroundView.frame.size.height;
    
    [self updateHeightsWithTableContentHeight:tableContentHeight
              searchResultsTableContentHeight:searchResultsTableContentHeight
                         updateContainersOnly:YES];
}

- (BOOL) isTableAnimating
{
    return [self.pTableView isAnimating] || [self.pSearchResultsTableView isAnimating];
}

- (void)refreshTableHeights
{
    const float tableContentHeight = [m_pDataProvider getRealTableHeight];
    const float searchResultsTableContentHeight = [m_pSearchResultsDataProvider getRealTableHeight];
    
    [self updateHeightsWithTableContentHeight:tableContentHeight
              searchResultsTableContentHeight:searchResultsTableContentHeight
                         updateContainersOnly:NO];
}

- (void)refreshHeightForTable:(CustomTableView*)tableView
{
    Eegeo_ASSERT(tableView == self.pTableView || tableView == self.pSearchResultsTableView, "Can't refresh height for a table view not owned by this view");
    
    const float tableContentHeight = tableView == self.pTableView ? [m_pDataProvider getRealTableHeight] : self.pTableView.frame.size.height;
    const float searchResultsTableContentHeight = tableView == self.pSearchResultsTableView ? [m_pSearchResultsDataProvider getRealTableHeight] : self.pSearchResultsTableView.frame.size.height;
    
    [self updateHeightsWithTableContentHeight:tableContentHeight
              searchResultsTableContentHeight:searchResultsTableContentHeight
                         updateContainersOnly:NO];
}

- (void)updateHeightsWithTableContentHeight:(float)tableContentHeight
            searchResultsTableContentHeight:(float)searchResultsTableContentHeight
                       updateContainersOnly:(BOOL)updateContainersOnly
{
    float onScreenSearchResultsTableHeight;
    float tableY;
    
    if(searchResultsTableContentHeight > 0.0f)
    {
        const float maxOnScreenSearchResultsTableHeight = fmaxf(0.0f, m_maxScreenSpace - tableContentHeight - m_tableSpacing);
        
        onScreenSearchResultsTableHeight = fminf(maxOnScreenSearchResultsTableHeight, searchResultsTableContentHeight);
        tableY = (onScreenSearchResultsTableHeight > 0.0f) ? onScreenSearchResultsTableHeight + m_tableSpacing : 0.0f;
    }
    else
    {
        onScreenSearchResultsTableHeight = 0.0f;
        tableY = 0.0f;
    }
    
    const float tableViewContainerHeight = fminf(m_maxScreenSpace, tableY + tableContentHeight);
    
    CGRect frame = self.pTableView.frame;
    frame.origin.y = tableY;
    self.pTableView.frame = frame;
    
    if(!updateContainersOnly)
    {
        frame = self.pTableView.frame;
        frame.size.height = tableContentHeight;
        self.pTableView.frame = frame;
        
        frame = self.pTableView.pBackgroundView.frame;
        frame.size.height = tableContentHeight;
        self.pTableView.pBackgroundView.frame = frame;
        
        frame = self.pSearchResultsTableView.frame;
        frame.size.height = searchResultsTableContentHeight;
        self.pSearchResultsTableView.frame = frame;
        
        frame = self.pSearchResultsTableView.pBackgroundView.frame;
        frame.size.height = searchResultsTableContentHeight;
        self.pSearchResultsTableView.pBackgroundView.frame = frame;
    }
    
    frame = self.pSearchTableSeparator.frame;
    frame.origin.y = tableY;
    self.pSearchTableSeparator.frame = frame;
    
    frame = self.pSearchResultsTableContainerView.frame;
    frame.size.height = onScreenSearchResultsTableHeight;
    self.pSearchResultsTableContainerView.frame = frame;
    
    [self.pSearchResultsTableContainerView setContentSize:CGSizeMake(self.pSearchResultsTableView.frame.size.width, searchResultsTableContentHeight)];
    
    frame = self.pTableViewContainer.frame;
    frame.size.height = tableViewContainerHeight;
    self.pTableViewContainer.frame = frame;
    
    [self.pTableViewContainer setContentSize:CGSizeMake(self.pTableViewContainer.frame.size.width, tableY + tableContentHeight)];
}

- (float) getHeightForTable:(CustomTableView*)tableView
{
    Eegeo_ASSERT(tableView == self.pTableView || tableView == self.pSearchResultsTableView, "Can't get height for a table view not owned by this view");
    
    if(tableView == self.pTableView)
    {
        return [m_pDataProvider getRealTableHeight];
    }
    else
    {
        return [m_pSearchResultsDataProvider getRealTableHeight];
    }
}

- (void) setSearchSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)searchSection
{
    [m_pSearchResultsDataProvider updateSearchResultsSection:searchSection];
}

- (void)onSectionExpanded
{
    [self.pSearchEditBox setText:@""];
    m_pSearchMenuInterop->OnSearchCleared();
}

- (void)onSectionContracted
{
    
}

- (void)onRowSelected
{
    [self.pSearchEditBox resignFirstResponder];
}

@end
