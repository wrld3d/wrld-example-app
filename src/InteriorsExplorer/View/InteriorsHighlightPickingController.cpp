// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorsHighlightPickingController.h"
#include "AggregateCollisionBvhProvider.h"
#include "MathsHelpers.h"
#include "EnvironmentRayCaster.h"
#include "CollisionMeshRayPicker.h"
#include "DebugRenderer.h"
#include "CollisionSubMeshBuilder.h"
#include "CollisionBvhGatherer.h"
#include "CollisionBvh.h"
#include "Colors.h"
#include "CollisionVisualizationModule.h"
#include "CollisionVisualizationRenderableFactory.h"
#include "CollisionVisualizationRenderable.h"
#include "CollisionVisualizationRenderer.h"
#include "MaterialSelectionController.h"
#include "InteriorsModel.h"
#include "InteriorsFloorCells.h"
#include "InteriorsFloorCell.h"
#include "InteriorsFloorModel.h"
#include "InteriorHighlightRenderable.h"
#include "SwallowSearchConstants.h"
#include "SwallowMeetingRoomResultModel.h"
#include "SwallowSearchParser.h"


using namespace Eegeo;

namespace ExampleApp
{
    namespace Picking
    {
        InteriorsHighlightPickingController::InteriorsHighlightPickingController(Eegeo::Collision::IRayCaster& rayCaster,
                                                               Eegeo::Resources::Interiors::IInteriorController& interiorController,
                                                               Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                               ExampleAppMessaging::TSdkModelDomainEventBus& domainBus)
        : PickingController(rayCaster, interiorController, environmentFlatteningService, Eegeo::Collision::CollisionGroup::Highlights)
        , m_interiorsController(interiorController)
        , m_messageBus(messageBus)
        , m_categorySearchHandlerBinding(this, &InteriorsHighlightPickingController::OnCategorySearchPerformed)
        , m_searchResultHandlerBinding(this, &InteriorsHighlightPickingController::OnSearchResultCleared)
        , m_interiorsHandlerBinding(this, &InteriorsHighlightPickingController::OnInteriorsEntered)
        , m_interiorsExitHandlerBinding(this, &InteriorsHighlightPickingController::OnInteriorsExited)
        , m_availabilityChangedHandlerBinding(this, &InteriorsHighlightPickingController::OnAvailabilityChanged)
        , m_searchResultReceivedHandler(this, &InteriorsHighlightPickingController::OnSearchResultsLoaded)
        , m_domainBus(domainBus)
        {
            m_messageBus.SubscribeNative(m_categorySearchHandlerBinding);
            m_domainBus.Subscribe(m_interiorsHandlerBinding);
            m_messageBus.SubscribeNative(m_interiorsExitHandlerBinding);
            m_messageBus.SubscribeNative(m_searchResultHandlerBinding);
            m_messageBus.SubscribeNative(m_availabilityChangedHandlerBinding);
            m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
        }
        
        InteriorsHighlightPickingController::~InteriorsHighlightPickingController()
        {
            m_messageBus.UnsubscribeNative(m_categorySearchHandlerBinding);
            m_messageBus.UnsubscribeNative(m_interiorsExitHandlerBinding);
            m_domainBus.Unsubscribe(m_interiorsHandlerBinding);
            m_messageBus.UnsubscribeNative(m_searchResultHandlerBinding);
            m_messageBus.UnsubscribeNative(m_availabilityChangedHandlerBinding);
            m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
        }
        
