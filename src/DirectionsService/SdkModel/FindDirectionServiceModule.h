// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "FindDirectionService.h"
#include "FindDirectionQueryPerformer.h"
#include "FindDirectionResultJsonParser.h"
#include "FindDirectionHttpRequestFactory.h"
#include "AlertBox.h"

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
                                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,                          Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                    const std::string& eegeoApiKey,
                                           ExampleAppMessaging::TMessageBus& messageBus);
                ~FindDirectionServiceModule();
                FindDirectionService& GetFindDirectionService() const;
                FindDirectionQueryPerformer& GetFindDirectionQueryPerformer() const;
                
            private:
                FindDirectionService* m_pDirectionService;
                FindDirectionResultJsonParser* m_pDirectionResultJsonParser;
                FindDirectionHttpRequestFactory* m_pDirectionHttpRequestFactory;
                FindDirectionQueryPerformer* m_pDirectionQueryPerformer;                                
                
            };
        }
    }
}