// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointOnMapModel.h"
#include "WorldPinFocusData.h"
#include "WorldPinVisibility.h"
#include "IWorldPinsService.h"
#include "WayPointSelectionHandler.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            
            WayPointOnMapModel::WayPointOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                   TagSearch::ISearchResultIconKeyMapper& searchResultIconCategoryMapper,
                                                   PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository,
                                                   ExampleAppMessaging::TMessageBus& messageBus)
            : m_onWayPointAddedCallBack(this, &WayPointOnMapModel::OnWayPointAdded)
            , m_onWayPointRemovedCallBack(this, &WayPointOnMapModel::OnWayPointRemoved)
            , m_worldPinsService(worldPinsService)
            , m_wayPointsRepository(wayPointsRepository)
            , m_messageBus(messageBus)
            {
                wayPointsRepository.InsertItemAddedCallback(m_onWayPointAddedCallBack);
                wayPointsRepository.InsertItemRemovedCallback(m_onWayPointRemovedCallBack);
            }
            
            WayPointOnMapModel::~WayPointOnMapModel()
            {
                m_wayPointsRepository.RemoveItemAddedCallback(m_onWayPointAddedCallBack);
                m_wayPointsRepository.RemoveItemRemovedCallback(m_onWayPointRemovedCallBack);
            }
            
            void WayPointOnMapModel::OnWayPointAdded(WayPoint*& wayPoint)
            {
                AddWayPointView(wayPoint);
            }
            
            void WayPointOnMapModel::AddWayPointView(WayPoint*& wayPoint)
            {
                WorldPins::SdkModel::WorldPinFocusData worldPinFocusData("",
                                                                      "",
                                                                      "",
                                                                      "",
                                                                      "",
                                                                      0);
                
                WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData(Eegeo::Resources::Interiors::InteriorId::NullId(), 0);
                
                ExampleApp::WorldPins::SdkModel::WorldPinItemModel *pinItemModel =
                m_worldPinsService.AddPin(Eegeo_NEW(WayPointSelectionHandler(m_messageBus))
                                          , NULL
                                          , worldPinFocusData
                                          , false
                                          , worldPinInteriorData
                                          , wayPoint->GetLocation()
                                          , GetWayPointIconForType(wayPoint->GetType())
                                          , 0.f
                                          , WorldPins::SdkModel::WorldPinVisibility::Search);
                
                pinItemModel->SetFocusable(false);
                // Add pin to map
                
                m_wayPointsToPinModel.insert(std::make_pair(wayPoint, pinItemModel));
            }
            
            void WayPointOnMapModel::OnWayPointRemoved(WayPoint*& wayPoint)
            {
                RemoveWayPointView(wayPoint);
            }
            
            void WayPointOnMapModel::RemoveWayPointView(WayPoint*& wayPoint)
            {
                mapIt it = m_wayPointsToPinModel.find(wayPoint);
                
                Eegeo_ASSERT(it != m_wayPointsToPinModel.end(),
                             "Trying to remove the world pin for a search result, but no pin exists for result.");
                
                ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pinItemModel = it->second;
                m_worldPinsService.RemovePin(pinItemModel);
                m_wayPointsToPinModel.erase(it);
            }
            
            std::string WayPointOnMapModel::GetWayPointIconForType(const ExampleApp::PathDrawing::WayPointType::Values type)
            {
                switch(type) {
                    case ExampleApp::PathDrawing::WayPointType::Start:
                    case ExampleApp::PathDrawing::WayPointType::End:
                        return "tourism";
                    case ExampleApp::PathDrawing::WayPointType::CheckPoint:
                        return "blank";
                    case ExampleApp::PathDrawing::WayPointType::InteriorEntry:
                        return "indoor_map";
                    case ExampleApp::PathDrawing::WayPointType::Elevator:
                        return "elevator";
                    default:
                        return "misc";
                }
                
            }
        }
    }
}
