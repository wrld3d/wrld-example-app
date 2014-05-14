//
//  RouteMatchingExample.h
//  ExampleApp
//
//  Created by Scott on 16/01/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteMatchingExample__
#define __ExampleApp__RouteMatchingExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "Route.h"
#include "EegeoWorld.h"
#include "IdentityRouteThicknessPolicy.h"
#include "AndroidNativeState.h"
#include "UiThreadToNativeThreadTaskQueue.h"

namespace Examples
{
    class RouteMatchingExample : public IExample
    {
    private:
        Eegeo::Routes::RouteService& m_routeService;
        Eegeo::EegeoWorld& m_world;
    	AndroidNativeState& m_nativeState;
    	jclass m_routeMatchingExampleHudClass;
    	jobject m_routeMatchingExampleHud;
        
        bool m_createdRoutes;
        bool m_routesMatchedToNavigationGraph;
        std::vector<Eegeo::Routes::Route*> m_routes;
        Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;

    	UiThreadToNativeThreadTaskQueue m_uiToNativeQueue;

        void CreateRoutes(bool shouldMatchToNavigationGraph);
        void DestroyRoutes();
        void CreateAndBindUI();
        void TeardownUI();
        
    public:
        RouteMatchingExample(Eegeo::Routes::RouteService& routeService,
                             Eegeo::EegeoWorld& eegeoWorld,
                             AndroidNativeState& nativeState);

    	void PostWorkToNative(UiThreadToNativeThreadTaskQueue::IBufferedWork* work);

        void Start() {}
        void Update(float dt);
        void Draw() {}
        void Suspend();
        
        void ToggleMatching();
    };
}

#include <jni.h>

extern "C"
{
	JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
			JNIEnv* jenv, jobject obj,
			jlong nativeObjectPtr);
}

#endif /* defined(__ExampleApp__RouteMatchingExample__) */
