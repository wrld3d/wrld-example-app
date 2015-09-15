// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourStateMachineFactory.h"
#include "ExampleTourState.h"
#include "TourModel.h"
#include "TourStateMachine.h"
#include "ITourRepository.h"
#include "TourModel.h"
#include "LatLongAltitude.h"
#include <vector>

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
                    ExampleTourStateMachineFactory::ExampleTourStateMachineFactory(Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                                                   Camera::IToursCameraController& toursCameraController,
                                                                                   WorldPins::SdkModel::IWorldPinsService& worldPinsService
                                                                             )
                    : m_toursCameraController(toursCameraController)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_worldPinsService(worldPinsService)
                    {
                        
                    }
                    
                    ExampleTourStateMachineFactory::~ExampleTourStateMachineFactory()
                    {
                        
                    }
                    
                    States::ITourStateMachine* ExampleTourStateMachineFactory::CreateTourStateMachine(const TourModel& tourModel)
                    {
                        std::vector<States::ITourStateMachineState*> stateMachineStates;
                        
                        Eegeo_ASSERT(tourModel.States().size() == 3); // Sanity check while testing.
                        
                        int tourIndex = 0;
                        
                        stateMachineStates.push_back(Eegeo_NEW(ExampleTourState(tourModel.States()[tourIndex++],
                                                                                Eegeo::Space::LatLong::FromDegrees(37.784783, -122.402659),
                                                                                m_toursCameraTransitionController,
                                                                                m_worldPinsService)));

                        
                        stateMachineStates.push_back(Eegeo_NEW(ExampleTourState(tourModel.States()[tourIndex++],
                                                                                Eegeo::Space::LatLong::FromDegrees(37.783487, -122.406571),
                                                                                m_toursCameraTransitionController,
                                                                                m_worldPinsService)));
                        
                        stateMachineStates.push_back(Eegeo_NEW(ExampleTourState(tourModel.States()[tourIndex++],
                                                                                Eegeo::Space::LatLong::FromDegrees(37.787939, -122.407558),
                                                                                m_toursCameraTransitionController,
                                                                                m_worldPinsService)));
                        
                        
                        return Eegeo_NEW(States::TourStateMachine)(stateMachineStates,
                                                                   NULL);
                    }
                }
            }
        }
    }
}