// Copyright (c) 2014 eeGeo. All rights reserved.

#pragma once

#include "IExample.h"
#include "TrafficCongestion.h"
#include "ITrafficCongestionService.h"

namespace Examples
{
    class TrafficCongestionExample : public IExample
    {
    private:
        Eegeo::TrafficCongestion::ITrafficCongestionService& m_trafficCongestionService;
        float m_timeAccumulator;
        Eegeo::Streaming::MortonKey m_key;
        int m_congestionValue;
        
    public:
        TrafficCongestionExample(
                Eegeo::TrafficCongestion::ITrafficCongestionService& trafficCongestionService);
        
        static std::string GetName() { return "TrafficCongestionExample"; }
        std::string Name() const { return GetName(); }
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend();
    };
}
