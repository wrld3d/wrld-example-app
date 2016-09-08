// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AboutPage.h"
#include "ICallback.h"
#include "IAboutPageViewModel.h"
#include "IAboutPageView.h"
#include "IMetricsService.h"

namespace ExampleApp
{
    namespace AboutPage
    {
        namespace View
        {
            class AboutPageController : private Eegeo::NonCopyable
            {
            private:
                const std::shared_ptr<IAboutPageView> m_view;
                const std::shared_ptr<IAboutPageViewModel> m_viewModel;

                Eegeo::Helpers::TCallback0<AboutPageController> m_viewOpened;
                Eegeo::Helpers::TCallback0<AboutPageController> m_viewClosed;
                Eegeo::Helpers::TCallback0<AboutPageController> m_viewCloseTapped;
                
                const std::shared_ptr<Metrics::IMetricsService> m_metricsService;

                void OnOpen();

                void OnClose();

                void OnCloseTapped();
            public:
                AboutPageController(const std::shared_ptr<IAboutPageView>& view,
                                    const std::shared_ptr<IAboutPageViewModel>& viewModel,
                                    const std::shared_ptr<Metrics::IMetricsService>& metricsService);

                ~AboutPageController();
            };
        }
    }
}
