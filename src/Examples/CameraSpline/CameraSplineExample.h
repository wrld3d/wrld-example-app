// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__CameraSplineExample__
#define __ExampleApp__CameraSplineExample__

#include "IExample.h"
#include "Camera.h"
#include "Geometry.h"
#include "Streaming.h"

namespace Examples
{
/*!
 *  CameraSplineExample demonstrates a camera controller that can animate the camera along a spline
 */
class CameraSplineExample : public IExample
{
private:
	
    Eegeo::EegeoWorld& m_world;
    Eegeo::Streaming::ResourceCeilingProvider& m_resourceCeilingProvider;
    Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
    
    Eegeo::Geometry::CatmullRomSpline* m_pPositionSpline;
	Eegeo::Geometry::CatmullRomSpline* m_pTargetSpline;
    Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController* m_pSplineCameraController;
    
public:
	CameraSplineExample(Eegeo::EegeoWorld& eegeoWorld,
                        Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                        Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider);
    
	static std::string GetName()
	{
		return "CameraSplineExample";
	}
	std::string Name() const
	{
		return GetName();
	}
    
	void Start();
	void EarlyUpdate(float dt) {};
	void Update(float dt) { }
	void Draw() {}
	void Suspend();
    
	void UpdateCamera(Eegeo::Camera::GlobeCamera::GlobeCameraController* pGlobeCameraController,
	                  Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* pCameraTouchController,
	                  float dt);
};
}

#endif /* defined(__ExampleApp__CameraSplineExample__) */
