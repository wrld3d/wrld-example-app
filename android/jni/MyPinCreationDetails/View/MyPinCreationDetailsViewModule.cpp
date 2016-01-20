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
                AndroidNativeState& nativeState,
                MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& viewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
            {
                m_pView = Eegeo_NEW(MyPinCreationDetailsView)(nativeState);

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
