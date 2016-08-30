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
                const std::shared_ptr<ISearchResultPoiMyPinService> m_searchResultPoiMyPinService;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultPoiPinToggledMessageHandler, const SearchResultPoiPinToggledMessage&> m_handlerBinding;
                
                void OnSearchResultPoiPinToggled(const SearchResultPoiPinToggledMessage& message);
                
            public:
                SearchResultPoiPinToggledMessageHandler(const std::shared_ptr<ISearchResultPoiMyPinService>& searchResultPoiMyPinService,
                                                        const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                
                ~SearchResultPoiPinToggledMessageHandler();
            };
        }
    }
}
