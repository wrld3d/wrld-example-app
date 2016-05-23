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

                YelpSearchQuery::YelpSearchQuery(
                    const std::string& yelpConsumerKey,
                    const std::string& yelpConsumerSecret,
                    const std::string& yelpOAuthToken,
                    const std::string& yelpOAuthTokenSecret,
                    const Search::SdkModel::SearchQuery& searchQuery,
                    Eegeo::Helpers::ICallback0& completionCallback,
                    Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                    bool enableSSL)
                    : MaxRadiusMetres(40000.0f)
                    , m_searchQuery(searchQuery)
                    , m_completionCallback(completionCallback)
                    , m_responseString()
                    , m_cancelled(false)
                    , m_dispatched(false)
                    , m_isSuccess(false)
                    , m_enableSSL(enableSSL)
                    , m_yelpConsumerKey(yelpConsumerKey)
                    , m_yelpConsumerSecret(yelpConsumerSecret)
                    , m_yelpOAuthToken(yelpOAuthToken)
                    , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
                    , m_webRequestFactory(webRequestFactory)
                    , m_consumer(m_yelpConsumerKey, m_yelpConsumerSecret)
                    , m_token(m_yelpOAuthToken, m_yelpOAuthTokenSecret)
                    , m_client(&m_consumer, &m_token)
                    , m_apiUrl("http://api.yelp.com")
                    , m_apiUrlSecure("https://api.yelp.com")
                    , m_searchPath("/v2/search")
                    , m_searchLimit("20")
                    , m_webRequestCompleteCallback(this, &YelpSearchQuery::HandleWebResponseComplete)
                {

                }

                YelpSearchQuery::~YelpSearchQuery()
                {
                }

                void YelpSearchQuery::Dispatch()
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
                    std::stringstream conversionStream;

                    conversionStream.setf(std::ios::fixed);

                    conversionStream << std::setprecision(17) << m_searchQuery.Location().GetLatitudeInDegrees()
                                     << "," << std::setprecision(17) << m_searchQuery.Location().GetLongitudeInDegrees();
                    std::string latLong = conversionStream.str();

                    conversionStream.clear();
                    conversionStream.str("");

                    conversionStream << radiusFilter;
                    std::string radiusFilterStr = conversionStream.str();

                    params["term"] = searchTerm;
                    params["category_filter"] = categoryFilter;
                    params["ll"] = latLong;
                    params["radius_filter"] = radiusFilterStr;
                    params["limit"] = m_searchLimit;

                    const std::string prefix = (m_enableSSL ? m_apiUrlSecure : m_apiUrl)  + m_searchPath + "?";

                    std::string parmsUrl = UrlGetParamsEncoder(params);
                    std::string rawUrl = prefix + parmsUrl;

                    std::string requestUrl = m_client.getURLQueryString(OAuth::Http::RequestType::Get, rawUrl);

                    m_webRequestFactory.Begin(Eegeo::Web::HttpVerbs::Values::GET, prefix + requestUrl, m_webRequestCompleteCallback).Build()->Load();
                }

                void YelpSearchQuery::Cancel()
                {
                    Eegeo_ASSERT(m_dispatched, "Cannot cancel YelpSearchQuery until query has been dispatched.\n");
                    m_cancelled = true;
                }

                void YelpSearchQuery::HandleQueryCompleted(const std::string& queryString, bool success)
                {
                    if (!m_cancelled)
                    {
                        m_isSuccess = success;
                        m_responseString = queryString;
                        m_completionCallback();
                    }

                    Eegeo_DELETE this;
                }

                void YelpSearchQuery::HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse)
                {
                    size_t resultSize = webResponse.GetBodyData().size();
                    std::string responseString = resultSize > 0 ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";

                    HandleQueryCompleted(responseString, webResponse.IsSucceeded());
                }

                bool YelpSearchQuery::IsSucceeded()
                {
                    return m_isSuccess;
                }

                const std::string& YelpSearchQuery::ResponseString()
                {
                    return m_responseString;
                }

                const Search::SdkModel::SearchQuery& YelpSearchQuery::GetSearchQuery() const
                {
                    return m_searchQuery;
                }
            }
        }
    }
}
