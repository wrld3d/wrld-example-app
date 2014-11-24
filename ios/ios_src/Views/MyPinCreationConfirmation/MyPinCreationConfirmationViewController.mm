// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "MyPinCreationConfirmationViewController.h"
#include "MyPinCreationConfirmationView.h"
#include "MyPinCreationConfirmationViewModel.h"
#include "MyPinCreationConfirmationViewControllerInterop.h"
#include "ScreenProperties.h"
#include "IMyPinCreationDetailsViewModel.h"
#include "MyPinCreationViewStateChangedMessage.h"

@implementation MyPinCreationConfirmationViewController

- (id)initWithParams:(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*)pUiToNativeMessageBus
                    :(ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel*)pViewModel
                    :(ExampleApp::MyPinCreation::IMyPinCreationCompositeViewModel*)pCompositeViewModel
                    :(ExampleApp::MyPinCreationDetails::IMyPinCreationDetailsViewModel*)pDetailsViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

{
    if(self = [super init])
    {
        self.pMyPinCreationConfirmationView = [[[MyPinCreationConfirmationView alloc] initWithParams :self
                                                                                                 :pScreenProperties->GetScreenWidth()
                                                                                                 :pScreenProperties->GetScreenHeight()
                                                                                                 :pScreenProperties->GetPixelScale()] autorelease];
        
        m_pUiToNativeMessageBus = pUiToNativeMessageBus;
        m_pViewModel = pViewModel;
        m_pDetailsViewModel = pDetailsViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::MyPinCreation::MyPinCreationConfirmationViewControllerInterop)(self, *m_pViewModel, *pCompositeViewModel);
        
        [self.pMyPinCreationConfirmationView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
        
    }
    
    return self;
}

- (void)dealloc
{
    [self.pMyPinCreationConfirmationView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) handleScreenStateChanged:(float)onScreenState
{
    if(m_pViewModel->IsFullyOffScreen())
    {
        [self.pMyPinCreationConfirmationView setFullyOffScreen];
    }
    else if(m_pViewModel->IsFullyOnScreen())
    {
        [self.pMyPinCreationConfirmationView setFullyOnScreen];
    }
    else
    {
        [self.pMyPinCreationConfirmationView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
    }
}

- (void) handleCloseButtonSelected
{
    m_pViewModel->Close();
    m_pUiToNativeMessageBus->Publish(ExampleApp::MyPinCreation::MyPinCreationViewStateChangedMessage(ExampleApp::MyPinCreation::Inactive));
}

- (void) handleConfirmButtonSelected
{
    m_pViewModel->Close();
    m_pUiToNativeMessageBus->Publish(ExampleApp::MyPinCreation::MyPinCreationViewStateChangedMessage(ExampleApp::MyPinCreation::Details));
    m_pViewModel->RemoveFromScreen();
    m_pDetailsViewModel->Open();
}

@end
