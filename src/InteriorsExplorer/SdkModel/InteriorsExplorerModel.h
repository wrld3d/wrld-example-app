// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteriorsExplorerSelectFloorMessage.h"
#include "InteriorPinsVisibilityMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModel : private Eegeo::NonCopyable
            {
            public:
                
                InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorsController& controller,
                                       ExampleAppMessaging::TMessageBus& messageBus);
                ~InteriorsExplorerModel();
                
                void SelectFloor(int floor);
                void Exit();
                
            private:
                
                void OnControllerStateChanged();
                void OnExit(const InteriorsExplorerExitMessage& message);
                void OnSelectFloor(const InteriorsExplorerSelectFloorMessage& message);
                void OnChangePinVisibility(const InteriorPinsVisibilityMessage& message);
                
                Eegeo::Resources::Interiors::InteriorsController& m_controller;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Helpers::TCallback0<InteriorsExplorerModel> m_controllerStateChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerExitMessage&> m_exitCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorsExplorerSelectFloorMessage&> m_selectFloorCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerModel, const InteriorPinsVisibilityMessage&> m_changePinVisibilityCallback;
            };
        }
    }
}