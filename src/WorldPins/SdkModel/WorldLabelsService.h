// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
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

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            // Alternative WorldPinsService that deals in labels.
            class WorldLabelsService : public IWorldPinsService, private Eegeo::NonCopyable
            {
            public:
                
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinSelectionHandler*> TPinToSelectionHandlerMap;
                typedef TPinToSelectionHandlerMap::iterator TPinToSelectionHandlerMapIt;
                
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinVisibilityStateChangedHandler*> TPinToVisiblityHandlerMap;
                typedef TPinToVisiblityHandlerMap::iterator TPinToVisiblityHandlerMapIt;
                
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, Eegeo::Labels::LabelModel::IdType> TWorldPinToLabelMap;
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, WorldPinItemModel*> TWorldPinItemModelMap;
                
                WorldLabelsService(Eegeo::Labels::ILabelModelService& labelModelService,
                                   Eegeo::Labels::ILabelAnchorFilterModel& labelAnchorFilterModel,
                                   const Eegeo::Labels::LabelAnchorCategory& labelAnchorCategory,
                                   Eegeo::Labels::ILabelPicker& labelPicker,
                                   const Eegeo::Labels::LabelLayer::IdType& labelLayerId,
                                   IWorldPinsRepository& worldPinsRepository,
                                   Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService);
                ~WorldLabelsService();
                
                WorldPinItemModel* AddPin(IWorldPinSelectionHandler* pSelectionHandler,
                                          IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                          const WorldPinFocusData& worldPinFocusData,
                                          bool interior,
                                          const WorldPinInteriorData& worldPinInteriorData,
                                          const Eegeo::Space::LatLong& location,
                                          const std::string& pinIconKey,
                                          float heightAboveTerrainMetres,
                                          int visibilityMask);
                
                void RemovePin(WorldPinItemModel* pinItemModel);
                
                void UpdatePinScale(const WorldPinItemModel& pinItemModel, float scale);
                
                void GetPinEcefAndScreenLocations(const WorldPinItemModel& pinItemModel,
                                                          Eegeo::dv3& ecefLocation,
                                                          Eegeo::v2& screenLocation) const;
                
                bool HandleTouchTap(const Eegeo::v2& screenTapPoint);
                
                bool HandleTouchDoubleTap(const Eegeo::v2& screenTapPoint);
                
                void SelectPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                void Update(float dt) ;
                
                
            private:
                
                IWorldPinSelectionHandler* GetSelectionHandlerForPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                void Erase(const WorldPinItemModel::WorldPinItemModelId& id);
                
                bool TrySelectPinAtPoint(const Eegeo::v2& screenPoint);
                
                bool LabelHiddenPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const;
                
                Eegeo::Labels::ILabelModelService& m_labelModelService;
                Eegeo::Labels::ILabelAnchorFilterModel& m_labelAnchorFilterModel;
                const Eegeo::Labels::LabelAnchorCategory& m_labelAnchorCategory;
                Eegeo::Labels::ILabelPicker& m_labelPicker;
                IWorldPinsRepository& m_worldPinsRepository;
                Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& m_interiorMarkerPickingService;
                Eegeo::Pins::TPinId m_lastLabelId;
                const Eegeo::Labels::LabelLayer::IdType m_labelLayerId;
                Eegeo::Labels::TLabelAnchorFilter<WorldLabelsService> m_labelHiddenFilter;
                
                TPinToSelectionHandlerMap m_pinsToSelectionHandlers;
                TPinToVisiblityHandlerMap m_pinsToVisbilityChangedHandlers;
                TWorldPinToLabelMap m_worldPinsToLabels;
                TWorldPinItemModelMap m_worldPinItemModelMap;
                
                bool m_pinAlreadySelected;
            };

        }
    }
}
