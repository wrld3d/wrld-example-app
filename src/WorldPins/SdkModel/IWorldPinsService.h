// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "WorldPinItemModel.h"
#include "Space.h"
#include "VectorMath.h"
#include "WorldPinFocusData.h"
#include "WorldPinInteriorData.h"

#include <string>

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
                                                  const std::string& pinIconKey,
                                                  float heightAboveTerrainMetres,
                                                  int visibilityMask,
                                                  std::string id = "",
                                                  std::string labelStyleName = "marker_default") = 0;

                virtual void RemovePin(WorldPinItemModel* pinItemModel) = 0;

                virtual void HighlightPin(WorldPinItemModel* pinItemModel,
                                            std::string labelStyleName = "selected_highlight") = 0;

                virtual bool HandleTouchTap(const Eegeo::v2& screenTapPoint) = 0;

				virtual bool HandleTouchDoubleTap(const Eegeo::v2& screenTapPoint) = 0;
            };
        }
    }
}
