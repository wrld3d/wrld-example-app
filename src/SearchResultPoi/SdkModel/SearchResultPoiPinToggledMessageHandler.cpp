// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiPinToggledMessageHandler.h"
#include "SearchResultModel.h"
#include "ISearchResultPoiMyPinService.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            SearchResultPoiPinToggledMessageHandler::SearchResultPoiPinToggledMessageHandler(ISearchResultPoiMyPinService& searchResultPoiMyPinService,
                                                                                             ExampleAppMessaging::TMessageBus& messageBus)
            : m_searchResultPoiMyPinService(searchResultPoiMyPinService)
            , m_messageBus(messageBus)
            , m_handlerBinding(this, &SearchResultPoiPinToggledMessageHandler::OnSearchResultPoiPinToggled)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }
            
            SearchResultPoiPinToggledMessageHandler::~SearchResultPoiPinToggledMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }
            
            void SearchResultPoiPinToggledMessageHandler::OnSearchResultPoiPinToggled(const SearchResultPoiPinToggledMessage& message)
            {
                Search::SdkModel::SearchResultModel searchResult = message.GetModel();
                m_searchResultPoiMyPinService.AddOrRemoveSearchResultFromMyPins(searchResult);
            }
        }
    }
}
