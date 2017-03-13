// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "InteriorsExplorer.h"
#include <map>
#include <string>
#include "BidirectionalBus.h"
#include "InitialExperience.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorWorldPinController
            {
            public:
                
                InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                           ExampleAppMessaging::TMessageBus& messageBus,
                                           const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel);
                ~InteriorWorldPinController();
                
                const bool PinInteractionAllowed(const std::string& interiorId) const;
                
            private:

                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;

                ExampleAppMessaging::TMessageBus& m_messageBus;
                const InitialExperience::SdkModel::IInitialExperienceModel& m_initialExperienceModel;
                bool m_menuIsDragging;
                
                
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Menu::MenuDragStateChangedMessage&> m_menuDraggedCallback;
                
                void HandleMenuDragged(const Menu::MenuDragStateChangedMessage& message);
            };
        }
    }
}