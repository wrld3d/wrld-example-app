//
//  RouteSimulationExample.h
//  ExampleApp
//
//  Created by Scott on 21/11/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

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
#import <UIKit/UIKit.h>
#include "IdentityRouteThicknessPolicy.h"

namespace Examples
{
    class RouteSimulationExample : public IExample
    {
    private:
        Eegeo::Routes::RouteService& m_routeService;
        Eegeo::Routes::Simulation::RouteSimulationService& m_routeSimulationService;
        Eegeo::Routes::Simulation::View::RouteSimulationViewService& m_routeSimulationViewService;
        Eegeo::Rendering::GLState& m_glState;
        Eegeo::Helpers::IFileIO& m_fileIO;
        Eegeo::Helpers::ITextureFileLoader& m_textureLoader;
        Eegeo::Camera::GlobeCamera::GlobeCameraController& m_defaultCamera;
        Eegeo::Location::IInterestPointProvider& m_interestPointProvider;
        UIView* m_pView;
        Eegeo::EegeoWorld& m_world;
        
        bool m_initialised;
        bool m_usingFollowCamera;
        Eegeo::Model* m_pModel;
        Eegeo::Routes::Route* m_route;
        Eegeo::Routes::IdentityRouteThicknessPolicy m_routeThicknessPolicy;
        
        Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCycle;
        Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionAlternatingSpeedChanger;
        Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCamera;
        
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
                               Eegeo::Helpers::ITextureFileLoader& textureLoader,
                               Eegeo::Camera::GlobeCamera::GlobeCameraController& defaultCamera,
                               Eegeo::Location::IInterestPointProvider& interestPointProvider,
                               Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory routeSimulationGlobeCameraControllerFactory,
                               UIView* pView,
                               Eegeo::EegeoWorld& eegeoWorld);
        
        void Start() {}
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
