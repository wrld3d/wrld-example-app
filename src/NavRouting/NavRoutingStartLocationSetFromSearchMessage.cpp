// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingStartLocationSetFromSearchMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingStartLocationSetFromSearchMessage::NavRoutingStartLocationSetFromSearchMessage(const SdkModel::NavRoutingLocationModel& startLocation)
        : m_startLocation(startLocation)
        {

        }

        const SdkModel::NavRoutingLocationModel& NavRoutingStartLocationSetFromSearchMessage::GetStartLocation() const
        {
            return m_startLocation;
        }
    }
}
