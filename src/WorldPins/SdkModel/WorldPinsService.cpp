// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsService.h"
#include "IWorldPinSelectionHandler.h"
#include "IWorldPinsRepository.h"
#include "IWorldPinsFactory.h"
#include "PinRepository.h"
#include "PinController.h"
#include "LatLongAltitude.h"
#include "Pin.h"
#include "Bounds.h"
#include "EarthConstants.h"
#include "Logger.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsService::WorldPinsService(IWorldPinsRepository& worldPinsRepository,
                                               IWorldPinsFactory& worldPinsFactory,
                                               Eegeo::Pins::PinRepository& pinRepository,
                                               Eegeo::Pins::PinController& pinController,
                                               const Eegeo::Rendering::EnvironmentFlatteningService& flatteningService)
                : m_worldPinsRepository(worldPinsRepository)
                , m_worldPinsFactory(worldPinsFactory)
                , m_pinRepository(pinRepository)
                , m_pinController(pinController)
                , m_environmentFlatteningService(flatteningService)
            {
            }

            WorldPinsService::~WorldPinsService()
            {
                while(m_worldPinsRepository.GetItemCount() != 0)
                {
                    WorldPinItemModel* item = m_worldPinsRepository.GetItemAtIndex(0);
                    RemovePin(item);
                }
            }

            WorldPinItemModel* WorldPinsService::AddPin(IWorldPinSelectionHandler* pSelectionHandler,
                                                        IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                                        const WorldPinFocusData& worldPinFocusData,
                                                        bool interior,
                                                        const WorldPinInteriorData& worldPinInteriorData,
                                                        const Eegeo::Space::LatLong& location,
                                                        int iconIndex,
                                                        float heightAboveTerrainMetres,
                                                        int visibilityMask)
            {
                
                Eegeo::Pins::Pin* pPin = m_worldPinsFactory.CreatePin(location, iconIndex, heightAboveTerrainMetres);

                m_pinRepository.AddPin(*pPin);

                Eegeo::Pins::TPinId pinId = pPin->GetId();

                TPinToSelectionHandlerMapIt pinToSelectionHandlerMapIt = m_pinsToSelectionHandlers.find(pinId);
                Eegeo_ASSERT(pinToSelectionHandlerMapIt == m_pinsToSelectionHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToSelectionHandlers[pinId] = pSelectionHandler;
                
                TPinToVisiblityHandlerMapIt pinToVisiblityHandlerMapIt = m_pinsToVisbilityChangedHandlers.find(pinId);
                Eegeo_ASSERT(pinToVisiblityHandlerMapIt == m_pinsToVisbilityChangedHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToVisbilityChangedHandlers[pinId] = pVisibilityStateChangedHandler;

                WorldPinItemModel* model = Eegeo_NEW(WorldPinItemModel)(pinId,
                                                                        pSelectionHandler,
                                                                        pVisibilityStateChangedHandler,
                                                                        worldPinFocusData,
                                                                        interior,
                                                                        worldPinInteriorData,
                                                                        visibilityMask);
                m_worldPinsRepository.AddItem(model);

                UpdatePinScale(*model, model->TransitionStateValue());

                return model;
            }

            void WorldPinsService::RemovePin(WorldPinItemModel* pinItemModel)
            {
                Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(pinItemModel->Id());

                //EXAMPLE_LOG("Pin removed\n");
                m_pinRepository.RemovePin(*pPin);
                ErasePin(pinItemModel->Id());

                m_worldPinsRepository.RemoveItem(pinItemModel);
                Eegeo_DELETE pinItemModel;
            }

            void WorldPinsService::UpdatePinScale(const WorldPinItemModel& pinItemModel, float scale)
            {
                Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(pinItemModel.Id());
                Eegeo_ASSERT(pPin != NULL);

                float scaleWithTerrainHeight = pPin->HasTerrainHeight() ? scale : 0.f;
                m_pinController.SetScaleForPin(*pPin, scaleWithTerrainHeight);
            }

            bool WorldPinsService::HandleTouchTap(const Eegeo::v2& screenTapPoint)
            {
                std::vector<Eegeo::Pins::Pin*> intersectingPinsClosestToCameraFirst;

                if(m_pinController.TryGetPinsIntersectingScreenPoint(screenTapPoint, intersectingPinsClosestToCameraFirst))
                {
                    Eegeo_ASSERT(intersectingPinsClosestToCameraFirst.size() > 0);
                    Eegeo::Pins::Pin* pSelectedPin = intersectingPinsClosestToCameraFirst[0];
                    Eegeo_ASSERT(pSelectedPin != NULL);
                    TPinToSelectionHandlerMapIt pinToSelectionHandlerMapIt = m_pinsToSelectionHandlers.find(pSelectedPin->GetId());
                    Eegeo_ASSERT(pinToSelectionHandlerMapIt != m_pinsToSelectionHandlers.end(),
                                 "Selected pin with unknown ID %d.\n", pSelectedPin->GetId());
                    IWorldPinSelectionHandler& selectionHandler = *pinToSelectionHandlerMapIt->second;
                    selectionHandler.SelectPin();
                    return true;
                }

                return false;
            }

            void WorldPinsService::GetPinEcefAndScreenLocations(const WorldPinItemModel& pinItemModel,
                    Eegeo::dv3& ecefLocation,
                    Eegeo::v2& screenLocation) const
            {
                Eegeo::Pins::Pin* pPin = m_pinRepository.GetPinById(pinItemModel.Id());
                Eegeo_ASSERT(pPin != NULL);

                ecefLocation = m_environmentFlatteningService.GetScaledPointEcef(pPin->GetEcefPosition(),
                               m_environmentFlatteningService.GetCurrentScale());

                Eegeo::Geometry::Bounds2D outScreenBounds = Eegeo::Geometry::Bounds2D::Empty();
                m_pinController.GetScreenBoundsForPin(*pPin, outScreenBounds);
                screenLocation = outScreenBounds.center();
            }

            void WorldPinsService::ErasePin(const WorldPinItemModel::WorldPinItemModelId& id)
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
        }
    }
}
