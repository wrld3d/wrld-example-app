// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "CellConstants.h"
#include "SearchMenuViewInterop.h"
#include "MenuViewInterop.h"
#include "UIHelpers.h"

@implementation SearchMenuView

- (ExampleApp::SearchMenu::View::SearchMenuViewInterop*) getSearchMenuInterop
{
    return m_pSearchMenuInterop;
}

- (void) initialiseViews:(size_t)numberOfSections numberOfCells:(size_t)numberOfCells
{
    m_pSearchMenuInterop = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchMenuViewInterop)(self);

    m_pColour = ExampleApp::Helpers::ColorPalette::WhiteTone;

    m_stateChangeAnimationTimeSeconds = 0.2f;
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float upperMargin = isPhone ? 20.0f : 50.0f;

    m_mainContainerOffscreenOffsetX = (0.f * m_pixelScale);
    m_mainContainerOffscreenOffsetY = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedX = (0.f * m_pixelScale);
    m_mainContainerVisibleOnScreenWhenClosedY = (0.f * m_pixelScale);
    m_mainContainerX = (0.f * m_pixelScale) - m_mainContainerOffscreenOffsetX;
    m_mainContainerY = (upperMargin * m_pixelScale);
    m_mainContainerOnScreenWidth = (220.f * m_pixelScale);
    m_mainContainerOnScreenHeight = m_screenHeight - m_mainContainerY;
    m_mainContainerWidth = m_mainContainerOnScreenWidth + m_mainContainerOffscreenOffsetX;
    m_mainContainerHeight = m_mainContainerOnScreenHeight;

    self.pMenuContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_mainContainerX, m_mainContainerY, m_mainContainerWidth, m_mainContainerHeight)] autorelease];
    self.pMenuContainer.backgroundColor = [UIColor clearColor];
    
    m_dragTabWidth = (50.f * m_pixelScale);
    m_dragTabHeight = (50.f * m_pixelScale);
    m_dragTabX = m_mainContainerOnScreenWidth;
    m_dragTabY = m_mainContainerY + (0.f * m_pixelScale);
    self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabX, m_dragTabY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    self.pDragTab.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"menu_button")];
    self.pDragTab.transform = CGAffineTransformScale(CGAffineTransformIdentity, -1.f, 1.f);

    m_searchBoxContainerX = m_mainContainerVisibleOnScreenWhenClosedX;
    m_searchBoxContainerY = m_mainContainerVisibleOnScreenWhenClosedY;
    m_searchBoxContainerWidth = m_mainContainerOnScreenWidth;
    m_searchBoxContainerHeight = 50 * m_pixelScale;
    self.pSearchEditBoxContainer = [[[UIView alloc] initWithFrame:CGRectMake(m_searchBoxContainerX, m_searchBoxContainerY, m_searchBoxContainerWidth, m_searchBoxContainerHeight)] autorelease];
    self.pSearchEditBoxContainer.backgroundColor = [UIColor colorWithPatternImage:ExampleApp::Helpers::ImageHelpers::LoadImage(@"menu_bar")];
    self.pSearchEditBoxContainer.transform = CGAffineTransformScale(CGAffineTransformIdentity, -1.f, 1.f);

    m_searchBoxOffsetIntoContainer = m_searchBoxContainerWidth*0.05f;
    m_searchBoxX = m_searchBoxOffsetIntoContainer;
    m_searchBoxY = m_searchBoxContainerHeight * 0.18f * m_pixelScale;
    m_searchBoxWidth = (m_searchBoxContainerWidth - (2 * m_searchBoxOffsetIntoContainer));
    m_searchBoxHeight = (m_searchBoxContainerHeight * 0.65f * m_pixelScale);
    self.pSearchEditBox = [[[UITextField alloc] initWithFrame:CGRectMake(m_searchBoxX, m_searchBoxY, m_searchBoxWidth, m_searchBoxHeight)] autorelease];
    self.pSearchEditBox.text = @"";
    self.pSearchEditBox.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.pSearchEditBox.clearButtonMode = UITextFieldViewModeAlways;

    m_tableOffsetIntoContainerX = m_tableOffsetIntoContainerY = m_mainContainerVisibleOnScreenWhenClosedX;
    m_tableX = m_tableOffsetIntoContainerX;
    m_tableY = m_tableOffsetIntoContainerY + m_searchBoxContainerHeight;
    m_tableWidth = m_mainContainerOnScreenWidth - (2 * m_tableOffsetIntoContainerX);
    m_tableHeight = m_mainContainerHeight - m_searchBoxHeight;
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
                        ] autorelease];
    self.pTableview.backgroundColor = [UIColor clearColor];
    self.pTableview.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.pTableview.bounces = NO;
    
    self.pTableview.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    
    m_offscreenX = -(m_mainContainerWidth + m_dragTabWidth);
    m_openX = (0.f * m_pixelScale);
    m_closedX = -(m_mainContainerOnScreenWidth - m_mainContainerVisibleOnScreenWhenClosedX);

    [self addSubview: self.pMenuContainer];
    [self addSubview: self.pDragTab];
    [self.pMenuContainer addSubview:self.pSearchEditBoxContainer];
    [self.pMenuContainer addSubview:self.pSearchEditBox];

    [self.pTableviewContainer addSubview:self.pTableview];
    [self.pMenuContainer addSubview:self.pTableviewContainer];

    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "search_magglass", ExampleApp::Helpers::ImageHelpers::Centre);

    self.pSearchEditBox.borderStyle = UITextBorderStyleRoundedRect;
    self.pSearchEditBox.returnKeyType = UIReturnKeySearch;

    m_returnPressed = false;
    m_keyboardActive = false;

    [[NSNotificationCenter defaultCenter]
     addObserver:self
     selector:@selector(keyboardDidChangeFrame:)
     name:UIKeyboardDidChangeFrameNotification
     object:nil];

    [self.pSearchEditBox setDelegate:self];
    
    [self.pSearchEditBox setPlaceholder:@"Enter search term"];
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter]
     removeObserver:self
     name:UIKeyboardDidChangeFrameNotification
     object:nil];

    [self.pSearchEditBox removeFromSuperview];
    [self.pSearchEditBox release];

    [self.pSearchEditBoxContainer removeFromSuperview];
    [self.pSearchEditBoxContainer release];

    [self.pTableview removeFromSuperview];
    [self.pTableview release];

    [self.pTableviewContainer removeFromSuperview];
    [self.pTableviewContainer release];

    [self.pDragTab removeFromSuperview];
    [self.pDragTab release];

    [self.pMenuContainer removeFromSuperview];
    [self.pMenuContainer release];

    Eegeo_DELETE m_pSearchMenuInterop;
    [self removeFromSuperview];
    [super dealloc];
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    [super setOffscreenPartsHiddenState:hidden];
    self.pSearchEditBox.hidden = hidden;
    self.pSearchEditBoxContainer.hidden = hidden;
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

