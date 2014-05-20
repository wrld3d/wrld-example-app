//
//  AndroidRouteMatchingExampleView.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__AndroidRouteMatchingExampleView__
#define __ExampleApp__AndroidRouteMatchingExampleView__

#include "Types.h"
#include "IRouteMatchingExampleView.h"
#include "AndroidNativeState.h"
#include "UiThreadToNativeThreadTaskQueue.h"
#include <vector>
#include <jni.h>

namespace Examples
{
    class AndroidRouteMatchingExampleView : public IRouteMatchingExampleView, private Eegeo::NonCopyable
    {
        std::vector<IUIActionHandler*> m_matchingToggledHandlers;
    	AndroidNativeState& m_nativeState;
    	jclass m_routeMatchingExampleHudClass;
    	jobject m_routeMatchingExampleHud;
    	UiThreadToNativeThreadTaskQueue& m_uiToNativeQueue;
        
    public:
        AndroidRouteMatchingExampleView(AndroidNativeState& androidNativeState, UiThreadToNativeThreadTaskQueue& uiToNativeQueue);
        
        ~AndroidRouteMatchingExampleView();
        
        void AddMatchingToggledHandler(IUIActionHandler& handler);
        
        void RemoveMatchingToggledHandler(IUIActionHandler& handler);
        
        void ToggleMatching();

    	void PostWorkToNative(UiThreadToNativeThreadTaskQueue::IBufferedWork* work);
    };
}

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);
}

#endif /* defined(__ExampleApp__iOSRouteMatchingExampleView__) */
