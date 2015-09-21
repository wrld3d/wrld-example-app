// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "WorldPins.h"
#include <string>
#include "Interiors.h"

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
                    class ExampleTourStateMachineFactory : private Eegeo::NonCopyable
                    {
                    public:
                        
                        ExampleTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                       Camera::IToursCameraController& toursCameraController,
                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                       bool interiorsEnabled,
                                                       Eegeo::Resources::Interiors::InteriorsController& interiorController
                                                    );
                        ~ExampleTourStateMachineFactory();
                        
                        States::ITourStateMachine* CreateTourStateMachine(const TourModel& tourModel);
                        
                    private:
                        
                        Camera::IToursCameraTransitionController& m_toursCameraTransitionController;
                        Camera::IToursCameraController& m_toursCameraController;
                        WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                        
                        bool m_interiorsEnabled;
                        Eegeo::Resources::Interiors::InteriorsController& m_interiorController;
                    };
                }
            }
        }
    }
}