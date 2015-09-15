// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ITourStateMachineState.h"
#include "Tours.h"
#include "TourStateModel.h"
#include "OrbitCameraMode.h"
#include "LatLongAltitude.h"
#include "WorldPins.h"
#include <string>

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Example
                {
                    class ExampleTourState : public States::ITourStateMachineState, private Eegeo::NonCopyable
                    {
                    public:
                        
                        ExampleTourState(const TourStateModel& stateModel,
                                         Eegeo::Space::LatLong position,
                                         Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                         WorldPins::SdkModel::IWorldPinsService& worldPinsService);
                        ~ExampleTourState();
                        
                        void Enter();
                        
                        void Update(float dt);
                        
                        void Exit();
                        
                    private:
                        
                        TourStateModel m_stateModel;
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::OrbitCameraMode m_cameraMode;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        WorldPins::SdkModel::WorldPinItemModel* m_pPinItemModel;
                        Eegeo::Space::LatLong m_position;
                        bool m_cameraTransitionComplete;
                    };
                }
            }
        }
    }
}