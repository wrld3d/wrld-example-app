// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoInteriorSearchQuery.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "InteriorId.h"
#include "ApiTokenModel.h"

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
                                                                   const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                   int floorIdx,
                                                                   Eegeo::Helpers::ICallback0& completionCallback)
                : m_apiTokenModel(apiTokenModel)
                , m_completionCallback(completionCallback)
                , m_responseString("")
                , m_isSuccess(false)
                , m_interiorId(interiorId)
                , m_floorIdx(floorIdx)
                , m_webRequestCompleteCallback(this, &EegeoInteriorSearchQuery::OnWebResponseReceived)
                {
                    Eegeo_ASSERT(query.IsTag(), "Only support tag indoor queries");
                    const int maximumNumberOfResults = 60;
                    
                    std::string encodedQuery;
                    urlEncoder.UrlEncode(query.Query(), encodedQuery);
                    
                    std::stringstream urlstream;
                    urlstream.setf(std::ios_base::fixed);
                    urlstream << serviceUrl;
                    urlstream << "/indoor?";
                    if (!encodedQuery.empty())
                    {
                        urlstream << "t=" << encodedQuery << "&";
                    }
                    urlstream << "f=" << m_floorIdx;
                    urlstream << "&i=" << m_interiorId.Value();
                    urlstream << "&n=" << maximumNumberOfResults;
                    urlstream << "&lat=" << std::setprecision(8) << query.Location().GetLatitudeInDegrees();
                    urlstream << "&lon=" << std::setprecision(8) << query.Location().GetLongitudeInDegrees();
                    urlstream << "&apikey=" << m_apiTokenModel.GetApiKey();
                    
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
