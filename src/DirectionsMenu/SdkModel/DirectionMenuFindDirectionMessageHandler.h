// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "FindDirectionQueryPerformer.h"
#include "DirectionMenuFindDirectionMessage.h"

namespace ExampleApp
{
    namespace DirectiondMenu
    {
        namespace SdkModel
        {
            class DirectionMenuFindDirectionMessageHandler : private Eegeo::NonCopyable
            {
            private:
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Direction::SdkModel::FindDirectionQueryPerformer& m_findDirectionQueryPerformer;
                
                Eegeo::Helpers::TCallback1<DirectionMenuFindDirectionMessageHandler, const DirectionsMenu::DirectionMenuFindDirectionMessage&> m_handleFindDirectionMessageBinding;
                
                void OnFindDirectionMessage(const DirectionsMenu::DirectionMenuFindDirectionMessage& message);


                
            public:
                
                DirectionMenuFindDirectionMessageHandler(ExampleAppMessaging::TMessageBus& messageBus,Direction::SdkModel::FindDirectionQueryPerformer& findDirectionQueryPerformer);
                ~DirectionMenuFindDirectionMessageHandler();
                
            };
        }
    }
}
