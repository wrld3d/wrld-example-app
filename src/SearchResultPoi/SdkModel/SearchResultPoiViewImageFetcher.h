// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "ISearchResultPoiViewImageFetcher.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            class SearchResultPoiViewImageFetcher : public ISearchResultPoiViewImageFetcher, private Eegeo::NonCopyable
            {
                const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory> m_webRequestFactory;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Web::TWebLoadRequestCompletionCallback<SearchResultPoiViewImageFetcher> m_webRequestCallback;
                
                void OnImageFetchResponseReceived(Eegeo::Web::IWebResponse& webResponse);
                
            public:
                SearchResultPoiViewImageFetcher(const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory>& webRequestFactory,
                                                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                
                ~SearchResultPoiViewImageFetcher();
                
                void FetchImageForSearchResult(const std::string& imageUrl);
            };
        }
    }
}
