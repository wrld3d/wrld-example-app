// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsViewController.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        MyPinCreationDetailsViewModule::MyPinCreationDetailsViewModule(ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus,
                                                                       IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                                                                       Eegeo::Web::IConnectivityService& connectivityService,
                                                                       UIViewController* rootViewController)
        {
            m_pController = [[MyPinCreationDetailsViewController alloc] initWithParams:&uiToNativeMessageBus
                                                                                      :&myPinCreationDetailsViewModel
                                                                                      :&connectivityService];
            
            [rootViewController addChildViewController: m_pController];
        }
        
        MyPinCreationDetailsViewModule::~MyPinCreationDetailsViewModule()
        {
            [m_pController removeFromParentViewController];
            [m_pController release];
        }
        
        MyPinCreationDetailsViewController& MyPinCreationDetailsViewModule::GetMyPinCreationDetailsViewController() const
        {
            return *m_pController;
        }
        
        MyPinCreationDetailsView& MyPinCreationDetailsViewModule::GetMyPinCreationDetailsView() const
        {
            return *[m_pController pMyPinCreationDetailsView];
        }
    }
}