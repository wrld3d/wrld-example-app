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
                                 ExampleAppMessaging::TMessageBus& messageBus);
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
                                          const std::string& tag,
                                          std::string identifier = "");
                
                void RemovePin(WorldPinItemModel* pinItemModel);

                void UpdatePinCategory(const WorldPinItemModel& pinItemModel, const std::string& iconKey);

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
                
                void ResetLastMarkerSubPriority();
                
                IWorldPinsRepository& m_worldPinsRepository;
                Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& m_interiorMarkerPickingService;
                
                Eegeo::Markers::IMarkerService& m_markerService;
                ExampleAppMessaging::TSdkModelDomainEventBus& m_sdkModelDomainEventBus;
                
                Eegeo::Helpers::TCallback1<WorldPinsService, const WorldPinHiddenStateChangedMessage&> m_worldPinHiddenStateChangedMessageBinding;
                Eegeo::Helpers::TCallback1<WorldPinsService, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_onSearchResultSelected;

                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinSelectionHandler*> TPinToSelectionHandlerMap;
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinVisibilityStateChangedHandler*> TPinToVisiblityHandlerMap;
                
                
                TPinToSelectionHandlerMap m_pinsToSelectionHandlers;
                TPinToVisiblityHandlerMap m_pinsToVisbilityChangedHandlers;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Markers::IMarker::IdType m_lastHighPriorityMarkerId;
            };

        }
    }
}
