// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuView.h"

#include "CellConstants.h"
#include "ImageHelpers.h"
#include "MenuViewInterop.h"
#include "SettingsMenuViewInterop.h"
#include "UIHelpers.h"
#include "UIColors.h"
#include "CircleCurve.h"
#include "ViewAlphaAnimator.h"
#include "ViewPositionAnimator.h"

#import "UIButton+DefaultStates.h"

@interface SettingsMenuView()
{
    ExampleApp::SettingsMenu::View::SettingsMenuViewInterop* m_pSettingsMenuInterop;
    
    float m_titleAnimationDelaySeconds;
    float m_titleAnimationDurationSeconds;
    
    float m_titleLabelWidth;
    float m_titleLabelHeight;
    float m_titleLabelOffScreenX;
    float m_titleLabelOffScreenY;
    float m_titleLabelClosedOnScreenX;
    float m_titleLabelClosedOnScreenY;
    float m_titleLabelOpenOnScreenX;
    float m_titleLabelOpenOnScreenY;
}

@property (nonatomic, retain) UILabel* pTitleLabel;

@end

@implementation SettingsMenuView

- (ExampleApp::SettingsMenu::View::SettingsMenuViewInterop*) getSettingsMenuInterop
{
    return m_pSettingsMenuInterop;
}

