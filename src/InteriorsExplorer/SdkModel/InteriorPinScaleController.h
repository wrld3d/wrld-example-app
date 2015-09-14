// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "MyPinCreation.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "AppModes.h"

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
                                           AppModes::SdkModel::IAppModeModel& appModeModel,
                                           ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InteriorPinScaleController();
                
            private:
                enum ModalMenuState
                {
                    Closed,
                    Opening,
                    Open,
                    Closing
                };
                void UpdateInteriorPinsHiddenState();
            
                Eegeo::Resources::Interiors::InteriorsPinsController& m_interiorsPinsController;
                AppModes::SdkModel::IAppModeModel& m_appModeModel;
                ModalMenuState m_modalMenuState;
                bool m_myPinCreateOpen;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                void OnModalityChangedMessage(const Modality::ModalityChangedMessage& message);
                void OnMyPinCreationStateChanged(const MyPinCreation::MyPinCreationStateChangedMessage& message);
                void OnAppModeChanged();
                bool ShouldHidePins() const;
                
                
                Eegeo::Helpers::TCallback1<InteriorPinScaleController, const Modality::ModalityChangedMessage&> m_modalityChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorPinScaleController, const MyPinCreation::MyPinCreationStateChangedMessage&> m_myPinCreationStateChangedCallback;
                Eegeo::Helpers::TCallback0<InteriorPinScaleController> m_appModeChangedCallback;
            };
        }
    }
}