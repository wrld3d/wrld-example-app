// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#import "MyPinCreationConfirmationViewModule.h"
#include "RenderContext.h"
#include "MyPinCreationConfirmationView.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        MyPinCreationConfirmationViewModule::MyPinCreationConfirmationViewModule(ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                                                                 IMyPinCreationConfirmationViewModel& viewModel,
                                                                                 IMyPinCreationCompositeViewModel& compositeViewModel,
                                                                                 MyPinCreationDetails::IMyPinCreationDetailsViewModel& MyPinCreationDetailsViewModel,
                                                                                 const Eegeo::Rendering::ScreenProperties& screenProperties)
        {
            m_pController = [[MyPinCreationConfirmationViewController alloc] initWithParams:&uiToNativeMessageBus
                                                                                           :&viewModel
                                                                                           :&compositeViewModel
                                                                                           :&MyPinCreationDetailsViewModel
                                                                                           :&screenProperties];
        }
        
        MyPinCreationConfirmationViewModule::~MyPinCreationConfirmationViewModule()
        {
            [m_pController release];
        }
        
        MyPinCreationConfirmationViewController& MyPinCreationConfirmationViewModule::GetMyPinCreationConfirmationViewController() const
        {
            return *m_pController;
        }
        
        MyPinCreationConfirmationView& MyPinCreationConfirmationViewModule::GetMyPinCreationConfirmationView() const
        {
            return *[m_pController pMyPinCreationConfirmationView];
        }
    }
}
