// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FindDirectionServiceModule.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            FindDirectionServiceModule::FindDirectionServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,                          Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,
                                                                                   const std::string& eegeoApiKey,ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pDirectionResultJsonParser = Eegeo_NEW(FindDirectionResultJsonParser)();
                m_pDirectionHttpRequestFactory = Eegeo_NEW(FindDirectionHttpRequestFactory)(eegeoApiKey,webRequestFactory,urlEncoder);
                m_pDirectionService = Eegeo_NEW(FindDirectionService)(*m_pDirectionHttpRequestFactory,*m_pDirectionResultJsonParser,alertBoxFactory,messageBus);
                m_pDirectionQueryPerformer = Eegeo_NEW(FindDirectionQueryPerformer)(GetFindDirectionService());

            }

            FindDirectionServiceModule::~FindDirectionServiceModule()
            {
                Eegeo_DELETE m_pDirectionResultJsonParser;
                Eegeo_DELETE m_pDirectionHttpRequestFactory;
                Eegeo_DELETE m_pDirectionService;
            }
            
            FindDirectionService& FindDirectionServiceModule::GetFindDirectionService() const
            {
                return *m_pDirectionService;
            }
            
            FindDirectionQueryPerformer& FindDirectionServiceModule::GetFindDirectionQueryPerformer() const
            {
                return *m_pDirectionQueryPerformer;
            }


        }
    }
}