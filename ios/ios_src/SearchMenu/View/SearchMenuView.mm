// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "CellConstants.h"
#include "CustomTableDataProvider.h"
#include "SearchMenuResultsSpinner.h"
#include "SearchResultsTableDataProvider.h"
#include "SearchMenuViewInterop.h"
#include "MenuViewInterop.h"
#include "UIHelpers.h"
#include "BackCurve.h"
#include "CircleCurve.h"
#include "ViewAlphaAnimator.h"
#include "ViewFrameAnimator.h"
#include "ViewPositionAnimator.h"
#include "ViewSizeAnimator.h"
#include "SearchMenuDragTab.h"

#import "UIButton+DefaultStates.h"

@interface SearchMenuView()
{
    SearchResultsTableDataProvider* m_pSearchResultsDataProvider;
    ExampleApp::SearchMenu::View::SearchMenuViewInterop* m_pSearchMenuInterop;
    
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_pOnScreenResultsAnimationController;
    ExampleApp::Helpers::UIAnimation::ViewAnimationController* m_pAnchorAnimationController;
    
    bool m_resultsVisible;
    bool m_titleContainersRequireRefresh;
    bool m_resultsScrollable;
    
    float m_anchorAnimationDurationSeconds;
    
    float m_animationDelaySeconds;
    float m_animationDurationSeconds;
    
    float m_textFadeAnimationDelaySeconds;
    float m_textFadeAnimationDurationSeconds;
    
    float m_maxScreenSpace;
    
    float m_titleContainerClosedOnScreenWidthWithResults;
    float m_titleContainerClosedOnScreenXWithResults;
    
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
    
    float m_searchCountLabelClosedOnScreenAlphaWithResults;
    float m_searchCountLabelClosedOnScreenYWithResults;
    
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
    
    float m_anchorArrowWidth;
    float m_anchorArrowClosedHeight;
    float m_anchorArrowOpenHeight;
    
    float m_totalTableHeight;
}

@property (nonatomic, retain) UILabel* pSearchCountLabel;
@property (nonatomic, retain) UIView* pSearchEditBoxBackground;
@property (nonatomic, retain) UITextField* pSearchEditBox;
@property (nonatomic, retain) UIView* pSearchEditBoxClearButtonContainer;
@property (nonatomic, retain) UIButton* pSearchEditBoxClearButton;
@property (nonatomic, retain) SearchMenuResultsSpinner* pSearchEditBoxResultsSpinner;
@property (nonatomic, retain) UIView* pSearchTableSeparator;
@property (nonatomic, retain) UIImageView* pAnchorArrowImage;
@property (nonatomic, retain) UIView* pSearchMenuScrollButtonContainer;
@property (nonatomic, retain) UIButton* pSearchMenuScrollButton;
@property (nonatomic, retain) UIImageView* pSearchMenuFadeImage;
@property (nonatomic, retain) SearchMenuDragTab* pSearchMenuDragTab;

@end

@implementation SearchMenuView

- (id)initWithParams:(float)width
                    :(float)height
                    :(float)pixelScale
                    :(CustomTableDataProvider*)dataProvider
                    :(int)tableCount
                    :(SearchResultsTableDataProvider*)searchResultsDataProvider
{
    [super initWithParams:width
                         :height
                         :pixelScale
                         :dataProvider
                         :tableCount];
    
    dataProvider.rowSelectionDelegate = self;
    
    m_pSearchResultsDataProvider = searchResultsDataProvider;
    [m_pSearchResultsDataProvider initWithParams:self];
    
    return self;
}

- (ExampleApp::SearchMenu::View::SearchMenuViewInterop*) getSearchMenuInterop
{
    return m_pSearchMenuInterop;
}

-(float) getUpperMargin
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    return (isPhone ? 20.0f : 50.0f) * m_pixelScale;
}

