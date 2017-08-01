// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuInputDelegate.h"

#include "SearchMenuViewInterop.h"
#include "UIColors.h"

@interface SearchMenuInputDelegate()
{
    UITextField* m_pTextField;
    UIButton* m_pClearButton;
    SearchMenuResultsSpinner* m_pResultsSpinner;
    ExampleApp::SearchMenu::View::SearchMenuViewInterop* m_pInterop;
    UIButton* m_pSearchMenuScrollButton;
    UIScrollView* m_pSearchMenuScrollView;
    NSTimer *searchMenuScrollUpdateTimer;
    SearchMenuDragTab* m_pDragTab;
    
    BOOL m_keyboardActive;
    BOOL m_returnPressed;
    BOOL m_currentSearchIsTag;
    BOOL m_hasResults;
    BOOL m_searchInProgress;
    BOOL m_editingText;
    BOOL m_menuOpen;
    
    float m_scrollSpeed;
}

@end

@implementation SearchMenuInputDelegate

- (id)initWithTextField:(UITextField*)textField
            clearButton:(UIButton*)clearButton
         resultsSpinner:(SearchMenuResultsSpinner*)resultsSpinner
                interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop
            searchMenuScrollButton:(UIButton*)searchMenuScrollButton
            searchMenuScrollView:(UIScrollView*)searchMenuScrollView
                dragTab:(SearchMenuDragTab*)dragTab
{
    m_hasResults = NO;
    m_pTextField = textField;
    m_pClearButton = clearButton;
    m_pResultsSpinner = resultsSpinner;
    m_pInterop = interop;
    m_pSearchMenuScrollButton = searchMenuScrollButton;
    m_pSearchMenuScrollView = searchMenuScrollView;
    m_pDragTab = dragTab;
    m_menuOpen = false;
    
    m_pTextField.delegate = self;
    
    [m_pClearButton addTarget:self action:@selector(clearSearch) forControlEvents:UIControlEventTouchUpInside];
    
    [m_pSearchMenuScrollButton addTarget:self action:@selector(searchMenuScrollStart) forControlEvents:UIControlEventTouchDown];
    [m_pSearchMenuScrollButton addTarget:self action:@selector(searchMenuScrollStop) forControlEvents:UIControlEventTouchUpInside];
    [m_pSearchMenuScrollButton addTarget:self action:@selector(searchMenuScrollStop) forControlEvents:UIControlEventTouchDragExit];

    [self updateClearButtonVisibility:m_pTextField];
    
    m_keyboardActive = false;
    m_returnPressed = false;
    m_currentSearchIsTag = false;
    m_searchInProgress = false;
    m_editingText = false;
    
    m_scrollSpeed = 25.0f;
    
    [[NSNotificationCenter defaultCenter]addObserver:self
                                            selector:@selector(keyboardDidChangeFrame:)
                                                name:UIKeyboardDidChangeFrameNotification
                                              object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(textFieldTextDidChange:)
                                                 name:UITextFieldTextDidChangeNotification
                                               object:m_pTextField];
    
    [m_pTextField addTarget:self action:@selector(textFieldDidChange:)forControlEvents:UIControlEventEditingChanged];
    
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter] removeObserver:self
                                                    name:UITextFieldTextDidChangeNotification
                                                  object:m_pTextField];
    
    [[NSNotificationCenter defaultCenter]removeObserver:self
                                                   name:UIKeyboardDidChangeFrameNotification
                                                 object:nil];
    
    m_pTextField.delegate = nil;
    
    [super dealloc];
}

- (void) setSearchInProgress
{
    [m_pResultsSpinner startAnimating];
    m_searchInProgress = true;
    m_editingText = false;
    [self updateClearButtonVisibility:m_pTextField];
}

- (void) setSearchEnded
{
    [m_pResultsSpinner stopAnimating];
    m_searchInProgress = false;
    [self updateClearButtonVisibility:m_pTextField];
}

- (void) removeSeachKeyboard
{
    [m_pTextField resignFirstResponder];
}

- (void) setEditText :(NSString*)searchText
                     :(bool)isTag
{
    if(![m_pTextField isEditing])
    {
        [m_pTextField setText:searchText];
    }
    
    m_currentSearchIsTag = isTag;
    
    [self updateClearButtonVisibility:m_pTextField];
    [m_pDragTab showCloseView: !m_pTextField.hasText];
}

