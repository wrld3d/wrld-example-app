// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "Types.h"
#include "Pins.h"
#include "PinController.h"
#include "WorldPins.h"
#include "IWorldPinsService.h"
#include "VectorMath.h"
#include "EnvironmentFlatteningService.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsService : public IWorldPinsService, private Eegeo::NonCopyable
            {
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinSelectionHandler*> TPinToSelectionHandlerMap;
                typedef TPinToSelectionHandlerMap::iterator TPinToSelectionHandlerMapIt;
                
                typedef std::map<WorldPinItemModel::WorldPinItemModelId, IWorldPinVisibilityStateChangedHandler*> TPinToVisiblityHandlerMap;
                typedef TPinToVisiblityHandlerMap::iterator TPinToVisiblityHandlerMapIt;

                TPinToSelectionHandlerMap m_pinsToSelectionHandlers;
                TPinToVisiblityHandlerMap m_pinsToVisbilityChangedHandlers;

                const std::shared_ptr<IWorldPinsRepository> m_worldPinsRepository;
                const std::shared_ptr<IWorldPinsFactory> m_worldPinsFactory;
                const std::shared_ptr<Eegeo::Pins::PinRepository> m_pinRepository;
                const std::shared_ptr<Eegeo::Pins::PinController> m_pinController;
                const std::shared_ptr<const Eegeo::Rendering::EnvironmentFlatteningService> m_environmentFlatteningService;
                const std::shared_ptr<const IWorldPinIconMapping> m_worldPinIconMapping;
                bool m_pinAlreadySelected;

            public:
                WorldPinsService(const std::shared_ptr<IWorldPinsRepository>& worldPinsRepository,
                                 const std::shared_ptr<IWorldPinsFactory>& worldPinsFactory,
                                 const std::shared_ptr<Eegeo::Pins::PinRepository>& pinRepository,
                                 const std::shared_ptr<Eegeo::Pins::PinController>& pinController,
                                 const std::shared_ptr<Eegeo::Rendering::EnvironmentFlatteningService>& environmentFlatteningService,
                                 const std::shared_ptr<IWorldPinIconMapping>& worldPinIconMapping);

                ~WorldPinsService();

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

                bool HandleTouchTap(const Eegeo::v2& screenTapPoint);

				bool HandleTouchDoubleTap(const Eegeo::v2& screenTapPoint);

                void GetPinEcefAndScreenLocations(const WorldPinItemModel& pinItemModel,
                                                  Eegeo::dv3& ecefLocation,
                                                  Eegeo::v2& screenLocation) const;

                void SelectPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                void Update(float dt);

            private:
                IWorldPinSelectionHandler* GetSelectionHandlerForPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId);
                
                void ErasePin(const WorldPinItemModel::WorldPinItemModelId& id);

				bool TrySelectPinAtPoint(const Eegeo::v2& screenPoint);

            };
        }
    }
}
