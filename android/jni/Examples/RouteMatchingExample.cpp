//
//  RouteMatchingExample.cpp
//  ExampleApp
//
//  Created by Scott on 16/01/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "RouteMatchingExample.h"
#include "RouteBuilder.h"
#include "VectorMath.h"
#include "RouteStyle.h"

using namespace Examples;
using namespace Eegeo;
using namespace Eegeo::Routes;

RouteMatchingExample::RouteMatchingExample(RouteService& routeService,
                                           EegeoWorld& world,
                                           AndroidNativeState& nativeState)
:m_routeService(routeService)
,m_world(world)
,m_nativeState(nativeState)
,m_createdRoutes(false)
,m_routesMatchedToNavigationGraph(false)
{
    
}

void RouteMatchingExample::CreateRoutes(bool shouldMatchToNavigationGraph)
{
    // This function generates some routes, potentially matching them to the navigation graph based on the
    // value of the shouldMatchToNavigationGraph parameter. The API used here to build and submit the routes
    // is not explained as has been covered in RouteDrawingExample.cpp - please refer to this example for more
    // information about these API points at http://sdk.eegeo.com/developers/mobiledocs/routes
    
    const float halfWidth = 5.f;
    const float routeSpeedMetersPerSecond = 40.f;
    const Eegeo::v4 routeRed(1, 0, 0, 0.6f);
    const Eegeo::v4 routeGreen(0, 1, 0, 0.6f);
    const Eegeo::v4 routeBlue(0, 0, 1, 0.6f);
    const float altitudeMeters = 3.f;
    Eegeo::Routes::Style::RouteStyle hardJoinStyle(Eegeo::Routes::Style::RouteStyle::JoinStyleHard, m_routeThicknessPolicy);
    Eegeo::Routes::Style::RouteStyle arcJoinStyle(Eegeo::Routes::Style::RouteStyle::JoinStyleArc, m_routeThicknessPolicy);
    
    RouteBuilder builder;
    
    // Create a route on roads at the north coast of San Francisco at Fishermans wharf. This route
    // demonstrates fitting to the road graph
    //
    std::vector<RouteVertex> fishermansWharfPoints = builder.Start(routeRed, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
    .AddPoint(37.807173,-122.408929, altitudeMeters)
    .AddPoint(37.806982,-122.410527, altitudeMeters)
    .ChangeColor(routeGreen)
    .AddPoint(37.806059,-122.41035, altitudeMeters)
    .AddPoint(37.805847,-122.411986, altitudeMeters)
    .ChangeColor(routeRed)
    .AddPoint(37.805385,-122.411916, altitudeMeters)
    .AddPoint(37.805177,-122.413537, altitudeMeters)
    .ChangeColor(routeBlue)
    .AddPoint(37.805635,-122.413633, altitudeMeters)
    .AddPoint(37.80658,-122.413816, altitudeMeters)
    .FinishRoute();
    
    Route* route = m_routeService.CreateRoute(fishermansWharfPoints, hardJoinStyle, shouldMatchToNavigationGraph);
    m_routes.push_back(route);
    
    // Create a route at Buena Vista park in San Francisco - the park is on a hill, this example demonstrates
    // fitting to the road graph on elevated terrain.
    //
    std::vector<RouteVertex> buenaVistaPoints = builder.Start(routeBlue, halfWidth/2.f, routeSpeedMetersPerSecond, Routes::Road)
    .AddPoint(37.766088,-122.442888,altitudeMeters)
    .AddPoint(37.76597,-122.442698,altitudeMeters)
    .AddPoint(37.766037,-122.442576,altitudeMeters)
    .AddPoint(37.766129,-122.442381,altitudeMeters)
    .AddPoint(37.766171,-122.442263,altitudeMeters)
    .AddPoint(37.766307,-122.442053,altitudeMeters)
    .AddPoint(37.766667,-122.44175,altitudeMeters)
    .AddPoint(37.766945,-122.441635,altitudeMeters)
    .AddPoint(37.767274,-122.441549,altitudeMeters)
    .AddPoint(37.767683,-122.441276,altitudeMeters)
    .FinishRoute();
    
    m_routes.push_back(m_routeService.CreateRoute(buenaVistaPoints, arcJoinStyle, shouldMatchToNavigationGraph));
    
    // Create a route on Treasure Island in San Francisco. This route starts on the road network, but includes a
    // pedestrian section. The road vertices are colored red and the pedestrian section is colored blue. The
    // pedestrian section is not matched to any navigation graphs, while the road section is (if the value of
    // shouldMatchToNavigationGraph is true).
    //
    std::vector<RouteVertex> islandPoints = builder.Start(routeRed, halfWidth, routeSpeedMetersPerSecond, Routes::Road)
    .AddPoint(37.817416,-122.3681912, altitudeMeters)
    .AddPoint(37.818747,-122.369023, altitudeMeters)
    .AddPoint(37.818243,-122.370348, altitudeMeters)
    .AddPoint(37.820277,-122.3717, altitudeMeters)
    .AddPoint(37.820768,-122.370456, altitudeMeters)
    .AddPoint(37.822794,-122.371775, altitudeMeters)
    .ChangeClassification(Routes::Pedestrian)
    .ChangeColor(routeBlue)
    .AddPoint(37.822887,-122.371207, altitudeMeters)
    .AddPoint(37.822396,-122.370273, altitudeMeters)
    .AddPoint(37.824709,-122.370316, altitudeMeters)
    .FinishRoute();
    
    m_routes.push_back(m_routeService.CreateRoute(islandPoints, arcJoinStyle, shouldMatchToNavigationGraph));
    
    //We have created the routes so don't need to do so again.
    m_createdRoutes = true;
}

void RouteMatchingExample::DestroyRoutes()
{
    //Destroy all of the routes...
    for(std::vector<Route*>::iterator i = m_routes.begin(); i != m_routes.end(); ++ i)
    {
        //Destroy the route - we do not need to delete the route pointer ourselves, the API will handle this
        //as well as cleaning up associated views, etc.
        m_routeService.DestroyRoute(*i);
    }
    
    m_routes.clear();
    m_createdRoutes = false;
}

void RouteMatchingExample::Update(float dt)
{
    //Defer creating the routes until the loading state is over.
    if(m_world.Initialising()) {
        return;
    }
    
    //Just create the routes once.
    if(!m_createdRoutes)
    {
        CreateRoutes(m_routesMatchedToNavigationGraph);
        CreateAndBindUI();
    }

	m_uiToNativeQueue.TryExectuteBufferedWork();
}

void RouteMatchingExample::Suspend()
{
    DestroyRoutes();
    TeardownUI();
}

void RouteMatchingExample::ToggleMatching()
{
    m_routesMatchedToNavigationGraph = !m_routesMatchedToNavigationGraph;
    DestroyRoutes();
    CreateRoutes(m_routesMatchedToNavigationGraph);
}

void RouteMatchingExample::PostWorkToNative(UiThreadToNativeThreadTaskQueue::IBufferedWork* pWork)
{
	m_uiToNativeQueue.PostWork(pWork);
}

//Create some UI to let us toggle route matching
//
//The native Android UI performs JNI interop; see the documentation and examples at
//http://sdk.eegeo.com/developers/mobiledocs/native_android_ui for more information on how this
//works.
void RouteMatchingExample::CreateAndBindUI()
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

	//construct an instance of the RouteMatchingExampleHud, and create and cache a persistent reference to it.
	//we will make calls on to this instance, and it will add elements to the UI for us form Java.
	jlong pThis = (jlong)(this);

	jobject instance = env->NewObject(
			m_routeMatchingExampleHudClass,
			routeMatchingExampleHudConstructor,
    		m_nativeState.activity,
    		pThis);

	m_routeMatchingExampleHud = env->NewGlobalRef(instance);
}

void RouteMatchingExample::TeardownUI()
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

class ToggleRouteMatchingWorkItem : public UiThreadToNativeThreadTaskQueue::IBufferedWork
{
	Examples::RouteMatchingExample* m_pExample;

public:
	ToggleRouteMatchingWorkItem(Examples::RouteMatchingExample* pExample)
	: m_pExample(pExample) {
	}

	void DoWork() {
		//now we are executing on the main thread, so can safely read and write native structures
		m_pExample->ToggleMatching();

		// A little untidy, but we know it was dynamically allocated below in Java handler...
		delete this;
	}
};

JNIEXPORT void JNICALL Java_com_eegeo_examples_RouteMatchingExampleHud_ToggleRouteMatching(
		JNIEnv* jenv, jobject obj,
		jlong nativeObjectPtr)
{
	Examples::RouteMatchingExample* example = (Examples::RouteMatchingExample*)(nativeObjectPtr);;
	example->PostWorkToNative(new ToggleRouteMatchingWorkItem(example));
}
