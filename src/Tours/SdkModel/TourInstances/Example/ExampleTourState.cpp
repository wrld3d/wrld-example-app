// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourState.h"
#include "LatLongAltitude.h"
#include "IToursCameraTransitionController.h"
#include "IWorldPinsService.h"
#include "WorldPinFocusData.h"
#include "ExampleTourPinSelectionHandler.h"

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
                    ExampleTourState::ExampleTourState(const TourStateModel& stateModel,
                                                       Eegeo::Space::LatLong position,
                                                       bool isInterior,
                                                       Camera::IToursCameraTransitionController& toursCameraTransitionController,
                                                       WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                       WorldPins::SdkModel::WorldPinInteriorData& worldPinInteriorData)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_position(position)
                    , m_cameraMode(position.ToECEF(), 300, 300)
                    , m_worldPinsService(worldPinsService)
                    , m_pPinItemModel(NULL)
                    , m_interior(isInterior)
                    , m_worldPinInteriorData(worldPinInteriorData)
                    {
                        
                    }
                    
                    ExampleTourState::~ExampleTourState()
                    {
                        
                    }
                    
                    void ExampleTourState::Enter()
                    {
                        m_cameraTransitionComplete = false;
                        m_cameraMode.Reset();
                        m_toursCameraTransitionController.TransitionTo(m_cameraMode);
                    }
                    
                    void ExampleTourState::Update(float dt)
                    {
                        if(m_toursCameraTransitionController.IsTransitionComplete() && !m_cameraTransitionComplete)
                        {   
                            m_cameraTransitionComplete = true;
                            
                            // Add pin.
                            ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(m_stateModel.Headline(), m_stateModel.Description());
                            
                            const int iconIndex = 4;
                            
                            m_pPinItemModel = m_worldPinsService.AddPin(Eegeo_NEW(ExampleTourPinSelectionHandler),
                                                                        NULL,
                                                                        worldPinFocusData,
                                                                        m_interior,
                                                                        m_worldPinInteriorData,
                                                                        m_position,
                                                                        iconIndex,
                                                                        0.0f);
                        }
                    }
                    
                    void ExampleTourState::Exit()
                    {
                        if(m_pPinItemModel != NULL)
                        {
                            m_worldPinsService.RemovePin(m_pPinItemModel);
                        }
                        
                        m_pPinItemModel = NULL;
                    }
                }
            }
        }
    }
}