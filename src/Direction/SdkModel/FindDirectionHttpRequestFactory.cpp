// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FindDirectionHttpRequestFactory.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
        
            FindDirectionHttpRequestFactory::FindDirectionHttpRequestFactory(const std::string& eegeoApiKey
                                                                             ,Eegeo::Web::IWebLoadRequestFactory& webRequestFactory
                                                                             ,Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder)
            : m_webRequestFactory(webRequestFactory)
            , m_urlEncoder(urlEncoder)
            , m_apiUrl("https://routing.eegeo.com/v1/route?")
            , m_eegeoApiKey(eegeoApiKey)
            {
                
            }
            
            FindDirectionHttpRequestFactory::~FindDirectionHttpRequestFactory()
            {
            }
            
            FindDirectionHttpRequest* FindDirectionHttpRequestFactory::CreateFindDirectionQuery(const FindDirectionQuery& query,
                                                               Eegeo::Helpers::ICallback0& completionCallback)
            {
                return Eegeo_NEW(FindDirectionHttpRequest)(m_apiUrl,completionCallback,m_webRequestFactory,m_urlEncoder,query,m_eegeoApiKey);
            }
            
        }
    }
}