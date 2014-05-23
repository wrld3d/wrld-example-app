//
//  AndroidRouteMatchingExampleView.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "AndroidRouteMatchingExampleView.h"
#include "UIHelpers.h"
#include "IMessage.h"
#include "AndroidRouteMatchingProxy.h"

using namespace Examples;

namespace Examples
{
	AndroidRouteMatchingExampleView::AndroidRouteMatchingExampleView(
			AndroidNativeState& androidNativeState,
			AndroidRouteMatchingProxy *pProxy)
    : m_nativeState(androidNativeState)
	, m_pProxy(pProxy)
    {
		Eegeo_ASSERT(pProxy != NULL, "AndroidRouteMatchingExampleView pProxy must be non-null.\n");

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
		jmethodID routeMatchingExampleHudConstructor = env->GetMethodID(routeMatchingExampleHudClass, "<init>", "(Lcom/eegeo/MainActivity;JJ)V");

		//construct an instance of the RouteMatchingExampleHud, and create and cache a persistent reference to it.
		//we will make calls on to this instance, and it will add elements to the UI for us form Java.
		jlong pThis = (jlong)(this);

		jobject instance = env->NewObject(
				m_routeMatchingExampleHudClass,
				routeMatchingExampleHudConstructor,
	    		m_nativeState.activity,
	    		pThis,
	    		(jlong)(m_pProxy));

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

	    Eegeo_DELETE m_pProxy;
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
