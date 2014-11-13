// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapModalityObserver.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapModalityObserver::SearchResultOnMapModalityObserver(SearchResultOnMapScaleController& searchResultOnMapScaleController,
                                                                             ExampleAppMessaging::UiToNativeMessageBus& messageBus)
        : m_searchResultOnMapScaleController(searchResultOnMapScaleController)
        , m_messageBus(messageBus)
        , m_handlerBinding(this, &SearchResultOnMapModalityObserver::HandleReceivedModalityChangedMessage)
        {
            m_messageBus.Subscribe(m_handlerBinding);
        }
        
        SearchResultOnMapModalityObserver::~SearchResultOnMapModalityObserver()
        {
            m_messageBus.Unsubscribe(m_handlerBinding);
        }
        
        void SearchResultOnMapModalityObserver::HandleReceivedModalityChangedMessage(const Modality::ModalityChangedMessage& message)
        {
            m_searchResultOnMapScaleController.SetModality(message.Modality());
        }
    }
}
