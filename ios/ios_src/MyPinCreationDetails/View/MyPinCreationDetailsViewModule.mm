// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinCreationDetailsController.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsViewModule::MyPinCreationDetailsViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                    IMyPinCreationDetailsViewModel& myPinCreationDetailsViewModel,
                    const Eegeo::Rendering::ScreenProperties& screenProperties,
                    Eegeo::Web::IConnectivityService& connectivityService)
            {
                m_pView = [[MyPinCreationDetailsView alloc] initWithParams:screenProperties.GetScreenWidth() :screenProperties.GetScreenHeight()];

                m_pController = Eegeo_NEW(MyPinCreationDetailsController)(*[m_pView getInterop], myPinCreationDetailsViewModel, connectivityService, messageBus);
            }

            MyPinCreationDetailsViewModule::~MyPinCreationDetailsViewModule()
            {
                Eegeo_DELETE m_pController;

                [m_pView release];
            }

            MyPinCreationDetailsController& MyPinCreationDetailsViewModule::GetMyPinCreationDetailsController() const
            {
                return *m_pController;
            }

            MyPinCreationDetailsView& MyPinCreationDetailsViewModule::GetMyPinCreationDetailsView() const
            {
                return *m_pView;
            }
        }
    }
}
