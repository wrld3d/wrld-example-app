// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinSelectionHandler.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            class WayPointSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler, private Eegeo::NonCopyable
            {
                ExampleAppMessaging::TMessageBus& m_messageBus;
            public:
                WayPointSelectionHandler(ExampleAppMessaging::TMessageBus& messageBus);
                
                virtual ~WayPointSelectionHandler();

                void SelectPin();
            };
        }
    }
}
