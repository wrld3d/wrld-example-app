// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidRouteMatchingExampleView.h"
#include "UIHelpers.h"
#include "IMessage.h"
#include "AndroidRouteMatchingProxy.h"

using namespace Examples;

namespace Examples
{
AndroidRouteMatchingExampleView::AndroidRouteMatchingExampleView(
    AndroidNativeState& androidNativeState)
	: m_nativeState(androidNativeState)
{
	//get an env for the current thread
	//
	//AndroidSafeNativeThreadAttachment will detach the thread if required at the end of the method
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//get the java RouteMatchingExampleHud class
	jstring strClassName = env->NewStringUTF("com/eegeo/examples/RouteMatchingExampleHud");
	jclass routeMatchingExampleHudClass = m_nativeState.LoadClass(env, strClassName);
	env->DeleteLocalRef(strClassName);

	//create a persistent reference to the class
	m_routeMatchingExampleHudClass = static_cast<jclass>(env->NewGlobalRef(routeMatchingExampleHudClass));

	//get the constructor for the RouteMatchingExampleHud, which takes the activity, a pointer to 'this' as
	//a parameter, and a flag to indicate if currently in follow mode.
	jmethodID routeMatchingExampleHudConstructor = env->GetMethodID(routeMatchingExampleHudClass, "<init>", "(Lcom/eegeo/MainActivity;J)V");

	jobject instance = env->NewObject(
	                       m_routeMatchingExampleHudClass,
	                       routeMatchingExampleHudConstructor,
	                       m_nativeState.activity,
	                       (jlong)(this));

	m_routeMatchingExampleHud = env->NewGlobalRef(instance);
}

AndroidRouteMatchingExampleView::~AndroidRouteMatchingExampleView()
{
	AndroidSafeNativeThreadAttachment attached(m_nativeState);
	JNIEnv* env = attached.envForThread;

	//Get a reference to the 'removeHud' method and call it to remove the HUD.
	jmethodID removeHudMethod = env->GetMethodID(m_routeMatchingExampleHudClass, "removeHud", "()V");
	env->CallVoidMethod(m_routeMatchingExampleHud, removeHudMethod);

	//Destroy the cached global references.
	env->DeleteGlobalRef(m_routeMatchingExampleHud);
	env->DeleteGlobalRef(m_routeMatchingExampleHudClass);
}

void AndroidRouteMatchingExampleView::AddMatchingToggledHandler(IUIActionHandler& handler)
{
	m_matchingToggledHandlers.push_back(&handler);
}

void AndroidRouteMatchingExampleView::RemoveMatchingToggledHandler(IUIActionHandler& handler)
{
	RemoveFrom(m_matchingToggledHandlers, &handler);
}

void AndroidRouteMatchingExampleView::ToggleMatching()
{
	InvokeAllHandlers(m_matchingToggledHandlers);
}
}
