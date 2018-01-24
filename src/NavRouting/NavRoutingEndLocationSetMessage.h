// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "NavRoutingLocationModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingEndLocationSetMessage
        {
        private:
            SdkModel::NavRoutingLocationModel m_endLocation;

        public:
            NavRoutingEndLocationSetMessage(const SdkModel::NavRoutingLocationModel& endLocation);

            const SdkModel::NavRoutingLocationModel& GetEndLocation() const;
        };
    }
}
