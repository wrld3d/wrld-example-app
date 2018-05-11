// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "ICallback.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingRouteModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class INavWidgetView
            {
            public:
                virtual ~INavWidgetView() { };

                virtual void Show() = 0;

                virtual void Hide() = 0;

                virtual void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearStartLocation() = 0;

                virtual void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearEndLocation() = 0;

                virtual void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel) = 0;

                virtual void ClearRoute() = 0;

                virtual void SetCurrentDirection(int directionIndex) = 0;

                virtual void SetRemainingRouteDuration(double seconds) = 0;

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

                virtual void InsertSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) = 0;
                virtual void RemoveSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback) = 0;

                virtual void InsertCurrentNavModeChangedCallback(Eegeo::Helpers::ICallback1<const NavRoutingMode>& currentNavModeChangedCallback) = 0;
                virtual void RemoveCurrentNavModeChangedCallback(Eegeo::Helpers::ICallback1<const NavRoutingMode>& currentNavModeChangedCallback) = 0;
            };
        }
    }
}
