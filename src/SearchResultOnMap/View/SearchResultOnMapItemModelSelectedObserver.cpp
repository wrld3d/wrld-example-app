// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModelSelectedObserver.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            SearchResultOnMapItemModelSelectedObserver::SearchResultOnMapItemModelSelectedObserver(const std::shared_ptr<SearchResultPoi::View::ISearchResultPoiViewModel>& searchResultPoiViewModel,
                                                                                                   const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                                                                   const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction)
                : m_searchResultPoiViewModel(searchResultPoiViewModel)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &SearchResultOnMapItemModelSelectedObserver::OnSearchResultOnMapItemModelSelectedMessage)
                , m_menuReaction(menuReaction)
            {
                m_messageBus->SubscribeUi(m_handlerBinding);
            }

            SearchResultOnMapItemModelSelectedObserver::~SearchResultOnMapItemModelSelectedObserver()
            {
                m_messageBus->UnsubscribeUi(m_handlerBinding);
            }

            void SearchResultOnMapItemModelSelectedObserver::OnSearchResultOnMapItemModelSelectedMessage(const SearchResultOnMapItemModelSelectedMessage& message)
            {
                if (m_menuReaction->GetShouldOpenMenu())
                {
                    if (!m_searchResultPoiViewModel->IsOpen())
                    {
                        m_searchResultPoiViewModel->Open(message.GetModel(), false);
                    }
                }
                else
                {
                    m_searchResultPoiViewModel->Open(message.GetModel(), false);
                }
            }
        }
    }
}
