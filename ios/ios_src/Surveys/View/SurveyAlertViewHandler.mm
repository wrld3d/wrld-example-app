// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyAlertViewHandler.h"

#include "CallbackCollection.h"

@interface SurveyAlertViewHandler()
{
    Eegeo::Helpers::CallbackCollection0* m_pOnAcceptCallbacks;
    Eegeo::Helpers::CallbackCollection0* m_pOnRejectCallbacks;
}

@end

@implementation SurveyAlertViewHandler

- (id)initWithCallbacks:(Eegeo::Helpers::ICallback0&)acceptCallback
                       :(Eegeo::Helpers::ICallback0&)rejectCallback
{
    [super init];
    
    m_pOnAcceptCallbacks = Eegeo_NEW(Eegeo::Helpers::CallbackCollection0)();
    m_pOnRejectCallbacks = Eegeo_NEW(Eegeo::Helpers::CallbackCollection0)();
    
    m_pOnAcceptCallbacks->AddCallback(acceptCallback);
    m_pOnRejectCallbacks->AddCallback(rejectCallback);
    
    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_pOnRejectCallbacks;
    
    Eegeo_DELETE m_pOnAcceptCallbacks;
    
    [super dealloc];
}

- (void)showAlert
{
    NSString* alertTitle = @"Want to help us improve our map?";
    NSString* alertMessage = @"Just a few quick questions - honest!";
    NSString* acceptMessage = @"Yes";
    NSString* rejectMessage = @"No";
    
    if([UIAlertController class])
    {
        UIAlertController* alert = [UIAlertController alertControllerWithTitle:alertTitle
                                                                       message:alertMessage
                                                                preferredStyle:UIAlertControllerStyleAlert];
        
        UIAlertAction* acceptAction = [UIAlertAction actionWithTitle:acceptMessage
                                                               style:UIAlertActionStyleDefault
                                                             handler:^(UIAlertAction * action){ m_pOnAcceptCallbacks->ExecuteCallbacks(); }];
        
        UIAlertAction* rejectAction = [UIAlertAction actionWithTitle:rejectMessage
                                                               style:UIAlertActionStyleCancel
                                                             handler:^(UIAlertAction * action) { m_pOnRejectCallbacks->ExecuteCallbacks(); }];
        
        [alert addAction:acceptAction];
        [alert addAction:rejectAction];
        
        UIWindow *window = [[UIApplication sharedApplication] keyWindow];
        UIViewController *viewController = window.rootViewController;
        [viewController presentViewController:alert animated:YES completion:nil];
    }
    else
    {
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:alertTitle
                                                        message:alertMessage
                                                       delegate:self
                                              cancelButtonTitle:rejectMessage
                                              otherButtonTitles:acceptMessage, nil];
        
        [alert show];
        [alert release];
    }
}

- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    alertView.delegate = nil;
    
    if(buttonIndex == 0)
    {
        m_pOnAcceptCallbacks->ExecuteCallbacks();
    }
    else
    {
        m_pOnRejectCallbacks->ExecuteCallbacks();
    }
}

@end