// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "ICallback.h"
#include "NavRouting.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingRouteModel.h"
#include "NavRoutingDirectionModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class INavWidgetView
            {
            public:
                typedef const int THeight;

                virtual ~INavWidgetView() { };

                virtual void Show() = 0;

                virtual void Hide() = 0;

                virtual void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearStartLocation() = 0;

                virtual void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearEndLocation() = 0;

                virtual void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel, bool isNewRoute) = 0;

                virtual void ClearRoute() = 0;

                virtual void SetCurrentDirection(int directionIndex) = 0;

                virtual void UpdateCurrentDirection(const SdkModel::NavRoutingDirectionModel& directionModel) = 0;

                virtual void SetSelectedDirection(int directionIndex) = 0;

                virtual void SetRemainingRouteDuration(double seconds) = 0;

                virtual void SetNavMode(SdkModel::NavRoutingMode mode) = 0;

                virtual void ShowRerouteDialog(const std::string message) = 0;
                
                virtual void ShowCalculatingRouteSpinner() = 0;
                virtual void HideCalculatingRouteSpinner() = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

                virtual void InsertSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) = 0;
                virtual void RemoveSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) = 0;

                virtual void InsertRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback) = 0;
                virtual void RemoveRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback) = 0;

                virtual THeight GetTopViewHeight() = 0;
                virtual THeight GetBottomViewHeight() = 0;

                virtual void SetStartPointFromResultIndex(int index) = 0;

                virtual void SetEndPointFromResultIndex(int index) = 0;

                virtual void InsertOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) = 0;
                virtual void RemoveOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) = 0;

                virtual void InsertOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) = 0;
                virtual void RemoveOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback) = 0;

                virtual void InsertOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback) = 0;
                virtual void RemoveOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool>& callback) = 0;
            };
        }
    }
}
