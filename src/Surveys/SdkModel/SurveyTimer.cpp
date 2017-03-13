// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "SurveyTimer.h"


namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            SurveyTimer::SurveyTimer(ExampleAppMessaging::TMessageBus& messageBus, long long surveyTimeRequirementSec)
            : m_messageBus(messageBus)
            , m_messageSent(false)
            , m_surveyRequirementTime(surveyTimeRequirementSec * 1000)
            {
                m_timer.Start();
            }
            
            void SurveyTimer::Update()
            {
                if(m_timer.Total() >= m_surveyRequirementTime && !m_messageSent)
                {
                    m_messageBus.Publish(SurveyTimeRequirementMetMessage());
                    m_messageSent = true;
                }
            }
        }
    }
}
