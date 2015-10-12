// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "WorldPinItemModel.h"
#include "Space.h"
#include "VectorMath.h"
#include "WorldPinFocusData.h"
#include "WorldPinInteriorData.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class IWorldPinsService
            {
            public:
                virtual ~IWorldPinsService() {}

                virtual WorldPinItemModel* AddPin(IWorldPinSelectionHandler* pSelectionHandler,
                                                  IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                                  const WorldPinFocusData& worldPinFocusData,
                                                  bool interior,
                                                  const WorldPinInteriorData& worldPinInteriorData,
                                                  const Eegeo::Space::LatLong& location,
                                                  int iconIndex,
                                                  float heightAboveTerrainMetres,
                                                  int visibilityMask) = 0;

                virtual void RemovePin(WorldPinItemModel* pinItemModel) = 0;

                virtual void UpdatePinScale(const WorldPinItemModel& pinItemModel, float scale) = 0;

                virtual void GetPinEcefAndScreenLocations(const WorldPinItemModel& pinItemModel,
                        Eegeo::dv3& ecefLocation,
                        Eegeo::v2& screenLocation) const = 0;

                virtual bool HandleTouchTap(const Eegeo::v2& screenTapPoint) = 0;

                virtual IWorldPinSelectionHandler* GetSelectionHandlerForPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId) = 0;

            };
        }
    }
}
