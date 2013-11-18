//
//  Pick3DObjectExample.h
//  ExampleApp
//
//  Created by Scott on 03/10/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__Pick3DObjectExample__
#define __ExampleApp__Pick3DObjectExample__

#include <iostream>

#include "IExample.h"
#include "RenderContext.h"
#include "SphereMesh.h"
#include "LatLongAltitude.h"
#include "VectorMath.h"

namespace Examples
{
    class Pick3DObjectExample : public IExample
    {
    private:
        struct Ray
        {
            Eegeo::dv3 origin;
            Eegeo::v3 direction;
        };
        
        bool m_movingObject;
        Eegeo::DebugRendering::SphereMesh* m_object;
        Eegeo::dv3 m_objectLocationEcef;
        
        Eegeo::Rendering::RenderContext& m_renderContext;
        Eegeo::Space::LatLongAltitude m_interestLocation;
        Eegeo::Camera::ICameraProvider& m_cameraProvider;
        
    public:
        Pick3DObjectExample(Eegeo::Rendering::RenderContext& renderContext,
                            Eegeo::Space::LatLongAltitude interestLocation,
                            Eegeo::Camera::ICameraProvider& cameraProvider);
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
        
        bool Event_TouchPan				(const AppInterface::PanData& data);
        bool Event_TouchDown            (const AppInterface::TouchData& data);
        bool Event_TouchUp              (const AppInterface::TouchData& data);
        
    private:
        void CreateSphereAtLocation(const Eegeo::dv3& location, const Eegeo::v3& colour);
        bool IsScreenPointInsideModel(const Eegeo::v2& screenPoint);
        void CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray);
    };
}

#endif /* defined(__ExampleApp__Pick3DObjectExample__) */
