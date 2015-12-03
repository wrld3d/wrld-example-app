// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinSelectionHandler.h"

#include <string>
#include "Tours.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace TwitterFeed
                {
                    class TwitterFeedPinSelectionHandler : public WorldPins::SdkModel::IWorldPinSelectionHandler
                    {
                    private:
                        TourStateModel m_tourStateModel;
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        
                    public:
                        TwitterFeedPinSelectionHandler(const TourStateModel& tourStateModel,
                                                       ExampleAppMessaging::TMessageBus& messageBus);
                        ~TwitterFeedPinSelectionHandler();
                        
                        void SelectPin();
                    };
                }
            }
        }
    }
}
