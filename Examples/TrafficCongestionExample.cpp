// Copyright (c) 2014 eeGeo. All rights reserved.
#import <EegeoWorld.h>
#include "TrafficCongestionExample.h"

namespace Examples
{
    TrafficCongestionExample::TrafficCongestionExample(
            Eegeo::TrafficCongestion::ITrafficCongestionService& trafficCongestionService,
            Eegeo::EegeoWorld& world) :
    m_trafficCongestionService(trafficCongestionService),
    m_world(world),
    m_hasCalled(false)
    {

    }

    void TrafficCongestionExample::Update(float dt)
    {
        if(!m_hasCalled && !m_world.Initialising())
        {
            m_hasCalled = true;

            bool success = m_trafficCongestionService.TrySetCongestionFor(
                    Eegeo::Streaming::MortonKey::CreateFromString("01131232132001"),
                    0,
                    Eegeo::TrafficCongestion::CongestionLevel::Heavy);

            Eegeo_ASSERT(success, "should've worked");
        }
    }
}
