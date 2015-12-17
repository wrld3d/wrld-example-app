// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "MyPinCreationInitiationViewModule.h"
#include "RenderContext.h"
#include "MyPinCreationInitiationView.h"
#include "MyPinCreationInitiationController.h"
#include "MyPinCreationInitiationViewInterop.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationInitiationViewModule::MyPinCreationInitiationViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                                                                 IMyPinCreationInitiationViewModel& viewModel,
                                                                                 IMyPinCreationConfirmationViewModel& confirmationViewModel,
                                                                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                                                 Metrics::IMetricsService& metricsService)
            {
                m_pView = [[MyPinCreationInitiationView alloc]
                           initWithParams:screenProperties.GetScreenWidth() :screenProperties.GetScreenHeight() :screenProperties.GetPixelScale()];


                m_pController = Eegeo_NEW(MyPinCreationInitiationController)(viewModel, *[m_pView getInterop], confirmationViewModel, messageBus, metricsService);
            }

            MyPinCreationInitiationViewModule::~MyPinCreationInitiationViewModule()
            {
                Eegeo_DELETE m_pController;

                [m_pView release];
            }

            MyPinCreationInitiationController& MyPinCreationInitiationViewModule::GetMyPinCreationInitiationController() const
            {
                return *m_pController;
            }

            MyPinCreationInitiationView& MyPinCreationInitiationViewModule::GetMyPinCreationInitiationView() const
            {
                return *m_pView;
            }
        }
    }
}
