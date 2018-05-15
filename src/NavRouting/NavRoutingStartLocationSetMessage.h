// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRoutingLocationModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingStartLocationSetMessage
        {
        private:
            SdkModel::NavRoutingLocationModel m_startLocation;

        public:
            NavRoutingStartLocationSetMessage(const SdkModel::NavRoutingLocationModel& startLocation);

            const SdkModel::NavRoutingLocationModel& GetStartLocation() const;
        };
    }
}
