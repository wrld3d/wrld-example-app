// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "TourOnMapSelectedMessage.h"
#include "TourExplorerCompositeViewController.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                class TourSelectedViewObserver : private Eegeo::NonCopyable
                {
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    TourExplorerCompositeViewController& m_tourExplorerCompositeViewController;
                    
                    Eegeo::Helpers::TCallback1<TourSelectedViewObserver, const TourOnMapSelectedMessage&> m_binding;
                    
                    void HandleTourSelected(const TourOnMapSelectedMessage& message);
                    
                public:
                    TourSelectedViewObserver(TourExplorerCompositeViewController& tourExplorerCompositeViewController,
                                             ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~TourSelectedViewObserver();
                };
            }
        }
    }
}
