//
//  ToggleTrafficExample.h
//  ExampleApp
//
//  Created by eeGeo on 14/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ToggleTrafficExample__
#define __ExampleApp__ToggleTrafficExample__

#include "IExample.h"
#include "TrafficSimulationController.h"

namespace Examples
{
    class ToggleTrafficExample : public IExample
    {
    private:
        long long m_lastToggle;
        Eegeo::Traffic::TrafficSimulationController& m_trafficSimulation;
        GlobeCameraStateRestorer m_globeCameraStateRestorer;
        
    public:
        ToggleTrafficExample(Eegeo::Traffic::TrafficSimulationController& trafficSimulation,
                             Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);

        static std::string GetName() { return "ToggleTrafficExample"; }
        std::string Name() const { return GetName(); }
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__ToggleTrafficExample__) */
