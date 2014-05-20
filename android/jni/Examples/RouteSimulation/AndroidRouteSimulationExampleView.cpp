//
//  AndroidRouteSimulationExampleView.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "AndroidRouteSimulationExampleView.h"
#include "UIHelpers.h"

using namespace Examples;

namespace Examples
{
	AndroidRouteSimulationExampleView::AndroidRouteSimulationExampleView(
			AndroidNativeState& androidNativeState,
			UiThreadToNativeThreadTaskQueue& uiToNativeQueue,
			bool usingFollowCamera)
    : m_nativeState(androidNativeState)
	, m_uiToNativeQueue(uiToNativeQueue)
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
    
    void AndroidRouteSimulationExampleView::PostWorkToNative(UiThreadToNativeThreadTaskQueue::IBufferedWork* pWork)
    {
    	m_uiToNativeQueue.PostWork(pWork);
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

namespace
{
	class RouteSimulationBufferedWorkItem : public UiThreadToNativeThreadTaskQueue::IBufferedWork
	{
		typedef void (AndroidRouteSimulationExampleView::*Callback)();
		Callback m_callback;
        AndroidRouteSimulationExampleView* m_pView;

	public:
		RouteSimulationBufferedWorkItem(AndroidRouteSimulationExampleView* pView, Callback callback)
		: m_pView(pView)
		, m_callback(callback) { }

		void DoWork() {
			(m_pView->*m_callback)();
			delete this;
		}
	};
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleFollowCamera(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* example = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	example->PostWorkToNative(new RouteSimulationBufferedWorkItem(example, &AndroidRouteSimulationExampleView::ToggleFollowCamera));
}


JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ChangeFollowDirection(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* example = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	example->PostWorkToNative(new RouteSimulationBufferedWorkItem(example, &AndroidRouteSimulationExampleView::ToggleCameraDirection));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_IncreaseSpeedFollowed(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* example = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	example->PostWorkToNative(new RouteSimulationBufferedWorkItem(example, &AndroidRouteSimulationExampleView::IncreaseSpeed));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_DecreaseSpeedFollowed(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* example = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	example->PostWorkToNative(new RouteSimulationBufferedWorkItem(example, &AndroidRouteSimulationExampleView::DecreaseSpeed));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleDirectFollow(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* example = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	example->PostWorkToNative(new RouteSimulationBufferedWorkItem(example, &AndroidRouteSimulationExampleView::ToggleRotateToFollow));
}

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteSimulationExampleHud_ToggleSideOfRoadToDriveOn(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::AndroidRouteSimulationExampleView* example = (Examples::AndroidRouteSimulationExampleView*)(nativeObjectPtr);
	example->PostWorkToNative(new RouteSimulationBufferedWorkItem(example, &AndroidRouteSimulationExampleView::ChangeSideOfRoad));
}

