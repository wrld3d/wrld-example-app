// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchQuery.h"
#include "IWebLoadRequestFactory.h"
#include "IWebLoadRequest.h"
#include "ApiTokenModel.h"
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
                EegeoSearchQuery::EegeoSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                   const Search::SdkModel::SearchQuery& query,
                                                   const std::string& serviceUrl,
                                                   const Eegeo::Web::ApiTokenModel& apiTokenModel,
                                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                   int interiorFloorIndex,
                                                   Eegeo::Helpers::ICallback0& completionCallback)
                : m_apiTokenModel(apiTokenModel)
                , m_completionCallback(completionCallback)
                , m_responseString("")
                , m_isSuccess(false)
                , m_webRequestCompleteCallback(this, &EegeoSearchQuery::OnWebResponseReceived)
                {
                    float minimumScore = 0.25;
                    const int maximumNumberOfResults = 60;
                    float radius = query.Radius() * 1.5f;

                    std::string encodedQuery;
                    urlEncoder.UrlEncode(query.Query(), encodedQuery);
                    
                    std::stringstream urlstream;
                    urlstream.setf(std::ios_base::fixed);
                    urlstream << serviceUrl;
                    if (query.IsTag())
                    {
                        urlstream << "/tag?";
                        if (!encodedQuery.empty())
                        {
                            urlstream << "t=" << encodedQuery << "&";
                        }
                    }
                    else
                    {
                        radius = 0.0f;
                        minimumScore = 0.4f;
                        urlstream << "/search?s=" << encodedQuery << "&";
                    }

                    if (interiorId.IsValid())
                    {
                        urlstream << "indoor_id=" << interiorId.Value() << "&"
                                  << "f=" << interiorFloorIndex << "&";
                    }

                    urlstream << "r=" << std::setprecision(4) << (radius);
                    urlstream << "&lat=" << std::setprecision(8) << query.Location().GetLatitudeInDegrees();
                    urlstream << "&lon=" << std::setprecision(8) << query.Location().GetLongitudeInDegrees();
                    urlstream << "&n=" << maximumNumberOfResults;
                    urlstream << "&ms=" << std::setprecision(2) << minimumScore;
                    urlstream << "&apikey=" << m_apiTokenModel.GetApiKey();
                    
                    std::string url = urlstream.str();
                    m_pWebLoadRequest = webRequestFactory
                        .Begin(Eegeo::Web::HttpVerbs::GET, url, m_webRequestCompleteCallback)
                        .SetShouldCacheAggressively(false)
                        .SetShouldRequestOnlyFromCache(false)
                        .Build();
                    m_pWebLoadRequest->Load();
                }
                
                EegeoSearchQuery::~EegeoSearchQuery()
                {
                    
                }
                
                void EegeoSearchQuery::Cancel()
                {
                    m_pWebLoadRequest->Cancel();
                }
                
                bool EegeoSearchQuery::IsSucceeded()
                {
                    return m_isSuccess;
                }
                
                const std::string& EegeoSearchQuery::ResponseString()
                {
                    return m_responseString;
                }
                
                void EegeoSearchQuery::OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse)
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
