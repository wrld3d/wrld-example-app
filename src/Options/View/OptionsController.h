// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Options.h"
#include "ICallback.h"
#include "IOptionsViewModel.h"
#include "IOptionsView.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsController : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<IOptionsView> m_view;
                const std::shared_ptr<IOptionsViewModel> m_viewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelOpened;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelClosed;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelCacheClearCeremonyCompleted;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewCloseSelected;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewStreamOverWifiOnlySelectionChanged;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewCacheEnabledSelectionChanged;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewClearCacheSelected;

                void OnViewModelOpened();

                void OnViewModelClosed();

                void OnViewModelCacheClearCeremonyCompleted();

                void OnViewCloseSelected();
                
                void OnViewStreamOverWifiOnlySelectionChanged();
                
                void OnViewCacheEnabledSelectionChanged();
                
                void OnViewClearCacheSelected();
            public:
                OptionsController(const std::shared_ptr<IOptionsView>& view,
                                  const std::shared_ptr<IOptionsViewModel>& viewModel,
                                  const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~OptionsController();
            };
        }
    }
}
