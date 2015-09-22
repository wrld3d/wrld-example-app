// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "ActiveTourQuitSelectedMessage.h"
#include "Search.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class ActiveTourQuitSelectedMessageHandler : private Eegeo::NonCopyable
            {
                ITourService& m_tourService;
                Search::SdkModel::ISearchRefreshService& m_searchRefreshService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Helpers::TCallback1<ActiveTourQuitSelectedMessageHandler, const ActiveTourQuitSelectedMessage&> m_binding;
                
                void HandleActiveTourQuitSelected(const ActiveTourQuitSelectedMessage& message);
                
            public:
                ActiveTourQuitSelectedMessageHandler(ITourService& tourService,
                                                     Search::SdkModel::ISearchRefreshService& searchRefreshService,
                                                     ExampleAppMessaging::TMessageBus& messageBus);
                
                ~ActiveTourQuitSelectedMessageHandler();
            };
        }
    }
}
