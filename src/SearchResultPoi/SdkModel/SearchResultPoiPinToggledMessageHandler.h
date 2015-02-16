// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "SearchResultModel.h"
#include "SearchResultPoiPinToggledMessage.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            class SearchResultPoiPinToggledMessageHandler : Eegeo::NonCopyable
            {
                ISearchResultPoiMyPinService& m_searchResultPoiMyPinService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultPoiPinToggledMessageHandler, const SearchResultPoiPinToggledMessage&> m_handlerBinding;
                
                void OnSearchResultPoiPinToggled(const SearchResultPoiPinToggledMessage& message);
                
            public:
                SearchResultPoiPinToggledMessageHandler(ISearchResultPoiMyPinService& searchResultPoiMyPinService,
                                                        ExampleAppMessaging::TMessageBus& messageBus);
                
                ~SearchResultPoiPinToggledMessageHandler();
            };
        }
    }
}