- (void) initializeViews
{
    m_pSearchMenuInterop = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchMenuViewInterop)(self);
    
    m_pOnScreenResultsAnimationController = NULL;
    m_pAnchorAnimationController = NULL;
    
    m_resultsVisible = false;
    m_titleContainersRequireRefresh = false;
    m_resultsScrollable = false;
    
    m_anchorAnimationDurationSeconds = 0.1f;
    
    m_animationDelaySeconds = 0.2f;
    m_animationDurationSeconds = 0.1f;
    m_textFadeAnimationDelaySeconds = 0.25f;
    m_textFadeAnimationDurationSeconds = 0.05f;
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float upperMargin = [self getUpperMargin];
    const float lowerMargin = (isPhone ? 0.0f : 50.0f) * m_pixelScale;
    const float searchCountLabelWidth = (isPhone ? 28.f : 32.0f) * m_pixelScale;
    const float dragTabOffsetX = searchCountLabelWidth;
    const float dragTabSize = 50.0f * m_pixelScale;
    const float tableSpacing = 6.0f * m_pixelScale;
    
    const float tableCellRightInset = 5.0f * m_pixelScale;
    
    float tableCellWidth;
    
    if(isPhone)
    {
        const float rightMargin = upperMargin;
        
        tableCellWidth = m_screenWidth - (searchCountLabelWidth + tableCellRightInset + dragTabSize + rightMargin);
    }
    else
    {
        tableCellWidth = 295.0f * m_pixelScale;
    }
    
    const float searchEditBoxLeftInset = 8.0f * m_pixelScale;
    const float searchEditBoxInsetY = 8.0f * m_pixelScale;
    
    const float searchClearButtonSize = 24.0f * m_pixelScale;
    const float searchClearButtonRightInset = 6.0f * m_pixelScale;
    
    const float searchResultsScrollButtonSize = 48.0f * m_pixelScale;
    const float searchResultFadeImageHeight = 52.0f * m_pixelScale;
    
    const float anchorArrowSize = 14.0f * m_pixelScale;
    const float ancorArrowCenterInset = 21.0f * m_pixelScale;
    const float anchorArrowX = searchCountLabelWidth + (ancorArrowCenterInset - anchorArrowSize / 2.0f);
    const float anchorArrowY = -8.0f * m_pixelScale;
    
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
    
    self.pDragTab = [[[UIButton alloc] initWithFrame:CGRectMake(m_dragTabOffScreenX, m_dragTabOffScreenY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    [self.pDragTab setDefaultStatesWithImageNames:@"button_search_off" :@"button_search_on"];
    
    self.pSearchMenuDragTab = [[SearchMenuDragTab alloc] autorelease];
    [self.pSearchMenuDragTab init:self.pDragTab];
    
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
    
    m_titleContainerClosedOnScreenWidthWithResults = dragTabOffsetX;
    m_titleContainerClosedOnScreenXWithResults = 0.0f;
    
    self.pTitleContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_titleContainerOffScreenX, m_titleContainerOffScreenY, m_titleContainerOffScreenWidth, m_titleContainerOffScreenHeight)] autorelease];
    self.pTitleContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
    
    m_searchCountLabelWidth = searchCountLabelWidth;
    m_searchCountLabelHeight = dragTabSize;
    m_searchCountLabelOffScreenAlpha = 0.0f;
    m_searchCountLabelOffScreenX = 0.0f;
    m_searchCountLabelOffScreenY = 0.0f;
    m_searchCountLabelClosedOnScreenAlpha = 0.0f;
    m_searchCountLabelClosedOnScreenX = 0.0f;
    m_searchCountLabelClosedOnScreenY = 0.0f;
    m_searchCountLabelOpenOnScreenAlpha = 1.0f;
    m_searchCountLabelOpenOnScreenX = 0.0f;
    m_searchCountLabelOpenOnScreenY = 0.0f;
    
    m_searchCountLabelClosedOnScreenAlphaWithResults = 1.0f;
    m_searchCountLabelClosedOnScreenYWithResults = 0.0f;
    
    self.pSearchCountLabel = [[[UILabel alloc] initWithFrame:CGRectMake(m_searchCountLabelOffScreenX, m_searchCountLabelOffScreenY, m_searchCountLabelWidth, m_searchCountLabelHeight)] autorelease];
    [self.pSearchCountLabel setBackgroundColor:[UIColor clearColor]];
    [self.pSearchCountLabel setFont:[UIFont systemFontOfSize:16.0f]];
    [self.pSearchCountLabel setTextColor:ExampleApp::Helpers::ColorPalette::UiTextHeaderColor];
    [self.pSearchCountLabel setAlpha:m_searchCountLabelOffScreenAlpha];
    [self.pSearchCountLabel setTextAlignment:NSTextAlignmentCenter];
    [self.pSearchCountLabel setText:@""];
    
    m_searchEditBoxBackgroundOffScreenWidth = tableCellWidth;
    m_searchEditBoxBackgroundOffScreenHeight = 0.0f;
    m_searchEditBoxBackgroundOffScreenX = searchCountLabelWidth;
    m_searchEditBoxBackgroundOffScreenY = m_searchCountLabelHeight * 0.5f;
    m_searchEditBoxBackgroundClosedOnScreenWidth = m_searchEditBoxBackgroundOffScreenWidth;
    m_searchEditBoxBackgroundClosedOnScreenHeight = 0.0f;
    m_searchEditBoxBackgroundClosedOnScreenX = m_searchEditBoxBackgroundOffScreenX;
    m_searchEditBoxBackgroundClosedOnScreenY = m_searchEditBoxBackgroundOffScreenY;
    m_searchEditBoxBackgroundOpenOnScreenWidth = m_searchEditBoxBackgroundOffScreenWidth;
    m_searchEditBoxBackgroundOpenOnScreenHeight = dragTabSize - (searchEditBoxInsetY * 2.0f);
    m_searchEditBoxBackgroundOpenOnScreenX = m_searchEditBoxBackgroundOffScreenX;
    m_searchEditBoxBackgroundOpenOnScreenY = searchEditBoxInsetY;
    
    self.pSearchEditBoxBackground = [[[UIView alloc] initWithFrame:CGRectMake(m_searchEditBoxBackgroundOffScreenX, m_searchEditBoxBackgroundOpenOnScreenY, m_searchEditBoxBackgroundOffScreenWidth, m_searchEditBoxBackgroundOpenOnScreenHeight)] autorelease];
    self.pSearchEditBoxBackground.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBackgroundColor;
    self.pSearchEditBoxBackground.layer.cornerRadius = 5.0f;
    self.pSearchEditBoxBackground.layer.masksToBounds = YES;
    
    m_searchEditBoxWidth = tableCellWidth - searchEditBoxLeftInset;
    m_searchEditBoxHeight = dragTabSize - (searchEditBoxInsetY * 2.0f);
    m_searchEditBoxOffScreenAlpha = 0.0f;
    m_searchEditBoxOffScreenX = searchCountLabelWidth + searchEditBoxLeftInset;
    m_searchEditBoxOffScreenY = -dragTabSize * 0.5f;
    m_searchEditBoxClosedOnScreenAlpha = 0.0f;
    m_searchEditBoxClosedOnScreenX = m_searchEditBoxOffScreenX;
    m_searchEditBoxClosedOnScreenY = m_searchEditBoxOffScreenY;
    m_searchEditBoxOpenOnScreenAlpha = 1.0f;
    m_searchEditBoxOpenOnScreenX = m_searchEditBoxOffScreenX;
    m_searchEditBoxOpenOnScreenY = searchEditBoxInsetY;
    
    self.pSearchEditBox = [[[UITextField alloc] initWithFrame:CGRectMake(m_searchEditBoxOffScreenX, m_searchEditBoxOffScreenY, m_searchEditBoxWidth, m_searchEditBoxHeight)] autorelease];
    self.pSearchEditBox.text = @"";
    self.pSearchEditBox.textColor = ExampleApp::Helpers::ColorPalette::TextFieldEnabledColor;
    self.pSearchEditBox.font = [UIFont systemFontOfSize:18.0f];
    self.pSearchEditBox.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.pSearchEditBox.clearButtonMode = UITextFieldViewModeNever;
    self.pSearchEditBox.backgroundColor = [UIColor clearColor];
    self.pSearchEditBox.borderStyle = UITextBorderStyleNone;
    self.pSearchEditBox.returnKeyType = UIReturnKeySearch;
    self.pSearchEditBox.placeholder = @"Enter search term";
    
    self.pSearchEditBoxClearButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, searchClearButtonSize + searchClearButtonRightInset, searchClearButtonSize)] autorelease];
    
    self.pSearchEditBoxClearButton = [[[UIButton alloc] initWithFrame:CGRectMake(0.0f, 0.0f, searchClearButtonSize, searchClearButtonSize)] autorelease];
    [self.pSearchEditBoxClearButton setImage:[UIImage imageNamed:@"button_clear_search_off"] forState:UIControlStateNormal];
    [self.pSearchEditBoxClearButton setImage:[UIImage imageNamed:@"button_clear_search_on"] forState:UIControlStateHighlighted];
    
    self.pSearchEditBoxResultsSpinner = [[[SearchMenuResultsSpinner alloc] init] autorelease];
    self.pSearchEditBoxResultsSpinner.center = CGPointMake(12.0f, 12.0f);
    
    [self.pSearchEditBoxClearButtonContainer addSubview:self.pSearchEditBoxClearButton];
    [self.pSearchEditBoxClearButtonContainer addSubview:self.pSearchEditBoxResultsSpinner];
    
    self.pSearchEditBox.rightView = self.pSearchEditBoxClearButtonContainer;
    self.pSearchEditBox.rightViewMode = UITextFieldViewModeAlways;
    
    m_maxScreenSpace = m_screenHeight - (upperMargin + dragTabSize + m_tableSpacing + lowerMargin);
    
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
    self.pTableViewContainer.delaysContentTouches = false;
    
    m_anchorArrowWidth = anchorArrowSize;
    m_anchorArrowClosedHeight = 0.0f;
    m_anchorArrowOpenHeight = anchorArrowSize;
    
    self.pAnchorArrowImage = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"results_anchor_arrow.png"]] autorelease];
    self.pAnchorArrowImage.contentMode = UIViewContentModeTop;
    self.pAnchorArrowImage.frame = CGRectMake(anchorArrowX, anchorArrowY, m_anchorArrowWidth, m_anchorArrowClosedHeight);
    self.pAnchorArrowImage.clipsToBounds = YES;
    
    CGRect myframe = self.pSearchResultsTableContainerView.frame;
    
    self.pSearchMenuFadeImage = [[[UIImageView alloc] initWithImage:[UIImage imageNamed:@"SearchResults_Fade"]] autorelease];
    self.pSearchMenuFadeImage.contentMode = UIViewContentModeScaleAspectFill;
    self.pSearchMenuFadeImage.frame = CGRectMake(tableCellWidth/2 + m_searchCountLabelWidth - (tableCellWidth/2), myframe.size.height/2, tableCellWidth, searchResultFadeImageHeight);
    self.pSearchMenuFadeImage.clipsToBounds = YES;
    
    self.pSearchResultsTableContainerView = [[[UIScrollView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, m_menuContainerWidth, 0.0f)] autorelease];
    self.pSearchResultsTableContainerView.bounces = NO;
    self.pSearchResultsTableContainerView.contentSize = CGSizeMake(m_menuContainerWidth, 0.0f);
    self.pSearchResultsTableContainerView.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
    self.pSearchResultsTableContainerView.scrollEnabled = YES;
    self.pSearchResultsTableContainerView.userInteractionEnabled = YES;
    self.pSearchResultsTableContainerView.delegate = self;
    
    self.pSearchMenuScrollButtonContainer = [[[UIView alloc] initWithFrame:CGRectMake(tableCellWidth/2 + m_searchCountLabelWidth - (searchResultsScrollButtonSize/2) , myframe.size.height/2, searchResultsScrollButtonSize, searchResultsScrollButtonSize)] autorelease];
    
    self.pSearchMenuScrollButton = [[[UIButton alloc] initWithFrame:CGRectMake(0.0f, 0.0f, searchResultsScrollButtonSize, searchResultsScrollButtonSize)] autorelease];
    [self.pSearchMenuScrollButton setImage:[UIImage imageNamed:@"SearchResults_ScrollButton"] forState:UIControlStateNormal];
    [self.pSearchMenuScrollButton setImage:[UIImage imageNamed:@"SearchResults_ScrollButton_Down"] forState:UIControlStateHighlighted];
    
    const float tableX = 0.0f;
    const float tableY = 0.0f;
    const float tableWidth = m_menuContainerWidth;
    const float tableHeight = 0.0f;
    
    for(int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        CustomTableView* customTableView = self.pTableViewMap[@(i)];
        
        [[customTableView initWithFrame:CGRectMake(tableX, tableY, tableWidth, tableHeight)
                                  style:UITableViewStylePlain
                               menuView:self
                            hasSubMenus:true
                              cellWidth:tableCellWidth
                              cellInset:searchCountLabelWidth
          ] autorelease];
        customTableView.backgroundColor = [UIColor clearColor];
        customTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        customTableView.bounces = NO;
        customTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    }
    
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
    
    [self addSubview: self.pDragTab];
    [self addSubview: self.pTitleContainer];
    [self.pTitleContainer addSubview: self.pSearchCountLabel];
    [self.pTitleContainer addSubview: self.pSearchEditBoxBackground];
    [self.pTitleContainer addSubview: self.pSearchEditBox];
    [self addSubview: self.pMenuContainer];
    [self.pMenuContainer addSubview: self.pTopTableSeparator];
    [self.pMenuContainer addSubview: self.pSearchTableSeparator];
    [self.pMenuContainer addSubview: self.pTableViewContainer];
    [self.pMenuContainer addSubview: self.pAnchorArrowImage];
    
    for (int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        [self.pTableViewContainer addSubview:self.pTableViewMap[@(i)]];
    }
    
    [self.pTableViewContainer addSubview:self.pSearchResultsTableContainerView];
    [self.pSearchResultsTableContainerView addSubview:self.pSearchResultsTableView];
    [self.pTableViewContainer addSubview:self.pSearchMenuFadeImage];
    [self.pSearchMenuScrollButtonContainer addSubview:self.pSearchMenuScrollButton];
    [self.pTableViewContainer addSubview:self.pSearchMenuScrollButtonContainer];
    
    self.frame = CGRectMake(0, 0, m_screenWidth, m_screenHeight);
    
    self.pInputDelegate = [[[SearchMenuInputDelegate alloc] initWithTextField:self.pSearchEditBox
                                                                  clearButton:self.pSearchEditBoxClearButton
                                                               resultsSpinner:self.pSearchEditBoxResultsSpinner
                                                                      interop:m_pSearchMenuInterop
                                                                searchMenuScrollButton:self.pSearchMenuScrollButton
                                                                searchMenuScrollView:self.pSearchResultsTableContainerView
                                                                      dragTab:self.pSearchMenuDragTab]autorelease];
}