- (void) enableEdit
{
    [self.pSearchEditBox setEnabled:YES];
    self.pSearchEditBox.textColor = [UIColor blackColor];
}

- (void) disableEdit
{
    [self.pSearchEditBox setEnabled:NO];
    self.pSearchEditBox.textColor = [UIColor lightGrayColor];
}

- (void) removeSeachKeyboard
{
    if (m_keyboardActive)
    {
        [self.pSearchEditBox resignFirstResponder];
    }
}

- (void)keyboardDidChangeFrame:(NSNotification*)aNotification
{
    if (m_keyboardActive)
    {
        [self.pSearchEditBox becomeFirstResponder];
    }
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    m_keyboardActive = true;
    m_returnPressed = false;

    textField.layer.borderColor = ExampleApp::Helpers::ColorPalette::MainHudColor.CGColor;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    m_returnPressed = true;
    [self.pSearchEditBox resignFirstResponder];
    return TRUE;
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
    m_keyboardActive = false;

    textField.layer.borderColor = [[UIColor clearColor] CGColor];

    if (!m_returnPressed || [self.pSearchEditBox.text isEqualToString:@""])
    {
        return;
    }

    std::string searchString = [self.pSearchEditBox.text UTF8String];
    m_pSearchMenuInterop->SearchPerformed(searchString);
}

- (void) animateToClosedOnScreen
{
    [super animateToClosedOnScreen];
}

- (void) animateToOpenOnScreen
{
    [super animateToOpenOnScreen];
}

@end
