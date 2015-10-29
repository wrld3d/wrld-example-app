// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionEnabledObserver.h"

// App includes
#include "UserInteractionEnabledChangedMessage.h"
#include "UserInteractionModel.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            UserInteractionEnabledObserver::UserInteractionEnabledObserver(UserInteractionModel& userInteractionModel, ExampleAppMessaging::TMessageBus& messageBus)
            : m_userInteractionModel(userInteractionModel)
            , m_messageBus(messageBus)
            , m_userInteractionEnabledChangedHandler(this, &UserInteractionEnabledObserver::OnUserInteractionEnabledChanged)
            {
                m_userInteractionModel.InsertEnabledChangedCallback(m_userInteractionEnabledChangedHandler);
            }
            
            UserInteractionEnabledObserver::~UserInteractionEnabledObserver()
            {
                m_userInteractionModel.RemoveEnabledChangedCallback(m_userInteractionEnabledChangedHandler);
            }
            
            void UserInteractionEnabledObserver::OnUserInteractionEnabledChanged()
            {
                m_messageBus.Publish(UserInteractionEnabledChangedMessage(m_userInteractionModel.IsEnabled()));
            }
        }
    }
}