- (void)dealloc
{
    [self.pInputDelegate release];
    
    [self.pSearchResultsTableView removeFromSuperview];
    [self.pSearchResultsTableView release];
    
    [self.pSearchResultsTableContainerView removeFromSuperview];
    [self.pSearchResultsTableContainerView release];
    
    [self.pAnchorArrowImage removeFromSuperview];
    [self.pAnchorArrowImage release];

    [self.pTableViewContainer removeFromSuperview];
    [self.pTableViewContainer release];
    
    [self.pSearchTableSeparator removeFromSuperview];
    [self.pSearchTableSeparator release];
    
    [self.pTopTableSeparator removeFromSuperview];
    [self.pTopTableSeparator release];
    
    [self.pMenuContainer removeFromSuperview];
    [self.pMenuContainer release];
    
    [self.pSearchEditBoxResultsSpinner removeFromSuperview];
    [self.pSearchEditBoxResultsSpinner release];
    
    [self.pSearchEditBoxClearButton removeFromSuperview];
    [self.pSearchEditBoxClearButton release];
    
    [self.pSearchEditBoxClearButtonContainer removeFromSuperview];
    [self.pSearchEditBoxClearButtonContainer release];
    
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
    
    [self.pSearchMenuFadeImage removeFromSuperview];
    [self.pSearchMenuFadeImage release];
    
    [self.pSearchMenuScrollButton removeFromSuperview];
    [self.pSearchMenuScrollButton release];
    
    [self.pSearchMenuScrollButtonContainer removeFromSuperview];
    [self.pSearchMenuScrollButtonContainer release];

    Eegeo_DELETE m_pAnchorAnimationController;
    
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
                                                                                                          m_textFadeAnimationDurationSeconds,
                                                                                                          m_textFadeAnimationDelaySeconds,
                                                                                                          m_searchEditBoxClosedOnScreenAlpha,
                                                                                                          m_searchEditBoxOpenOnScreenAlpha,
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchEditBox,
                                                                                                             m_animationDurationSeconds,
                                                                                                             m_animationDelaySeconds,
                                                                                                             Eegeo::v2(m_searchEditBoxClosedOnScreenX, m_searchEditBoxClosedOnScreenY),
                                                                                                             Eegeo::v2(m_searchEditBoxOpenOnScreenX, m_searchEditBoxOpenOnScreenY),
                                                                                                             Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
    
    // On screen results received animations
    m_pOnScreenResultsAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                                 nil,
                                                                                                                 nil);
    
    m_pOnScreenResultsAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pTitleContainer,
                                                                                                              m_animationDurationSeconds,
                                                                                                              0.0,
                                                                                                              Eegeo::v2(m_titleContainerClosedOnScreenX, m_titleContainerClosedOnScreenY),
                                                                                                              Eegeo::v2(m_titleContainerClosedOnScreenXWithResults, m_titleContainerClosedOnScreenY),
                                                                                                              Eegeo::v2(m_titleContainerClosedOnScreenWidth, m_titleContainerClosedOnScreenHeight),
                                                                                                              Eegeo::v2(m_titleContainerClosedOnScreenWidthWithResults, m_titleContainerClosedOnScreenHeight),
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    m_pOnScreenResultsAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAlphaAnimator)(self.pSearchCountLabel,
                                                                                                              m_animationDurationSeconds,
                                                                                                              0.0f,
                                                                                                              m_searchCountLabelClosedOnScreenAlpha,
                                                                                                              m_searchCountLabelClosedOnScreenAlphaWithResults,
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_pOnScreenResultsAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchCountLabel,
                                                                                                                 m_animationDurationSeconds,
                                                                                                                 0.0f,
                                                                                                                 Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenY),
                                                                                                                 Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenYWithResults),
                                                                                                                 Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
    
    
    // Anchor arrow animations
    m_pAnchorAnimationController = Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAnimationController)(self,
                                                                                                        nil,
                                                                                                        nil);
    
    m_pAnchorAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewSizeAnimator)(self.pAnchorArrowImage,
                                                                                                            m_anchorAnimationDurationSeconds,
                                                                                                            0.0,
                                                                                                            Eegeo::v2(m_anchorArrowWidth, m_anchorArrowClosedHeight),
                                                                                                            Eegeo::v2(m_anchorArrowWidth, m_anchorArrowOpenHeight),
                                                                                                            Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
}

