// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewModule.h"
#include "MyPinCreationConfirmationView.h"
#include "MyPinCreationConfirmationController.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace View
        {
            MyPinCreationViewModule::MyPinCreationViewModule(
                AndroidNativeState& nativeState,
                IMyPinCreationInitiationViewModel& initiationViewModel,
                IMyPinCreationConfirmationViewModel& confirmationViewModel,
                MyPinCreationDetails::View::IMyPinCreationDetailsViewModel& detailsViewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
            {
                m_pConfirmationView = Eegeo_NEW(MyPinCreationConfirmationView)(nativeState);
                m_pConfirmationController = Eegeo_NEW(MyPinCreationConfirmationController)(confirmationViewModel, *m_pConfirmationView, detailsViewModel, messageBus, metricsService);
            }

            MyPinCreationViewModule::~MyPinCreationViewModule()
            {
                Eegeo_DELETE m_pConfirmationController;
                Eegeo_DELETE m_pConfirmationView;
            }
        }
    }
}
