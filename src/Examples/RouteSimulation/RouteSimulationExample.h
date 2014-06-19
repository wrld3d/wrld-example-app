// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__RouteSimulationExample__
#define __ExampleApp__RouteSimulationExample__

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
#include "IdentityRouteThicknessPolicy.h"
#include "IRouteSimulationSessionObserver.h"
#include "IRouteSimulationExampleViewFactory.h"
#include "IRouteSimulationExampleView.h"
#include "UIActionHandler.h"

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
	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory& m_routeSimulationGlobeCameraControllerFactory;
	Eegeo::EegeoWorld& m_world;
	const IRouteSimulationExampleViewFactory& m_routeSimulationExampleViewFactory;
	IRouteSimulationExampleView* m_pRouteSimulationView;
	Examples::UIActionHandler<RouteSimulationExample> m_decreaseSpeedToggleHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_increaseSpeedToggleHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_followCameraToggleHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_rotateToFollowToggledHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_directionChangedHandler;
	Examples::UIActionHandler<RouteSimulationExample> m_roadSideChangedHandler;

	bool m_initialised;
	bool m_usingFollowCamera;
	Eegeo::Model* m_pModel;
	Eegeo::Routes::Route* m_pRoute;
	Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;

	Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCycle;
	Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionAlternatingSpeedChanger;
	Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCamera;

	Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCycleSession;
	Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForOscillatingSession;
	Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCameraSession;

	float m_linkSpeedMultiplier;


	Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraController* m_pRouteSessionFollowCameraController;

	RouteSimulationExampleObserver* m_pExampleObserver;
	GlobeCameraStateRestorer m_globeCameraStateRestorer;
public:
	RouteSimulationExample(Eegeo::Routes::RouteService& routeService,
	                       Eegeo::Routes::Simulation::RouteSimulationService& routeSimulationService,
	                       Eegeo::Routes::Simulation::View::RouteSimulationViewService& routeSimulationViewService,
	                       Eegeo::Rendering::GLState& glState,
	                       Eegeo::Helpers::IFileIO& fileIO,
	                       Eegeo::Rendering::AsyncTexturing::IAsyncTextureRequestor& textureRequestor,
	                       Eegeo::Camera::GlobeCamera::GlobeCameraController& defaultCamera,
	                       Eegeo::Location::IInterestPointProvider& interestPointProvider,
	                       Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory& routeSimulationGlobeCameraControllerFactory,
	                       const IRouteSimulationExampleViewFactory& routeSimulationExampleViewFactory,
	                       Eegeo::EegeoWorld& eegeoWorld);

	static std::string GetName()
	{
		return "RouteSimulationExample";
	}
	std::string Name() const
	{
		return GetName();
	}

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
	void ToggleRotateToFollow();
	void ToggleSideOfRoadToDriveOn();

private:

	void Initialise();

	void CreateAndBindUI();

	Eegeo::Routes::Route* BuildRoute() const;

	Eegeo::Model* LoadModelVehicleNodes(Eegeo::Node*& pVehicle1,
	                                    Eegeo::Node*& pVehicle2,
	                                    Eegeo::Node*& pVehicle3) const;
};
}

#endif /* defined(__ExampleApp__RouteSimulationExample__) */
