// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "ITourStateMachineState.h"
#include "Tours.h"
#include "TourStateModel.h"
#include "DroneLookatCameraMode.h"
#include "SplineCameraMode.h"
#include "BidirectionalBus.h"
#include "VisualMap.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Alcatraz
                {
                    class AlcatrazBeginTourState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        
                        Camera::DroneLookatCameraMode m_targetCameraMode;
                        Eegeo::Geometry::CatmullRomSpline m_positionSpline;
                        Eegeo::Geometry::CatmullRomSpline m_targetSpline;
                        Camera::SplineCameraMode* m_pSplineCameraMode;
                        
                        bool m_cameraTransitionComplete;
                        bool m_secondCameraTransitionComplete;
                        bool m_thirdCameraTransitionStarted;
                        float m_timeInState;

                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        
                        VisualMap::SdkModel::IVisualMapService& m_visualMapService;
                        
                    public:
                        AlcatrazBeginTourState(const TourStateModel& stateModel,
                                               Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                               VisualMap::SdkModel::IVisualMapService& visualMapService,
                                               ExampleAppMessaging::TMessageBus& messageBus);
                        
                        ~AlcatrazBeginTourState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                    };
                }
            }
        }
    }
}
