// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinSelectionHandler.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class WayPointSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler, private Eegeo::NonCopyable
            {
            public:
                WayPointSelectionHandler();
                
                virtual ~WayPointSelectionHandler();

                void SelectPin();
            };
        }
    }
}
