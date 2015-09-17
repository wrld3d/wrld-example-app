// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourStateMachineFactory.h"
#include "ExampleTourState.h"
#include "TourModel.h"
#include "TourStateMachine.h"
#include "ITourRepository.h"
#include "TourModel.h"
#include "LatLongAltitude.h"
#include "WorldPinInteriorData.h"
#include <vector>
#include "InteriorId.h"
#include "IToursCameraController.h"

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
                                                                                   WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                                                   bool interiorsEnabled,
                                                                                   Eegeo::Resources::Interiors::InteriorsController& interiorController
                                                                             )
                    : m_toursCameraController(toursCameraController)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_worldPinsService(worldPinsService)
                    , m_interiorController(interiorController)
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
                        
                        ExampleApp::WorldPins::SdkModel::WorldPinInteriorData blankWorldPinInteriorData;
                        
                        Eegeo::Resources::Interiors::InteriorId hotelId("intercontinental_hotel_8628");
                        ExampleApp::WorldPins::SdkModel::WorldPinInteriorData hotelPinInteriorData(hotelId, 3, true);
                        
                        stateMachineStates.push_back(Eegeo_NEW(ExampleTourState(tourModel.States()[tourIndex++],
                                                                                Eegeo::Space::LatLong::FromDegrees(37.784783, -122.402659),
                                                                                false,
                                                                                m_toursCameraTransitionController,
                                                                                m_worldPinsService,
                                                                                blankWorldPinInteriorData,
                                                                                m_interiorController,
                                                                                m_toursCameraController.GetRenderCamera())));

                        
                        stateMachineStates.push_back(Eegeo_NEW(ExampleTourState(tourModel.States()[tourIndex++],
                                                                                Eegeo::Space::LatLong::FromDegrees(37.781908, -122.404784),
                                                                                m_interiorsEnabled,
                                                                                m_toursCameraTransitionController,
                                                                                m_worldPinsService,
                                                                                hotelPinInteriorData,
                                                                                m_interiorController,
                                                                                m_toursCameraController.GetRenderCamera())));
                        
                        stateMachineStates.push_back(Eegeo_NEW(ExampleTourState(tourModel.States()[tourIndex++],
                                                                                Eegeo::Space::LatLong::FromDegrees(37.787939, -122.407558),
                                                                                false,
                                                                                m_toursCameraTransitionController,
                                                                                m_worldPinsService,
                                                                                blankWorldPinInteriorData,
                                                                                m_interiorController,
                                                                                m_toursCameraController.GetRenderCamera())));
                        
                        
                        return Eegeo_NEW(States::TourStateMachine)(stateMachineStates,
                                                                   NULL);
                    }
                }
            }
        }
    }
}