- (void) refreshTitleContainerAnimations:(Eegeo::v2)titleContainerClosedOnScreenPosition
                                        :(Eegeo::v2)titleContainerClosedOnScreenSize
                                        :(float)searchCountLabelClosedOnScreenAlpha
                                        :(Eegeo::v2)searchCountLabelClosedOnScreenPosition
{
    m_onScreenAnimationController->DeleteAnimatorsForView(self.pTitleContainer);
    m_onScreenAnimationController->DeleteAnimatorsForView(self.pSearchCountLabel);
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pTitleContainer,
                                                                                                              m_stateChangeAnimationTimeSeconds,
                                                                                                              0.0,
                                                                                                              Eegeo::v2(m_titleContainerOffScreenX, m_titleContainerOffScreenY),
                                                                                                              titleContainerClosedOnScreenPosition,
                                                                                                              Eegeo::v2(m_titleContainerOffScreenWidth, m_titleContainerOffScreenHeight),
                                                                                                              titleContainerClosedOnScreenSize,
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAlphaAnimator)(self.pSearchCountLabel,
                                                                                                              m_animationDurationSeconds,
                                                                                                              0.0f,
                                                                                                              m_searchCountLabelOffScreenAlpha,
                                                                                                              searchCountLabelClosedOnScreenAlpha,
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchCountLabel,
                                                                                                                 m_animationDurationSeconds,
                                                                                                                 0.0f,
                                                                                                                 Eegeo::v2(m_searchCountLabelOffScreenX, m_searchCountLabelOffScreenY),
                                                                                                                 searchCountLabelClosedOnScreenPosition,
                                                                                                                 Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
    
    m_openAnimationController->DeleteAnimatorsForView(self.pTitleContainer);
    m_openAnimationController->DeleteAnimatorsForView(self.pSearchCountLabel);
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pTitleContainer,
                                                                                                          m_stateChangeAnimationTimeSeconds,
                                                                                                          0.0,
                                                                                                          titleContainerClosedOnScreenPosition,
                                                                                                          Eegeo::v2(m_titleContainerOpenOnScreenX, m_titleContainerOpenOnScreenY),
                                                                                                          titleContainerClosedOnScreenSize,
                                                                                                          Eegeo::v2(m_titleContainerOpenOnScreenWidth, m_titleContainerOpenOnScreenHeight),
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewAlphaAnimator)(self.pSearchCountLabel,
                                                                                                          m_animationDurationSeconds,
                                                                                                          m_animationDelaySeconds,
                                                                                                          searchCountLabelClosedOnScreenAlpha,
                                                                                                          m_searchCountLabelOpenOnScreenAlpha,
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<float>())));
    
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pSearchCountLabel,
                                                                                                             m_animationDurationSeconds,
                                                                                                             m_animationDelaySeconds,
                                                                                                             searchCountLabelClosedOnScreenPosition,
                                                                                                             Eegeo::v2(m_searchCountLabelOpenOnScreenX, m_searchCountLabelOpenOnScreenY),
                                                                                                             Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>())));
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    [super setOffscreenPartsHiddenState:hidden];
    self.pSearchEditBox.hidden = hidden;
    self.pSearchEditBoxBackground.hidden = hidden;
    [self updateSearchResultsButtonVisibility];
}

