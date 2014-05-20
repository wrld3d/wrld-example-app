//
//  AndroidRouteSimulationExampleView.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__AndroidRouteSimulationExampleView__
#define __ExampleApp__AndroidRouteSimulationExampleView__

#include "Types.h"
#include "IRouteSimulationExampleView.h"
#include "AndroidNativeState.h"
#include "UiThreadToNativeThreadTaskQueue.h"
#include <vector>
#include <jni.h>

namespace Examples
{
    class AndroidRouteSimulationExampleView : public IRouteSimulationExampleView, private Eegeo::NonCopyable
    {
        std::vector<IUIActionHandler*> m_followCameraToggledHandlers;
        std::vector<IUIActionHandler*> m_directionChangedHandlers;
        std::vector<IUIActionHandler*> m_increaseSpeedHandlers;
        std::vector<IUIActionHandler*> m_decreaseSpeedHandlers;
        std::vector<IUIActionHandler*> m_rotateToFollowToggledHandlers;
        std::vector<IUIActionHandler*> m_roadSideChangedHandlers;

    	AndroidNativeState& m_nativeState;
    	jclass m_routeSimulationExampleHudClass;
    	jobject m_routeSimulationExampleHud;
    	UiThreadToNativeThreadTaskQueue& m_uiToNativeQueue;
        
    public:
        AndroidRouteSimulationExampleView(
        		AndroidNativeState& androidNativeState,
        		UiThreadToNativeThreadTaskQueue& uiToNativeQueue,
        		bool usingFollowCamera);
        
        ~AndroidRouteSimulationExampleView();
        
        void AddFollowCameraToggledHandler(IUIActionHandler& handler);

        void RemoveFollowCameraToggledHandler(IUIActionHandler& handler);

        void ToggleFollowCamera();

        void AddFollowCameraDirectionChangedHandler(IUIActionHandler& handler);

        void RemoveFollowCameraDirectionChangedHandler(IUIActionHandler& handler);

        void ToggleCameraDirection();

        void AddIncreaseSpeedHandler(IUIActionHandler& handler);

        void RemoveIncreaseSpeedHandler(IUIActionHandler& handler);

        void IncreaseSpeed();

        void AddDecreaseSpeedHandler(IUIActionHandler& handler);

        void RemoveDecreaseSpeedHandler(IUIActionHandler& handler);

        void DecreaseSpeed();

        void AddRotateToFollowToggledHandler(IUIActionHandler& handler);

        void RemoveRotateToFollowToggledHandler(IUIActionHandler& handler);

        void ToggleRotateToFollow();

        void AddSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler);

        void RemoveSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler);

        void ChangeSideOfRoad();

    	void PostWorkToNative(UiThreadToNativeThreadTaskQueue::IBufferedWork* work);
    };
}

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleFollowCamera(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ChangeFollowDirection(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_IncreaseSpeedFollowed(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_DecreaseSpeedFollowed(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleDirectFollow(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);

	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleSideOfRoadToDriveOn(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);
}

#endif /* defined(__ExampleApp__AndroidRouteSimulationExampleView__) */
