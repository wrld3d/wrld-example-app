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
                                                                           Metrics::IMetricsService& metricsService,
                                                                           UIViewController* rootViewController)
            {
                m_pView = [[MyPinCreationDetailsView alloc] initWithParams: screenProperties.GetScreenWidth()
                                                                          : screenProperties.GetScreenHeight()
                                                                          : rootViewController];

                m_pController = Eegeo_NEW(MyPinCreationDetailsController)(*[m_pView getInterop], myPinCreationDetailsViewModel, messageBus, metricsService);
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
