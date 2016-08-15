// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleTourState.h"
#include "LatLongAltitude.h"
#include "IToursCameraTransitionController.h"
#include "IWorldPinsService.h"
#include "WorldPinFocusData.h"
#include "ExampleTourPinSelectionHandler.h"
#include "ExampleCurrentTourCardTappedHandler.h"
#include "WorldPinItemModel.h"
#include "WorldPinVisibility.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorSelectionModel.h"
#include "SearchVendorNames.h"
#include "InteriorInteractionModel.h"

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
                                                       InteriorsExplorer::SdkModel::InteriorVisibilityUpdater& interiorVisibilityUpdater,
                                                       Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                       Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                       ExampleAppMessaging::TMessageBus& messageBus)
                    : m_stateModel(stateModel)
                    , m_toursCameraTransitionController(toursCameraTransitionController)
                    , m_position(position)
                    , m_cameraMode(position.ToECEF(), 300, 300)
                    , m_worldPinsService(worldPinsService)
                    , m_pPinItemModel(NULL)
                    , m_interior(isInterior)
                    , m_worldPinInteriorData(worldPinInteriorData)
                    , m_interiorVisibilityUpdater(interiorVisibilityUpdater)
                    , m_interiorInteractionModel(interiorInteractionModel)
                    , m_interiorSelectionModel(interiorSelectionModel)
                    , m_messageBus(messageBus)
                    , m_pTourCardTappedHandler(NULL)
                    {
                        
                    }
                    
                    ExampleTourState::~ExampleTourState()
                    {
                        
                    }
                    
                    void ExampleTourState::Enter()
                    {
                        m_interiorTransitionComplete = false;
                        m_cameraTransitionComplete = false;
                        m_cameraMode.Reset();
                        
                        m_toursCameraTransitionController.TransitionTo(m_cameraMode, false);
                        
                        if(m_interior && m_interiorSelectionModel.GetSelectedInteriorId() != m_worldPinInteriorData.building)
                        {
                            m_interiorSelectionModel.SelectInteriorId(m_worldPinInteriorData.building);
                            m_interiorVisibilityUpdater.SetInteriorShouldDisplay(false);
                        }
                        else if (!m_interior)
                        {
                            m_interiorSelectionModel.ClearSelection();
                            m_interiorVisibilityUpdater.SetInteriorShouldDisplay(false);
                        }
                        
                        m_pTourCardTappedHandler = Eegeo_NEW(ExampleCurrentTourCardTappedHandler)(m_messageBus, m_stateModel);
                    }
                    
                    void ExampleTourState::Update(float dt)
                    {
                        if(m_toursCameraTransitionController.IsTransitionComplete() && !m_cameraTransitionComplete)
                        {   
                            m_cameraTransitionComplete = true;
                            
                            m_interiorVisibilityUpdater.SetInteriorShouldDisplay(true);
                            
                            // Add pin.
                            ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(m_stateModel.Headline(),
                                                                                                 m_stateModel.Description(),
                                                                                                 Search::ExampleTourVendorName);
                            
                            const float heightOffsetMetres = 0.0f;
                            const std::string tourEntryPinIconKey = "tour_entry";
                            
                            m_pPinItemModel = m_worldPinsService.AddPin(Eegeo_NEW(ExampleTourPinSelectionHandler)(m_messageBus, m_stateModel),
                                                                        NULL,
                                                                        worldPinFocusData,
                                                                        m_interior,
                                                                        m_worldPinInteriorData,
                                                                        m_position,
                                                                        tourEntryPinIconKey,
                                                                        heightOffsetMetres,
                                                                        WorldPins::SdkModel::WorldPinVisibility::TourPin);
                        }
                        else if(!m_interiorTransitionComplete && m_interior && m_interiorInteractionModel.HasInteriorModel())
                        {
                            m_interiorTransitionComplete = true;
                            m_interiorInteractionModel.SetSelectedFloorIndex(m_worldPinInteriorData.floor);
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