- (void) setSearchResultCount:(NSInteger)searchResultCount
{
    
    [self.pSearchCountLabel setText:[NSString stringWithFormat:@"%d", static_cast<int>(searchResultCount)]];
    
    if(!m_resultsVisible)
    {
        if([super isAnimating])
        {
            m_titleContainersRequireRefresh = true;
        }
        else
        {
            m_titleContainersRequireRefresh = false;
            
            [self refreshTitleContainerAnimations:Eegeo::v2(m_titleContainerClosedOnScreenXWithResults, m_titleContainerClosedOnScreenY)
                                                 :Eegeo::v2(m_titleContainerClosedOnScreenWidthWithResults, m_titleContainerClosedOnScreenHeight)
                                                 :m_searchCountLabelClosedOnScreenAlphaWithResults
                                                 :Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenYWithResults)];
        }
        
        if([self openOnScreenState] == 0.0f)
        {
            m_pOnScreenResultsAnimationController->Play();
        }
        
        m_resultsVisible = true;
    }
    
    if(searchResultCount > 0)
    {
        m_pAnchorAnimationController->Play();
    }
    else if(self.pAnchorArrowImage.frame.size.height > 0)
    {
        m_pAnchorAnimationController->PlayReverse();
    }
    
    [self.pInputDelegate setHasResults: searchResultCount>0];
}

