// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingModel::NavRoutingModel()
            : m_startLocationIsSet(false)
            , m_endLocationIsSet(false)
            , m_routeIsSet(false)
            , m_currentDirectionIndex(0)
            , m_remainingRouteDuration(0)
            {

            }

            void NavRoutingModel::SetStartLocation(const NavRoutingLocationModel& locationModel)
            {
                m_startLocation = locationModel;
                m_startLocationIsSet = true;
                m_startLocationSetCallbacks.ExecuteCallbacks(m_startLocation);
            }

            void NavRoutingModel::ClearStartLocation()
            {
                m_startLocationIsSet = false;
                m_startLocationClearedCallbacks.ExecuteCallbacks();
            }

            bool NavRoutingModel::TryGetStartLocation(NavRoutingLocationModel &out_startLocation) const
            {
                if (m_startLocationIsSet)
                {
                    out_startLocation = m_startLocation;
                    return true;
                }

                return false;
            }

            void NavRoutingModel::SetEndLocation(const NavRoutingLocationModel& locationModel)
            {
                m_endLocation = locationModel;
                m_endLocationIsSet = true;
                m_endLocationSetCallbacks.ExecuteCallbacks(m_endLocation);
            }

            void NavRoutingModel::ClearEndLocation()
            {
                m_endLocationIsSet = false;
                m_endLocationClearedCallbacks.ExecuteCallbacks();
            }

            bool NavRoutingModel::TryGetEndLocation(NavRoutingLocationModel &out_endLocation) const
            {
                if (m_endLocationIsSet)
                {
                    out_endLocation = m_endLocation;
                    return true;
                }

                return false;
            }

            bool NavRoutingModel::HasRoute() const
            {
                return m_routeIsSet;
            }

            void NavRoutingModel::SetRoute(const NavRoutingRouteModel& routeModel)
            {
                m_route = routeModel;
                m_routeIsSet = true;
                m_routeSetCallbacks.ExecuteCallbacks(m_route);
            }

            void NavRoutingModel::ClearRoute()
            {
                m_routeIsSet = false;
                m_routeClearedCallbacks.ExecuteCallbacks();
            }

            bool NavRoutingModel::TryGetRoute(NavRoutingRouteModel &out_routeModel) const
            {
                if (m_routeIsSet)
                {
                    out_routeModel = m_route;
                    return true;
                }

                return false;
            }

            void NavRoutingModel::SetCurrentDirection(int directionIndex)
            {
                m_currentDirectionIndex = directionIndex;
                m_currentDirectionSetCallbacks.ExecuteCallbacks(m_currentDirectionIndex);
            }

            int NavRoutingModel::GetCurrentDirection() const
            {
                return m_currentDirectionIndex;
            }

            void NavRoutingModel::SetRemainingRouteDuration(double seconds)
            {
                m_remainingRouteDuration = seconds;
                m_remainingRouteDurationSetCallbacks.ExecuteCallbacks(seconds);
            }

            double NavRoutingModel::GetRemainingRouteDuration() const
            {
                return m_remainingRouteDuration;
            }

            void NavRoutingModel::InsertStartLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& startLocationSetCallback)
            {
                m_startLocationSetCallbacks.AddCallback(startLocationSetCallback);
            }

            void NavRoutingModel::RemoveStartLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& startLocationSetCallback)
            {
                m_startLocationSetCallbacks.RemoveCallback(startLocationSetCallback);
            }

            void NavRoutingModel::InsertStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback)
            {
                m_startLocationClearedCallbacks.AddCallback(startLocationClearedCallback);
            }

            void NavRoutingModel::RemoveStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback)
            {
                m_startLocationClearedCallbacks.RemoveCallback(startLocationClearedCallback);
            }

            void NavRoutingModel::InsertEndLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& endLocationSetCallback)
            {
                m_endLocationSetCallbacks.AddCallback(endLocationSetCallback);
            }

            void NavRoutingModel::RemoveEndLocationSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingLocationModel&>& endLocationSetCallback)
            {
                m_endLocationSetCallbacks.RemoveCallback(endLocationSetCallback);
            }

            void NavRoutingModel::InsertEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback)
            {
                m_endLocationClearedCallbacks.AddCallback(endLocationClearedCallback);
            }

            void NavRoutingModel::RemoveEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback)
            {
                m_endLocationClearedCallbacks.RemoveCallback(endLocationClearedCallback);
            }

            void NavRoutingModel::InsertRouteSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingRouteModel&>& routeSetCallback)
            {
                m_routeSetCallbacks.AddCallback(routeSetCallback);
            }

            void NavRoutingModel::RemoveRouteSetCallback(Eegeo::Helpers::ICallback1<const NavRoutingRouteModel&>& routeSetCallback)
            {
                m_routeSetCallbacks.RemoveCallback(routeSetCallback);
            }

            void NavRoutingModel::InsertRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback)
            {
                m_routeClearedCallbacks.AddCallback(routeClearedCallback);
            }

            void NavRoutingModel::RemoveRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback)
            {
                m_routeClearedCallbacks.RemoveCallback(routeClearedCallback);
            }

            void NavRoutingModel::InsertCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback)
            {
                m_currentDirectionSetCallbacks.AddCallback(currentDirectionSetCallback);
            }

            void NavRoutingModel::RemoveCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback)
            {
                m_currentDirectionSetCallbacks.RemoveCallback(currentDirectionSetCallback);
            }

            void NavRoutingModel::InsertRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback)
            {
                m_remainingRouteDurationSetCallbacks.AddCallback(remainingRouteDurationSetCallback);
            }

            void NavRoutingModel::RemoveRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback)
            {
                m_remainingRouteDurationSetCallbacks.RemoveCallback(remainingRouteDurationSetCallback);
            }
        }
    }
}
