// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"

#include "BidirectionalBus.h"
#include "ICallback.h"
#include "Metrics.h"
#include "StartUxSurveyMessage.h"
#include "SurveyViewIncludes.h"
#include "URLRequestHandler.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            class SurveyViewInterop : private Eegeo::NonCopyable
            {
            private:
                SurveyAlertViewHandler* m_pSurveyAlertViewHandler;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                URLRequest::View::URLRequestHandler& m_urlRequestHandler;
                
                std::string m_currentSurveyUrl;
                std::string m_currentSurveyMetricName;
                
                Eegeo::Helpers::TCallback1<SurveyViewInterop, const StartUxSurveyMessage&> m_startUxSurveyCallback;
                
                Eegeo::Helpers::TCallback0<SurveyViewInterop> m_onSurveyAccepted;
                Eegeo::Helpers::TCallback0<SurveyViewInterop> m_onSurveyRejected;
                
                void StartUxSurveyCallback(const StartUxSurveyMessage& message);
                
                void OnSurveyAccepted();
                void OnSurveyRejected();
                
                std::string m_timerSurveyUrl;
                
            public:
                SurveyViewInterop(ExampleAppMessaging::TMessageBus& messageBus,
                                  Metrics::IMetricsService& metricsService,
                                  URLRequest::View::URLRequestHandler& urlRequestHandler,
                                  const std::string& timerSurveyUrl);
                
                ~SurveyViewInterop();
                
                
            };
        }
    }
}