- (void) hideSearchResultCount
{
    [self.pSearchCountLabel setText:@""];
    
    if(m_resultsVisible)
    {
        if(self.pAnchorArrowImage.frame.size.height > 0)
        {
            m_pAnchorAnimationController->PlayReverse();
        }
        
        if([super isAnimating])
        {
            m_titleContainersRequireRefresh = true;
        }
        else
        {
            m_titleContainersRequireRefresh = false;
            
            [self refreshTitleContainerAnimations:Eegeo::v2(m_titleContainerClosedOnScreenX, m_titleContainerClosedOnScreenY)
                                                 :Eegeo::v2(m_titleContainerClosedOnScreenWidth, m_titleContainerClosedOnScreenHeight)
                                                 :m_searchCountLabelClosedOnScreenAlpha
                                                 :Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenY)];
        }
        
        if([self openOnScreenState] == 0.0f)
        {
            m_pOnScreenResultsAnimationController->PlayReverse();
        }
        
        m_resultsVisible = false;
    }
    
    [self.pInputDelegate setHasResults: false];
}

- (void) removeSearchQueryResults
{
    [self hideSearchResultCount];
    [self.pInputDelegate interopClearSearch];
}

- (void) onMenuStateUpdated
{
    switch (m_menuState)
    {
        case OFF_SCREEN: [self.pInputDelegate setMenuOpen:false]; break;
        case CLOSED_ON_SCREEN: [self.pInputDelegate setMenuOpen:false]; break;
        case OPEN_ON_SCREEN: [self.pInputDelegate setMenuOpen:true]; break;
        default: break;
    }
    
    if(m_titleContainersRequireRefresh)
    {
        if(m_resultsVisible)
        {
            [self refreshTitleContainerAnimations:Eegeo::v2(m_titleContainerClosedOnScreenXWithResults, m_titleContainerClosedOnScreenY)
                                                 :Eegeo::v2(m_titleContainerClosedOnScreenWidthWithResults, m_titleContainerClosedOnScreenHeight)
                                                 :m_searchCountLabelClosedOnScreenAlphaWithResults
                                                 :Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenYWithResults)];
            
            if(self.pTitleContainer.frame.origin.x != m_titleContainerClosedOnScreenXWithResults)
            {
                m_pOnScreenResultsAnimationController->Play();
            }
        }
        else
        {
            [self refreshTitleContainerAnimations:Eegeo::v2(m_titleContainerClosedOnScreenX, m_titleContainerClosedOnScreenY)
                                                 :Eegeo::v2(m_titleContainerClosedOnScreenWidth, m_titleContainerClosedOnScreenHeight)
                                                 :m_searchCountLabelClosedOnScreenAlpha
                                                 :Eegeo::v2(m_searchCountLabelClosedOnScreenX, m_searchCountLabelClosedOnScreenY)];
        }
    }
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
    
    float onScreenState = [self openOnScreenState];
    bool isPlayingForward = m_openAnimationController->IsPlayingForward();
    bool showCloseView = (onScreenState > 0.0f && isPlayingForward)
                            && [self.pInputDelegate getEditText].length() == 0;
    [self.pSearchMenuDragTab showCloseView:showCloseView];
}

