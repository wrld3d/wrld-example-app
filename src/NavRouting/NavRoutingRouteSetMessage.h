// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "INavRoutingModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingRouteSetMessage
        {
        private:
            SdkModel::NavRoutingRouteModel m_routeModel;

        public:
            NavRoutingRouteSetMessage(const SdkModel::NavRoutingRouteModel& routeModel);

            const SdkModel::NavRoutingRouteModel& GetRouteModel() const;
        };
    }
}