        void InteriorsHighlightPickingController::OnCategorySearchPerformed(const CategorySearch::CategorySearchSelectedMessage &message)
        {
            if(message.Category() != Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
            {
                ClearHighlightRenderables();
            }
        }
        
        void InteriorsHighlightPickingController::OnAvailabilityChanged(const ExampleApp::SearchResultOnMap::SearchResultMeetingAvailabilityChanged& message)
        {
            const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(message.GetModel());
            const std::string& roomName = meetingRoom.GetName();
            std::map<std::string, Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>::iterator it =
            m_currentHighlightRenderables.find(roomName);
            
            if (it != m_currentHighlightRenderables.end())
            {
                ConfigureRenderableForAvailability(*it->second, message.GetAvailability());
            }
            
            m_highlightAvailabilityData[roomName] = message.GetAvailability();
        }
        
        void InteriorsHighlightPickingController::ClearHighlightRenderables()
        {
            const v4 transparent(1.0f, 1.0f, 1.0f, 0.0f);
            
            for (std::map<std::string, Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>::iterator it = m_currentHighlightRenderables.begin();
                 it != m_currentHighlightRenderables.end();
                 ++it)
            {
                it->second->SetDiffuseColor(transparent);
            }
            
//            m_currentHighlightRenderables.clear();
        }
        
        void InteriorsHighlightPickingController::OnSearchResultCleared(const SearchResultMenu::SearchResultViewClearedMessage& message)
        {
            ClearHighlightRenderables();
        }
        
        void InteriorsHighlightPickingController::OnInteriorsExited(const InteriorsExplorer::InteriorsExplorerExitMessage& message)
        {
            ClearHighlightRenderables();
            m_currentHighlightRenderables.clear();
        }
        
        void InteriorsHighlightPickingController::OnInteriorsEntered(const InteriorsExplorer::InteriorsExplorerEnteredMessage& message)
        {
            Eegeo::Resources::Interiors::InteriorId id = message.GetInteriorId();
            const Resources::Interiors::InteriorsModel *model = NULL;
            
            if(m_interiorsController.TryGetCurrentModel(model))
            {
                Eegeo_ASSERT(model->GetId() == id, "ID's not the same");
                
                for(Eegeo::Resources::Interiors::TFloorModelVector::const_iterator floors = model->GetFloors().begin();
                    floors != model->GetFloors().end();
                    ++floors)
                {
                    Eegeo::Resources::Interiors::InteriorsFloorCells* floorCells = model->GetFloorCells((*floors)->GetFloorNumber());
                    
                    for (int cellIndex = 0; cellIndex < floorCells->GetCellCount(); ++cellIndex)
                    {
                        Eegeo::Resources::Interiors::InteriorsFloorCell* cell = floorCells->GetFloorCells()[cellIndex];
                        
                        std::vector<Rendering::Renderables::InteriorHighlightRenderable*> renderables = cell->GetHighlightRenderables();
                        
                        for (std::vector<Rendering::Renderables::InteriorHighlightRenderable*>::iterator renderableIterator = renderables.begin();
                             renderableIterator != renderables.end();
                             ++renderableIterator)
                        {
                            AddHighlight(**renderableIterator);
                        }
                    }
                }
            }
        }
        
        void InteriorsHighlightPickingController::AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable)
        {
            static const std::string highlightPrefix = "entity_highlight ";
            const std::string& id = renderable.GetRenderableId();
            
            if (id.compare(0, highlightPrefix.length(), highlightPrefix) == 0)
            {
                std::string roomName = id.substr(highlightPrefix.length());
                m_currentHighlightRenderables.insert(std::make_pair(roomName, &renderable));
                std::map<std::string, std::string>::iterator availabilityData = m_highlightAvailabilityData.find(roomName);
                
                if (availabilityData != m_highlightAvailabilityData.end())
                {
                    ConfigureRenderableForAvailability(renderable, availabilityData->second);
                }
            }
        }
        
