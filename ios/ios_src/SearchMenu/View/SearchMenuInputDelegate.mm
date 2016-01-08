// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuInputDelegate.h"

#include "SearchMenuViewInterop.h"
#include "UIColors.h"

@interface SearchMenuInputDelegate()
{
    UITextField* m_pTextField;
    ExampleApp::SearchMenu::View::SearchMenuViewInterop* m_pInterop;
    
    BOOL m_keyboardActive;
    BOOL m_returnPressed;
    BOOL m_currentSearchIsCategory;
}

@end

@implementation SearchMenuInputDelegate

- (id)initWithTextField:(UITextField*)textField
                interop:(ExampleApp::SearchMenu::View::SearchMenuViewInterop*)interop
{
    m_pTextField = textField;
    m_pInterop = interop;
    
    m_pTextField.delegate = self;
    
    m_keyboardActive = false;
    m_returnPressed = false;
    m_currentSearchIsCategory = false;
    
    [[NSNotificationCenter defaultCenter]addObserver:self
                                            selector:@selector(keyboardDidChangeFrame:)
                                                name:UIKeyboardDidChangeFrameNotification
                                              object:nil];
    
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter]removeObserver:self
                                                   name:UIKeyboardDidChangeFrameNotification
                                                 object:nil];
    
    m_pTextField.delegate = nil;
    
    [super dealloc];
}

- (void) enableEdit
{
    [m_pTextField setEnabled:YES];
    m_pTextField.textColor = [UIColor blackColor];
}

- (void) disableEdit
{
    [m_pTextField setEnabled:NO];
    m_pTextField.textColor = [UIColor lightGrayColor];
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
    return NO;
}

@end