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
                NavWidgetOpenableControl m_openable;

            public:
                NavWidgetViewModel(Eegeo::Helpers::TIdentity identity,
                                   Reaction::View::IReactionControllerModel& reactionControllerModel);

                ~NavWidgetViewModel();

                bool TryAcquireReactorControl();

                bool IsOpen() const;

                void Open();

                void Close();

                void SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel);

                void ClearStartLocation();

                void SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel);

                void ClearEndLocation();

                void SetRoute(const SdkModel::NavRoutingRouteModel& routeModel);

                void ClearRoute();

                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl();

                void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

                void InsertStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback);

                void RemoveStartLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& startLocationSetCallback);

                void InsertStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback);

                void RemoveStartLocationClearedCallback(Eegeo::Helpers::ICallback0& startLocationClearedCallback);

                void InsertEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback);

                void RemoveEndLocationSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingLocationModel&>& endLocationSetCallback);

                void InsertEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback);

                void RemoveEndLocationClearedCallback(Eegeo::Helpers::ICallback0& endLocationClearedCallback);

                void InsertRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback);

                void RemoveRouteSetCallback(Eegeo::Helpers::ICallback1<const SdkModel::NavRoutingRouteModel&>& routeSetCallback);

                void InsertRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback);

                void RemoveRouteClearedCallback(Eegeo::Helpers::ICallback0& routeClearedCallback);

            };
        }
    }
}
