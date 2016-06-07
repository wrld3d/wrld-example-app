// Copyright eeGeo Ltd (2012-2015), All Rights Reserved



#include "YelpBusinessQuery.h"
#include "IWebLoadRequest.h"
#include "urlencode.h"
#include "ISearchResultParser.h"
#include "YelpBusinessJsonParser.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "IWebLoadRequestFactory.h"
#include "IdentitySearchCallbackData.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpBusinessQuery::YelpBusinessQuery(
                                                     const std::string& requestUrl,
                                                     Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& completionCallback,
                                                     Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                     const YelpBusinessJsonParser& yelpBusinessParser)
                    : m_pWebLoadRequest(NULL)
                    , m_completionCallback(completionCallback)
                    , m_yelpBusinessParser(yelpBusinessParser)
                    , m_dispatched(false)
                    , m_webRequestCompleteCallback(this, &YelpBusinessQuery::HandleWebResponseComplete)
                {
                    m_pWebLoadRequest = webRequestFactory.Begin(Eegeo::Web::HttpVerbs::Values::GET, requestUrl, m_webRequestCompleteCallback).Build();
                }

                YelpBusinessQuery::~YelpBusinessQuery()
                {
                }

                void YelpBusinessQuery::Dispatch()
                {
                    Eegeo_ASSERT(!m_dispatched, "YelpBusinessQuery already dispatched");
                    m_dispatched = true;
                    
                    m_pWebLoadRequest->Load();
                }

                void YelpBusinessQuery::Cancel()
                {
                    Eegeo_ASSERT(m_dispatched, "Cannot cancel YelpBusinessQuery until query has been dispatched.\n");
                    
                    m_pWebLoadRequest->Cancel();
                    
                    Eegeo_DELETE this;
                }

                void YelpBusinessQuery::HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse)
                {
                    Eegeo_ASSERT(!webResponse.IsCancelled());
                    
                    size_t resultSize = webResponse.GetBodyData().size();
                    const std::string& responseString = resultSize > 0 ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";

                    bool parseSuccess = false;
                    Search::SdkModel::SearchResultModel result;
                    
                    if (webResponse.IsSucceeded())
                    {
                        parseSuccess = m_yelpBusinessParser.TryParse(responseString, result);
                    }
                    else
                    {
                        Eegeo_TTY("YelpBusinessQuery failed: %s", responseString.c_str());
                    }
                    
                    const Search::SdkModel::IdentitySearchCallbackData& callbackData = parseSuccess
                        ? Search::SdkModel::IdentitySearchCallbackData::CreateSucceeded(result)
                        : Search::SdkModel::IdentitySearchCallbackData::CreateFailed(result);

                    m_completionCallback(callbackData);

                    Eegeo_DELETE this;
                }


            }
        }
    }
}
