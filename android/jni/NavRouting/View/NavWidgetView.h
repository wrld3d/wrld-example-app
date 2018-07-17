// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "AndroidNativeState.h"
#include "CallbackCollection.h"
#include "INavWidgetView.h"
#include "NavRoutingLocationModel.h"
#include "ICompassView.h"
#include "IInteriorsExplorerView.h"
#include "MyTestSearchProvider.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetView : public INavWidgetView, Eegeo::NonCopyable
            {
            private:
                AndroidNativeState& m_nativeState;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClearButtonClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClearButtonClickedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startEndLocationsSwappedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startEndRoutingButtonClicked;
                Eegeo::Helpers::CallbackCollection1<const int> m_selectedDirectionIndexChangedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const bool> m_rerouteDialogClosedCallbacks;

                Eegeo::Helpers::CallbackCollection1<THeight>& m_navWidgetViewTopHeightChangedCallbacks;
                Eegeo::Helpers::CallbackCollection1<THeight>& m_navWidgetViewBottomHeightChangedCallbacks;

                Eegeo::Helpers::CallbackCollection1<const int> m_navigationStartPointFromResultCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_navigationEndPointFromResultCallbacks;
                Eegeo::Helpers::CallbackCollection2<const bool, const bool> m_searchingForLocationCallbacks;

                jclass m_uiViewClass;
                jobject m_uiView;

                int m_topViewHeight;
                int m_bottomViewHeight;

                SearchProviders::MyTestSearchProvider& m_navSearchProvider;

                void AddSuggestionProvider(SearchProviders::MyTestSearchProvider& navSearchProvider);
                void RemoveSuggestionProvider(SearchProviders::MyTestSearchProvider& navSearchProvider);

            public:
                NavWidgetView(AndroidNativeState& nativeState,
                              SearchProviders::MyTestSearchProvider& navSearchProvider,
                              Eegeo::Helpers::CallbackCollection1<THeight>& navWidgetViewTopHeightChangedCallbacks,
                              Eegeo::Helpers::CallbackCollection1<THeight>& navWidgetViewBottomHeightChangedCallbacks);

                ~NavWidgetView();

                void Show() override;

                void Hide() override;

                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;

                void ClearStartLocation() override;

                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;

                void ClearEndLocation() override;

                void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel, bool isNewRoute) override;

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

                void HandleCloseClicked();

                void InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void HandleStartLocationClicked();

                void InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void HandleEndLocationClicked();

                void InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void HandleStartLocationClearButtonClicked();

                void InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) override;

                void RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) override;

                void HandleEndLocationClearButtonClicked();

                void InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void HandleStartEndLocationsSwapped();

                void InsertStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void RemoveStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) override;

                void HandleStartEndRoutingButtonClicked();

                void InsertSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) override;

                void RemoveSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) override;

                void HandleSelectedDirectionIndexChanged(int selectedDirectionIndex);

                void InsertRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback) override;

                void RemoveRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback) override;

                void HandleRerouteDialogClosed(bool shouldReroute);

                void SetTopViewHeight(THeight topViewHeight);

                void SetBottomViewHeight(THeight bottomViewHeight);

                THeight GetTopViewHeight() override;

                THeight GetBottomViewHeight() override;

                void SetStartPointFromResultIndex(int index) override;

                void SetEndPointFromResultIndex(int index) override;

                void SetSearchingForLocation(bool isSearching, bool isStartLocation);

                void InsertOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;

                void RemoveOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;

                void InsertOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;

                void RemoveOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) override;

                void InsertOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback) override;

                void RemoveOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback) override;

            private:
                void SetLocation(const SdkModel::NavRoutingLocationModel& locationModel, bool isStartLocation);

                void CallVoidMethod(const std::string& methodName);

                jclass CreateJavaClass(const std::string& viewClass);

                jobject CreateJavaObject(jclass uiViewClass);

                jobjectArray CreateJavaArray(const std::vector<std::string>& stringVector);
            };
        }
    }
}
