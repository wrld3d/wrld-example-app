// Copyright (c) 2014 eeGeo. All rights reserved.
#include "EegeoWorld.h"
#include "TrafficCongestionExample.h"
#include <string>

namespace
{
    const std::string congestionLevelNames[] = {"Light", "Normal", "Heavy", "GridLock"};
    const int RoadId = 0;
    const float NumSecondsEachCongestion = 5.f;
}

namespace Examples
{
    TrafficCongestionExample::TrafficCongestionExample(Eegeo::TrafficCongestion::ITrafficCongestionService& trafficCongestionService,
                                                       Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController) :
    m_trafficCongestionService(trafficCongestionService),
    m_timeAccumulator(5.f),
    m_congestionValue(static_cast<int>(Eegeo::TrafficCongestion::CongestionLevel::Light)),
    m_key(Eegeo::Streaming::MortonKey::CreateFromString("01131232132001"))
    ,m_globeCameraStateRestorer(cameraController)
    {

    }
    
    void TrafficCongestionExample::Suspend()
    {
        m_trafficCongestionService.TrySetCongestionFor(m_key,
                                                       RoadId,
                                                       Eegeo::TrafficCongestion::CongestionLevel::Normal);
    }
    
    void TrafficCongestionExample::Update(float dt)
    {
        if(m_timeAccumulator > NumSecondsEachCongestion)
        {
            Eegeo::TrafficCongestion::CongestionLevel::CongestionLevelValues congestionLevel =
                static_cast<Eegeo::TrafficCongestion::CongestionLevel::CongestionLevelValues>(m_congestionValue);
           
            bool success = m_trafficCongestionService.TrySetCongestionFor(m_key,
                                                                          RoadId,
                                                                          congestionLevel);
            
            Eegeo_TTY("%s congestion level %s on road id %d for morton key %s\n",
                      success ? "Successfully set" : "Failed to set",
                      congestionLevelNames[m_congestionValue].c_str(),
                      RoadId,
                      m_key.ToString().c_str());
            
            if(++m_congestionValue > Eegeo::TrafficCongestion::CongestionLevel::Gridlock)
            {
                m_congestionValue = 0;
            }
            
            m_timeAccumulator -= NumSecondsEachCongestion;
        }
        
        m_timeAccumulator += dt;
    }
}
