#ifndef __Mapply__AppOnMap__
#define __Mapply__AppOnMap__

#include "IAppOnMap.h"
#include "EegeoWorld.h"
#include "RenderContext.h"
#include "NewGlobeCamera.h"

class MyApp : public Eegeo::IAppOnMap
{
public:
    Eegeo::Camera::NewGlobeCamera* pGlobeCamera;
    
    MyApp(Eegeo::Camera::NewGlobeCamera* pGlobeCamera):pGlobeCamera(pGlobeCamera) { }
    ~MyApp() { }
    
    void OnStart ()
    {
        float interestPointLatitudeDegrees = 37.7858f;
        float interestPointLongitudeDegrees = -122.401f;
        float interestPointAltitudeMeters = 2.7;
        
        Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude(interestPointLatitudeDegrees,
                                                                               interestPointLongitudeDegrees,
                                                                               interestPointAltitudeMeters,
                                                                               Eegeo::Space::LatLongUnits::Degrees);
        
        World().GetCameraModel().SetWorldPosition(location.ToECEF());
        
        float cameraControllerOrientationDegrees = 0.0f;
        float cameraControllerDistanceFromInterestPointMeters = 1781.0f;
        
        pGlobeCamera->SetInterestHeadingDistance(location,
                                                 cameraControllerOrientationDegrees,
                                                 cameraControllerDistanceFromInterestPointMeters);
    }
    
    void Update (float dt)
    {
        World().Update(dt);
    }
    
    void Draw (float dt)
    {
        Eegeo::Rendering::GLState& glState = World().GetRenderContext().GLState();
        glState.ClearColor(0.8f, 0.8f, 0.8f, 1.f);
        World().Draw(dt);
    }
    
    void Event_TouchRotate 			(const AppInterface::RotateData& data) { World().GetCameraController().Event_TouchRotate(data); }
    void Event_TouchRotate_Start	(const AppInterface::RotateData& data) { World().GetCameraController().Event_TouchRotate_Start(data); }
    void Event_TouchRotate_End 		(const AppInterface::RotateData& data) { World().GetCameraController().Event_TouchRotate_End(data); }
    
    void Event_TouchPinch 			(const AppInterface::PinchData& data) { World().GetCameraController().Event_TouchPinch(data); }
    void Event_TouchPinch_Start 	(const AppInterface::PinchData& data) { World().GetCameraController().Event_TouchPinch_Start(data); }
    void Event_TouchPinch_End 		(const AppInterface::PinchData& data) { World().GetCameraController().Event_TouchPinch_End(data); }
    
    void Event_TouchPan				(const AppInterface::PanData& data) { World().GetCameraController().Event_TouchPan(data); }
    void Event_TouchPan_Start		(const AppInterface::PanData& data) { World().GetCameraController().Event_TouchPan_Start(data); }
    void Event_TouchPan_End 		(const AppInterface::PanData& data) { World().GetCameraController().Event_TouchPan_End(data); }
    
    void Event_TouchTap 			(const AppInterface::TapData& data) { World().GetCameraController().Event_TouchTap(data); }
    void Event_TouchDoubleTap		(const AppInterface::TapData& data) { World().GetCameraController().Event_TouchDoubleTap(data); }
    
    void Event_TouchDown 			(const AppInterface::TouchData& data) { World().GetCameraController().Event_TouchDown(data); }
    void Event_TouchMove 			(const AppInterface::TouchData& data) { World().GetCameraController().Event_TouchMove(data); }
    void Event_TouchUp 				(const AppInterface::TouchData& data) { World().GetCameraController().Event_TouchUp(data); }
};

#endif /* defined(__Mapply__AppOnMap__) */
