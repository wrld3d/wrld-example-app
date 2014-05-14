/*
 * ShowJavaPlaceJumpUIExample.h
 *
 *  Created on: Oct 30, 2013
 *      Author: kimbleoperations
 */

#ifndef SHOWJAVAPLACEJUMPUIEXAMPLE_H_
#define SHOWJAVAPLACEJUMPUIEXAMPLE_H_

#include "IExample.h"
#include "AndroidNativeState.h"
#include "LatLongAltitude.h"
#include "Camera.h"

#include <pthread.h>
#include <map>
#include <string>
#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_examples_PlaceJumpMenu_visitLocation(JNIEnv* jenv, jobject obj, jlong nativeAppWindowPtr, jstring location);
}

namespace Examples
{
    class ShowJavaPlaceJumpUIExample : public IExample
    {
    	struct ViewLocation
    	{
            Eegeo::Space::LatLongAltitude location;
    		float heading;
    		float distance;
            
    		ViewLocation(): location(0,0,0)
    		{
                location = Eegeo::Space::LatLongAltitude::FromDegrees(0, 0, 0);
            }

    		ViewLocation(float lat, float lon, float alt, float heading, float distance) : location(0,0,0)
            {
                location = Eegeo::Space::LatLongAltitude::FromDegrees(lat, lon, alt);
                this->heading = heading;
                this->distance = distance;
            }
        };

    	std::map<std::string, ViewLocation> m_locations;
    	AndroidNativeState& m_nativeState;
        Eegeo::Camera::ICameraJumpController& m_cameraJumpController;

    	jclass m_placeJumpMenuClass;
    	jobject m_placeJumpMenu;

    	pthread_mutex_t m_mutex;
    	ViewLocation* m_pTargetLocation;

    public:
    	ShowJavaPlaceJumpUIExample(
    			AndroidNativeState& pNativeState,
    			Eegeo::Camera::ICameraJumpController& cameraJumpController);

    	void JumpToLocation(const std::string& location);
        void Start();
        void Update(float dt);
        void Draw() {}
        void Suspend();
    };
}

#endif /* SHOWJAVAPLACEJUMPUIEXAMPLE_H_ */
