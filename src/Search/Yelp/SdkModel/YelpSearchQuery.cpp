// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <sstream>
#include <iomanip>

#include "YelpSearchQuery.h"
#include "urlencode.h"
#include "IWebLoadRequest.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                namespace
                {

                }

                YelpSearchQuery::YelpSearchQuery(
                                                 const std::string& requestUrl,
                                                 Eegeo::Helpers::ICallback0& completionCallback,
                                                 Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
                    : m_pWebLoadRequest(NULL)
                    , m_completionCallback(completionCallback)
                    , m_responseString()
                    , m_dispatched(false)
                    , m_isSuccess(false)
                    , m_webRequestFactory(webRequestFactory)
                    , m_webRequestCompleteCallback(this, &YelpSearchQuery::HandleWebResponseComplete)
                {
                    m_pWebLoadRequest = m_webRequestFactory
                        .Begin(Eegeo::Web::HttpVerbs::Values::GET, requestUrl, m_webRequestCompleteCallback)
                        .Build();
                }

                YelpSearchQuery::~YelpSearchQuery()
                {
                }

                void YelpSearchQuery::Dispatch()
                {
                    Eegeo_ASSERT(!m_dispatched, "Cannot dispatch YelpSearchQuery if query has already been dispatched.\n");
                    m_dispatched = true;

                    m_pWebLoadRequest->Load();
                }

                void YelpSearchQuery::Cancel()
                {
                    Eegeo_ASSERT(m_dispatched, "Cannot cancel YelpSearchQuery until query has been dispatched.\n");
                    m_pWebLoadRequest->Cancel();
                    
                    Eegeo_DELETE this;
                }

                void YelpSearchQuery::HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse)
                {
                    Eegeo_ASSERT(!webResponse.IsCancelled());
                    
                    size_t resultSize = webResponse.GetBodyData().size();
                    
                    m_isSuccess = webResponse.IsSucceeded();
                    
                    m_responseString = (resultSize > 0) ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";
                    
                    m_completionCallback();
                    
                    Eegeo_DELETE this;
                }

                bool YelpSearchQuery::IsSucceeded()
                {
                    return m_isSuccess;
                }

                const std::string& YelpSearchQuery::ResponseString()
                {
                    return m_responseString;
                }
            }
        }
    }
}
