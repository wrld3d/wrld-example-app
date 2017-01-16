// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationDetailsViewModule.h"
#include "MyPinCreationDetailsView.h"
#include "MyPinCreationDetailsController.h"

namespace ExampleApp
{
    namespace MyPinCreationDetails
    {
        namespace View
        {
            MyPinCreationDetailsViewModule::MyPinCreationDetailsViewModule(
                WindowsNativeState& nativeState,
                MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& viewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService,
                bool isInKioskMode
            )
            {
                m_pView = Eegeo_NEW(MyPinCreationDetailsView)(nativeState, messageBus, isInKioskMode);

                m_pController = Eegeo_NEW(MyPinCreationDetailsController)(*m_pView,
                                viewModel,
                                messageBus,
                                metricsService
                                                                         );
            }

            MyPinCreationDetailsViewModule::~MyPinCreationDetailsViewModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }
        }
    }
}
