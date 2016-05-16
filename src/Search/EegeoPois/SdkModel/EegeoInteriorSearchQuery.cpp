// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoInteriorSearchQuery.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "ApiKey.h"
#include "InteriorId.h"

#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoInteriorSearchQuery::EegeoInteriorSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                   const Search::SdkModel::SearchQuery& query,
                                                                   const std::string& serviceUrl,
                                                                   const std::string& apiKey,
                                                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                   int floorIdx,
                                                                   Eegeo::Helpers::ICallback0& completionCallback)
                : m_apiKey(apiKey)
                , m_completionCallback(completionCallback)
                , m_responseString("")
                , m_isSuccess(false)
                , m_interiorId(interiorId)
                , m_floorIdx(floorIdx)
                , m_webRequestCompleteCallback(this, &EegeoInteriorSearchQuery::OnWebResponseReceived)
                {
                    Eegeo_ASSERT(query.IsCategory(), "Only support category indoor queries");
                    const int maximumNumberOfResults = 99;
                    
                    std::string encodedQuery;
                    urlEncoder.UrlEncode(query.Query(), encodedQuery);
                    
                    std::stringstream urlstream;
                    urlstream.setf(std::ios_base::fixed);
                    urlstream << serviceUrl;
                    urlstream << "/indoor?c=";
                    urlstream << encodedQuery;
                    urlstream << "&f=";
                    urlstream << m_floorIdx;
                    urlstream << "&i=";
                    urlstream << m_interiorId.Value();
                    urlstream << "&n=" << maximumNumberOfResults;
                    urlstream << "&apikey=" << m_apiKey;
                    
                    std::string url = urlstream.str();
                    m_pWebLoadRequest = webRequestFactory.Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback).Build();
                    m_pWebLoadRequest->Load();
                }
                
                EegeoInteriorSearchQuery::~EegeoInteriorSearchQuery()
                {
                    
                }
                
                void EegeoInteriorSearchQuery::Cancel()
                {
                    m_pWebLoadRequest->Cancel();
                }
                
                bool EegeoInteriorSearchQuery::IsSucceeded()
                {
                    return m_isSuccess;
                }
                
                const std::string& EegeoInteriorSearchQuery::ResponseString()
                {
                    return m_responseString;
                }
                
                void EegeoInteriorSearchQuery::OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse)
                {
                    if(webResponse.IsSucceeded())
                    {
                        size_t resultSize = webResponse.GetBodyData().size();
                        m_responseString = std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize);
                        m_isSuccess = true;
                    }
                    
                    m_completionCallback();
                }
            }
        }
    }
}
