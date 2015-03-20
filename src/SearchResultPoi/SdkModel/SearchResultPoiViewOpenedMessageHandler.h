// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchResultPoiViewOpenedMessage.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            class SearchResultPoiViewOpenedMessageHandler : private Eegeo::NonCopyable
            {
                ExampleAppMessaging::TMessageBus& m_messageBus;
                ISearchResultPoiViewImageFetcher& m_searchResultPoiViewImageFetcher;
                
                Eegeo::Helpers::TCallback1<SearchResultPoiViewOpenedMessageHandler, const SearchResultPoiViewOpenedMessage&> m_handlerBinding;
                
                void OnSearchResultPoiViewOpenedMessage(const SearchResultPoiViewOpenedMessage& message);
                
            public:
                SearchResultPoiViewOpenedMessageHandler(ISearchResultPoiViewImageFetcher& searchResultPoiViewImageFetcher,
                                                        ExampleAppMessaging::TMessageBus& messageBus);
                
                ~SearchResultPoiViewOpenedMessageHandler();
            };
        }
    }
}
