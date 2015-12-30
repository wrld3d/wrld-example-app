// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "ImageHelpers.h"
#include "UIColors.h"
#include "CellConstants.h"
#include "SearchMenuViewInterop.h"
#include "MenuViewInterop.h"
#include "UIHelpers.h"
#include "BackCurve.h"
#include "ViewFrameAnimator.h"

@interface SearchMenuView()
{
    ExampleApp::SearchMenu::View::SearchMenuViewInterop* m_pSearchMenuInterop;
    
    bool m_keyboardActive;
    bool m_returnPressed;
    bool m_currentSearchIsCategory;
    
    float m_searchEditBoxAnimationDelaySeconds;
    float m_searchEditBoxAnimationDurationSeconds;
    
    float m_searchEditBoxOffScreenWidth;
    float m_searchEditBoxOffScreenHeight;
    float m_searchEditBoxOffScreenX;
    float m_searchEditBoxOffScreenY;
    float m_searchEditBoxClosedOnScreenWidth;
    float m_searchEditBoxClosedOnScreenHeight;
    float m_searchEditBoxClosedOnScreenX;
    float m_searchEditBoxClosedOnScreenY;
    float m_searchEditBoxOpenOnScreenWidth;
    float m_searchEditBoxOpenOnScreenHeight;
    float m_searchEditBoxOpenOnScreenX;
    float m_searchEditBoxOpenOnScreenY;
}

@property (nonatomic, retain) UITextField* pSearchEditBox;

@end

@implementation SearchMenuView

- (ExampleApp::SearchMenu::View::SearchMenuViewInterop*) getSearchMenuInterop
{
    return m_pSearchMenuInterop;
}

