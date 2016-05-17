// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <sstream>

#include "YelpBusinessQuery.h"
#include "IWebLoadRequest.h"
#include "urlencode.h"

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
                    std::string UrlGetParamsEncoder(const std::map<std::string, std::string>& params)
                    {
                        std::string url;
                        
                        for (std::map<std::string, std::string>::const_iterator it = params.begin();
                             it != params.end();
                             ++it)
                        {
                            url += it->first + "=" + urlencode(it->second, URLEncodeType::URLEncode_Everything) + "&";
                        }
                        
                        //remove trailing &
                        url[url.length() - 1] = '\0';
                        
                        return url;
                    }
                }
                
                YelpBusinessQuery::YelpBusinessQuery(
                    const std::string& yelpConsumerKey,
                    const std::string& yelpConsumerSecret,
                    const std::string& yelpOAuthToken,
                    const std::string& yelpOAuthTokenSecret,
                    const Search::SdkModel::SearchQuery& searchQuery,
                    Eegeo::Helpers::ICallback0& completionCallback,
                    Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
                    : MaxRadiusMetres(40000.0f)
                    , m_searchQuery(searchQuery)
                    , m_completionCallback(completionCallback)
                    , m_responseString()
                    , m_cancelled(false)
                    , m_dispatched(false)
                    , m_isSuccess(false)
                    , m_yelpConsumerKey(yelpConsumerKey)
                    , m_yelpConsumerSecret(yelpConsumerSecret)
                    , m_yelpOAuthToken(yelpOAuthToken)
                    , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
                    , m_webRequestFactory(webRequestFactory)
                    , m_consumer(m_yelpConsumerKey, m_yelpConsumerSecret)
                    , m_token(m_yelpOAuthToken, m_yelpOAuthTokenSecret)
                    , m_client(&m_consumer, &m_token)
                    , m_apiUrl("http://api.yelp.com")
                    , m_searchPath("/v2/search")
                    , m_searchLimit("20")
                    , m_webRequestCompleteCallback(this, &YelpBusinessQuery::HandleWebResponseComplete)
                {

                }

                YelpBusinessQuery::~YelpBusinessQuery()
                {
                }

                void YelpBusinessQuery::Dispatch()
                {
                    Eegeo_ASSERT(!m_dispatched, "Cannot dispatch YelpSearchQuery if query has already been dispatched.\n");
                    m_dispatched = true;
                    
                    std::string searchTerm = "";
                    std::string categoryFilter = "";
                    
                    if (m_searchQuery.IsCategory())
                    {
                        categoryFilter = m_searchQuery.Query();
                    }
                    else
                    {
                        searchTerm = m_searchQuery.Query();
                    }
                    
                    int radiusFilter = (int)((m_searchQuery.Radius() > MaxRadiusMetres || !m_searchQuery.IsCategory()) ? MaxRadiusMetres : m_searchQuery.Radius());
                    
                    std::map<std::string, std::string> params;
                    
                    params["term"] = searchTerm;
                    params["category_filter"] = categoryFilter;
                    
                    std::stringstream conversionStream;
                    
                    conversionStream << m_searchQuery.Location().GetLatitudeInDegrees() << "," << m_searchQuery.Location().GetLongitudeInDegrees();
                    params["ll"] = conversionStream.str();
                    
                    conversionStream.clear();
                    conversionStream.str("");
                    
                    conversionStream << radiusFilter;
                    params["radiusFilter"] = conversionStream.str();
                    
                    params["limit"] = m_searchLimit;
                    
                    const std::string prefix = m_apiUrl + m_searchPath + "?";
                    
                    std::string parmsUrl = UrlGetParamsEncoder(params);
                    
                    std::string rawUrl = prefix + parmsUrl;
                    
                    std::string requestUrl = m_client.getURLQueryString(OAuth::Http::RequestType::Get, rawUrl);
                    
                    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::Values::GET, prefix + requestUrl, m_webRequestCompleteCallback).Build()->Load();
                }

                void YelpBusinessQuery::Cancel()
                {
                    Eegeo_ASSERT(m_dispatched, "Cannot cancel YelpBusinessQuery until query has been dispatched.\n");
                    m_cancelled = true;
                }

                void YelpBusinessQuery::HandleQueryCompleted(const std::string& queryString, bool success)
                {
                    if (!m_cancelled)
                    {
                        m_isSuccess = success;
                        m_responseString = queryString;
                        m_completionCallback();
                    }

                    Eegeo_DELETE this;
                }

                void YelpBusinessQuery::HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse)
                {
                    size_t resultSize = webResponse.GetBodyData().size();
                    std::string responseString = resultSize > 0 ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";

                    HandleQueryCompleted(responseString, webResponse.IsSucceeded());
                }

                bool YelpBusinessQuery::IsSucceeded()
                {
                    return m_isSuccess;
                }

                const std::string& YelpBusinessQuery::ResponseString()
                {
                    return m_responseString;
                }

                const Search::SdkModel::SearchQuery& YelpBusinessQuery::GetSearchQuery() const
                {
                    return m_searchQuery;
                }
            }
        }
    }
}
