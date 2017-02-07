// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyViewInterop.h"

#include "IMetricsService.h"
#include "SurveyAlertViewHandler.h"

namespace
{
    const std::string uxSurveyMetricName = "UxSurveyOffered";
    
    const std::string surveyAcceptedKeyName = "SurveyAccepted";
    const std::string surveyAcceptedValue = "Yes";
    const std::string surveyRejectedValue = "No";
}

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            SurveyViewInterop::SurveyViewInterop(ExampleAppMessaging::TMessageBus& messageBus,
                                                 Metrics::IMetricsService& metricsService,
                                                 URLRequest::View::URLRequestHandler& urlRequestHandler,
                                                 const std::string& timerSurveyUrl)
            : m_pSurveyAlertViewHandler(NULL)
            , m_messageBus(messageBus)
            , m_metricsService(metricsService)
            , m_urlRequestHandler(urlRequestHandler)
            , m_startUxSurveyCallback(this, &SurveyViewInterop::StartUxSurveyCallback)
            , m_onSurveyAccepted(this, &SurveyViewInterop::OnSurveyAccepted)
            , m_onSurveyRejected(this, &SurveyViewInterop::OnSurveyRejected)
            , m_timerSurveyUrl(timerSurveyUrl)
            {
                m_pSurveyAlertViewHandler = [[[[SurveyAlertViewHandler alloc] initWithCallbacks:m_onSurveyAccepted :m_onSurveyRejected] autorelease] retain];
                
                m_messageBus.SubscribeUi(m_startUxSurveyCallback);
            }
            
            SurveyViewInterop::~SurveyViewInterop()
            {
                m_messageBus.UnsubscribeUi(m_startUxSurveyCallback);
                
                [m_pSurveyAlertViewHandler release];
            }
            
            void SurveyViewInterop::StartUxSurveyCallback(const StartUxSurveyMessage& message)
            {
                if(m_timerSurveyUrl == "")
                    return;
                m_currentSurveyUrl = m_timerSurveyUrl;
                m_currentSurveyMetricName = uxSurveyMetricName;
                
                [m_pSurveyAlertViewHandler showAlert];
            }
            
            void SurveyViewInterop::OnSurveyAccepted()
            {
                m_metricsService.SetEvent(m_currentSurveyMetricName, surveyAcceptedKeyName, surveyAcceptedValue);
                
                m_urlRequestHandler.RequestExternalURL(m_currentSurveyUrl);
            }
            
            void SurveyViewInterop::OnSurveyRejected()
            {
                m_metricsService.SetEvent(m_currentSurveyMetricName, surveyAcceptedKeyName, surveyRejectedValue);
            }
        }
    }
}