- (void) updateTableAnimation:(float)deltaSeconds
{
    if([super isTableAnimating])
    {
        [super updateTableAnimation:deltaSeconds];
    }
    
    if([self.pSearchResultsTableView isAnimating])
    {
        [self.pSearchResultsTableView updateAnimation:deltaSeconds];
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
    return [super isTableAnimating] || [self.pSearchResultsTableView isAnimating];
}

- (void)refreshTableHeights
{
    float totalTableHeight = 0.0f;
    float onScreenSearchResultsTableHeight;
    float tableY;
    float maxOnScreenSearchResultsTableHeight = 0.0f;
    
    for(int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        CustomTableView* customTableView = self.pTableViewMap[@(i)];
        
        const float tableHeight = [customTableView refreshHeight:[m_pDataProvider getRealHeightForTable:customTableView]];
        
        CGRect frame = customTableView.frame;
        frame.origin.y = totalTableHeight;
        customTableView.frame = frame;
        
        totalTableHeight += tableHeight;
    }
    m_totalTableHeight = totalTableHeight;
    
    const float searchResultsTableContentHeight = [self.pSearchResultsTableView refreshHeight:[m_pSearchResultsDataProvider getRealTableHeight]];
    
    if(searchResultsTableContentHeight > 0.0f)
    {
        maxOnScreenSearchResultsTableHeight = fmaxf(0.0f, m_maxScreenSpace - totalTableHeight - m_tableSpacing);
        
        onScreenSearchResultsTableHeight = fminf(maxOnScreenSearchResultsTableHeight, searchResultsTableContentHeight);
        tableY = (onScreenSearchResultsTableHeight > 0.0f) ? onScreenSearchResultsTableHeight + m_tableSpacing : 0.0f;
    }
    else
    {
        onScreenSearchResultsTableHeight = 0.0f;
        tableY = 0.0f;
    }
    
    if(tableY != 0.0)
    {
        for(int i = 0; i < [self.pTableViewMap count]; ++i)
        {
            CustomTableView* customTableView = self.pTableViewMap[@(i)];
            
            CGRect frame = customTableView.frame;
            frame.origin.y = frame.origin.y + tableY;
            customTableView.frame = frame;
        }
    }
    
    const float tableViewContainerHeight = fminf(m_maxScreenSpace, tableY + totalTableHeight);
    
    CGRect frame = self.pSearchTableSeparator.frame;
    frame.origin.y = tableY;
    self.pSearchTableSeparator.frame = frame;
    
    frame = self.pSearchResultsTableContainerView.frame;
    frame.size.height = onScreenSearchResultsTableHeight;
    self.pSearchResultsTableContainerView.frame = frame;
    
    if (m_resultsVisible && m_resultsScrollable && !self.isTableAnimating) {
        CGRect buttonFrame = self.pSearchMenuScrollButtonContainer.frame;
        buttonFrame.origin.y = onScreenSearchResultsTableHeight - (buttonFrame.size.height * m_pixelScale);
        self.pSearchMenuScrollButtonContainer.frame = buttonFrame;
        
        buttonFrame = self.pSearchMenuFadeImage.frame;
        buttonFrame.origin.y = onScreenSearchResultsTableHeight - (buttonFrame.size.height * m_pixelScale);
        self.pSearchMenuFadeImage.frame = buttonFrame;
    }
    else
    {
        _pSearchMenuScrollButtonContainer.hidden = true;
        _pSearchMenuFadeImage.hidden = true;
    }

    [self.pSearchResultsTableContainerView setContentSize:CGSizeMake(self.pSearchResultsTableView.frame.size.width, searchResultsTableContentHeight)];
    
    frame = self.pTableViewContainer.frame;
    frame.size.height = tableViewContainerHeight;
    self.pTableViewContainer.frame = frame;
    
    [self.pTableViewContainer setContentSize:CGSizeMake(self.pTableViewContainer.frame.size.width, tableY + totalTableHeight)];
    
    if (searchResultsTableContentHeight > maxOnScreenSearchResultsTableHeight)
    {
        m_resultsScrollable = true;
    }
    else
    {
        m_resultsScrollable = false;
    }
    
    [self updateSearchResultsButtonVisibility];
}

- (float) getHeightForTable:(CustomTableView*)tableView
{
    if(tableView == self.pSearchResultsTableView)
    {
        return [m_pSearchResultsDataProvider getRealTableHeight];
    }
    else
    {
        return [super getHeightForTable:tableView];
    }
}

- (void) setSearchSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)searchSection
{
    [m_pSearchResultsDataProvider updateSearchResultsSection:searchSection];
}

