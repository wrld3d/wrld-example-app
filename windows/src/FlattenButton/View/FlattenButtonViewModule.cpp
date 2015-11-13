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
                Metrics::IMetricsService& metricsService,
                const AppModes::SdkModel::IAppModeModel& appModeModel
            )
            {
                m_pView = Eegeo_NEW(FlattenButtonView)(nativeState);

                m_pController = Eegeo_NEW(FlattenButtonController)(
                                    viewModel,
                                    *m_pView,
                                    messageBus,
                                    metricsService);
            }

            void FlattenButtonViewModule::AnimateOffScreen()
            {
                m_pView->SetFullyOffScreen();
            }

            void FlattenButtonViewModule::AnimateOnScreen()
            {
                m_pView->SetFullyOnScreen();
            }

            FlattenButtonViewModule::~FlattenButtonViewModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pView;
            }
        }
    }
}
