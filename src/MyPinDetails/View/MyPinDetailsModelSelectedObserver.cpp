// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModelSelectedObserver.h"
#include "IMyPinDetailsDisplayService.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsModelSelectedObserver::MyPinDetailsModelSelectedObserver(IMyPinDetailsDisplayService& myPinDetailsDisplayService,
                                                                                 ExampleAppMessaging::TMessageBus& messageBus)
                : m_myPinDetailsDisplayService(myPinDetailsDisplayService)
                , m_messageBus(messageBus)
                , m_userCreatedBinding(this, &MyPinDetailsModelSelectedObserver::OnUserCreatedMyPinDetailsModelSelectedMessage)
                , m_searchResultBinding(this, &MyPinDetailsModelSelectedObserver::OnSearchResultMyPinDetailsModelSelectedMessage)
            {
                m_messageBus.SubscribeUi(m_userCreatedBinding);
                m_messageBus.SubscribeUi(m_searchResultBinding);
            }

            MyPinDetailsModelSelectedObserver::~MyPinDetailsModelSelectedObserver()
            {
                m_messageBus.UnsubscribeUi(m_searchResultBinding);
                m_messageBus.UnsubscribeUi(m_userCreatedBinding);
            }
            
            void MyPinDetailsModelSelectedObserver::OnUserCreatedMyPinDetailsModelSelectedMessage(const UserCreatedMyPinDetailsModelSelectedMessage& message)
            {
                m_myPinDetailsDisplayService.DisplayUserCreatedMyPinDetails(message.GetMyPinId(),
                                                                            message.GetMyPinTitle(),
                                                                            message.GetMyPinDescription(),
                                                                            message.GetImagePath());
            }
            
            void MyPinDetailsModelSelectedObserver::OnSearchResultMyPinDetailsModelSelectedMessage(const SearchResultMyPinDetailsModelSelectedMessage& message)
            {
                m_myPinDetailsDisplayService.DisplaySearchResultMyPinDetails(message.GetSearchResultModel());
            }
        }
    }
}
