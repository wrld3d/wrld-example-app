// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingEndLocationSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingEndLocationSetMessage::NavRoutingEndLocationSetMessage(const SdkModel::NavRoutingLocationModel& endLocation)
        : m_endLocation(endLocation)
        {

        }

        const SdkModel::NavRoutingLocationModel& NavRoutingEndLocationSetMessage::GetEndLocation() const
        {
            return m_endLocation;
        }
    }
}
