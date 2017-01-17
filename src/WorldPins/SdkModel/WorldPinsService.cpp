// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsService.h"
#include "ILabelModelService.h"
#include "LatLongAltitude.h"
#include "IWorldPinsRepository.h"
#include "IInteriorMarkerPickingService.h"

#include "IMarkerService.h"
#include "MarkerBuilder.h"

#include <cstdlib>
#include <sstream>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsService::WorldPinsService(
                                               IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService,
                                               Eegeo::Markers::IMarkerService& markerService,
                                               ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus)
            : m_worldPinsRepository(worldPinsRepository)
            , m_interiorMarkerPickingService(interiorMarkerPickingService)
            , m_markerService(markerService)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_worldPinHiddenStateChangedMessageBinding(this, &WorldPinsService::OnWorldPinHiddenStateChanged)
            {
                m_sdkModelDomainEventBus.Subscribe(m_worldPinHiddenStateChangedMessageBinding);
            }
            
            WorldPinsService::~WorldPinsService()
            {
                m_sdkModelDomainEventBus.Unsubscribe(m_worldPinHiddenStateChangedMessageBinding);
            }
            
            Eegeo::Markers::IMarker::IdType WorldPinsService::GetMarkerIdForWorldPinItemModelId(SdkModel::WorldPinItemModel::WorldPinItemModelId worldPinId) const
            {
                const Eegeo::Markers::IMarker::IdType markerId = worldPinId;
                return markerId;
            }
            
            WorldPinItemModel::WorldPinItemModelId WorldPinsService::GetWorldPinItemModelIdForMarkerId(Eegeo::Markers::IMarker::IdType markerId) const
            {
                const WorldPinItemModel::WorldPinItemModelId worldPinItemModelId = markerId;
                return worldPinItemModelId;
            }
            
            
            void WorldPinsService::OnWorldPinHiddenStateChanged(const WorldPinHiddenStateChangedMessage& message)
            {
                const SdkModel::WorldPinItemModel& worldPin = message.GetWorldPin();

                Eegeo::Markers::IMarker& marker = m_markerService.Get(GetMarkerIdForWorldPinItemModelId(worldPin.Id()));
                
                const bool isHidden = worldPin.IsHidden();
                marker.SetHidden(isHidden);
            }
            
            WorldPinItemModel* WorldPinsService::AddPin(IWorldPinSelectionHandler* pSelectionHandler,
                                                          IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                                          const WorldPinFocusData& worldPinFocusData,
                                                          bool interior,
                                                          const WorldPinInteriorData& worldPinInteriorData,
                                                          const Eegeo::Space::LatLong& location,
                                                          const std::string& pinIconKey,
                                                          float heightAboveTerrainMetres,
                                                          int visibilityMask)
            {
            
                const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
                    .SetLocation(location.GetLatitudeInDegrees(), location.GetLongitudeInDegrees())
                    .SetLabelText(worldPinFocusData.title)
                    .SetLabelIcon(pinIconKey)
                    .SetInterior(worldPinInteriorData.building.Value(), worldPinInteriorData.floor)
                    .Build();
                
                
                const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);
                const WorldPinItemModel::WorldPinItemModelId pinId = markerId;
                
                Eegeo_ASSERT(m_pinsToSelectionHandlers.find(pinId) == m_pinsToSelectionHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToSelectionHandlers[pinId] = pSelectionHandler;
                
                Eegeo_ASSERT(m_pinsToVisbilityChangedHandlers.find(pinId) == m_pinsToVisbilityChangedHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToVisbilityChangedHandlers[pinId] = pVisibilityStateChangedHandler;

                WorldPinItemModel* model = Eegeo_NEW(WorldPinItemModel)(pinId,
                                                                        pSelectionHandler,
                                                                        pVisibilityStateChangedHandler,
                                                                        worldPinFocusData,
                                                                        interior,
                                                                        worldPinInteriorData,
                                                                        visibilityMask,
                                                                        m_sdkModelDomainEventBus);
            
                m_worldPinsRepository.AddItem(model);

                return model;
            }
            
            void WorldPinsService::RemovePin(WorldPinItemModel* pPinItemModel)
            {
                const WorldPinItemModel::WorldPinItemModelId pinId = pPinItemModel->Id();
                
                const Eegeo::Markers::IMarker::IdType markerId = GetWorldPinItemModelIdForMarkerId(pinId);
                
                m_markerService.Destroy(markerId);
                
                IWorldPinSelectionHandler* pSelectionHandler = m_pinsToSelectionHandlers.at(pinId);
                m_pinsToSelectionHandlers.erase(pinId);
                Eegeo_DELETE pSelectionHandler;
                
                IWorldPinVisibilityStateChangedHandler* pVisibilityHandler = m_pinsToVisbilityChangedHandlers.at(pinId);
                m_pinsToVisbilityChangedHandlers.erase(pinId);
                Eegeo_DELETE pVisibilityHandler;
                
                m_worldPinsRepository.RemoveItem(pPinItemModel);
                Eegeo_DELETE pPinItemModel;
            }
            
            void WorldPinsService::UpdatePinCategory(const WorldPinItemModel& pinItemModel, const std::string& iconKey)
            {
                //Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(pinItemModel.Id());
                //Eegeo_ASSERT(pPin != NULL, "Couldn't find Pin to set category on");
                //pPin->SetCategoryId(m_worldPinIconMapping.IconIndexForKey(iconKey));
            }

            bool WorldPinsService::HandleTouchTap(const Eegeo::v2& screenTapPoint)
            {
                return TrySelectPinAtPoint(screenTapPoint);
            }
            
            bool WorldPinsService::HandleTouchDoubleTap(const Eegeo::v2& screenTapPoint)
            {
                return TrySelectPinAtPoint(screenTapPoint);
            }
            
            void WorldPinsService::SelectPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId)
            {
                IWorldPinSelectionHandler* selectionHandler = GetSelectionHandlerForPin(worldPinItemModelId);
                if(selectionHandler != NULL)
                {
                    selectionHandler->SelectPin();
                }
            }
            
            
            IWorldPinSelectionHandler* WorldPinsService::GetSelectionHandlerForPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId)
            {
                if (m_pinsToSelectionHandlers.find(worldPinItemModelId) != m_pinsToSelectionHandlers.end())
                {
                    return m_pinsToSelectionHandlers[worldPinItemModelId];
                }
                else
                {
                    return NULL;
                }
            }
            
            bool WorldPinsService::TrySelectPinAtPoint(const Eegeo::v2& screenPoint)
            {
                if (m_interiorMarkerPickingService.TryEnterInterior(screenPoint))
                {
                    return true;
                }
                
                auto pickedMarkerId = Eegeo::Markers::IMarker::InvalidId;
                if (m_markerService.TryPick(screenPoint, pickedMarkerId))
                {
                    const WorldPinItemModel::WorldPinItemModelId pinId = GetWorldPinItemModelIdForMarkerId(pickedMarkerId);
                    SelectPin(pinId);
                    return true;
                }
                
                return false;
            }
        }
    }
}
