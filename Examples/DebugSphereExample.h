#ifndef __ExampleApp__DebugSphereExample__
#define __ExampleApp__DebugSphereExample__

#include "IExample.h"
#include "RenderContext.h"
#include "NewGlobeCamera.h"
#include "SphereMesh.h"
#include "LatLongAltitude.h"

namespace Examples
{
    class DebugSphereExample : public IExample
    {
    private:
        std::vector<Eegeo::DebugRendering::SphereMesh*> renderables;
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Space::LatLongAltitude interestLocation;
        Eegeo::Camera::CameraModel& cameraModel;
        Eegeo::RenderCamera& renderCamera;
        
        void AddSphere(Eegeo::Space::LatLongAltitude sphereLocation,
                       Eegeo::v3 color);
        
    public:
        DebugSphereExample(Eegeo::Rendering::RenderContext& renderContext,
                           Eegeo::Space::LatLongAltitude interestLocation,
                           Eegeo::Camera::CameraModel& cameraModel,
                           Eegeo::RenderCamera& renderCamera);
        
        void Start();
        void Update();
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__DebugSphereExample__) */
