// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsService.h"
#include "ILabelModelService.h"
#include "LatLongAltitude.h"
#include "IWorldPinsRepository.h"
#include "IInteriorMarkerPickingService.h"
#include "ISearchResultMyPinsService.h"
#include "IMarkerService.h"
#include "MarkerBuilder.h"
#include "ICameraTransitionController.h"
#include <cstdlib>
#include <sstream>
#include "InteriorsExplorer.h"
#include "PinHelpers.h"

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
                                               ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               Eegeo::Location::NavigationService& navigationService,
                                               Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultOnMapMyPinsService,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            : m_worldPinsRepository(worldPinsRepository)
            , m_interiorMarkerPickingService(interiorMarkerPickingService)
            , m_markerService(markerService)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_worldPinHiddenStateChangedMessageBinding(this, &WorldPinsService::OnWorldPinHiddenStateChanged)
            , m_onSearchResultSelected(this, &WorldPinsService::OnMenuItemSelected)
            , m_messageBus(messageBus)
            , m_navigationService(navigationService)
            , m_pSelectedPinHighlight(nullptr)
            , m_selectedPinId(-1)
            , m_searchResultOnMapMyPinsService(searchResultOnMapMyPinsService)
            , m_cameraTransitionController(cameraTransitionController)
            {
                m_sdkModelDomainEventBus.Subscribe(m_worldPinHiddenStateChangedMessageBinding);
                m_messageBus.SubscribeNative(m_onSearchResultSelected);
            }
            
            WorldPinsService::~WorldPinsService()
            {
                m_messageBus.UnsubscribeNative(m_onSearchResultSelected);
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
                                                          int visibilityMask,
                                                          std::string identifier,
                                                          std::string labelStyleName)
            {
                const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
                    .SetLocation(location.GetLatitudeInDegrees(), location.GetLongitudeInDegrees())
                    .SetLabelText(worldPinFocusData.title)
                    .SetLabelIcon(pinIconKey)
                    .SetElevation(heightAboveTerrainMetres)
                    // temp workaround to specify interior floor by zero-based index rather than 'floor number' id (MPLY-8062)
                    .SetInteriorWithFloorIndex(worldPinInteriorData.building.Value(), worldPinInteriorData.floor)
                    .SetSubPriority(worldPinFocusData.priorityOrder)
                    .SetLabelStyle(labelStyleName)
                    .Build();
                
                const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);
                const WorldPinItemModel::WorldPinItemModelId pinId = markerId;
                
                m_pinsToIconKeys[pinId] = pinIconKey;
                
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
                                                                        m_sdkModelDomainEventBus,
                                                                        identifier);
            
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

                if(m_selectedPinId == pinId)
                {
                    const WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(pinId);
                    if (pWorldPinItemModel != nullptr)
                    {
                        RemoveHighlightPin(m_pSelectedPinHighlight);
                    }
                }
                
                m_worldPinsRepository.RemoveItem(pPinItemModel);
                Eegeo_DELETE pPinItemModel;
            }

            void WorldPinsService::HighlightPin(WorldPinItemModel* pinItemModel, std::string labelStyleName)
            {
                if(m_selectedPinId != pinItemModel->Id())
                {
                    RemoveHighlight(m_selectedPinId);
                }

                WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(pinItemModel->Id());
                AddHighlight(pWorldPinItemModel, labelStyleName);
            }

            void WorldPinsService::AddHighlight(WorldPinItemModel* pinItemModel, std::string labelStyleName)
            {
                if(pinItemModel != nullptr)
                {
                    bool pinAlreadySelected = m_selectedPinId == pinItemModel->Id();

                    UpdateLabelStyle(pinItemModel, "selected_default");

                    m_selectedSearchResultId = pinItemModel->GetIdentifier();
                    m_selectedPinId = pinItemModel->Id();

                    const auto& markerId = GetMarkerIdForWorldPinItemModelId(pinItemModel->Id());
                    Eegeo::Markers::IMarker& marker = m_markerService.Get(markerId);

                    if (m_pSelectedPinHighlight == nullptr || !pinAlreadySelected)
                    {
                        AddHighlightPin(pinItemModel, marker, labelStyleName);
                    }

                    const int highPriorityDrawOrder = 0;
                    marker.SetSubPriority(highPriorityDrawOrder);
                }
                else
                {
                    m_selectedSearchResultId = "";
                    m_selectedPinId = -1;
                }
            }

            void WorldPinsService::AddHighlightPin(const WorldPinItemModel* pinItemModel, const Eegeo::Markers::IMarker& marker, std::string labelStyleName)
            {
                const IWorldPinsInFocusModel& inFocusModel = pinItemModel->GetInFocusModel();
                const WorldPinFocusData focusData = WorldPinFocusData("", "", "", "", "", 0, inFocusModel.GetPriorityOrder() + 1);

                const Eegeo::Space::LatLong& location = marker.GetAnchorLocation().GetLatLong();
                float elevation = marker.GetElevation();

                m_pSelectedPinHighlight = AddPin(m_pinsToSelectionHandlers[pinItemModel->Id()],
                                                    m_pinsToVisbilityChangedHandlers[pinItemModel->Id()],
                                                    focusData,
                                                    pinItemModel->IsInterior(),
                                                    pinItemModel->GetInteriorData(),
                                                    location,
                                                    "selected_pin",
                                                    elevation,
                                                    pinItemModel->VisibilityMask(),
                                                    "selected_highlight",
                                                    labelStyleName);
            }

            void WorldPinsService::RemoveHighlight(SdkModel::WorldPinItemModel::WorldPinItemModelId id)
            {
                WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(id);
                if (pWorldPinItemModel != nullptr)
                {
                    UpdateLabelStyle(pWorldPinItemModel, "marker_faded_in");
                    RemoveHighlightPin(m_pSelectedPinHighlight);
                }
            }

            void WorldPinsService::RemoveHighlightPin(WorldPinItemModel* pPinItemModel)
            {
                if (m_pSelectedPinHighlight != nullptr)
                {
                    const Eegeo::Markers::IMarker::IdType markerId = GetWorldPinItemModelIdForMarkerId(pPinItemModel->Id());
                    m_markerService.Destroy(markerId);

                    m_worldPinsRepository.RemoveItem(pPinItemModel);
                    Eegeo_DELETE pPinItemModel;

                    m_pSelectedPinHighlight = nullptr;
                }
            }

            void WorldPinsService::UpdateLabelStyle(WorldPinItemModel* pinItemModel, const std::string& labelStyleName)
            {
                const auto& oldMarkerId = GetMarkerIdForWorldPinItemModelId(pinItemModel->Id());
                Eegeo::Markers::IMarker& oldMarker = m_markerService.Get(oldMarkerId);
                const Eegeo::Space::LatLong& location = oldMarker.GetAnchorLocation().GetLatLong();
                double elevation = oldMarker.GetElevation();
                m_markerService.Destroy(oldMarkerId);

                const IWorldPinsInFocusModel& inFocusModel = pinItemModel->GetInFocusModel();
                const WorldPinInteriorData interiorData = pinItemModel->GetInteriorData();

                WorldPinItemModel::WorldPinItemModelId pinId = pinItemModel->Id();

                IWorldPinSelectionHandler* pSelectionHandler = m_pinsToSelectionHandlers.at(pinId);
                m_pinsToSelectionHandlers.erase(pinId);

                IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler = m_pinsToVisbilityChangedHandlers.at(pinId);
                m_pinsToVisbilityChangedHandlers.erase(pinId);

                const std::string iconKey = m_pinsToIconKeys.at(pinId);
                m_pinsToIconKeys.erase(pinId);

                const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
                    .SetLocation(location.GetLatitudeInDegrees(), location.GetLongitudeInDegrees())
                    .SetElevation(elevation)
                    .SetLabelText(inFocusModel.GetTitle())
                    .SetLabelIcon(iconKey)
                    // temp workaround to specify interior floor by zero-based index rather than 'floor number' id (MPLY-8062)
                    .SetInteriorWithFloorIndex(interiorData.building.Value(), interiorData.floor)
                    .SetSubPriority(inFocusModel.GetPriorityOrder())
                    .SetLabelStyle(labelStyleName)
                    .Build();

                const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);
                pinId = markerId;

                m_pinsToSelectionHandlers[pinId] = pSelectionHandler;
                m_pinsToVisbilityChangedHandlers[pinId] = pVisibilityStateChangedHandler;
                m_pinsToIconKeys[pinId] = iconKey;

                pinItemModel->SetId(pinId);
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
                    if(m_selectedPinId != worldPinItemModelId)
                    {
                        RemoveHighlight(m_selectedPinId);
                    }
                    
                    selectionHandler->SelectPin();
                    ClearSelectedSearchResult();

                    WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(worldPinItemModelId);
                    AddHighlight(pWorldPinItemModel);

                    const Eegeo::Markers::IMarker::IdType markerId = GetMarkerIdForWorldPinItemModelId(pWorldPinItemModel->Id());
                    const Eegeo::Space::LatLong& location = m_markerService.Get(markerId).GetAnchorLocation().GetLatLong();

                    if(pWorldPinItemModel->IsInterior())
                    {
                        m_cameraTransitionController.StartTransitionTo(location.ToECEF(),
                                                                        InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance,
                                                                        pWorldPinItemModel->GetInteriorData().building,
                                                                        pWorldPinItemModel->GetInteriorData().floor);
                    }
                    else
                    {
                        const float pinAltitude = Helpers::PinHelpers::PIN_ALTITUDE;
                        m_cameraTransitionController.StartTransitionTo(location.ToECEF(), pinAltitude);
                    }
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
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsMode::GpsModeOff);
                    return true;
                }
                
                auto pickedMarkerId = Eegeo::Markers::IMarker::InvalidId;
                if (m_markerService.TryPick(screenPoint, pickedMarkerId))
                {
                    WorldPinItemModel::WorldPinItemModelId pinId = GetWorldPinItemModelIdForMarkerId(pickedMarkerId);

                    if (m_pSelectedPinHighlight != nullptr && pinId == m_pSelectedPinHighlight->Id())
                    {
                        pinId = m_selectedPinId;
                    }

                    SelectPin(pinId);
                    return true;
                }
                
                return false;
            }
            
            WorldPinItemModel* WorldPinsService::FindWorldPinItemModelOrNull(const std::string& searchResultId) const
            {
                if (searchResultId.empty())
                {
                    return nullptr;
                }
            
                for (int i = 0; i < m_worldPinsRepository.GetItemCount(); i++)
                {
                    WorldPinItemModel* pWorldPinItemModel = m_worldPinsRepository.GetItemAtIndex(i);
                    if (pWorldPinItemModel->GetIdentifier() == searchResultId)
                    {
                        return pWorldPinItemModel;
                    }
                }
                
                return nullptr;
            }

            WorldPinItemModel* WorldPinsService::FindWorldPinItemModelOrNull(SdkModel::WorldPinItemModel::WorldPinItemModelId id) const
            {
                if (id < 0)
                {
                    return nullptr;
                }

                for (int i = 0; i < m_worldPinsRepository.GetItemCount(); i++)
                {
                    WorldPinItemModel* pWorldPinItemModel = m_worldPinsRepository.GetItemAtIndex(i);
                    if (pWorldPinItemModel->Id() == id)
                    {
                        return pWorldPinItemModel;
                    }
                }

                return nullptr;
            }
            
            void WorldPinsService::OnMenuItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
            {
                std::string identifier = message.ModelIdentifier();

                WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(identifier);
                if (pWorldPinItemModel == nullptr)
                {
                    std::string title = "";
                    if (m_searchResultOnMapMyPinsService.TryGetPinTitleForSearchResultIdentifier(identifier, title))
                    {
                        identifier = title;
                        pWorldPinItemModel = FindWorldPinItemModelOrNull(identifier);
                    }
                }

                if(pWorldPinItemModel != nullptr)
                {
                    if (m_selectedSearchResultId != identifier)
                    {
                        RemoveHighlight(m_selectedPinId);
                    }
                
                    ClearSelectedSearchResult();
                
                    Eegeo_ASSERT(m_selectedSearchResultId.empty());
            
                    m_selectedSearchResultId = identifier;
                
                    AddHighlight(pWorldPinItemModel);
                }
            }
            
            void WorldPinsService::ClearSelectedSearchResult()
            {
                if (m_selectedSearchResultId.empty())
                {
                    return;
                }
                
                const WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(m_selectedSearchResultId);
                if (pWorldPinItemModel != nullptr)
                {
                    const auto& lastHighPriorityMarkerId = GetMarkerIdForWorldPinItemModelId(pWorldPinItemModel->Id());
                    
                    const int priorityOrder = pWorldPinItemModel->GetInFocusModel().GetPriorityOrder();
                    
                    Eegeo::Markers::IMarker& marker = m_markerService.Get(lastHighPriorityMarkerId);
                    marker.SetSubPriority(priorityOrder);
                }
                
                m_selectedSearchResultId.clear();
            }
        }
    }
}
