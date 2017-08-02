// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Search.h"
#include "ICallback.h"
#include "SearchResultModel.h"
#include "YelpSearchQueryFactory.h"
#include "YelpSearchQuery.h"
#include "YelpSearchConstants.h"
#include "YelpCategoryModel.h"


#include "urlencode.h"
#include <sstream>
#include <iomanip>

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
                YelpSearchQueryFactory::YelpSearchQueryFactory(
                    const std::string& yelpConsumerKey,
                    const std::string& yelpConsumerSecret,
                    const std::string& yelpOAuthToken,
                    const std::string& yelpOAuthTokenSecret,
                    SdkModel::SearchTagToYelpCategoryMapper& searchTagToYelpCategoryMap,
                    Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
                : m_webRequestFactory(webRequestFactory)
                , m_consumer(yelpConsumerKey, yelpConsumerSecret)
                , m_token(yelpOAuthToken, yelpOAuthTokenSecret)
                , m_searchTagToYelpCategoryMap(searchTagToYelpCategoryMap)
                , m_client(&m_consumer, &m_token)
                , m_apiUrl("https://api.yelp.com/v2/search")
                {

                }

                YelpSearchQueryFactory::~YelpSearchQueryFactory()
                {
                }

                SdkModel::IYelpSearchQuery* YelpSearchQueryFactory::CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& searchQuery,
                    Eegeo::Helpers::ICallback0 &completionCallback)

                {
                    std::string searchTerm = "";
                    YelpCategoryModel categoryFilter { "", true };
                    std::string searchLimit("20");
                    
                    if (searchQuery.IsTag())
                    {
                        m_searchTagToYelpCategoryMap.TryGetBestYelpCategoryForSearchTag(searchQuery.Query(), categoryFilter);
                        if(categoryFilter.skipYelpSearch == true)
                        {
                            searchLimit = "0";
                        }
                    }
                    else
                    {
                        searchTerm = searchQuery.Query();
                    }
                    
                    std::map<std::string, std::string> params;
                    std::stringstream conversionStream;
                    
                    conversionStream.setf(std::ios::fixed);
                    
                    conversionStream << std::setprecision(17) << searchQuery.Location().GetLatitudeInDegrees()
                    << "," << std::setprecision(17) << searchQuery.Location().GetLongitudeInDegrees();
                    std::string latLong = conversionStream.str();
                    
                    params["term"] = searchTerm;
                    params["category_filter"] = categoryFilter.yelpCategoryFilter;
                    params["ll"] = latLong;
                    params["limit"] = searchLimit;
                    
                    std::stringstream rawUrl;
                    rawUrl << m_apiUrl << "?" << UrlGetParamsEncoder(params);
                    
                    std::stringstream requestUrl;
                    requestUrl << m_apiUrl << "?" << m_client.getURLQueryString(OAuth::Http::RequestType::Get, rawUrl.str());
                    
                    return Eegeo_NEW(YelpSearchQuery)(
                        requestUrl.str(),
                        completionCallback,
                        m_webRequestFactory);
                }


            }
        }
    }
}
