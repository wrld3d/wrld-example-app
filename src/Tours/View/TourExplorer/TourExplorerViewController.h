// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "ICallback.h"
#include "IScreenControlViewModel.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "ITourHovercardView.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class TourExplorerViewController: private Eegeo::NonCopyable
                {
                public:
                    
                    TourExplorerViewController(ITourExplorerViewModel& viewModel,
                                               ITourExplorerCompositeViewController& tourExplorerCompositeViewController,
                                               ITourExplorerView& view,
                                               TourHovercard::ITourHovercardView& hovercardView,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               Metrics::IMetricsService& metricsService);
                    
                    ~TourExplorerViewController();
                    
                private:
                    
                    void OnDismissed();
                    void OnStateChanged(int& activeStateIndex);
                    void OnTourChangeRequested(std::string& tourName);
                    void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);
                    void OnCurrentTourCardTapped();
                    
                    ITourExplorerViewModel& m_viewModel;
                    ITourExplorerCompositeViewController& m_tourExplorerCompositeViewController;
                    ITourExplorerView& m_view;
                    TourHovercard::ITourHovercardView& m_hovercardView;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    Eegeo::Helpers::TCallback2<TourExplorerViewController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                    Eegeo::Helpers::TCallback0<TourExplorerViewController> m_dismissedCallback;
                    Eegeo::Helpers::TCallback1<TourExplorerViewController, int> m_stateChangedCallback;
                    Eegeo::Helpers::TCallback1<TourExplorerViewController, std::string> m_tourChangeRequestCallback;
                    Eegeo::Helpers::TCallback0<TourExplorerViewController> m_currentTourCardTappedCallback;
                    
                    Metrics::IMetricsService& m_metricsService;
                };
            }
        }
    }
}
