// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingRouteSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingRouteSetMessage::NavRoutingRouteSetMessage(const SdkModel::NavRoutingRouteModel& routeModel)
        : m_routeModel(routeModel)
        {

        }

        const SdkModel::NavRoutingRouteModel& NavRoutingRouteSetMessage::GetRouteModel() const
        {
            return m_routeModel;
        }
    }
}
