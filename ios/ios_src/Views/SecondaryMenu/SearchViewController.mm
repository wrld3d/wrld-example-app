// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import <UIKit/UIKit.h>
#include <string>
#include "SearchViewController.h"
#include "ISearchQueryPerformer.h"
#include "IMenuViewModel.h"
#include "UIColors.h"
#include "NativeToUiMessageBus.h"

@implementation SearchViewController

- (id)initWithParams:(UITextField*)pTextView
                    :(ExampleApp::Search::ISearchQueryPerformer*) pSearchQueryPerformer
                    :(ExampleApp::ExampleAppMessaging::NativeToUiMessageBus*) pNativeToUiMessageBus
                    :(ExampleApp::Menu::IMenuViewModel*) pMenuViewModel
{
    if(self = [super init])
    {
        self.pTextView = pTextView;
        self.view = pTextView;
        self.pTextView.borderStyle = UITextBorderStyleRoundedRect;
        self.pTextView.returnKeyType = UIReturnKeySearch;
        
        m_returnPressed = false;
        m_keyboardActive = false;
        
        m_pSearchQueryPerformer = pSearchQueryPerformer;
        m_pMenuViewModel = pMenuViewModel;
        
        m_pInterop = Eegeo_NEW(ExampleApp::SecondaryMenu::SearchViewControllerInterop)(self, *pMenuViewModel, *pNativeToUiMessageBus);
        
        [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(keyboardDidChangeFrame:)
         name:UIKeyboardDidChangeFrameNotification
         object:nil];
        
        [self.pTextView setDelegate:self];
    }
    
    return self;
}

- (void)dealloc
{
    [[NSNotificationCenter defaultCenter]
     removeObserver:self
     name:UIKeyboardDidChangeFrameNotification
     object:nil];
    
    Eegeo_DELETE m_pInterop;
    
    [self.pTextView release];
    
    [super dealloc];
}

- (void) enableEdit
{
    [self.pTextView setEnabled:YES];
    self.pTextView.textColor = [UIColor blackColor];
}

- (void) disableEdit
{
    [self.pTextView setEnabled:NO];
    self.pTextView.textColor = [UIColor lightGrayColor];
}

- (void) removeSeachKeyboard
{
	if (m_keyboardActive)
	{
		[self.pTextView resignFirstResponder];
	}
}

- (void)keyboardDidChangeFrame:(NSNotification*)aNotification
{
	if (m_keyboardActive)
	{
		[self.pTextView becomeFirstResponder];
	}
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
	m_keyboardActive = true;
	m_returnPressed = false;
    
    textField.layer.borderColor = ExampleApp::Helpers::ColorPalette::MainHudColor.CGColor;
    textField.layer.borderWidth = 2.0;
    textField.layer.cornerRadius = 10.0;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
	m_returnPressed = true;
	[self.pTextView resignFirstResponder];
	return TRUE;
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
	m_keyboardActive = false;
    
    textField.layer.borderColor = [[UIColor clearColor] CGColor];
    textField.layer.borderWidth = 1.0;
    textField.layer.cornerRadius = 10.0;
    
    if (!m_returnPressed || [self.pTextView.text isEqualToString:@""])
	{
        return;
	}
	
    std::string searchString = [self.pTextView.text UTF8String];
    m_pSearchQueryPerformer->PerformSearchQuery(searchString, false);
    
    m_pMenuViewModel->Close();
}

@end


