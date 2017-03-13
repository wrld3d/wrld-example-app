// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ISurveyViewModule.h"
#include "Types.h"

#include "BidirectionalBus.h"
#include "Metrics.h"
#include "SurveyViewIncludes.h"
#include "URLRequestHandler.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            class SurveyViewModule : public ISurveyViewModule, private Eegeo::NonCopyable
            {
            private:
                SurveyViewInterop* m_pInterop;
                
            public:
                SurveyViewModule(ExampleAppMessaging::TMessageBus& messageBus,
                                 Metrics::IMetricsService& metricsService,
                                 URLRequest::View::URLRequestHandler& urlRequestHandler,
                                 const std::string& surveyUrl);
                
                ~SurveyViewModule();
            };
        }
    }
}
