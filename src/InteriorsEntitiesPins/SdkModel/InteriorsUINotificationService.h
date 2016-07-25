// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInteriorsEntitiesPinsController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsUINotificationService : public Eegeo::NonCopyable
            {
            public:
                
                InteriorsUINotificationService(InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController& interiorsPinsController);
                
                ~InteriorsUINotificationService();
                
            private:
                InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController& m_interiorsPinsController;

                Eegeo::Helpers::TCallback1<InteriorsUINotificationService, const std::vector<Eegeo::Pins::Pin*>&> m_interiorsPinSelectedCallback;
                void OnInteriorPinSelected(const std::vector<Eegeo::Pins::Pin*>& selectedPins);

                std::vector<int> m_notifiableIcons;
                bool RequiresUINotification(int iconCategory);
            };
        }
    }
}