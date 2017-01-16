// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsService.h"
#include "ILabelModelService.h"
#include "LatLongAltitude.h"
#include "IWorldPinsRepository.h"
#include "IInteriorMarkerPickingService.h"
#include "ILabelPicker.h"
#include "ILabelAnchorFilter.h"
#include <cstdlib>
#include <sstream>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsService::WorldPinsService(Eegeo::Labels::ILabelModelService& labelModelService,
                                               Eegeo::Labels::ILabelAnchorFilterModel& labelAnchorFilterModel,
                                               const Eegeo::Labels::LabelAnchorCategory& labelAnchorCategory,
                                               Eegeo::Labels::ILabelPicker& labelPicker,
                                               const Eegeo::Labels::LabelLayer::IdType& labelLayerId,
                                               IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService)
            : m_labelModelService(labelModelService)
            , m_labelAnchorFilterModel(labelAnchorFilterModel)
            , m_labelAnchorCategory(labelAnchorCategory)
            , m_labelPicker(labelPicker)
            , m_labelLayerId(labelLayerId)
            , m_worldPinsRepository(worldPinsRepository)
            , m_interiorMarkerPickingService(interiorMarkerPickingService)
            , m_lastLabelId(0)
            , m_pinAlreadySelected(false)
            , m_labelHiddenFilter(this, &WorldPinsService::LabelHiddenPredicate)
            {
                m_labelAnchorFilterModel.SetFilter(m_labelLayerId, &m_labelHiddenFilter);
            }
            
            WorldPinsService::~WorldPinsService()
            {
                m_labelAnchorFilterModel.SetFilter(m_labelLayerId, NULL);
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
                Eegeo::Pins::TPinId pinId = m_lastLabelId++;
                std::stringstream ss;
                ss << pinId;
                std::string labelModelId = ss.str();
                Eegeo::v3 offset = Eegeo::v3::Zero();
                Eegeo::Labels::LabelModelCreationParams labelParams(labelModelId,
                                                                    m_labelAnchorCategory,
                                                                    "world_pin",
                                                                    worldPinFocusData.title,
                                                                    pinIconKey,
                                                                    location.ToECEF(),
                                                                    offset,
                                                                    pinId);
                labelParams.fitToSurface = true;
                labelParams.interiorId = worldPinInteriorData.building;
                labelParams.interiorFloorIndex = worldPinInteriorData.floor;
                m_labelModelService.CreateAndAdd(labelParams);
                
                TPinToSelectionHandlerMapIt pinToSelectionHandlerMapIt = m_pinsToSelectionHandlers.find(pinId);
                Eegeo_ASSERT(pinToSelectionHandlerMapIt == m_pinsToSelectionHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToSelectionHandlers[pinId] = pSelectionHandler;
                
                TPinToVisiblityHandlerMapIt pinToVisiblityHandlerMapIt = m_pinsToVisbilityChangedHandlers.find(pinId);
                Eegeo_ASSERT(pinToVisiblityHandlerMapIt == m_pinsToVisbilityChangedHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToVisbilityChangedHandlers[pinId] = pVisibilityStateChangedHandler;

                m_worldPinsToLabels[pinId] = labelModelId;
                
                WorldPinItemModel* model = Eegeo_NEW(WorldPinItemModel)(pinId,
                                                                        pSelectionHandler,
                                                                        pVisibilityStateChangedHandler,
                                                                        worldPinFocusData,
                                                                        interior,
                                                                        worldPinInteriorData,
                                                                        visibilityMask);
            
                m_worldPinsRepository.AddItem(model);
                m_worldPinItemModelMap[pinId] = model;
                
                return model;
            }
            
            void WorldPinsService::RemovePin(WorldPinItemModel* pinItemModel)
            {
                const std::string& labelId = m_worldPinsToLabels[pinItemModel->Id()];
                m_labelModelService.RemoveAndDestroy(labelId);
                
                //EXAMPLE_LOG("Pin removed\n");
                Erase(pinItemModel->Id());
                
                m_worldPinsRepository.RemoveItem(pinItemModel);
                Eegeo_DELETE pinItemModel;
            }
            
            bool WorldPinsService::LabelHiddenPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
            {
                WorldPinItemModel::WorldPinItemModelId pinId = atoi(anchoredLabel.GetId().c_str());
                if(m_worldPinItemModelMap.find(pinId) == m_worldPinItemModelMap.end())
                {
                    return false;
                }
                
                WorldPinItemModel* pWorldPin = m_worldPinItemModelMap.at(pinId);
                return !pWorldPin->IsVisible();
                
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
                if(m_pinAlreadySelected)
                {
                    return;
                }
                IWorldPinSelectionHandler* selectionHandler = GetSelectionHandlerForPin(worldPinItemModelId);
                if(selectionHandler != NULL)
                {
                    m_pinAlreadySelected = true;
                    selectionHandler->SelectPin();
                }
            }
            
            void WorldPinsService::Update(float dt)
            {
                m_labelAnchorFilterModel.SetFilter(m_labelLayerId, &m_labelHiddenFilter);
                
                m_pinAlreadySelected = false;
            }
            
            void WorldPinsService::Erase(const WorldPinItemModel::WorldPinItemModelId &id)
            {
                TPinToSelectionHandlerMapIt pinToSelectionHandlerMapIt = m_pinsToSelectionHandlers.find(id);
                Eegeo_ASSERT(pinToSelectionHandlerMapIt != m_pinsToSelectionHandlers.end(), "Attempting to remove pin with unknown ID %d.\n", id);
                IWorldPinSelectionHandler* pSelectionHandler = pinToSelectionHandlerMapIt->second;
                m_pinsToSelectionHandlers.erase(pinToSelectionHandlerMapIt);
                Eegeo_DELETE pSelectionHandler;
                
                TPinToVisiblityHandlerMapIt pinToVisiblityHandlerMapIt = m_pinsToVisbilityChangedHandlers.find(id);
                Eegeo_ASSERT(pinToVisiblityHandlerMapIt != m_pinsToVisbilityChangedHandlers.end(), "Attempting to remove pin with unknown ID %d.\n", id);
                IWorldPinVisibilityStateChangedHandler* pVisibilityHandler = pinToVisiblityHandlerMapIt->second;
                m_pinsToVisbilityChangedHandlers.erase(pinToVisiblityHandlerMapIt);
                Eegeo_DELETE pVisibilityHandler;
                
                auto pinToLabelIt = m_worldPinsToLabels.find(id);
                m_worldPinsToLabels.erase(pinToLabelIt);
                
                auto worldPinItemModelIt = m_worldPinItemModelMap.find(id);
                m_worldPinItemModelMap.erase(worldPinItemModelIt);

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
                
                const auto& query = Eegeo::Labels::LabelPickQuery::Make(screenPoint, m_labelLayerId);
                const auto& result = m_labelPicker.Pick(query);
                
                if (!result())
                {
                    return false;
                }
                
                const Eegeo::Labels::IAnchoredLabel* pLabel = result.GetLabelModel();
                WorldPinItemModel::WorldPinItemModelId pinId = atoi(pLabel->GetId().c_str());
                SelectPin(pinId);
                
                return false;

            }
        }
    }
}
