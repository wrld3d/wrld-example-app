//
//  RouteSimulationAnimationExample.h
//  ExampleApp
//
//  Created by Ian Hutchinson on 18/02/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__RouteSimulationAnimationExample__
#define __ExampleApp__RouteSimulationAnimationExample__

#include <vector>
#include "IExample.h"
#include "RouteService.h"
#include "RouteBuilder.h"
#include "Route.h"
#include "RouteStyle.h"
#include "RouteSimulationService.h"
#include "RouteSimulationSession.h"
#include "RouteSimulationViewService.h"
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
#include "IdentityRouteThicknessPolicy.h"

namespace Examples
{
    class RouteSimulationAnimationExample : public IExample
    {
    private:
        Eegeo::Routes::RouteService& m_routeService;
        Eegeo::Routes::Simulation::RouteSimulationService& m_routeSimulationService;
        Eegeo::Routes::Simulation::View::RouteSimulationViewService& m_routeSimulationViewService;
        Eegeo::Rendering::GLState& m_glState;
        Eegeo::Helpers::IFileIO& m_fileIO;
        Eegeo::Helpers::ITextureFileLoader& m_textureLoader;
        Eegeo::EegeoWorld& m_world;
        float m_modelAnimationSpeed;
        
        bool m_initialised;
        Eegeo::Model* m_pModel;
        Eegeo::Routes::Route* m_route;
        Eegeo::Routes::Style::Thickness::IdentityRouteThicknessPolicy m_routeThicknessPolicy;
    
        Eegeo::Routes::Simulation::RouteSimulationSession* m_pSessionCamera;
        
        Eegeo::Routes::Simulation::View::RouteSimulationModelBinding* m_pViewBindingForCameraSession;
        
        Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory m_routeSimulationGlobeCameraControllerFactory;
        Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraController* m_pRouteSessionFollowCameraController;
        
    public:
        RouteSimulationAnimationExample(Eegeo::Routes::RouteService& routeService,
                                        Eegeo::Routes::Simulation::RouteSimulationService& routeSimulationService,
                                        Eegeo::Routes::Simulation::View::RouteSimulationViewService& routeSimulationViewService,
                                        Eegeo::Rendering::GLState& glState,
                                        Eegeo::Helpers::IFileIO& fileIO,
                                        Eegeo::Helpers::ITextureFileLoader& textureLoader,
                                        Eegeo::Routes::Simulation::Camera::RouteSimulationGlobeCameraControllerFactory routeSimulationGlobeCameraControllerFactory,
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
        
    private:
        
        void Initialise();
        
        Eegeo::Routes::Route* BuildRoute();
        
        Eegeo::Model* LoadCharacterModel(Eegeo::Node*& pCharacter) const;
    };
}


#endif /* defined(__ExampleApp__RouteSimulationAnimationExample__) */
