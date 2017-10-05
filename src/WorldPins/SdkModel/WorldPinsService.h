// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "Types.h"
#include "WorldPins.h"
#include "IWorldPinsService.h"
#include "VectorMath.h"
#include "Labels.h"
#include "LabelModel.h"
#include "Pins.h"
#include "WorldPinItemModel.h"
#include "Interiors.h"
#include "LabelLayer.h"
#include "ILabelAnchorFilter.h"
#include "Markers.h"
#include "SdkModelDomainEventBus.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "BidirectionalBus.h"
#include "NavigationService.h"
#include "Search.h"
#include "CameraTransitions.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsService : public IWorldPinsService, private Eegeo::NonCopyable
            {
            public:

                
                WorldPinsService(
                                 IWorldPinsRepository& worldPinsRepository,
                                 Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService,
                                 Eegeo::Markers::IMarkerService& markerService,
                                 ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                 ExampleAppMessaging::TMessageBus& messageBus,
                                 Eegeo::Location::NavigationService& navigationService,
                                 Search::SdkModel::MyPins::ISearchResultMyPinsService& searchResultOnMapMyPinsService,
                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);
                ~WorldPinsService();
                
                WorldPinItemModel* AddPin(IWorldPinSelectionHandler* pSelectionHandler,
                                          IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                          const WorldPinFocusData& worldPinFocusData,
                                          bool interior,
                                          const WorldPinInteriorData& worldPinInteriorData,
                                          const Eegeo::Space::LatLong& location,
                                          const std::string& pinIconKey,
                                          float heightAboveTerrainMetres,
                                          int visibilityMask,
                                          std::string identifier = "",
                                          std::string labelStyleName = "marker_default");
                
                void RemovePin(WorldPinItemModel* pinItemModel);

                void HighlightPin(WorldPinItemModel* pinItemModel,
                                    std::string labelStyleName = "selected_highlight");
                
                bool HandleTouchTap(const Eegeo::v2& screenTapPoint);
                
                bool HandleTouchDoubleTap(const Eegeo::v2& screenTapPoint);
                
            private:
                
                IWorldPinSelectionHandler* GetSelectionHandlerForPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                bool TrySelectPinAtPoint(const Eegeo::v2& screenPoint);

                void SelectPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                void OnWorldPinHiddenStateChanged(const WorldPinHiddenStateChangedMessage& message);
                
                Eegeo::Markers::IMarker::IdType GetMarkerIdForWorldPinItemModelId(SdkModel::WorldPinItemModel::WorldPinItemModelId worldPinId) const;
                
                WorldPinItemModel::WorldPinItemModelId GetWorldPinItemModelIdForMarkerId(Eegeo::Markers::IMarker::IdType markerId) const;
                
                void OnMenuItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message);
                
                void ClearSelectedSearchResult();
                
                WorldPinItemModel* FindWorldPinItemModelOrNull(const std::string& searchResultId) const;
                WorldPinItemModel* FindWorldPinItemModelOrNull(SdkModel::WorldPinItemModel::WorldPinItemModelId id) const;

                void AddHighlight(WorldPinItemModel* pinItemModel, std::string labelStyleName = "selected_highlight");
                void AddHighlightPin(const WorldPinItemModel* pinItemModel, const Eegeo::Markers::IMarker& marker, std::string labelStyleName);
                void RemoveHighlight(SdkModel::WorldPinItemModel::WorldPinItemModelId id);
                void RemoveHighlightPin(WorldPinItemModel* pinItemModel);

                void UpdateLabelStyle(WorldPinItemModel* pinItemModel, const std::string& labelStyleName);
                
                IWorldPinsRepository& m_worldPinsRepository;
                Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& m_interiorMarkerPickingService;
                
                Eegeo::Location::NavigationService& m_navigationService;
                
                Eegeo::Markers::IMarkerService& m_markerService;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkModelDomainEventBus;
                
                Eegeo::Helpers::TCallback1<WorldPinsService, const WorldPinHiddenStateChangedMessage&> m_worldPinHiddenStateChangedMessageBinding;
                Eegeo::Helpers::TCallback1<WorldPinsService, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_onSearchResultSelected;

                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinSelectionHandler*> TPinToSelectionHandlerMap;
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinVisibilityStateChangedHandler*> TPinToVisiblityHandlerMap;
                
                
                TPinToSelectionHandlerMap m_pinsToSelectionHandlers;
                TPinToVisiblityHandlerMap m_pinsToVisbilityChangedHandlers;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                std::map<WorldPinItemModel::WorldPinItemModelId, std::string> m_pinsToIconKeys;

                std::string m_selectedSearchResultId;

                WorldPinItemModel* m_pSelectedPinHighlight;

                WorldPinItemModel::WorldPinItemModelId m_selectedPinId;

                const Search::SdkModel::MyPins::ISearchResultMyPinsService& m_searchResultOnMapMyPinsService;

                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
            };

        }
    }
}
