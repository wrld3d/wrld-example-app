// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourSelectedViewObserver.h"
#include "TourExplorerCompositeViewController.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourExplorer
            {
                TourSelectedViewObserver::TourSelectedViewObserver(const std::shared_ptr<TourExplorerCompositeViewController>& tourExplorerCompositeViewController,
                                                                   const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
                : m_tourExplorerCompositeViewController(tourExplorerCompositeViewController)
                , m_messageBus(messageBus)
                , m_binding(this, &TourSelectedViewObserver::HandleTourSelected)
                {
                    m_messageBus->SubscribeUi(m_binding);
                }
                
                TourSelectedViewObserver::~TourSelectedViewObserver()
                {
                    m_messageBus->UnsubscribeUi(m_binding);
                }
                
                void TourSelectedViewObserver::HandleTourSelected(const TourOnMapSelectedMessage& message)
                {
                    m_tourExplorerCompositeViewController->OpenTourExplorer(message.GetTourModel(), message.GetInitialCard(), message.GetShowBackButton());
                }
            }
        }
    }
}