- (void) initializeViews
{
    m_pSettingsMenuInterop = Eegeo_NEW(ExampleApp::SettingsMenu::View::SettingsMenuViewInterop)(self);
    
    m_titleAnimationDelaySeconds = 0.0f;
    m_titleAnimationDurationSeconds = 0.3f;
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float upperMargin = (isPhone ? 20.0f : 50.0f) * m_pixelScale;
    const float dragTabOffsetX = 28.0f * m_pixelScale;
    const float dragTabSize = 50.0f * m_pixelScale;
    const float tableSpacing = 6.0f * m_pixelScale;
    const float tableInset = 5.0f * m_pixelScale;
    
    float tableCellWidth;
    
    if(isPhone)
    {
        const float leftMargin = upperMargin;
        
        tableCellWidth = m_screenWidth - (leftMargin + dragTabSize + tableInset * 2);
    }
    else
    {
        tableCellWidth = 295.0f * m_pixelScale;
    }
    
    const float titleLabelInsetX = 12.0f * m_pixelScale;
    
    m_tableSpacing = tableSpacing;
    
    m_dragTabOffsetX = dragTabOffsetX;
    m_dragTabWidth = dragTabSize;
    m_dragTabHeight = dragTabSize;
    m_dragTabOffScreenX = m_screenWidth;
    m_dragTabOffScreenY = upperMargin;
    m_dragTabClosedOnScreenX = m_screenWidth - (m_dragTabWidth + m_dragTabOffsetX);
    m_dragTabClosedOnScreenY = m_dragTabOffScreenY;
    m_dragTabOpenOnScreenX = m_screenWidth - (m_dragTabWidth + tableCellWidth + tableInset * 2);
    m_dragTabOpenOnScreenY = m_dragTabOffScreenY;
    
    self.pDragTab = [[[UIButton alloc] initWithFrame:CGRectMake(m_dragTabOffScreenX, m_dragTabOffScreenY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    [self.pDragTab setDefaultStatesWithImageNames:@"button_settings_off" :@"button_settings_on"];
    
    m_titleContainerOffScreenWidth = 0.0f;
    m_titleContainerOffScreenHeight = m_dragTabHeight;
    m_titleContainerOffScreenX = m_dragTabOffScreenX + m_dragTabWidth;
    m_titleContainerOffScreenY = upperMargin;
    
    m_titleContainerClosedOnScreenWidth = 0.0f;
    m_titleContainerClosedOnScreenHeight = m_titleContainerOffScreenHeight;
    m_titleContainerClosedOnScreenX = m_dragTabClosedOnScreenX + m_dragTabWidth;
    m_titleContainerClosedOnScreenY = m_titleContainerOffScreenY;
    
    m_titleContainerOpenOnScreenWidth = tableCellWidth + tableInset * 2;
    m_titleContainerOpenOnScreenHeight = m_titleContainerOffScreenHeight;
    m_titleContainerOpenOnScreenX = m_dragTabOpenOnScreenX + m_dragTabWidth;
    m_titleContainerOpenOnScreenY = m_titleContainerOffScreenY;
    
    self.pTitleContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_titleContainerOffScreenX, m_titleContainerOffScreenY, m_titleContainerOffScreenWidth, m_titleContainerOffScreenHeight)] autorelease];
    self.pTitleContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::UiBorderColor;
    self.pTitleContainer.clipsToBounds = YES;
    
    m_titleLabelWidth = tableCellWidth - titleLabelInsetX;
    m_titleLabelHeight = dragTabSize;
    m_titleLabelOffScreenX = titleLabelInsetX;
    m_titleLabelOffScreenY = -dragTabSize * 0.5f;
    m_titleLabelClosedOnScreenX = m_titleLabelOffScreenX;
    m_titleLabelClosedOnScreenY = 0.0f;
    m_titleLabelOpenOnScreenX = m_titleLabelOffScreenX;
    m_titleLabelOpenOnScreenY = m_titleLabelClosedOnScreenY;
    
    self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(m_titleLabelOffScreenX, m_titleLabelOffScreenY, m_titleLabelWidth, m_titleLabelHeight)] autorelease];
    self.pTitleLabel.text = @"Settings";
    self.pTitleLabel.font = [UIFont boldSystemFontOfSize:24];
    self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::UiTextHeaderColor;
    
    m_menuContainerWidth = tableCellWidth + tableInset * 2;
    m_menuContainerHeight = m_screenHeight - (upperMargin + dragTabSize);
    m_menuContainerOffScreenX = m_screenWidth;
    m_menuContainerOffScreenY = upperMargin + dragTabSize;
    m_menuContainerClosedOnScreenX = m_menuContainerOffScreenX;
    m_menuContainerClosedOnScreenY = m_menuContainerOffScreenY;
    m_menuContainerOpenOnScreenX = m_dragTabOpenOnScreenX + m_dragTabWidth;
    m_menuContainerOpenOnScreenY = m_menuContainerOffScreenY;
    
    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_menuContainerOffScreenX, m_menuContainerOffScreenY, m_menuContainerWidth, m_menuContainerHeight)] autorelease];
    
    self.pTopTableSeparator = [[[UIView alloc] initWithFrame:CGRectMake(0.0f, 0.0f, m_menuContainerWidth, m_tableSpacing)] autorelease];
    self.pTopTableSeparator.backgroundColor = ExampleApp::Helpers::ColorPalette::TableSeparatorColor;
    
    self.pTableViewContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(0.0f, m_tableSpacing, m_menuContainerWidth, 0.0f)] autorelease];
    self.pTableViewContainer.bounces = NO;
    self.pTableViewContainer.contentSize = CGSizeMake(m_menuContainerWidth, 0.0f);
    self.pTableViewContainer.backgroundColor = [UIColor clearColor];
    self.pTableViewContainer.scrollEnabled = YES;
    self.pTableViewContainer.userInteractionEnabled = YES;
    
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
                              cellInset:tableInset
          ] autorelease];
        customTableView.backgroundColor = [UIColor clearColor];
        customTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
        customTableView.bounces = NO;
        customTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    }
    
    [self addSubview: self.pDragTab];
    [self addSubview: self.pTitleContainer];
    [self.pTitleContainer addSubview:self.pTitleLabel];
    [self addSubview: self.pMenuContainer];
    [self.pMenuContainer addSubview: self.pTopTableSeparator];
    [self.pMenuContainer addSubview: self.pTableViewContainer];
    
    for (int i = 0; i < [self.pTableViewMap count]; ++i)
    {
        [self.pTableViewContainer addSubview:self.pTableViewMap[@(i)]];
    }
    
    self.frame = CGRectMake(0, 0, m_screenWidth, m_screenHeight);
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter]
     removeObserver:self
     name:UIKeyboardDidChangeFrameNotification
     object:nil];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];
    
    [self.pTopTableSeparator removeFromSuperview];
    [self.pTopTableSeparator release];
    
    [self.pMenuContainer removeFromSuperview];
    [self.pMenuContainer release];

    [self.pTableViewContainer removeFromSuperview];
    [self.pTableViewContainer release];
    
    [self.pTitleContainer removeFromSuperview];
    [self.pTitleContainer release];

    [self.pDragTab removeFromSuperview];
    [self.pDragTab release];

    Eegeo_DELETE m_pSettingsMenuInterop;
    [self removeFromSuperview];
    [super dealloc];
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    self.pTitleContainer.hidden = hidden;
}

- (void)initializeAnimators
{
    [super initializeAnimators];
    
    // On / off screen animations
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pTitleLabel,
                                                                                                                 m_titleAnimationDurationSeconds,
                                                                                                                 0.0,
                                                                                                                 Eegeo::v2(m_titleLabelOffScreenX, m_titleLabelOffScreenY),
                                                                                                                 Eegeo::v2(m_titleLabelClosedOnScreenX, m_titleLabelClosedOnScreenY),
                                                                                                                 Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
    
    // Open / closed on screen animations
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewPositionAnimator)(self.pTitleLabel,
                                                                                                  m_titleAnimationDurationSeconds,
                                                                                                  m_titleAnimationDelaySeconds,
                                                                                                  Eegeo::v2(m_titleLabelClosedOnScreenX, m_titleLabelClosedOnScreenY),
                                                                                                  Eegeo::v2(m_titleLabelOpenOnScreenX, m_titleLabelOpenOnScreenY),
                                                                                                  Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::CircleInOut<Eegeo::v2>)()));
}

@end
