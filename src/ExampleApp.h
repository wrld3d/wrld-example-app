#ifndef __ExampleApp__ExampleApp__
#define __ExampleApp__ExampleApp__

#include "GlobeCamera.h"
#include "EegeoWorld.h"
#include "ExampleController.h"

class ExampleApp
{
private:
	Eegeo::Camera::GlobeCamera::GlobeCameraController* m_globeCameraController;
	Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_cameraTouchController;
	Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider& m_globeCameraInterestPointProvider;
	Eegeo::EegeoWorld* m_pWorld;
	Examples::ExampleController& m_exampleController;

	Eegeo::EegeoWorld& World()
	{
		return * m_pWorld;
	}

public:
	ExampleApp(Eegeo::EegeoWorld* pWorld,
	           Eegeo::Camera::GlobeCamera::GlobeCameraInterestPointProvider& globeCameraInterestPointProvider,
	           Examples::ExampleController& exampleController);

	~ExampleApp();

	void OnPause();

	void OnResume();

	void Update (float dt);

	void Draw (float dt);

	Eegeo::Camera::GlobeCamera::GlobeCameraController& GetCameraController()
	{
		return *m_globeCameraController;
	}

	Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetTouchController()
	{
		return *m_cameraTouchController;
	}

	void Event_TouchRotate 			(const AppInterface::RotateData& data);
	void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
	void Event_TouchRotate_End 		(const AppInterface::RotateData& data);

	void Event_TouchPinch 			(const AppInterface::PinchData& data);
	void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
	void Event_TouchPinch_End 		(const AppInterface::PinchData& data);

	void Event_TouchPan				(const AppInterface::PanData& data);
	void Event_TouchPan_Start		(const AppInterface::PanData& data);
	void Event_TouchPan_End 		(const AppInterface::PanData& data);

	void Event_TouchTap 			(const AppInterface::TapData& data);
	void Event_TouchDoubleTap		(const AppInterface::TapData& data);

	void Event_TouchDown 			(const AppInterface::TouchData& data);
	void Event_TouchMove 			(const AppInterface::TouchData& data);
	void Event_TouchUp 				(const AppInterface::TouchData& data);
};

#endif /* defined(__ExampleApp__ExampleApp__) */
