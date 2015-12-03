// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourExplorerViewInterop.h"
#include "TourExplorerView.h"
#include "TourWebView.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                TourExplorerViewInterop::TourExplorerViewInterop(TourExplorerView* pView,
                                                                 URLRequest::View::URLRequestHandler& urlRequestHandler)
                : m_pView(pView)
                , m_urlRequestHandler(urlRequestHandler)
                , m_tourModel(SdkModel::TourModel::Empty())
                {
                }
                
                void TourExplorerViewInterop::SetCurrentTour(const SdkModel::TourModel& tourModel, int initialCard, bool showBackButton)
                {
                    m_tourModel = tourModel;
                    [m_pView configureViewForTour:m_tourModel :initialCard :showBackButton];
                }
                
                const SdkModel::TourModel& TourExplorerViewInterop::GetCurrentTour()
                {
                    return m_tourModel;
                }

                
                void TourExplorerViewInterop::OnStateSelected(int activeStateIndex)
                {
                    m_stateChangedCallbacks.ExecuteCallbacks(activeStateIndex);
                }
                
                void TourExplorerViewInterop::OnChangeTourRequested(const std::string& name)
                {
                    std::string requestedTourName = name;
                    m_changeTourCallbacks.ExecuteCallbacks(requestedTourName);
                }
                
                void TourExplorerViewInterop::ShowExternalURL(const std::string &url)
                {
                    m_urlRequestHandler.RequestExternalURL(url);
                }
                
                void TourExplorerViewInterop::ShowDeeplinkURL(const std::string& deeplinkUrl, const std::string& httpFallbackUrl)
                {
                    m_urlRequestHandler.RequestDeeplinkURL(deeplinkUrl, httpFallbackUrl);
                }
                
                bool TourExplorerViewInterop::CanHandleDeeplinkURL(const std::string& deeplinkUrl)
                {
                    return m_urlRequestHandler.CanHandleDeeplinkURL(deeplinkUrl);
                }
                
                void TourExplorerViewInterop::OnDismissed()
                {
                    m_tourModel = SdkModel::TourModel::Empty();
                    m_dismissedCallbacks.ExecuteCallbacks();
                }
                
                void TourExplorerViewInterop::OnExited()
                {
                    m_tourModel = SdkModel::TourModel::Empty();
                    m_exitedCallbacks.ExecuteCallbacks();
                }
                
                void TourExplorerViewInterop::InsertStateChangedCallback(Eegeo::Helpers::ICallback1<int> &callback)
                {
                    m_stateChangedCallbacks.AddCallback(callback);
                }
                
                void TourExplorerViewInterop::RemoveStateChangedCallback(Eegeo::Helpers::ICallback1<int> &callback)
                {
                    m_stateChangedCallbacks.RemoveCallback(callback);
                }
                
                void TourExplorerViewInterop::InsertDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_dismissedCallbacks.AddCallback(callback);
                }
                
                void TourExplorerViewInterop::RemoveDismissedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_dismissedCallbacks.RemoveCallback(callback);
                }
                
                void TourExplorerViewInterop::InsertExitedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_exitedCallbacks.AddCallback(callback);
                }
                
                void TourExplorerViewInterop::RemoveExitedCallback(Eegeo::Helpers::ICallback0 &callback)
                {
                    m_exitedCallbacks.RemoveCallback(callback);
                }
                
                void TourExplorerViewInterop::InsertChangeTourRequestCallback(Eegeo::Helpers::ICallback1<std::string>& callback)
                {
                    m_changeTourCallbacks.AddCallback(callback);
                }
                
                void TourExplorerViewInterop::RemoveChangeTourRequestCallback(Eegeo::Helpers::ICallback1<std::string>& callback)
                {
                    m_changeTourCallbacks.RemoveCallback(callback);
                }
                
                void TourExplorerViewInterop::SetFullyOffScreen()
                {
                    [m_pView setFullyOffScreen];
                }
                
                void TourExplorerViewInterop::SetFullyOnScreen()
                {
                    [m_pView setFullyOnScreen];
                }
                
                void TourExplorerViewInterop::SetOnScreenStateToIntermediateValue(float value)
                {
                    [m_pView setOnScreenStateToIntermediateValue: value];
                }
                
                void TourExplorerViewInterop::OnCurrentTourCardTapped()
                {
                    m_currentTourCardTappedCallbacks.ExecuteCallbacks();
                }
                
                void TourExplorerViewInterop::InsertCurrentTourCardTappedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_currentTourCardTappedCallbacks.AddCallback(callback);
                }
                
                void TourExplorerViewInterop::RemoveCurrentTourCardTappedCallback(Eegeo::Helpers::ICallback0& callback)
                {
                    m_currentTourCardTappedCallbacks.RemoveCallback(callback);
                }
            }
        }
    }
}