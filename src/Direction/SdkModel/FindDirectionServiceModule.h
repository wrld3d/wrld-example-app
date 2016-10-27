// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "FindDirectionService.h"
#include "FindDirectionResultJsonParser.h"
#include "FindDirectionHttpRequestFactory.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class FindDirectionServiceModule
            {
            public:
                FindDirectionServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                    const std::string& eegeoApiKey);
                ~FindDirectionServiceModule();
                FindDirectionService& GetFindDirectionService() const;
                
            private:
                FindDirectionService* m_pDirectionService;
                FindDirectionResultJsonParser* m_pDirectionResultJsonParser;
                FindDirectionHttpRequestFactory* m_pDirectionHttpRequestFactory;
                
                
            };
        }
    }
}