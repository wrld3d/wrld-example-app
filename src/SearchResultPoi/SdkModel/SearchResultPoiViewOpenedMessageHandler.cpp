// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewOpenedMessageHandler.h"
#include "ISearchResultPoiViewImageFetcher.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            SearchResultPoiViewOpenedMessageHandler::SearchResultPoiViewOpenedMessageHandler(ISearchResultPoiViewImageFetcher& searchResultPoiViewImageFetcher,
                                                                                             ExampleAppMessaging::TMessageBus& messageBus)
            : m_searchResultPoiViewImageFetcher(searchResultPoiViewImageFetcher)
            , m_messageBus(messageBus)
            , m_handlerBinding(this, &SearchResultPoiViewOpenedMessageHandler::OnSearchResultPoiViewOpenedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }
            
            SearchResultPoiViewOpenedMessageHandler::~SearchResultPoiViewOpenedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }
            
            void SearchResultPoiViewOpenedMessageHandler::OnSearchResultPoiViewOpenedMessage(const SearchResultPoiViewOpenedMessage& message)
            {
                if(!message.GetImageUrl().empty())
                {
                    m_searchResultPoiViewImageFetcher.FetchImageForSearchResult(message.GetImageUrl());
                }
            }
        }
    }
}
