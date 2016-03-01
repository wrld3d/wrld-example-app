// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyViewModule.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            SurveyViewModule::SurveyViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                               Metrics::IMetricsService& metricsService)
                : m_messageBus(messageBus)
                , m_metricsService(metricsService)
            {

            }
            
            SurveyViewModule::~SurveyViewModule()
            {

            }
        }
    }
}
