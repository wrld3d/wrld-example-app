//
//  ScreenPickExample.h
//  ExampleApp
//

#ifndef __ExampleApp__ScreenPickExample__
#define __ExampleApp__ScreenPickExample__

#include "IExample.h"
#include "Rendering.h"
#include "Terrain.h"
#include "Camera.h"
#include "DebugRendering.h"

namespace Examples
{
    /*!
     *  ScreenPickExample demonstrates projecting a ray through the camera origin and
     *  a screen pixel when the touch screen is tapped. 
     *  We attempt to intersect the ray with the collision meshes of any currently
     *  streamed terrain resources, making use of Eegeo::Resources::Terrain::Collision::TerrainRayPicker.
     *  We draw a red marker sphere at the intersection point if found.
     */
    class ScreenPickExample : public IExample
    {
    private:
        Eegeo::DebugRendering::SphereMesh* m_sphere;
        Eegeo::Rendering::RenderContext& m_renderContext;
        Eegeo::Camera::ICameraProvider& m_cameraProvider;        
        Eegeo::Resources::Terrain::Collision::TerrainRayPicker* m_rayPicker;
        
    public:
        ScreenPickExample(Eegeo::Rendering::RenderContext& renderContext,
                               Eegeo::Camera::ICameraProvider& cameraProvider,
                               Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                               const Eegeo::Resources::Terrain::Collision::ICollisionMeshResourceProvider& collisionMeshResourceProvider);
        
        virtual ~ScreenPickExample();
        
        static std::string GetName() { return "ScreenPickExample"; }
        std::string Name() const { return GetName(); }
        
        void Start();
        void Update(float dt);
        void Draw();
        void Suspend();
        
        bool Event_TouchTap(const AppInterface::TapData& data);
    };
}

#endif /* defined(__ExampleApp__ScreenPickExample__) */
