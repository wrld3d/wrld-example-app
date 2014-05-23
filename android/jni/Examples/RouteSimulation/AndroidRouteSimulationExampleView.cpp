//
//  AndroidRouteSimulationExampleView.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "AndroidRouteSimulationExampleView.h"
#include "UIHelpers.h"
#include "IAndroidExampleMessage.h"

using namespace Examples;

namespace Examples
{
	AndroidRouteSimulationExampleView::AndroidRouteSimulationExampleView(
			AndroidNativeState& androidNativeState,
        	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue,
			bool usingFollowCamera)
    : m_nativeState(androidNativeState)
	, m_messageQueue(messageQueue)
    {
		//get an env for the current thread
		//
		//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
		AndroidSafeNativeThreadAttachment attached(m_nativeState);
		JNIEnv* env = attached.envForThread;

		//get the java RouteSimulationExampleHud class
		jstring strClassName = env->NewStringUTF("com/eegeo/examples/RouteSimulationExampleHud");
		jclass routeSimulationExampleHudClass = m_nativeState.LoadClass(env, strClassName);
		env->DeleteLocalRef(strClassName);

		//create a persistent reference to the class
		m_routeSimulationExampleHudClass = static_cast<jclass>(env->NewGlobalRef(routeSimulationExampleHudClass));

		//get the constructor for the RouteSimulationExampleHud, which takes the activity, a pointer to 'this' as
		//a parameter, and a flag to indicate if currently in follow mode.
		jmethodID routeSimulationExampleHudConstructor = env->GetMethodID(routeSimulationExampleHudClass, "<init>", "(Lcom/eegeo/MainActivity;JZ)V");

		//construct an instance of the RouteSimulationExampleHud, and create and cache a persistent reference to it.
		//we will make calls on to this instance, and it will add elements to the UI for us form Java.
		jlong pThis = (jlong)(this);

		jobject instance = env->NewObject(
	    		m_routeSimulationExampleHudClass,
	    		routeSimulationExampleHudConstructor,
	    		m_nativeState.activity,
	    		pThis,
	    		usingFollowCamera);

	    m_routeSimulationExampleHud = env->NewGlobalRef(instance);
    }
    
	AndroidRouteSimulationExampleView::~AndroidRouteSimulationExampleView()
    {
		AndroidSafeNativeThreadAttachment attached(m_nativeState);
		JNIEnv* env = attached.envForThread;

		//Get a reference to the 'removeHud' method and call it to remove the HUD.
		jmethodID removeHudMethod = env->GetMethodID(m_routeSimulationExampleHudClass, "removeHud", "()V");
		env->CallVoidMethod(m_routeSimulationExampleHud, removeHudMethod);

		//Destroy the cached global references.
	    env->DeleteGlobalRef(m_routeSimulationExampleHud);
	    env->DeleteGlobalRef(m_routeSimulationExampleHudClass);
    }
    
	void AndroidRouteSimulationExampleView::SendMessage(IAndroidExampleMessage* pMessage)
    {
    	m_messageQueue.Enqueue(pMessage);
    }

    void AndroidRouteSimulationExampleView::AddFollowCameraToggledHandler(IUIActionHandler& handler)
    {
        m_followCameraToggledHandlers.push_back(&handler);
    }

    void AndroidRouteSimulationExampleView::RemoveFollowCameraToggledHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_followCameraToggledHandlers, &handler);
    }

    void AndroidRouteSimulationExampleView::ToggleFollowCamera()
    {
        InvokeAllHandlers(m_followCameraToggledHandlers);
    }

    void AndroidRouteSimulationExampleView::AddFollowCameraDirectionChangedHandler(IUIActionHandler& handler)
    {
        m_directionChangedHandlers.push_back(&handler);
    }

    void AndroidRouteSimulationExampleView::RemoveFollowCameraDirectionChangedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_directionChangedHandlers, &handler);
    }

    void AndroidRouteSimulationExampleView::ToggleCameraDirection()
    {
        InvokeAllHandlers(m_directionChangedHandlers);
    }

    void AndroidRouteSimulationExampleView::AddIncreaseSpeedHandler(IUIActionHandler& handler)
    {
        m_increaseSpeedHandlers.push_back(&handler);
    }

    void AndroidRouteSimulationExampleView::RemoveIncreaseSpeedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_increaseSpeedHandlers, &handler);
    }

    void AndroidRouteSimulationExampleView::IncreaseSpeed()
    {
        InvokeAllHandlers(m_increaseSpeedHandlers);
    }

    void AndroidRouteSimulationExampleView::AddDecreaseSpeedHandler(IUIActionHandler& handler)
    {
        m_decreaseSpeedHandlers.push_back(&handler);
    }

    void AndroidRouteSimulationExampleView::RemoveDecreaseSpeedHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_decreaseSpeedHandlers, &handler);
    }

    void AndroidRouteSimulationExampleView::DecreaseSpeed()
    {
        InvokeAllHandlers(m_decreaseSpeedHandlers);
    }

    void AndroidRouteSimulationExampleView::AddRotateToFollowToggledHandler(IUIActionHandler& handler)
    {
        m_rotateToFollowToggledHandlers.push_back(&handler);
    }

    void AndroidRouteSimulationExampleView::RemoveRotateToFollowToggledHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_rotateToFollowToggledHandlers, &handler);
    }

    void AndroidRouteSimulationExampleView::ToggleRotateToFollow()
    {
        InvokeAllHandlers(m_rotateToFollowToggledHandlers);
    }

    void AndroidRouteSimulationExampleView::AddSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)
    {
        m_roadSideChangedHandlers.push_back(&handler);
    }

    void AndroidRouteSimulationExampleView::RemoveSideOfRoadToDriveOnToggledHandler(IUIActionHandler& handler)
    {
        RemoveFrom(m_roadSideChangedHandlers, &handler);
    }

    void AndroidRouteSimulationExampleView::ChangeSideOfRoad()
    {
        InvokeAllHandlers(m_roadSideChangedHandlers);
    }
}

