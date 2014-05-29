//
//  EnvironmentFlatteningExample.h
//  ExampleApp
//
//  Created by Scott on 04/06/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__EnvironmentFlatteningExample__
#define __ExampleApp__EnvironmentFlatteningExample__

#include "IExample.h"
#include "EnvironmentFlatteningService.h"

namespace Examples
{
    class EnvironmentFlatteningExample : public IExample
    {
    private:
        long long m_lastToggle;
        bool m_scaleUp;
        Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
        float m_initialEnvironmentScale;
        GlobeCameraStateRestorer m_globeCameraStateRestorer;
        
    public:
        EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                     Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);
        
        static std::string GetName() { return "EnvironmentFlatteningExample"; }
        std::string Name() const { return GetName(); }
        
        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__EnvironmentFlatteningExample__) */
