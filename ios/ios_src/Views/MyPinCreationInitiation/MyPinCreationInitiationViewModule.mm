// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "MyPinCreationInitiationViewModule.h"
#include "RenderContext.h"
#include "MyPinCreationInitiationView.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationInitiationViewModule::MyPinCreationInitiationViewModule(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                                                             IMyPinCreationInitiationViewModel& viewModel,
                                                                             const Eegeo::Rendering::ScreenProperties& screenProperties)
        {
            m_pController = [[MyPinCreationInitiationViewController alloc] initWithParams:&uiToNativeMessageBus
                                                                                         :&viewModel
                                                                                         :&screenProperties];
        }
        
        MyPinCreationInitiationViewModule::~MyPinCreationInitiationViewModule()
        {
            [m_pController release];
        }
        
        MyPinCreationInitiationViewController& MyPinCreationInitiationViewModule::GetMyPinCreationInitiationViewController() const
        {
            return *m_pController;
        }
        
        MyPinCreationInitiationView& MyPinCreationInitiationViewModule::GetMyPinCreationInitiationView() const
        {
            return *[m_pController pMyPinCreationInitiationView];
        }
    }
}
