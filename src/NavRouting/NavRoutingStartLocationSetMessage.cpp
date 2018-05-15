// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingStartLocationSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingStartLocationSetMessage::NavRoutingStartLocationSetMessage(const SdkModel::NavRoutingLocationModel& startLocation)
        : m_startLocation(startLocation)
        {

        }

        const SdkModel::NavRoutingLocationModel& NavRoutingStartLocationSetMessage::GetStartLocation() const
        {
            return m_startLocation;
        }
    }
}
