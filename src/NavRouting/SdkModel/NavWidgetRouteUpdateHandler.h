// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include "Types.h"
#include "INavRoutingModel.h"
#include "NavRoutingLocationModel.h"
#include "RouteData.h"
#include "BidirectionalBus.h"
#include "NavRoutingViewStartEndLocationSwappedMessage.h"
#include "INavRoutingServiceController.h"
#include "AlertBox.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"
#include "InteriorsModelRepository.h"
#include "InteriorsModel.h"
#include "BidirectionalBus.h"
#include "NavRoutingViewClosedMessage.h"

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
                Eegeo::Resources::Interiors::InteriorsModelRepository& m_interiorsModelRepository;
                Eegeo::UI::NativeAlerts::IAlertBoxFactory& m_alertBoxFactory;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                NavRoutingLocationModel m_startLocation;
                bool m_startLocationIsSet;
                NavRoutingLocationModel m_endLocation;
                bool m_endLocationIsSet;

                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const NavRoutingLocationModel&> m_startLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteUpdateHandler> m_startLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const NavRoutingLocationModel&> m_endLocationSetCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteUpdateHandler> m_endLocationClearedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const std::vector<Eegeo::Routes::Webservice::RouteData>> m_queryCompletedCallback;
                Eegeo::Helpers::TCallback0<NavWidgetRouteUpdateHandler> m_queryFailedCallback;
                Eegeo::UI::NativeAlerts::TSingleOptionAlertBoxDismissedHandler<NavWidgetRouteUpdateHandler> m_failAlertHandler;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, Eegeo::Resources::Interiors::InteriorsModel&> m_interiorModelAddedCallback;
                Eegeo::Helpers::TCallback1<NavWidgetRouteUpdateHandler, const NavRoutingViewClosedMessage&> m_viewClosedMessageHandler;

                void OnStartLocationSet(const NavRoutingLocationModel& startLocation);

                void OnStartLocationCleared();

                void OnEndLocationSet(const NavRoutingLocationModel& endLocation);

                void OnEndLocationCleared();

                void UpdateRoute();

                void UpdateDirectionsFromRoute(const Eegeo::Routes::Webservice::RouteData& route);

                void OnRoutingQueryCompleted(const std::vector<Eegeo::Routes::Webservice::RouteData>& data);

                void OnRoutingQueryFailed();

                void OnFailAlertBoxDismissed();

                void OnInteriorModelAdded(Eegeo::Resources::Interiors::InteriorsModel& interiorsModel);

                void OnNavRoutingViewClosedMessage(const NavRoutingViewClosedMessage& message);

            public:
                NavWidgetRouteUpdateHandler(INavRoutingModel& navRoutingModel,
                                            INavRoutingServiceController& navRoutingServiceController,
                                            Eegeo::Resources::Interiors::InteriorsModelRepository& interiorsModelRepository,
                                            Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                            ExampleAppMessaging::TMessageBus& messageBus
                );

                ~NavWidgetRouteUpdateHandler();
            };
        }
    }
}
