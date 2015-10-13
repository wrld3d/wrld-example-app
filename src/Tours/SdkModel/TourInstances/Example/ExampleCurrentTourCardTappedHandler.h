// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CurrentTourCardTappedMessage.h"
#include "Tours.h"
#include "BidirectionalBus.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace TourInstances
            {
                namespace Example
                {
                    class ExampleCurrentTourCardTappedHandler
                    {
                        
                    public:
                        ExampleCurrentTourCardTappedHandler(ExampleAppMessaging::TMessageBus& messageBus,TourStateModel& stateModel);
                        ~ExampleCurrentTourCardTappedHandler();
                        
                    private:
                        
                        void OnCurrentTourCardTapped(const CurrentTourCardTappedMessage& message);
                        
                        ExampleAppMessaging::TMessageBus& m_messageBus;
                        TourStateModel& m_stateModel;
                        std::string CreateJsonData();
                        
                        Eegeo::Helpers::TCallback1<ExampleCurrentTourCardTappedHandler, const CurrentTourCardTappedMessage&> m_currentTourCardTappedCallback;
                    };
                }
            }
        }
    }
}