- (std::string) getEditText
{
    return std::string([m_pTextField.text UTF8String]);
}

- (bool) hasTagSearch
{
    return m_currentSearchIsTag;
}

- (void) clearSearch
{
    m_pInterop->OnSearchCleared();
    
    m_pTextField.text = @"";
    
    [self updateClearButtonVisibility:m_pTextField];
    [m_pDragTab showCloseView: true];
    m_currentSearchIsTag = false;
}

- (void) interopClearSearch
{
    if(!m_editingText)
    {
        m_pTextField.text = @"";
        [m_pDragTab showCloseView: m_menuOpen];
    }
    [self updateClearButtonVisibility:m_pTextField];
    m_currentSearchIsTag = false;
}

- (void) setHasResults :(bool)hasResults
{
    m_hasResults = hasResults;
}

- (void) setMenuOpen :(bool)menuOpen
{
    m_menuOpen = menuOpen;
}

- (void)updateClearButtonVisibility :(UITextField*)textField
{
    if(m_searchInProgress)
    {
        m_pClearButton.hidden = YES;
    }
    else
    {
        m_pClearButton.hidden = !textField.hasText;
    }
}

- (void)textFieldTextDidChange:(NSNotification*)aNotification
{
    if(aNotification.object != m_pTextField)
    {
        return;
    }
}

- (void)keyboardDidChangeFrame:(NSNotification*)aNotification
{
    if (m_keyboardActive)
    {
        [m_pTextField becomeFirstResponder];
    }
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
    m_keyboardActive = true;
    m_returnPressed = false;
    
    if(m_currentSearchIsTag)
    {
        m_currentSearchIsTag = false;
        [self interopClearSearch];
    }
    [self updateClearButtonVisibility:textField];
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    m_returnPressed = true;
    [textField resignFirstResponder];
    return TRUE;
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
    m_keyboardActive = false;
    
    if (!m_returnPressed || [textField.text isEqualToString:@""])
    {
        [self updateClearButtonVisibility:textField];
        return;
    }
    
    std::string searchString = [textField.text UTF8String];
    m_pInterop->SearchPerformed(searchString);
    [self updateClearButtonVisibility:textField];
}

- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    m_pInterop->OnSearchCleared();
    
    textField.text = @"";
    
    [self updateClearButtonVisibility:textField];
    return NO;
}

- (void)clampScrollOffsetY:(CGPoint &)scrollOffset
{
    if (scrollOffset.y > m_pSearchMenuScrollView.contentSize.height - m_pSearchMenuScrollView.frame.size.height)
    {
        scrollOffset.y = m_pSearchMenuScrollView.contentSize.height - m_pSearchMenuScrollView.frame.size.height;
    }
}

- (void)searchMenuScrollDown
{
    CGPoint searchResultListScrollOffset = m_pSearchMenuScrollView.contentOffset;
    searchResultListScrollOffset.y += m_scrollSpeed;

    [self clampScrollOffsetY:searchResultListScrollOffset];

    [UIView animateWithDuration:0.15
                          delay:0
                        options:UIViewAnimationCurveLinear
                     animations:^ {
        m_pSearchMenuScrollView.contentOffset = searchResultListScrollOffset;
    } completion:nil];
}

- (void)searchMenuScrollStart
{
    CGPoint searchResultListScrollOffset = m_pSearchMenuScrollView.contentOffset;
    searchResultListScrollOffset.y += m_scrollSpeed;
    
    [self clampScrollOffsetY:searchResultListScrollOffset];
    
    [UIView animateWithDuration:0.15
                          delay:0
                        options:UIViewAnimationCurveLinear
                     animations:^ {
                         m_pSearchMenuScrollView.contentOffset = searchResultListScrollOffset;
                     } completion:nil];
    
    searchMenuScrollUpdateTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(searchMenuScrollDown) userInfo:nil repeats:YES];
}

- (void)searchMenuScrollStop
{
    [searchMenuScrollUpdateTimer invalidate];
    searchMenuScrollUpdateTimer = nil;
}

- (void) textFieldDidChange :(UITextField *)textField
{
    [self updateClearButtonVisibility:textField];
    m_editingText = true;
    
    [m_pDragTab showCloseView: !textField.hasText];
}

@end
