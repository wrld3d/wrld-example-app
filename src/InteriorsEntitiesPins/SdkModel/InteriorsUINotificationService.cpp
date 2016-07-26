// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsUINotificationService.h"
#include "InteriorsEntitiesPinsController.h"
#include "InteriorsExplorerUINotifyMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            const int NumNotifiableIcons = 3;

            InteriorsUINotificationService::InteriorsUINotificationService(ExampleAppMessaging::TMessageBus& messageBus,
                                                                           InteriorsEntitiesPins::SdkModel::IInteriorsEntitiesPinsController& interiorsPinsController)
                : m_interiorsPinsController(interiorsPinsController)
                , m_interiorsPinSelectedCallback(this, &InteriorsUINotificationService::OnInteriorPinSelected)
                , m_notifiableIcons(NumNotifiableIcons)
                , m_messageBus(messageBus)
            {
                m_interiorsPinsController.RegisterInteriorsPinSelected(m_interiorsPinSelectedCallback);

                m_notifiableIcons[0] = InteriorsEntitiesPins::SdkModel::InteriorsPinIconType::Elevator;
                m_notifiableIcons[1] = InteriorsEntitiesPins::SdkModel::InteriorsPinIconType::Escalator;
                m_notifiableIcons[2] = InteriorsEntitiesPins::SdkModel::InteriorsPinIconType::Stairs;
            }

            InteriorsUINotificationService::~InteriorsUINotificationService()
            {
                m_interiorsPinsController.UnregisterInteriorsPinSelected(m_interiorsPinSelectedCallback);
            }

            void InteriorsUINotificationService::OnInteriorPinSelected(const std::vector<Eegeo::Pins::Pin*>& selectedPins)
            {
                for (std::vector<Eegeo::Pins::Pin*>::const_iterator i = selectedPins.begin();
                    i != selectedPins.end();
                    ++i)
                {
                    if (RequiresUINotification((*i)->GetCategoryId()))
                    {
                        m_messageBus.Publish(InteriorsExplorer::InteriorsExplorerUINotifyMessage());
                    }
                }
            }

            bool InteriorsUINotificationService::RequiresUINotification(int iconCategory)
            {
                if (std::find(m_notifiableIcons.begin(), m_notifiableIcons.end(), iconCategory) != m_notifiableIcons.end())
                {
                    return true;
                }

                return false;
            }
        }
    }
}