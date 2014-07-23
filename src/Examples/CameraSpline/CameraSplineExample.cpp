// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraSplineExample.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "CatmullRomSpline.h"
#include "CameraSplinePlaybackController.h"
#include "ResourceCeilingProvider.h"
#include "GlobeCameraController.h"
#include "GlobeCameraTouchController.h"
#include "EegeoWorld.h"

namespace Examples
{
    CameraSplineExample::CameraSplineExample(Eegeo::EegeoWorld& eegeoWorld,
                                             Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                             Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider)
    : m_world(eegeoWorld)
    , m_globeCameraController(globeCameraController)
    , m_resourceCeilingProvider(resourceCeilingProvider)
    {
        
    }
    
    void CameraSplineExample::Start()
    {
        // Initialise our spline paths
        m_pPositionSpline = new Eegeo::Geometry::CatmullRomSpline();
        m_pTargetSpline = new Eegeo::Geometry::CatmullRomSpline();
        
        // The CameraSplinePlaybackController takes in two splines
        // One defines the camera's movement, the other defines what it looks at
        // For this example, we'll do a simple path around San Francisco.
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.777145, -122.402181, 600).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.789423, -122.392311, 600).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.804480, -122.412223, 600).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.804276, -122.428188, 650).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.808141, -122.448787, 650).ToECEF());
        
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.781215, -122.407116, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.789389, -122.395658, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.802886, -122.412995, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.802241, -122.429776, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.803461, -122.447843, 0).ToECEF());
        
        // Initialise the camera controller and assign which splines we want to use for the animation
        m_pSplineCameraController = new Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController(m_resourceCeilingProvider);
        m_pSplineCameraController->SetSplines(m_pPositionSpline, m_pTargetSpline);
        
        // Select a playback speed
        m_pSplineCameraController->SetPlaybackSpeed(0.03);
        
        // Loop the animation
        m_pSplineCameraController->SetLooped(true);
        
        // Tell the SDK that we want to use the animated CameraSplinePlaybackController's camera for viewing the world.
        m_world.SetCamera(m_pSplineCameraController->GetCamera());
        
        // Start the animation
        m_pSplineCameraController->Begin();
    }
    
    void CameraSplineExample::Suspend()
    {
        // Switch back to the normal camera.
        m_world.SetCamera(m_globeCameraController.GetCamera());
        
        // Stop the animation
        m_pSplineCameraController->Reset();
        
        // Cleanup
        delete m_pSplineCameraController;
        delete m_pPositionSpline;
        delete m_pTargetSpline;
    }
    
    void CameraSplineExample::UpdateCamera(Eegeo::Camera::GlobeCamera::GlobeCameraController *pGlobeCameraController, Eegeo::Camera::GlobeCamera::GlobeCameraTouchController *pCameraTouchController, float dt)
    {
        // Update the camera spline animation
        m_pSplineCameraController->Update(dt);
    }
}