- (void)onSectionExpanded
{
    m_pSearchMenuInterop->OnSearchCleared();
}

- (void)onSectionContracted
{
    
}

- (void)onRowSelected
{
    [self.pInputDelegate removeSeachKeyboard];
}

- (void)scrollViewDidScroll:(UIScrollView *)sender
{
    [self updateSearchResultsButtonVisibility];
}

- (void)updateSearchResultsButtonVisibility
{
    if(self.pSearchResultsTableContainerView.contentOffset.y + self.pSearchResultsTableContainerView.frame.size.height == self.pSearchResultsTableContainerView.contentSize.height)
    {
        _pSearchMenuScrollButtonContainer.hidden = true;
        _pSearchMenuFadeImage.hidden = true;
    }
    else
    {
        if(_pSearchMenuScrollButtonContainer.hidden == true)
        {
            _pSearchMenuScrollButton.alpha = 0.0;
            [UIView animateWithDuration:1.0 animations:^{_pSearchMenuScrollButton.alpha = 1.0;}];
        }
        _pSearchMenuScrollButtonContainer.hidden = false;
        _pSearchMenuFadeImage.hidden = false;
    }
}

-(BOOL) pointInside:(CGPoint)point
          withEvent:(UIEvent*)event
{
    return point.y < [self getUpperMargin] + m_dragTabHeight + m_totalTableHeight + self.pSearchResultsTableContainerView.frame.size.height + 2.0f*m_tableSpacing;
}

@end
