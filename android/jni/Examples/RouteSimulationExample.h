/*
 * RouteSimulationExample.h
 *
 *  Created on: Nov 25, 2013
 *      Author: kimbleoperations
 */

#ifndef ROUTESIMULATIONEXAMPLE_H_
#define ROUTESIMULATIONEXAMPLE_H_

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "RouteBuilder.h"
#include "Route.h"
#include "RouteStyle.h"
#include "RouteSimulationService.h"
#include "RouteSimulationSession.h"
#include "RouteSimulationViewService.h"
#include "SphereMesh.h"
#include "RouteSimulationModelBinding.h"
#include "RouteSimulationGlobeCameraController.h"
#include "RouteSimulationGlobeCameraControllerFactory.h"
#include "GLState.h"
#include "IFileIO.h"
#include "ITextureFileLoader.h"
#include "Model.h"
#include "Node.h"
#include "GlobeCameraController.h"
#include "EegeoWorld.h"
#include "IInterestPointProvider.h"
#include "AndroidNativeState.h"
#include "IdentityRouteThicknessPolicy.h"
#include "IRouteSimulationSessionObserver.h"

namespace Examples
{
	class RouteSimulationExampleObserver : public Eegeo::Routes::Simulation::IRouteSimulationSessionObserver
	{
	public:
		RouteSimulationExampleObserver(
									   Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* pModelBinding,
									   Eegeo::Model* pModel)
		: m_pModelBinding(pModelBinding)
		, m_pModel(pModel)
		{
		}

		void OnLinkReached(const Eegeo::Routes::Simulation::RouteSimulationSession& session) const;

	private:
		Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pModelBinding;
		Eegeo::Model* m_pModel;
		Eegeo::Node* GetRandomModelNode() const;
	};

    class RouteSimulationExample : public IExample
    {
    private:
        Eegeo::Routes::RouteService& m_routeService;
        Eegeo::Routes::Simulation::RouteSimulationService& m_routeSimulationService;
        Eegeo::Routes::Simulation::View::RouteSimulationViewService& m_routeSimulationViewService;
        Eegeo::Rendering::GLState& m_glState;
        Eegeo::Helpers::IFileIO& m_fileIO;
        Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& m_textureRequestor;
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_defaultCamera;
        Eegeo::Location::IInterestPointProvider& m_interestPointProvider;
    	AndroidNativeState& m_nativeState;
        Eegeo::EegeoWorld& m_world;
    	jclass m_routeSimulationExampleHudClass;
    	jobject m_routeSimulationExampleHud;

        bool m_initialised;
        bool m_usingFollowCamera;
        Eegeo::Model* m_pModel;
        Eegeo::Routes::Route* m_route;
        Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;

        RouteSimulationExampleObserver* m_pExampleObserver;

        Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCycle;
        Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionAlternatingSpeedChanger;
        Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCamera;

        float m_linkSpeedMultiplier;

        Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCycleSession;
        Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForOscillatingSession;
        Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCameraSession;

        Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory m_routeSimulationGlobeCameraControllerFactory;
        Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraController* m_pRouteSessionFollowCameraController;

    public:
        RouteSimulationExample(Eegeo::Routes::RouteService& routeService,
                               Eegeo::Routes::Simulation::RouteSimulationService& routeSimulationService,
                               Eegeo::Routes::Simulation::View::RouteSimulationViewService& routeSimulationViewService,
                               Eegeo::Rendering::GLState& glState,
                               Eegeo::Helpers::IFileIO& fileIO,
                               Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
                               Eegeo::Camera::GlobeCamera::GlobeCameraController& defaultCamera,
                               Eegeo::Location::IInterestPointProvider& interestPointProvider,
                               Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory routeSimulationGlobeCameraControllerFactory,
                               AndroidNativeState& nativeState,
                               Eegeo::EegeoWorld& eegeoWorld);

        void Start() {}
        void EarlyUpdate(float dt);
        void Update(float dt);
        void Draw() {}
        void Suspend();

        bool Event_TouchRotate 			(const AppInterface::RotateData& data);
        bool Event_TouchRotate_Start	(const AppInterface::RotateData& data);
        bool Event_TouchRotate_End 		(const AppInterface::RotateData& data);

        bool Event_TouchPinch 			(const AppInterface::PinchData& data);
        bool Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
        bool Event_TouchPinch_End 		(const AppInterface::PinchData& data);

        bool Event_TouchPan				(const AppInterface::PanData& data);
        bool Event_TouchPan_Start		(const AppInterface::PanData& data);
        bool Event_TouchPan_End 		(const AppInterface::PanData& data);

        void ToggleFollowCamera();
        void ChangeFollowDirection();
        void IncreaseSpeedFollowed();
        void DecreaseSpeedFollowed();
        void ToggleDirectFollow();
        void ToggleSideOfRoadToDriveOn();

    private:

        void Initialise();

        void CreateAndBindUI();

        void TeardownUI();

        Eegeo::Routes::Route* BuildRoute() const;

        Eegeo::Model* LoadModelVehicleNodes(Eegeo::Node*& pVehicle1,
                                            Eegeo::Node*& pVehicle2,
                                            Eegeo::Node*& pVehicle3) const;
    };
}

#include <jni.h>

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

#endif /* ROUTESIMULATIONEXAMPLE_H_ */
