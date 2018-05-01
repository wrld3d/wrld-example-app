// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "MyPinCreationConfirmationViewModule.h"
#include "RenderContext.h"
#include "MyPinCreationConfirmationView.h"
#include "MyPinCreationConfirmationController.h"
#include "MyPinCreationConfirmationViewInterop.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationConfirmationViewModule::MyPinCreationConfirmationViewModule(
                ExampleApp::ExampleAppMessaging::TMessageBus& messageBus,
                IMyPinCreationConfirmationViewModel& viewModel,
                IMyPinCreationCompositeViewModel& compositeViewModel,
                MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& detailsViewModel,
                const Eegeo::Rendering::ScreenProperties& screenProperties,
                Metrics::IMetricsService& metricsService)
            {
                m_pView = [[MyPinCreationConfirmationView alloc] initWithParams: screenProperties.GetScreenWidth(): screenProperties.GetScreenHeight(): screenProperties.GetPixelScale()];

                m_pController = Eegeo_NEW(MyPinCreationConfirmationController)(viewModel, *[m_pView getInterop], detailsViewModel, messageBus, metricsService);
            }

            MyPinCreationConfirmationViewModule::~MyPinCreationConfirmationViewModule()
            {
                Eegeo_DELETE m_pController;

                [m_pView release];
            }

            MyPinCreationConfirmationController& MyPinCreationConfirmationViewModule::GetMyPinCreationConfirmationController() const
            {
                return *m_pController;
            }

            MyPinCreationConfirmationView& MyPinCreationConfirmationViewModule::GetMyPinCreationConfirmationView() const
            {
                return *m_pView;
            }
        }
    }
}
