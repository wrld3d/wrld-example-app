// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavWidgetViewModel.h"
#include "CallbackCollection.h"
#include "NavWidgetOpenableControl.h"
#include "Reaction.h"
#include "NavRoutingLocationModel.h"
#include "NavRoutingRouteModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetViewModel : public INavWidgetViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const SdkModel::NavRoutingLocationModel&> m_startLocationSetCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_startLocationClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const SdkModel::NavRoutingLocationModel&> m_endLocationSetCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_endLocationClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const SdkModel::NavRoutingRouteModel&> m_routeSetCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_routeClearedCallbacks;
                Eegeo::Helpers::CallbackCollection1<const int> m_currentDirectionSetCallbacks;
                Eegeo::Helpers::CallbackCollection1<const double> m_remainingRouteDurationSetCallbacks;
                NavWidgetOpenableControl m_openable;

            public:
                NavWidgetViewModel(Eegeo::Helpers::TIdentity identity,
                                   Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~NavWidgetViewModel();

                bool TryAcquireReactorControl() override;

                bool IsOpen() const override;

                void Open() override;

                void Close() override;

                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;

                void ClearStartLocation() override;

                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel) override;

                void ClearEndLocation() override;

                void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel) override;

                void ClearRoute() override;

                void SetCurrentDirection(int directionIndex) override;

                void SetRemainingRouteDuration(double seconds) override;

                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl() override;

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) override;

                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) override;

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) override;

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) override;

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
