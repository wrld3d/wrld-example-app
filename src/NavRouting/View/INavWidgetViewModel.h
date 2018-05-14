// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "IOpenableControlViewModel.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingRouteModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class INavWidgetViewModel
            {
            public:
                virtual ~INavWidgetViewModel() { }

                virtual bool TryAcquireReactorControl() = 0;

                virtual bool IsOpen() const = 0;

                virtual void Open() = 0;
                virtual void Close() = 0;

                virtual void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;
                virtual void ClearStartLocation() = 0;

                virtual void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) = 0;
                virtual void ClearEndLocation() = 0;

                virtual void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel) = 0;
                virtual void ClearRoute() = 0;

                virtual void SetCurrentDirection(int directionIndex) = 0;

                virtual void SetRemainingRouteDuration(double seconds) = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;
                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void InsertStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback) = 0;
                virtual void RemoveStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback) = 0;

                virtual void InsertStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) = 0;
                virtual void RemoveStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) = 0;

                virtual void InsertEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback) = 0;
                virtual void RemoveEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback) = 0;

                virtual void InsertEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) = 0;
                virtual void RemoveEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) = 0;

                virtual void InsertRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback) = 0;
                virtual void RemoveRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback) = 0;

                virtual void InsertRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback) = 0;
                virtual void RemoveRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback) = 0;

                virtual void InsertCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback) = 0;
                virtual void RemoveCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback) = 0;

                virtual void InsertRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback) = 0;
                virtual void RemoveRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback) = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetOpenableControl() = 0;
            };
        }
    }
}
