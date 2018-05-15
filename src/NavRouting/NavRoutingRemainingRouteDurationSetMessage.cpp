// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingRemainingRouteDurationSetMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavRoutingRemainingRouteDurationSetMessage::NavRoutingRemainingRouteDurationSetMessage(double remainingRouteDuration)
        : m_remainingRouteDuration(remainingRouteDuration)
        {

        }

        double NavRoutingRemainingRouteDurationSetMessage::GetRemainingRouteDuration() const
        {
            return m_remainingRouteDuration;
        }
    }
}
