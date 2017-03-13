// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyViewModule.h"

#include "SurveyViewInterop.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            SurveyViewModule::SurveyViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                               Metrics::IMetricsService& metricsService,
                                               URLRequest::View::URLRequestHandler& urlRequestHandler,
                                               const std::string& surveyUrl)
            : m_pInterop(NULL)
            {
                m_pInterop = Eegeo_NEW(SurveyViewInterop)(messageBus,
                                                          metricsService,
                                                          urlRequestHandler,
                                                          surveyUrl);
            }
            
            SurveyViewModule::~SurveyViewModule()
            {
                Eegeo_DELETE m_pInterop;
            }
        }
    }
}
