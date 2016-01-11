// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuInputDelegate.h"

#include "SearchMenuViewInterop.h"
#include "UIColors.h"

@interface SearchMenuInputDelegate()
{
    UITextField* m_pTextField;
    UIButton* m_pClearButton;
    ExampleApp::SearchMenu::View::SearchMenuViewInterop* m_pInterop;
    
    BOOL m_keyboardActive;
    BOOL m_returnPressed;
    BOOL m_currentSearchIsCategory;
    
    UITapGestureRecognizer* m_clearButtonTapGestureRecogniser;
}

@end

@implementation SearchMenuInputDelegate

- (id)initWithTextField:(UITextField*)textField
            clearButton:(UIButton*)clearButton
                interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop
{
    m_pTextField = textField;
    m_pClearButton = clearButton;
    m_pInterop = interop;
    
    m_pTextField.delegate = self;
    
    m_clearButtonTapGestureRecogniser = [[[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(clearSearch)] autorelease];
    [m_pClearButton addGestureRecognizer: m_clearButtonTapGestureRecogniser];
    
    m_pClearButton.hidden = m_pTextField.text.length == 0;
    
    m_keyboardActive = false;
    m_returnPressed = false;
    m_currentSearchIsCategory = false;
    
    [[NSNotificationCenter defaultCenter]addObserver:self
                                            selector:@selector(keyboardDidChangeFrame:)
                                                name:UIKeyboardDidChangeFrameNotification
                                              object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(textFieldTextDidChange:)
                                                 name:UITextFieldTextDidChangeNotification
                                               object:m_pTextField];
    
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
    
    [m_clearButtonTapGestureRecogniser release];
    
    m_pTextField.delegate = nil;
    
    [super dealloc];
}

- (void) enableEdit
{
    [m_pClearButton setEnabled:YES];
    [m_pTextField setEnabled:YES];
    m_pTextField.textColor = ExampleApp::Helpers::ColorPalette::TextFieldEnabledColor;
}

- (void) disableEdit
{
    [m_pClearButton setEnabled:NO];
    [m_pTextField setEnabled:NO];
    m_pTextField.textColor = ExampleApp::Helpers::ColorPalette::TextFieldDisabledColor;
}

- (void) removeSeachKeyboard
{
    [m_pTextField resignFirstResponder];
}

- (void) setEditText :(NSString*)searchText
                     :(bool)isCategory
{
    [m_pTextField setText:searchText];
    
    m_currentSearchIsCategory = isCategory;
    
    [self updateClearButtonVisibility];
}

- (void) clearSearch
{
    m_pInterop->OnSearchCleared();
    
    m_pTextField.text = @"";
    
    [self updateClearButtonVisibility];
}

- (void)updateClearButtonVisibility
{
    m_pClearButton.hidden = m_pTextField.text.length == 0;
}

- (void)textFieldTextDidChange:(NSNotification*)aNotification
{
    if(aNotification.object != m_pTextField)
    {
        return;
    }
    
    [self updateClearButtonVisibility];
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
    
    if(m_currentSearchIsCategory)
    {
        [textField setText:@""];
        m_currentSearchIsCategory = false;
        
        [self updateClearButtonVisibility];
    }
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
        return;
    }
    
    std::string searchString = [textField.text UTF8String];
    m_pInterop->SearchPerformed(searchString);
}

- (BOOL)textFieldShouldClear:(UITextField *)textField
{
    m_pInterop->OnSearchCleared();
    
    textField.text = @"";
    
    [self updateClearButtonVisibility];
    return NO;
}

@end