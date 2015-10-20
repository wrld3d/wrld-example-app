// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourState.h"
#include "LatLongAltitude.h"
#include "IToursCameraTransitionController.h"
#include "IWorldPinsService.h"
#include "WorldPinFocusData.h"
#include "ExampleTourPinSelectionHandler.h"
#include "InteriorController.h"
#include "ExampleCurrentTourCardTappedHandler.h"
#include "WorldPinItemModel.h"
#include "WorldPinVisibility.h"
#include "InteriorVisibilityUpdater.h"

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
                                                       WorldPins::SdkModel::WorldPinInteriorData& worldPinInteriorData,
                                                       Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                       InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_position(position)
                    , m_cameraMode(position.ToECEF(), 300, 300)
                    , m_worldPinsService(worldPinsService)
                    , m_pPinItemModel(NULL)
                    , m_interior(isInterior)
                    , m_worldPinInteriorData(worldPinInteriorData)
                    , m_interiorController(interiorController)
                    , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                    , m_messageBus(messageBus)
                    , m_pTourCardTappedHandler(NULL)
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
                        
                        if(m_interior)
                        {
                            m_interiorController.SetSelectedInterior(m_worldPinInteriorData.building);
                        }
                        else if (m_interiorController.InteriorIsVisible())
                        {
                            m_interiorController.ClearSelectedInterior();
                        }
                        
                         m_interiorVisibilityUpdater.SetInteriorShouldDisplay(false);
                        
                        m_pTourCardTappedHandler = Eegeo_NEW(ExampleCurrentTourCardTappedHandler)(m_messageBus, m_stateModel);
                    }
                    
                    void ExampleTourState::Update(float dt)
                    {
                        if(m_toursCameraTransitionController.IsTransitionComplete() && !m_cameraTransitionComplete)
                        {   
                            m_cameraTransitionComplete = true;
                            
                            m_interiorVisibilityUpdater.SetInteriorShouldDisplay(true);
                            
                            // Add pin.
                            ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(m_stateModel.Headline(), m_stateModel.Description());
                            
                            const float heightOffsetMetres = 0.0f;
                            const int iconIndex = 10;
                            
                            m_pPinItemModel = m_worldPinsService.AddPin(Eegeo_NEW(ExampleTourPinSelectionHandler)(m_messageBus, m_stateModel),
                                                                        NULL,
                                                                        worldPinFocusData,
                                                                        m_interior,
                                                                        m_worldPinInteriorData,
                                                                        m_position,
                                                                        iconIndex,
                                                                        heightOffsetMetres,
                                                                        WorldPins::SdkModel::WorldPinVisibility::TourPin);
                        }
                    }
                    
                    void ExampleTourState::Exit()
                    {
                        if(m_pTourCardTappedHandler != NULL)
                        {
                            Eegeo_DELETE m_pTourCardTappedHandler;
                            m_pTourCardTappedHandler = NULL;
                        }
                        
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