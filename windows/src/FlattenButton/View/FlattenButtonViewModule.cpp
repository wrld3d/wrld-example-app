// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlattenButtonViewModule.h"
#include "WindowsAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace View
        {
            FlattenButtonViewModule::FlattenButtonViewModule(
                WindowsNativeState& nativeState,
                IFlattenButtonViewModel& viewModel,
                ExampleAppMessaging::TMessageBus& messageBus,
                Metrics::IMetricsService& metricsService
            )
            {
                m_pView = Eegeo_NEW(FlattenButtonView)(nativeState);

                m_pController = Eegeo_NEW(FlattenButtonController)(
                                    viewModel,
                                    *m_pView,
                                    messageBus,
                                    metricsService);
            }

            FlattenButtonViewModule::~FlattenButtonViewModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }
        }
    }
}
