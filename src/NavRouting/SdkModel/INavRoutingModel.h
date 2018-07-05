// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "NavRouting.h"
#include "CallbackCollection.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingRouteModel.h"
#include "NavRoutingDirectionModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class INavRoutingModel
            {
            public:
                virtual ~INavRoutingModel() {}

                virtual void SetStartLocation(const NavRoutingLocationModel& locationModel) = 0;

                virtual bool SetStartLocationFromCurrentPosition() = 0;

                virtual void ClearStartLocation() = 0;

                virtual bool TryGetStartLocation(NavRoutingLocationModel &out_startLocation) const = 0;

                virtual void SetEndLocation(const NavRoutingLocationModel& locationModel) = 0;

                virtual void ClearEndLocation() = 0;

                virtual bool TryGetEndLocation(NavRoutingLocationModel &out_endLocation) const = 0;

                virtual bool HasRoute() const = 0;

                virtual bool IsUsingCurrentPositionAsStartLocation() = 0;

                virtual void SetRoute(const NavRoutingRouteModel& routeModel) = 0;

                virtual void ClearRoute() = 0;

                virtual bool TryGetRoute(NavRoutingRouteModel &out_routeModel) const = 0;

                virtual void RouteUpdated() const = 0;

                virtual void SetCurrentDirection(int directionIndex) = 0;

                virtual void UpdateCurrentDirection(const NavRoutingDirectionModel& directionModel) = 0;

                virtual void UpdateDirection(int index, const NavRoutingDirectionModel& directionModel) = 0;

                virtual int GetCurrentDirection() const = 0;

                virtual void SetSelectedDirection(int directionIndex) = 0;

                virtual int GetSelectedDirection() const = 0;

                virtual void SetRemainingRouteDuration(double seconds) = 0;

                virtual double GetRemainingRouteDuration() const = 0;

                virtual void SetNavMode(NavRoutingMode mode) = 0;

                virtual NavRoutingMode GetNavMode() const = 0;

                virtual void InsertStartLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& startLocationSetCallback) = 0;

                virtual void RemoveStartLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& startLocationSetCallback) = 0;

                virtual void InsertStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) = 0;

                virtual void RemoveStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) = 0;

                virtual void InsertEndLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& endLocationSetCallback) = 0;

                virtual void RemoveEndLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& endLocationSetCallback) = 0;

                virtual void InsertEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) = 0;

                virtual void RemoveEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) = 0;

                virtual void InsertRouteSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingRouteModel&>& routeSetCallback) = 0;

                virtual void RemoveRouteSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingRouteModel&>& routeSetCallback) = 0;

                virtual void InsertRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback) = 0;

                virtual void RemoveRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback) = 0;

                virtual void InsertRouteUpdatedCallback(Eegeo::Helpers::ICallback1<const NavRoutingRouteModel&>& routeUpdatedCallback) = 0;

                virtual void RemoveRouteUpdatedCallback(Eegeo::Helpers::ICallback1<const NavRoutingRouteModel&>& routeUpdatedCallback) = 0;

                virtual void InsertCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback) = 0;

                virtual void RemoveCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback) = 0;

                virtual void InsertCurrentDirectionUpdatedCallback(Eegeo::Helpers::ICallback1<const NavRoutingDirectionModel&>& currentDirectionUpdatedCallback) = 0;

                virtual void RemoveCurrentDirectionUpdatedCallback(Eegeo::Helpers::ICallback1<const NavRoutingDirectionModel&>& currentDirectionUpdatedCallback) = 0;

                virtual void InsertSelectedDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionSetCallback) = 0;

                virtual void RemoveSelectedDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionSetCallback) = 0;

                virtual void InsertRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback) = 0;

                virtual void RemoveRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback) = 0;

                virtual void InsertNavModeSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingMode>& navRoutingModeSetCallback) = 0;

                virtual void RemoveNavModeSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingMode>& navRoutingModeSetCallback) = 0;
            };
        }
    }
}
