// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInteriorsEntitiesPinsController.h"
#include "BidirectionalBus.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsUINotificationService : public Eegeo::NonCopyable
            {
            public:
                
                InteriorsUINotificationService(ExampleAppMessaging::TMessageBus& messageBus,
                                               InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController& interiorsPinsController,
                                               const WorldPins::SdkModel::IWorldPinIconMapping& pinIconMapping);
                
                ~InteriorsUINotificationService();
                
            private:
                InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController& m_interiorsPinsController;

                Eegeo::Helpers::TCallback1<InteriorsUINotificationService, const std::vector<Eegeo::Pins::Pin*>&> m_interiorsPinSelectedCallback;
                void OnInteriorPinSelected(const std::vector<Eegeo::Pins::Pin*>& selectedPins);

                std::vector<int> m_notifiableIcons;
                bool RequiresUINotification(int iconCategory);

                ExampleAppMessaging::TMessageBus& m_messageBus;
            };
        }
    }
}