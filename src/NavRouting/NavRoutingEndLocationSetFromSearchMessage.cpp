// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingEndLocationSetFromSearchMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingEndLocationSetFromSearchMessage::NavRoutingEndLocationSetFromSearchMessage(const SdkModel::NavRoutingLocationModel& endLocation)
        : m_endLocation(endLocation)
        {

        }

        const SdkModel::NavRoutingLocationModel& NavRoutingEndLocationSetFromSearchMessage::GetEndLocation() const
        {
            return m_endLocation;
        }
    }
}
