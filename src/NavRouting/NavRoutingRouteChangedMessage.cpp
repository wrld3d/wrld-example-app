// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingRouteChangedMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingRouteChangedMessage::NavRoutingRouteChangedMessage(const SdkModel::NavRoutingRouteModel& routeModel, bool isNewRoute)
        : m_routeModel(routeModel)
        , m_isNewRoute(isNewRoute)
        {

        }

        const SdkModel::NavRoutingRouteModel& NavRoutingRouteChangedMessage::GetRouteModel() const
        {
            return m_routeModel;
        }

        const bool NavRoutingRouteChangedMessage::GetIsNewRoute() const
        {
            return m_isNewRoute;
        }
    }
}