- (void) initializeViews
{
    m_pSearchMenuInterop = Eegeo_NEW(ExampleApp::SearchMenu::View::SearchMenuViewInterop)(self);
    
    m_searchEditBoxAnimationDelaySeconds = 0.2f;
    m_searchEditBoxAnimationDurationSeconds = 0.1f;
    
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    
    const float upperMargin = (isPhone ? 20.0f : 50.0f) * m_pixelScale;
    const float tableWidth = 248.0f * m_pixelScale;
    const float dragTabOffsetX = 28.0f * m_pixelScale;
    const float dragTabSize = 50.0f * m_pixelScale;
    const float tableViewContainerOffsetY = 2.0f * m_pixelScale;
    
    const float searchEditBoxInsetX = 12.0f * m_pixelScale;
    const float searchEditBoxInsetY = 6.0f * m_pixelScale;
    
    m_dragTabOffsetX = dragTabOffsetX;
    m_dragTabWidth = dragTabSize;
    m_dragTabHeight = dragTabSize;
    m_dragTabOffScreenX = -m_dragTabWidth;
    m_dragTabOffScreenY = upperMargin * m_pixelScale;
    m_dragTabClosedOnScreenX = m_dragTabOffsetX;
    m_dragTabClosedOnScreenY = m_dragTabOffScreenY;
    m_dragTabOpenOnScreenX = tableWidth;
    m_dragTabOpenOnScreenY = m_dragTabOffScreenY;
    
    self.pDragTab = [[[UIView alloc] initWithFrame:CGRectMake(m_dragTabOffScreenX, m_dragTabOffScreenY, m_dragTabWidth, m_dragTabHeight)] autorelease];
    self.pDragTab.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;
    
    m_titleContainerOffScreenWidth = 0.0f;
    m_titleContainerOffScreenHeight = m_dragTabHeight;
    m_titleContainerOffScreenX = m_dragTabOffScreenX;
    m_titleContainerOffScreenY = upperMargin * m_pixelScale;
    
    m_titleContainerClosedOnScreenWidth = 0.0f;
    m_titleContainerClosedOnScreenHeight = m_titleContainerOffScreenHeight;
    m_titleContainerClosedOnScreenX = m_dragTabClosedOnScreenX;
    m_titleContainerClosedOnScreenY = m_titleContainerOffScreenY;
    
    m_titleContainerOpenOnScreenWidth = tableWidth;
    m_titleContainerOpenOnScreenHeight = m_titleContainerOffScreenHeight;
    m_titleContainerOpenOnScreenX = 0.0f;
    m_titleContainerOpenOnScreenY = m_titleContainerOffScreenY;
    
    self.pTitleContainer = [[UIView alloc] initWithFrame:CGRectMake(m_titleContainerOffScreenX, m_titleContainerOffScreenY, m_titleContainerOffScreenWidth, m_titleContainerOffScreenHeight)];
    self.pTitleContainer.backgroundColor = ExampleApp::Helpers::ColorPalette::BorderHudColor;
    
    m_searchEditBoxOffScreenWidth = tableWidth - (searchEditBoxInsetX * 2.0f);
    m_searchEditBoxOffScreenHeight = 0.0f;
    m_searchEditBoxOffScreenX = searchEditBoxInsetX;
    m_searchEditBoxOffScreenY = dragTabSize / 2.0f;
    m_searchEditBoxClosedOnScreenWidth = m_searchEditBoxOffScreenWidth;
    m_searchEditBoxClosedOnScreenHeight = 0.0f;
    m_searchEditBoxClosedOnScreenX = m_searchEditBoxOffScreenX;
    m_searchEditBoxClosedOnScreenY = m_searchEditBoxOffScreenY;
    m_searchEditBoxOpenOnScreenWidth = m_searchEditBoxOffScreenWidth;
    m_searchEditBoxOpenOnScreenHeight = dragTabSize - (searchEditBoxInsetY * 2.0f);
    m_searchEditBoxOpenOnScreenX = m_searchEditBoxOffScreenX;
    m_searchEditBoxOpenOnScreenY = searchEditBoxInsetY;
    
    self.pSearchEditBox = [[[UITextField alloc] initWithFrame:CGRectMake(m_searchEditBoxOffScreenX, m_searchEditBoxOffScreenY, m_searchEditBoxOffScreenWidth, m_searchEditBoxOffScreenHeight)] autorelease];
    self.pSearchEditBox.text = @"";
    self.pSearchEditBox.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
    self.pSearchEditBox.clearButtonMode = UITextFieldViewModeAlways;

    m_tableViewContainerOffsetY = tableViewContainerOffsetY;
    m_tableViewContainerWidth = tableWidth;
    m_tableViewContainerHeight = 0.0f;
    m_tableViewContainerOffScreenX = -m_tableViewContainerWidth;
    m_tableViewContainerOffScreenY = upperMargin + dragTabSize + m_tableViewContainerOffsetY;
    m_tableViewContainerClosedOnScreenX = m_tableViewContainerOffScreenX;
    m_tableViewContainerClosedOnScreenY = m_tableViewContainerOffScreenY;
    m_tableViewContainerOpenOnScreenX = 0.0f;
    m_tableViewContainerOpenOnScreenY = m_tableViewContainerOffScreenY;
    
    self.pTableViewContainer = [[[UIScrollView alloc] initWithFrame:CGRectMake(m_tableViewContainerOffScreenX, m_tableViewContainerOffScreenY, m_tableViewContainerWidth, m_tableViewContainerHeight)] autorelease];
    self.pTableViewContainer.bounces = NO;
    self.pTableViewContainer.contentSize = CGSizeMake(m_tableWidth, 0.0f);
    self.pTableViewContainer.backgroundColor = [UIColor cyanColor];
    
    m_tableX = 0.0f;
    m_tableY = 0.0f;
    m_tableWidth = m_tableViewContainerWidth;
    m_tableHeight = 0.0f;
    
    self.pTableView = [[[CustomTableView alloc] initWithFrame:CGRectMake(m_tableX, m_tableY, m_tableWidth, m_tableHeight)
                                                        style:UITableViewStylePlain
                                                    container:self.pTableViewContainer
                                                     menuView:self
                                                  hasSubMenus:true
                        ] autorelease];
    self.pTableView.backgroundColor = [UIColor clearColor];
    self.pTableView.separatorStyle = UITableViewCellSeparatorStyleNone;
    self.pTableView.bounces = NO;
    
    self.pTableView.tableFooterView = [[UIView alloc] initWithFrame:CGRectZero];
    
    [self addSubview: self.pDragTab];
    [self addSubview: self.pTitleContainer];
    [self.pTitleContainer addSubview: self.pSearchEditBox];
    [self addSubview: self.pTableViewContainer];
    [self.pTableViewContainer addSubview:self.pTableView];

    ExampleApp::Helpers::ImageHelpers::AddPngImageToParentView(self.pDragTab, "search_magglass", ExampleApp::Helpers::ImageHelpers::Centre);
    
    self.frame = CGRectZero;
    
    self.pSearchEditBox.borderStyle = UITextBorderStyleRoundedRect;
    self.pSearchEditBox.returnKeyType = UIReturnKeySearch;

    m_returnPressed = false;
    m_keyboardActive = false;
    m_currentSearchIsCategory = false;

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

    [self.pTableView removeFromSuperview];
    [self.pTableView release];

    [self.pTableViewContainer removeFromSuperview];
    [self.pTableViewContainer release];
    
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
    m_onScreenAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pSearchEditBox,
                                                                                                              m_searchEditBoxAnimationDurationSeconds,
                                                                                                              0.0,
                                                                                                              Eegeo::v2(m_searchEditBoxOffScreenX, m_searchEditBoxOffScreenY),
                                                                                                              Eegeo::v2(m_searchEditBoxClosedOnScreenX, m_searchEditBoxClosedOnScreenY),
                                                                                                              Eegeo::v2(m_searchEditBoxOffScreenWidth, m_searchEditBoxOffScreenHeight),
                                                                                                              Eegeo::v2(m_searchEditBoxClosedOnScreenWidth, m_searchEditBoxClosedOnScreenHeight),
                                                                                                              Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::BackOut<Eegeo::v2>)()));
    // Open/closed on screen animations
    m_openAnimationController->AddAnimator(Eegeo_NEW(ExampleApp::Helpers::UIAnimation::ViewFrameAnimator)(self.pSearchEditBox,
                                                                                                          m_searchEditBoxAnimationDurationSeconds,
                                                                                                          m_searchEditBoxAnimationDelaySeconds,
                                                                                                          Eegeo::v2(m_searchEditBoxClosedOnScreenX, m_searchEditBoxClosedOnScreenY),
                                                                                                          Eegeo::v2(m_searchEditBoxOpenOnScreenX, m_searchEditBoxOpenOnScreenY),
                                                                                                          Eegeo::v2(m_searchEditBoxClosedOnScreenWidth, m_searchEditBoxClosedOnScreenHeight),
                                                                                                          Eegeo::v2(m_searchEditBoxOpenOnScreenWidth, m_searchEditBoxOpenOnScreenHeight),
                                                                                                          Eegeo_NEW(ExampleApp::Helpers::UIAnimation::Easing::BackOut<Eegeo::v2>)()));
}

- (void) setOffscreenPartsHiddenState:(bool)hidden
{
    [super setOffscreenPartsHiddenState:hidden];
    self.pSearchEditBox.hidden = hidden;
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

- (void) setEditText :(NSString*)searchText
                     :(bool)isCategory
{
    [self.pSearchEditBox setText:searchText];
    
    m_currentSearchIsCategory = isCategory;
}

- (void) collapseAll
{
    [m_pDataProvider collapseAll];
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
    
    if(m_currentSearchIsCategory)
    {
        [textField setText:@""];
        m_currentSearchIsCategory = false;
    }

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

- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    m_pSearchMenuInterop->OnSearchCleared();
    
    return YES;
}

@end
