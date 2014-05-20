// Copyright (c) 2014 eeGeo. All rights reserved.
#include "EegeoWorld.h"
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

            const int roadId = 0;

            Eegeo::Streaming::MortonKey key = Eegeo::Streaming::MortonKey::CreateFromString("01131232132001");

            bool success = m_trafficCongestionService.TrySetCongestionFor(
                    key,
                    roadId,
                    Eegeo::TrafficCongestion::CongestionLevel::Heavy);

            Eegeo_TTY("%s congestion level on road id %d for morton key %s\n",
                    success ? "Successfully set" : "Failed to set",
                    roadId,
                    key.ToString().c_str());
        }
    }
}
