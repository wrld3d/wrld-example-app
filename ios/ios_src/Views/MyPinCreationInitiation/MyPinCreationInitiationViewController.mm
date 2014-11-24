// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "MyPinCreationInitiationViewController.h"
#include "MyPinCreationInitiationView.h"
#include "MyPinCreationInitiationViewModel.h"
#include "MyPinCreationInitiationViewControllerInterop.h"
#include "ScreenProperties.h"
#include "MyPinCreationViewStateChangedMessage.h"
#include "IMyPinCreationConfirmationViewModel.h"

@implementation MyPinCreationInitiationViewController

- (id)initWithParams:(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus*) pUiToNativeMessageBus
                    :(ExampleApp::MyPinCreation::IMyPinCreationInitiationViewModel*)pViewModel
                    :(ExampleApp::MyPinCreation::IMyPinCreationConfirmationViewModel*) pConfirmationViewModel
                    :(const Eegeo::Rendering::ScreenProperties*)pScreenProperties;

{
    if(self = [super init])
    {
        self.pMyPinCreationInitiationView = [[[MyPinCreationInitiationView alloc] initWithParams :self
                                                                                     :pScreenProperties->GetScreenWidth()
                                                                                     :pScreenProperties->GetScreenHeight()
                                                                                     :pScreenProperties->GetPixelScale()] autorelease];
        
        m_pUiToNativeMessageBus = pUiToNativeMessageBus;
        m_pViewModel = pViewModel;
        m_pConfirmationViewModel = pConfirmationViewModel;
        m_pInterop = Eegeo_NEW(ExampleApp::MyPinCreation::MyPinCreationInitiationViewControllerInterop)(self, *m_pViewModel);

        [self.pMyPinCreationInitiationView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
        
    }
    
    return self;
}

- (void)dealloc
{
    [self.pMyPinCreationInitiationView release];
    
    Eegeo_DELETE m_pInterop;
    [super dealloc];
}

- (void) handleScreenStateChanged:(float)onScreenState
{

    [self.pMyPinCreationInitiationView shouldOffsetButton: m_pViewModel->ShouldOffsetViewButton()];
    
    if(m_pViewModel->IsFullyOffScreen())
    {
        [self.pMyPinCreationInitiationView setFullyOffScreen];
    }
    else if(m_pViewModel->IsFullyOnScreen())
    {
        [self.pMyPinCreationInitiationView setFullyOnScreen];
    }
    else
    {
        [self.pMyPinCreationInitiationView setOnScreenStateToIntermediateValue:m_pViewModel->OnScreenState()];
    }
}

- (void) setSelected:(BOOL)selected
{
    if(m_pConfirmationViewModel->TryOpen())
    {
        ExampleApp::MyPinCreation::MyPinCreationViewStateChangedMessage message(ExampleApp::MyPinCreation::Ring);
        m_pUiToNativeMessageBus->Publish(message);
    }
}


@end
