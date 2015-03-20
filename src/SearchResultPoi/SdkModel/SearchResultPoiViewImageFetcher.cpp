// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <vector>
#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "SearchResultPoiViewImageFetcher.h"
#include "IWebLoadRequestFactory.h"
#include "SearchResultPoiViewImageDownloadCompletedMessage.h"
#include "IWebLoadRequest.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            
            SearchResultPoiViewImageFetcher::SearchResultPoiViewImageFetcher(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                             ExampleAppMessaging::TMessageBus& messageBus)
            : m_webRequestFactory(webRequestFactory)
            , m_messageBus(messageBus)
            , m_webRequestCallback(this, &SearchResultPoiViewImageFetcher::OnImageFetchResponseReceived)
            {
            }
            
            SearchResultPoiViewImageFetcher::~SearchResultPoiViewImageFetcher()
            {
            }
            
            void SearchResultPoiViewImageFetcher::OnImageFetchResponseReceived(Eegeo::Web::IWebLoadRequest& message)
            {
                const std::vector<Byte>* pImageBytes = NULL;
                
                if(message.IsSucceeded())
                {
                    pImageBytes = message.TransferResourceDataOwnership();
                }
                
                m_messageBus.Publish(SearchResultPoiViewImageDownloadCompletedMessage(message.GetUrl(),
                                                                                      pImageBytes,
                                                                                      message.IsSucceeded()));
            }
            
            void SearchResultPoiViewImageFetcher::FetchImageForSearchResult(const std::string& imageUrl)
            {
                m_webRequestFactory.CreateGet(imageUrl, m_webRequestCallback, NULL)->Load();
            }
        }
    }
}
