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
                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& m_messageBus;
                    const std::shared_ptr<TourExplorerCompositeViewController>& m_tourExplorerCompositeViewController;
                    
                    Eegeo::Helpers::TCallback1<TourSelectedViewObserver, const TourOnMapSelectedMessage&> m_binding;
                    
                    void HandleTourSelected(const TourOnMapSelectedMessage& message);
                    
                public:
                    TourSelectedViewObserver(const std::shared_ptr<TourExplorerCompositeViewController>& tourExplorerCompositeViewController,
                                             const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                    
                    ~TourSelectedViewObserver();
                };
            }
        }
    }
}
