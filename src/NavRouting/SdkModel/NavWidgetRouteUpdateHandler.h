// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavRoutingModel.h"
#include "NavRoutingLocationModel.h"
#include "RouteData.h"
#include "BidirectionalBus.h"
#include "NavRoutingViewStartEndLocationSwappedMessage.h"
#include "INavRoutingServiceController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavWidgetRouteUpdateHandler : private Eegeo::NonCopyable
            {
            private:
                INavRoutingModel& m_navRoutingModel;
                INavRoutingServiceController& m_navRoutingServiceController;

                NavRoutingLocationModel m_startLocation;
                bool m_startLocationIsSet;
                NavRoutingLocationModel m_endLocation;
                bool m_endLocationIsSet;

                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const NavRoutingLocationModel&> m_startLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteUpdateHandler> m_startLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const NavRoutingLocationModel&> m_endLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteUpdateHandler> m_endLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const std::vector<Eegeo::Routes::Webservice::RouteData>> m_queryCompletedCallback;

                void OnStartLocationSet(const NavRoutingLocationModel& startLocation);

                void OnStartLocationCleared();

                void OnEndLocationSet(const NavRoutingLocationModel& endLocation);

                void OnEndLocationCleared();

                void UpdateRoute();

                void UpdateDirectionsFromRoute(const Eegeo::Routes::Webservice::RouteData& route);

                void OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& data);

            public:
                NavWidgetRouteUpdateHandler(INavRoutingModel& navRoutingModel,
                                            INavRoutingServiceController& navRoutingServiceController);

                ~NavWidgetRouteUpdateHandler();
            };
        }
    }
}
