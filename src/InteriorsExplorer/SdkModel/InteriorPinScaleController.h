// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "ICallback.h"

namespace ExampleApp
{
    class IAppModeModel;
    
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorPinScaleController : private Eegeo::NonCopyable
            {
            public:
                InteriorPinScaleController(Eegeo::Resources::Interiors::InteriorsPinsController& interiorsPinsController,
                                           IAppModeModel& appModeModel,
                                           ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InteriorPinScaleController();
                
            private:
                void UpdateInteriorPinsHiddenState();
            
                Eegeo::Resources::Interiors::InteriorsPinsController& m_interiorsPinsController;
                IAppModeModel& m_appModeModel;
                bool m_modalMenuOpen;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnModalityChangedMessage(const Modality::ModalityChangedMessage& message);
                void OnAppModeChanged();
                
                
                Eegeo::Helpers::TCallback1<InteriorPinScaleController, const Modality::ModalityChangedMessage&> m_modalityChangedCallback;
                Eegeo::Helpers::TCallback0<InteriorPinScaleController> m_appModeChangedCallback;
            };
        }
    }
}