#pragma once

#include <string>
#import <UIKit/UIKit.h>
#include "NavWidgetViewIncludes.h"
#include "WrldNav/WrldNav.h"
#include "WrldNavWidget/WrldNavWidget.h"
#include "NavRoutingRerouteDialog/NavRoutingRerouteDialog.h"
#include "NavRoutingCalculatingRoute/NavRoutingCalculatingRoute.h"
#include "IAppModeModel.h"
#include "INavWidgetView.h"
#include "INavWidgetViewModel.h"
#include "ICompassView.h"


namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            class NavWidgetView : public WRLDNSObjectObserverCpp, public INavWidgetView
            {
                
            private:
                
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClickedCallback;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClearButtonClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClearButtonClickedCallback;
                Eegeo::Helpers::CallbackCollection0 m_startEndLocationsSwappedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startEndRoutingButtonClickedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_selectedDirectionIndexChangedCallback;
                Eegeo::Helpers::CallbackCollection1<const bool> m_rerouteDialogClosedCallbacks;
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& m_topPanelVisibleHeightChangedCallbacks;
                Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& m_bottomPanelVisibleHeightChangedCallbacks;
                
                Eegeo::Helpers::TCallback1<NavWidgetView, const bool> m_rerouteDialogOptionSelectedCallback;
                
                WRLDNavWidgetBase* m_pView;
                WRLDNavModel* m_pNavModel;
                NavRoutingRerouteDialog* m_pRerouteDialog;
                NavRoutingCalculatingRoute* m_pCalculatingRoute;
                bool m_isVisible;
                
                void SetLocation(const SdkModel::NavRoutingLocationModel& locationModel, bool isStartLocation);
                void OnRerouteDialogOptionSelected(const bool& shouldReroute);
                
                WRLDNavRoute* BuildWRLDNavRouteFromNavRoutingRouteModel(const SdkModel::NavRoutingRouteModel& routeModel);
                WRLDNavDirection* BuildWlrdNavDirectionFromFromNavRoutingDirectionModel(const SdkModel::NavRoutingDirectionModel& directionModel );
                NSString* BuildNSStringFromString(const std::string& string);
                
                Eegeo::Helpers::CallbackCollection1<const int> m_navigationStartPointFromResultCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_navigationEndPointFromResultCallbacks;
                Eegeo::Helpers::CallbackCollection2<const bool, const bool> m_navigationSearchForLocationChangedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const bool> m_locationSetCallbacks;
                
            public:
                NavWidgetView(WRLDNavModel* m_pNavModel,
                              Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& topPanelVisibleHeightChangedCallbacks,
                              Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& bottomPanelVisibleHeightChangedCallbacks);
                
                ~NavWidgetView();
                
                UIView* GetUIView();
                
                void changeReceived(const std::string& keyPath) override;
                
                void Show() override;
                
                void Hide() override;
                
                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;
                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;
                
                void ClearStartLocation() override;
                void ClearEndLocation() override;
                
                void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel,  bool isNewRoute) override;
                
                void ClearRoute() override;
                
                void SetCurrentDirection(int directionIndex) override;
                void UpdateCurrentDirection(const SdkModel::NavRoutingDirectionModel& directionModel) override;
                void SetSelectedDirection(int directionIndex) override;

                void SetRemainingRouteDuration(double seconds) override;
                
                void SetNavMode(SdkModel::NavRoutingMode mode) override;
                
                void ShowRerouteDialog(const std::string message) override;
                
                void ShowCalculatingRouteSpinner() override;
                void HideCalculatingRouteSpinner() override;
                
                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void HandleClosedCallback();
                
                void InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void HandleStartLocationClickedCallback();
                
                void InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void HandleEndLocationClickedCallback();
                
                void InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void HandleStartLocationClearButtonClickedCallback();
                
                void InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) override;
                void RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) override;
                void HandleEndLocationClearButtonCallback();
                
                void InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void HandleStartEndLocationsSwappedCallback();
                
                void InsertStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void RemoveStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;
                void HandleStartEndRoutingButtonClickedCallback();
                
                void InsertSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) override;
                void RemoveSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) override;
                void HandleSelectedDirectionIndexChangedCallback(int selectedDirection);
                
                void InsertRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback) override;
                void RemoveRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback) override;
                void HandleRerouteDialogClosed(bool shouldReroute) ;
                
                void SetStartPointFromResultIndex(int index) override;
                void SetEndPointFromResultIndex(int index) override;
                void SetSearchingForLocation(bool isSearching, bool forStartLocation);
                
                void InsertOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;
                void RemoveOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;
                
                void InsertOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;
                void RemoveOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;
                
                void InsertOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback) override;
                void RemoveOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback) override;
                
                void InsertLocationSetCallback(Eegeo::Helpers::ICallback1<const bool>& callback);
                void RemoveLocationSetCallback(Eegeo::Helpers::ICallback1<const bool>& callback);
                
                THeight GetTopViewHeight() override;
                THeight GetBottomViewHeight() override;
            };
        }
    }
}
