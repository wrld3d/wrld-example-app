// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef SHOWJAVAPLACEJUMPUIEXAMPLE_H_
#define SHOWJAVAPLACEJUMPUIEXAMPLE_H_

#include "IExample.h"
#include "AndroidNativeState.h"
#include "LatLongAltitude.h"
#include "Camera.h"
#include "GlobeCameraController.h"
#include "EcefTangentBasis.h"

#include <pthread.h>
#include <map>
#include <string>
#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_placejump_PlaceJumpMenuJniMethods_VisitLocation(JNIEnv* jenv, jobject obj, jlong nativeAppWindowPtr, jstring location);
}

namespace Examples
{
class ShowJavaPlaceJumpUIExample : public IExample
{
	struct ViewLocation
	{
		Eegeo::Space::LatLongAltitude m_location;
		float m_heading;
		float m_distance;

		ViewLocation(): m_location(0,0,0), m_distance(0), m_heading(0)
		{
			m_location = Eegeo::Space::LatLongAltitude::FromDegrees(0, 0, 0);
		}

		ViewLocation(float lat, float lon, float alt, float heading, float distance) : m_location(0,0,0)
		{
			m_location = Eegeo::Space::LatLongAltitude::FromDegrees(lat, lon, alt);
			m_heading = heading;
			m_distance = distance;
		}
	};

	std::map<std::string, ViewLocation> m_locations;
	AndroidNativeState& m_nativeState;
	Eegeo::Camera::ICameraJumpController& m_cameraJumpController;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;

	jclass m_placeJumpMenuClass;
	jobject m_placeJumpMenu;

	pthread_mutex_t m_mutex;
	ViewLocation* m_pTargetLocation;

public:
	ShowJavaPlaceJumpUIExample(
	    AndroidNativeState& pNativeState,
	    Eegeo::Camera::GlobeCamera::GlobeCameraController& cameraController,
	    Eegeo::Camera::ICameraJumpController& cameraJumpController);

	void JumpToLocation(const std::string& location);

	static std::string GetName()
	{
		return "ShowJavaPlaceJumpUIExample";
	}
	std::string Name() const
	{
		return GetName();
	}

	void Start();
	void Update(float dt);
	void Draw() {}
	void Suspend();
};
}

#endif /* SHOWJAVAPLACEJUMPUIEXAMPLE_H_ */
