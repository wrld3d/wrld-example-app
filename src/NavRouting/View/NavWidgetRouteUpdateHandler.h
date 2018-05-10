// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "INavWidgetViewModel.h"
#include "NavRoutingLocationModel.h"
#include "RouteData.h"
#include "BidirectionalBus.h"
#include "NavRoutingQueryCompletedMessage.h"
#include "NavRoutingViewStartEndLocationSwappedMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetRouteUpdateHandler : private Eegeo::NonCopyable
            {
            private:
                INavWidgetViewModel& m_navWidgetViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                SdkModel::NavRoutingLocationModel m_startLocation;
                bool m_startLocationIsSet;
                SdkModel::NavRoutingLocationModel m_endLocation;
                bool m_endLocationIsSet;

                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const SdkModel::NavRoutingLocationModel&> m_startLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteUpdateHandler> m_startLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const SdkModel::NavRoutingLocationModel&> m_endLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteUpdateHandler> m_endLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const NavRoutingQueryCompletedMessage&> m_queryCompletedMessageHandler;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const NavRoutingViewStartEndLocationSwappedMessage&> m_startEndLocationSwappedMessageHandler;

                void OnStartLocationSet(const SdkModel::NavRoutingLocationModel& startLocation);

                void OnStartLocationCleared();

                void OnEndLocationSet(const SdkModel::NavRoutingLocationModel& endLocation);

                void OnEndLocationCleared();

                void UpdateRoute();

                void UpdateDirectionsFromRoute(const Eegeo::Routes::Webservice::RouteData& route);

                void OnRoutingQueryCompleted(const NavRoutingQueryCompletedMessage& message);

                void OnStartEndLocationSwapped(const NavRoutingViewStartEndLocationSwappedMessage& message);

            public:
                NavWidgetRouteUpdateHandler(INavWidgetViewModel& navWidgetViewModel,
                                            ExampleAppMessaging::TMessageBus& messageBus);

                ~NavWidgetRouteUpdateHandler();
            };
        }
    }
}
