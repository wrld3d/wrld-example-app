// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DebugPrimitiveRenderingExample.h"
#include "DebugRenderer.h"
#include "LatLongAltitude.h"
#include "CoordinateConversion.h"
#include "EcefTangentBasis.h"
#include "MortonKey.h"
#include "Colors.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "Frustum.h"
#include "Plane.h"


namespace Examples
{
DebugPrimitiveRenderingExample::DebugPrimitiveRenderingExample(Eegeo::DebugRendering::DebugRenderer &debugRenderer,
        const Eegeo::Camera::RenderCamera& renderCamera,
        Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController)
	:m_debugRenderer(debugRenderer)
    ,m_camera(renderCamera)
	,m_globeCameraStateRestorer(cameraController)
    ,m_frustumDrawTimer(0.0)
{
}

void DebugPrimitiveRenderingExample::Start()
{

}

void DebugPrimitiveRenderingExample::Update(float dt)
{
    // Debug rendering can generally be called from Update or Render.
    
    // Draw a red sphere at a given latitude & longitude
    Eegeo::dv3 ecefCenter = ConvertLatLongAltitudeToEcef(Eegeo::Space::LatLongAltitude::FromDegrees(37.78469,-122.40143, 200));
    m_debugRenderer.DrawSphere(ecefCenter, 20.0f, Eegeo::Rendering::Colors::RED);
    
    // Draw axes representing an ECEF tangent space at the sphere position too, using a Morton Key around the SF Bay area
    Eegeo::Streaming::MortonKey mortonKey = Eegeo::Streaming::MortonKey::CreateFromString("011312321320010");
    Eegeo::Space::EcefTangentBasis tangentBasis = Eegeo::Space::EcefTangentBasis::CreateFromMortonKey(mortonKey);
    const float axesSize = 50.0f;
    m_debugRenderer.DrawAxes(ecefCenter, tangentBasis.GetRight()*axesSize, tangentBasis.GetUp()*axesSize, tangentBasis.GetForward()*axesSize);
    
    // To demonstrate the difference between the tangent space and the ECEF space, also draw the base ECEF axes in different colours
    const float axesSizeEcef = 25.0f;
    m_debugRenderer.DrawAxes(ecefCenter, Eegeo::v3(axesSizeEcef, 0, 0), Eegeo::v3(0, axesSizeEcef, 0), Eegeo::v3(0, 0, axesSizeEcef),
                             Eegeo::Rendering::Colors::MAGENTA, Eegeo::Rendering::Colors::YELLOW, Eegeo::Rendering::Colors::CYAN);
    
    // Draw an animated 'Sine wave' using the DrawPolyline feature.
    std::vector<Eegeo::dv3> ecefWavePoints;
    for(int i = 0; i < 64; i++)
    {
        const double amplitude = 30.0;
        Eegeo::dv3 pos = ecefCenter + (tangentBasis.GetRight() * i) + (tangentBasis.GetUp() * amplitude * sin(m_frustumDrawTimer + i*0.1));
        ecefWavePoints.push_back(pos);
    }
    m_debugRenderer.DrawPolyLine(ecefWavePoints, Eegeo::Rendering::Colors::WHITE);
    
    // Draw a transparent XZ quad on the tangent space
    const float quadSize = 100.0f;
    Eegeo::v4 quadColor = Eegeo::v4(0.0f, 1.0f, 1.0f, 0.5f);
    m_debugRenderer.DrawQuad(ecefCenter, tangentBasis.GetForward()*quadSize, tangentBasis.GetRight()*quadSize, tangentBasis.GetUp()*quadSize, quadColor);
    
    // Draw a cube above the axes oriented to the tangent plane.
    Eegeo::dv3 ecefCenter2 = ConvertLatLongAltitudeToEcef(Eegeo::Space::LatLongAltitude::FromDegrees(37.78469,-122.40143, 300));
    const float cubeSize = 50.0f;
    m_debugRenderer.DrawCube(ecefCenter2, tangentBasis.GetRight()*cubeSize, tangentBasis.GetUp()*cubeSize, tangentBasis.GetForward()*cubeSize, Eegeo::Rendering::Colors::BLUE);
    
    // Every 5 seconds draw a representation of the camera Frustum that lasts for 3 seconds.
    m_frustumDrawTimer += dt;
    if(m_frustumDrawTimer >= 5.0)
    {
        m_frustumDrawTimer = 0.0;
        
        // Construct a frustum representation from the current render camera's ViewProjection matrix
        std::vector<Eegeo::Geometry::Plane> frustumPlanes;
        frustumPlanes.resize(6);
        Eegeo::Geometry::BuildFrustumPlanesFromViewProjection(frustumPlanes, m_camera.GetViewProjectionMatrix());
        Eegeo::Geometry::Frustum frustum;
        frustum.Update(frustumPlanes);
        
        // Draw this frustum for 3 seconds.
        m_debugRenderer.DrawWireFrustum(m_camera.GetEcefLocation(), frustum, Eegeo::Rendering::Colors::GREEN, 3.0f);
        
        // And draw some text for 4 seconds where the cube is
        Eegeo::dv3 ecefCenter3 = ConvertLatLongAltitudeToEcef(Eegeo::Space::LatLongAltitude::FromDegrees(37.78469,-122.40143, 400));
        m_debugRenderer.DrawText(ecefCenter3, "Debug Text!", 20, 4.0f);
    }

    
}

void DebugPrimitiveRenderingExample::Draw()
{


}

void DebugPrimitiveRenderingExample::Suspend()
{

}
}
