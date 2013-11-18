//
//  ScreenPickExample.cpp
//  ExampleApp
//

#include "ScreenPickExample.h"
#include "CameraHelpers.h"
#include "ICameraProvider.h"
#include "EarthConstants.h"
#include "SphereMesh.h"
#include "TerrainHeightProvider.h"

namespace Examples
{
    ScreenPickExample::ScreenPickExample(Eegeo::Rendering::RenderContext& renderContext,
                                         Eegeo::Camera::ICameraProvider& cameraProvider,
                                         Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider)
    : m_renderContext(renderContext)
    , m_cameraProvider(cameraProvider)
    , m_terrainHeightProvider(terrainHeightProvider)
    {
        const float radius = 20.f;
        const int numSegments = 16;
        const Eegeo::v3 red(1.f, 0.f, 0.f);
        
        m_sphere = new Eegeo::DebugRendering::SphereMesh(
                                                       renderContext,
                                                       radius,
                                                       numSegments, numSegments,
                                                       Eegeo::dv3(),
                                                       NULL,
                                                       red
                                                       );
        m_sphere->Tesselate();
    }
    
    ScreenPickExample::~ScreenPickExample()
    {
        delete m_sphere;
    }
    
    void ScreenPickExample::Start()
    {

    }
    
    void ScreenPickExample::Suspend()
    {
        
    }
    
    void ScreenPickExample::Update(float dt)
    {
        
    }
    
    void ScreenPickExample::Draw()
    {
        m_sphere->Draw(m_renderContext);
    }
    

    
    bool ScreenPickExample::Event_TouchTap(const AppInterface::TapData& data)
    {
        const Eegeo::Camera::RenderCamera& renderCamera = m_cameraProvider.GetRenderCamera();
        
        Eegeo::dv3 ecefIntersectionPoint;
        
        bool success = Eegeo::Camera::CameraHelpers::TryGetScreenPickIntersectionWithEarthCentredSphere(
            renderCamera,
            data.point.GetX(),
            data.point.GetY(),
            Eegeo::Space::EarthConstants::Radius,
            ecefIntersectionPoint);
        
        if (success)
        {
            //we are intersecting the idealised sphere, so get height at the intersection location
            //and set sphere height to result
            float height = 0.f;
            if (m_terrainHeightProvider.TryGetHeight(ecefIntersectionPoint, 0, height))
            {
                Eegeo::dv3 up = ecefIntersectionPoint.Norm();
                ecefIntersectionPoint += up * height;
            }
            m_sphere->SetPositionECEF(ecefIntersectionPoint);
        }
        
        return success;
    }
}