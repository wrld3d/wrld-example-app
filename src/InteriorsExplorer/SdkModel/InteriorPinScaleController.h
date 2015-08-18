// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "InteriorPinsSetScaleMessage.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorPinScaleController : private Eegeo::NonCopyable
            {
            public:
                InteriorPinScaleController(Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                           ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InteriorPinScaleController();
                
            private:
                Eegeo::Resources::Interiors::InteriorsPinsController& m_interiorsPinsController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnSetScaleMessageReceived(const InteriorPinsSetScaleMessage& message);
                Eegeo::Helpers::TCallback1<InteriorPinScaleController, const InteriorPinsSetScaleMessage&> m_setScaleCallback;
            };
        }
    }
}