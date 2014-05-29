//
//  SingleCityExample.h
//  ExampleApp
//
//  Created by Scott on 28/02/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__SingleCityExample__
#define __ExampleApp__SingleCityExample__

#include "IExample.h"
#include "EegeoWorld.h"
#include "PrecacheService.h"
#include "GlobeCameraController.h"
#include "StreamingVolumeController.h"

namespace Examples
{
    class SingleCityExample : public IExample
    {
    private:
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCamera;
        Eegeo::Web::PrecacheService& m_precacheService;
        Eegeo::Streaming::StreamingVolumeController& m_streamingVolumeController;
        Eegeo::EegeoWorld& m_world;
        GlobeCameraStateRestorer m_globeCameraStateRestorer;
        
        bool m_startedPrecaching;
        bool m_precacheComplete;
        
        void ConstrainCamera();
        
    public:
        SingleCityExample(Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCamera,
                          Eegeo::Web::PrecacheService& precacheService,
                          Eegeo::Streaming::StreamingVolumeController& streamingVolumeController,
                          Eegeo::EegeoWorld& world,
                          Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController);
        
        static std::string GetName() { return "SingleCityExample"; }
        std::string Name() const { return GetName(); }
        
        void Start() {}
        void Update(float dt);
        void AfterCameraUpdate();
        void Draw() {}
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__SingleCityExample__) */
