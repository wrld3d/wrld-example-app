// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SettingsMenuView.h"

#include "CellConstants.h"
#include "ImageHelpers.h"
#include "MenuViewInterop.h"
#include "SettingsMenuViewInterop.h"
#include "UIHelpers.h"
#include "UIColors.h"

@implementation SettingsMenuView

- (ExampleApp::SettingsMenu::View::SettingsMenuViewInterop*) getSettingsMenuInterop
{
    return m_pSettingsMenuInterop;
}

- (void) initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
    m_pSettingsMenuInterop = Eegeo_NEW(ExampleApp::SettingsMenu::View::SettingsMenuViewInterop)(self);

    m_pColour = ExampleApp::Helpers::ColorPalette::WhiteTone;

    m_stateChangeAnimationTimeSeconds = 0.2f;
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float upperMargin = isPhone ? 20.0f : 50.0f;

    m_mainContainerOffscreenOffsetX = (0.f * m_pixelScale);
    m_mainContainerOffscreenOffsetY = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedX = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedY = (0.f * m_pixelScale);
    m_mainContainerX = m_screenWidth - m_mainContainerVisibleOnScreenWhenClosedX;
    m_mainContainerY = (upperMargin * m_pixelScale);
    m_mainContainerOnScreenWidth = (220.f * m_pixelScale);
    m_mainContainerOnScreenHeight = m_screenHeight - m_mainContainerY;
    m_mainContainerWidth = m_mainContainerOnScreenWidth + m_mainContainerOffscreenOffsetX;
    m_mainContainerHeight = m_mainContainerOnScreenHeight;

    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_mainContainerX, m_mainContainerY, m_mainContainerWidth, m_mainContainerHeight)] autorelease];
    self.pMenuContainer.backgroundColor = [UIColor clearColor];

    m_dragTabY = m_mainContainerY + (0.f * m_pixelScale);
    m_dragTabWidth = (50.f * m_pixelScale);
    m_dragTabX = m_mainContainerX - m_dragTabWidth;
    m_dragTabHeight = (50.f * m_pixelScale);
    self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabX, m_dragTabY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    self.pDragTab.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;

    m_titleContainerX = m_mainContainerVisibleOnScreenWhenClosedX;
    m_titleContainerY = m_mainContainerVisibleOnScreenWhenClosedY;
    m_titleContainerWidth = m_mainContainerOnScreenWidth;
    m_titleContainerHeight = 50 * m_pixelScale;
    self.pTitleContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_titleContainerX, m_titleContainerY, m_titleContainerWidth, m_titleContainerHeight)] autorelease];
    self.pTitleContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;
    
    const float titleOffsetIntoContainer = m_titleContainerWidth*0.05f;
    const float titleX = titleOffsetIntoContainer;
    const float titleY = m_titleContainerHeight * 0.18f * m_pixelScale;
    const float titleWidth = (m_titleContainerWidth - (2 * titleOffsetIntoContainer));
    const float titleHeight = (m_titleContainerHeight * 0.65f * m_pixelScale);
    self.pTitleLabel = [[[UILabel alloc] initWithFrame:CGRectMake(titleX, titleY, titleWidth, titleHeight)] autorelease];
    self.pTitleLabel.text = @"Settings";
    self.pTitleLabel.font = [UIFont boldSystemFontOfSize:24];
    self.pTitleLabel.textColor = ExampleApp::Helpers::ColorPalette::WhiteTone;

    m_tableOffsetIntoContainerX = m_tableOffsetIntoContainerY = m_mainContainerVisibleOnScreenWhenClosedX;
    m_tableX = m_tableOffsetIntoContainerX;
    m_tableY = m_tableOffsetIntoContainerY + m_titleContainerHeight;
    m_tableWidth = m_mainContainerOnScreenWidth - (2 * m_tableOffsetIntoContainerX);
    m_tableHeight = m_mainContainerHeight - titleHeight;
    const float tableScreenY = m_mainContainerY + m_mainContainerOffscreenOffsetY + m_tableY;
    const float tableScreenSpace = m_screenHeight - tableScreenY;
    m_tableHeight = std::min(tableScreenSpace, m_tableHeight);

    const float realTableHeight =  (SECTION_HEADER_CELL_HEIGHT * numberOfSections) + (SUB_SECTION_CELL_HEIGHT * (numberOfCells));

    self.pTableviewContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight)] autorelease];
    self.pTableviewContainer.bounces = NO;
    self.pTableviewContainer.contentSize = CGSizeMake(m_tableWidth, realTableHeight);
    
    self.pTableview = [[[CustomTableView alloc] initWithFrame:CGRectMake(0.f, 0.f, m_tableWidth, realTableHeight)
                                                        style:UITableViewStylePlain
                                                    container:self.pTableviewContainer
                                                  hasSubMenus:true
                                                  onRowsAdded:nil
                                                onRowsDeleted:nil
                        ] autorelease];
    self.pTableview.backgroundColor = [UIColor clearColor];
    self.pTableview.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.pTableview.bounces = NO;
    
    self.pTableview.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    
    m_offscreenX = m_dragTabWidth + m_mainContainerVisibleOnScreenWhenClosedX;
    m_openX = -(m_mainContainerOnScreenWidth - m_mainContainerVisibleOnScreenWhenClosedX);
    m_closedX = (0.f * m_pixelScale);
    m_animationCurrentPos.x = m_offscreenX;
    m_animationCurrentPos.y = m_offscreenY;

    [self addSubview: self.pMenuContainer];
    [self addSubview: self.pDragTab];
    [self.pTitleContainer addSubview:self.pTitleLabel];
    [self.pMenuContainer addSubview:self.pTitleContainer];

    [self.pTableviewContainer addSubview:self.pTableview];
    [self.pMenuContainer addSubview:self.pTableviewContainer];

    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "settings_gear", ExampleApp::Helpers::ImageHelpers::Centre);
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter]
     removeObserver:self
     name:UIKeyboardDidChangeFrameNotification
     object:nil];
    
    [self.pTitleLabel removeFromSuperview];
    [self.pTitleLabel release];

    [self.pTitleContainer removeFromSuperview];
    [self.pTitleContainer release];

    [self.pTableview removeFromSuperview];
    [self.pTableview release];

    [self.pTableviewContainer removeFromSuperview];
    [self.pTableviewContainer release];

    [self.pDragTab removeFromSuperview];
    [self.pDragTab release];

    [self.pMenuContainer removeFromSuperview];
    [self.pMenuContainer release];

    Eegeo_DELETE m_pSettingsMenuInterop;
    [self removeFromSuperview];
    [super dealloc];
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

    [super animateToX:(open ? m_openX : m_closedX)];
    m_pInterop->HandleDraggingViewCompleted();
}

@end
