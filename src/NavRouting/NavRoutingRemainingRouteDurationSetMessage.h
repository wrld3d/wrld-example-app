// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavRoutingRemainingRouteDurationSetMessage
        {
        private:
            double m_remainingRouteDuration;

        public:
            NavRoutingRemainingRouteDurationSetMessage(double remainingRouteDuration);

            double GetRemainingRouteDuration() const;
        };
    }
}
