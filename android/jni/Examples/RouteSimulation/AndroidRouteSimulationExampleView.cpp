// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteSimulationExampleView.h"
#include "UIHelpers.h"
#include "AndroidRouteSimulationProxy.h"

using namespace Examples;

namespace Examples
{
AndroidRouteSimulationExampleView::AndroidRouteSimulationExampleView(
    AndroidNativeState& androidNativeState,
    bool usingFollowCamera)
	: m_nativeState(androidNativeState)
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the java RouteSimulationExampleHud class
	jstring strClassName = env->NewStringUTF("com/eegeo/examples/routesimulation/RouteSimulationExampleHud");
	jclass routeSimulationExampleHudClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	//create a persistent reference to the class
	m_routeSimulationExampleHudClass = static_cast<jclass>(env->NewGlobalRef(routeSimulationExampleHudClass));

	//get the constructor for the RouteSimulationExampleHud, which takes the activity, a pointer to 'this' as
	//a parameter, and a flag to indicate if currently in follow mode.
	jmethodID routeSimulationExampleHudConstructor = env->GetMethodID(routeSimulationExampleHudClass, "<init>", "(Lcom/eegeo/MainActivity;JZ)V");

	jobject instance = env->NewObject(
	                       m_routeSimulationExampleHudClass,
	                       routeSimulationExampleHudConstructor,
	                       m_nativeState.activity,
	                       (jlong)(this),
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

