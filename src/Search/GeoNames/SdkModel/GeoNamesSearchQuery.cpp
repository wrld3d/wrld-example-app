// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeoNamesSearchQuery.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "ApiKey.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                GeoNamesSearchQuery::GeoNamesSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                         Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                         const Search::SdkModel::SearchQuery& query,
                                                         Eegeo::Helpers::ICallback0& completionCallback)
                : m_completionCallback(completionCallback)
                , m_responseString("")
                , m_isSuccess(false)
                , m_webRequestCompleteCallback(this, &GeoNamesSearchQuery::OnWebResponseReceived)
                {
                    std::string encodedQuery;
                    urlEncoder.UrlEncode(query.Query(), encodedQuery);
                    
                    std::string url = "http://api.geonames.org/searchJSON?q="
                    + encodedQuery
                    + "&maxRows=1&featureClass=A&featureClass=P&orderby=relevance&username="
                    + ExampleApp::GeoNamesUserName;
                    
                    m_pWebLoadRequest = webRequestFactory.CreateGet(url, m_webRequestCompleteCallback, NULL);
                    m_pWebLoadRequest->Load();
                }
                
                GeoNamesSearchQuery::~GeoNamesSearchQuery()
                {
                    
                }
                
                void GeoNamesSearchQuery::Cancel()
                {
                    m_pWebLoadRequest->Cancel();
                }
                
                bool GeoNamesSearchQuery::IsSucceeded()
                {
                    return m_isSuccess;
                }
                
                const std::string& GeoNamesSearchQuery::ResponseString()
                {
                    return m_responseString;
                }
                
                void GeoNamesSearchQuery::OnWebResponseReceived(Eegeo::Web::IWebLoadRequest& webLoadRequest)
                {
                    if(webLoadRequest.IsSucceeded())
                    {
                        size_t resultSize = webLoadRequest.GetResourceData().size();
                        m_responseString = std::string(reinterpret_cast<char const*>(&(webLoadRequest.GetResourceData().front())), resultSize);
                        m_isSuccess = true;
                    }
                    
                    m_completionCallback();
                }
            }
        }
    }
}