        void InteriorsHighlightPickingController::ConfigureRenderableForAvailability(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable, const std::string& availability)
        {
            const v4 available(0.0f, 1.0f, 0.0f, 0.3f);
            const v4 availableSoon(1.0f, 0.8f, 0.0f, 0.3f);
            const v4 occupied(1.0f, 0.0f, 0.0f, 0.3f);
            const v4 unknown(1.0f, 1.0f, 1.0f, 0.0f);
            
            if (availability == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE)
            {
                renderable.SetDiffuseColor(available);
            }
            else if (availability == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
            {
                renderable.SetDiffuseColor(availableSoon);
            }
            else if (availability == Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED)
            {
                renderable.SetDiffuseColor(occupied);
            }
            else
            {
                renderable.SetDiffuseColor(unknown);
            }
        }
    
        void InteriorsHighlightPickingController::OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message)
        {
            ClearHighlightRenderables();

            for(std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = message.GetResults().begin(); it != message.GetResults().end(); ++it)
            {
                if((*it).GetCategory() != Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
                {
                    continue;
                }
                
                const Search::Swallow::SdkModel::SwallowMeetingRoomResultModel& meetingRoom = Search::Swallow::SdkModel::SearchParser::TransformToSwallowMeetingRoomResult(*it);
                
                const std::string& roomName = meetingRoom.GetName();
                const std::string& availability = meetingRoom.GetAvailability();
                
                std::map<std::string, Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>::iterator room =
                m_currentHighlightRenderables.find(roomName);
                
                if (room != m_currentHighlightRenderables.end())
                {
                    ConfigureRenderableForAvailability(*(room->second), availability);
                }

				m_highlightAvailabilityData[roomName] = availability;
            }
        }

        
        void InteriorsHighlightPickingController::ProcessRayCastResult(const Eegeo::Collision::RayCasterResult& pickResult)
        {
//            if(pickResult.intersects)
//            {
//                const std::string materialId = pickResult.pCollisionBvh->CollisionMaterialIdForIndex(pickResult.collisionMaterialIndex);
//                
//                const Resources::Interiors::InteriorsModel *model = NULL;
//                
//                if(m_interiorsController.TryGetCurrentModel(model))
//                {
//                    for (int floorIndex = 0; floorIndex < model->GetFloorCount(); ++floorIndex)
//                    {
//                        int floorNumber = model->GetFloorAtIndex(floorIndex).GetFloorNumber();
//                        Eegeo::Resources::Interiors::InteriorsFloorCells* floorCells = model->GetFloorCells(floorNumber);
//                        
//                        for (int cellIndex = 0; cellIndex < floorCells->GetCellCount(); ++cellIndex)
//                        {
//                            Eegeo::Resources::Interiors::InteriorsFloorCell* cell = floorCells->GetFloorCells()[cellIndex];
//                            
//                            std::vector<Rendering::Renderables::InteriorHighlightRenderable*> renderables = cell->GetHighlightRenderables();
//                            
//                            for (std::vector<Rendering::Renderables::InteriorHighlightRenderable*>::iterator renderable = renderables.begin();
//                                 renderable != renderables.end();
//                                 ++renderable)
//                            {
//                                Rendering::Renderables::InteriorHighlightRenderable* pCurrentRenderable = (*renderable);
//                                const std::string& renderableId = pCurrentRenderable->GetRenderableId();
//                                
//                                pCurrentRenderable->GetInteriorTerrainHeight();
//                                
//                                if (renderableId == materialId)
//                                {
//                                    if(pCurrentRenderable->GetDiffuseColor().GetX() == 1.0f && pCurrentRenderable->GetDiffuseColor().GetY() == 1.0f)
//                                        pCurrentRenderable->SetDiffuseColor(v4(0.0f, 1.0f, 0.0f, 0.3f));
//                                    else if(pCurrentRenderable->GetDiffuseColor().GetY() == 1.0f)
//                                        pCurrentRenderable->SetDiffuseColor(v4(1.0f, 0.0f, 0.0f, 0.3f));
//                                    else
//                                        pCurrentRenderable->SetDiffuseColor(v4(1.0f, 1.0f, 0.0f, 0.3f));
//                                    
//                                    return;
//                                }
//                            }
//                        }
//                    }
  //              }
//            }
        }
    }
}
