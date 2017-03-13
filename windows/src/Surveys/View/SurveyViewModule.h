// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ISurveyViewModule.h"
#include "Types.h"

#include "BidirectionalBus.h"
#include "Metrics.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            class SurveyViewModule : public ISurveyViewModule, private Eegeo::NonCopyable
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;

                std::string m_currentSurveyUrl;
                std::string m_currentSurveyMetricName;

                void StartUxSurveyCallback(const StartUxSurveyMessage& message);

                void OnSurveyAccepted();
                void OnSurveyRejected();
                
            public:
                SurveyViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                 Metrics::IMetricsService& metricsService);
                
                ~SurveyViewModule();
            };
        }
    }
}
