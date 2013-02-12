#ifndef __ExampleApp__ScreenUnprojectExample__
#define __ExampleApp__ScreenUnprojectExample__

#include "IExample.h"
#include "RenderContext.h"
#include "NewGlobeCamera.h"
#include "SphereMesh.h"
#include "TerrainHeightProvider.h"
#include "LatLongAltitude.h"

namespace Examples
{
    class ScreenUnprojectExample : public IExample
    {
    private:
        Eegeo::DebugRendering::SphereMesh* sphere;
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Camera::CameraModel& cameraModel;
        Eegeo::RenderCamera& renderCamera;
        Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider;
        
    public:
        ScreenUnprojectExample(Eegeo::Rendering::RenderContext& renderContext,
                               Eegeo::Camera::CameraModel& cameraModel,
                               Eegeo::RenderCamera& renderCamera,
                               Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);
        
        void Start();
        void Update();
        void Draw();
        void Suspend();
    };
}


#endif /* defined(__ExampleApp__DebugSphereExample__) */
