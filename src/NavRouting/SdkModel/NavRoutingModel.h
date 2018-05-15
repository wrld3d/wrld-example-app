// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavRoutingModel.h"
#include "CallbackCollection.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingRouteModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingModel : public INavRoutingModel, private Eegeo::NonCopyable
            {
                SdkModel::NavRoutingLocationModel m_startLocation;
                bool m_startLocationIsSet;
                SdkModel::NavRoutingLocationModel m_endLocation;
                bool m_endLocationIsSet;
                SdkModel::NavRoutingRouteModel m_route;
                bool m_routeIsSet;
                int m_currentDirectionIndex;
                int m_selectedDirectionIndex; //TODO add callbacks for selected direction
                double m_remainingRouteDuration;

                Eegeo::Helpers::CallbackCollection1<const SdkModel::NavRoutingLocationModel&> m_startLocationSetCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const SdkModel::NavRoutingLocationModel&> m_endLocationSetCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const SdkModel::NavRoutingRouteModel&> m_routeSetCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_routeClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_currentDirectionSetCallbacks;
                Eegeo::Helpers::CallbackCollection1<const double> m_remainingRouteDurationSetCallbacks;

            public:
                NavRoutingModel();

                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;

                void ClearStartLocation() override;

                bool TryGetStartLocation(SdkModel::NavRoutingLocationModel &out_startLocation) const override;

                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;

                void ClearEndLocation() override;

                bool TryGetEndLocation(SdkModel::NavRoutingLocationModel &out_endLocation) const override;

                void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel) override;

                void ClearRoute() override;

                bool TryGetRoute(SdkModel::NavRoutingRouteModel &out_routeModel) const override;

                void SetCurrentDirection(int directionIndex) override;

                int GetCurrentDirection() const override;

                void SetRemainingRouteDuration(double seconds) override;

                double GetRemainingRouteDuration() const override;

                void InsertStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback) override;

                void RemoveStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback) override;

                void InsertStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) override;

                void RemoveStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback) override;

                void InsertEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback) override;

                void RemoveEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback) override;

                void InsertEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) override;

                void RemoveEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback) override;

                void InsertRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback) override;

                void RemoveRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback) override;

                void InsertRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback) override;

                void RemoveRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback) override;

                void InsertCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback) override;

                void RemoveCurrentDirectionSetCallback(Eegeo::Helpers::ICallback1<const int>& currentDirectionSetCallback) override;

                void InsertRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback) override;

                void RemoveRemainingRouteDurationSetCallback(Eegeo::Helpers::ICallback1<const double>& remainingRouteDurationSetCallback) override;
            };
        }
    }
}
