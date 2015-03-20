// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "UserCreatedMyPinDetailsModelSelectedMessage.h"
#include "SearchResultMyPinDetailsModelSelectedMessage.h"
#include "MyPinDetails.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            class MyPinDetailsModelSelectedObserver : private Eegeo::NonCopyable
            {
                IMyPinDetailsDisplayService& m_myPinDetailsDisplayService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<MyPinDetailsModelSelectedObserver, const UserCreatedMyPinDetailsModelSelectedMessage&> m_userCreatedBinding;
                Eegeo::Helpers::TCallback1<MyPinDetailsModelSelectedObserver, const SearchResultMyPinDetailsModelSelectedMessage&> m_searchResultBinding;

                void OnUserCreatedMyPinDetailsModelSelectedMessage(const UserCreatedMyPinDetailsModelSelectedMessage& message);
                void OnSearchResultMyPinDetailsModelSelectedMessage(const SearchResultMyPinDetailsModelSelectedMessage& message);

            public:
                MyPinDetailsModelSelectedObserver(IMyPinDetailsDisplayService& myPinDetailsDisplayService,
                                                  ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinDetailsModelSelectedObserver();
            };
        }
    }
}
