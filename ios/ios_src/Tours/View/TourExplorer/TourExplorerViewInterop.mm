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
                TourExplorerViewInterop::TourExplorerViewInterop(TourExplorerView* pView)
                : m_pView(pView)
                , m_tourModel(SdkModel::TourModel::Empty())
                , m_initialCard(-1)
                {
                }
                
                void TourExplorerViewInterop::SetCurrentTour(const SdkModel::TourModel& tourModel)
                {
                    m_tourModel = tourModel;
                }
                
                void TourExplorerViewInterop::SetInitialCard(const int initialCard)
                {
                    m_initialCard = initialCard;
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
                
                void TourExplorerViewInterop::OnDismissed()
                {
                    m_dismissedCallbacks.ExecuteCallbacks();
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
                    [m_pView configureViewForTour:m_tourModel :m_initialCard];
                    [m_pView setFullyOnScreen];
                }
                
                void TourExplorerViewInterop::SetOnScreenStateToIntermediateValue(float value)
                {
                    [m_pView setOnScreenStateToIntermediateValue: value];
                }
            }
        }
    }
}