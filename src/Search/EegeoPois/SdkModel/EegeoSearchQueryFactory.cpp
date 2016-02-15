// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoSearchQueryFactory.h"
#include "EegeoSearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoSearchQueryFactory::EegeoSearchQueryFactory(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                         Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                         const std::string& apiKey)
                : m_webRequestFactory(webRequestFactory)
                , m_urlEncoder(urlEncoder)
                , m_apiKey(apiKey)
                {
                    
                }
                
                EegeoSearchQueryFactory::~EegeoSearchQueryFactory()
                {
                    
                }
                
                IEegeoSearchQuery* EegeoSearchQueryFactory::CreateEegeoSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                                                  Eegeo::Helpers::ICallback0& completionCallback)
                {
                    return Eegeo_NEW(EegeoSearchQuery)(m_webRequestFactory,
                                                           m_urlEncoder,
                                                           query,
                                                           m_apiKey,
                                                           completionCallback);
                }
            }
        }
    }
}