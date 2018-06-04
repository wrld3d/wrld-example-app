// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRoutingRouteModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingRouteChangedMessage
        {
        private:
            SdkModel::NavRoutingRouteModel m_routeModel;
            bool m_isNewRoute;

        public:
            NavRoutingRouteChangedMessage(const SdkModel::NavRoutingRouteModel& routeModel, bool isNewRoute);

            const SdkModel::NavRoutingRouteModel& GetRouteModel() const;

            const bool GetIsNewRoute() const;
        };
    }
}
