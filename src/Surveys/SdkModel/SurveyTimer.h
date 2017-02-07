// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "Types.h"

#include "BidirectionalBus.h"
#include "SurveyTimeRequirementMetMessage.h"

#include "TimeHelpers.h"
#include "Timer.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            class SurveyTimer : private Eegeo::NonCopyable
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::Timer m_timer;
                bool m_messageSent;
                long long m_surveyRequirementTime;
            public:
                SurveyTimer(ExampleAppMessaging::TMessageBus& messageBus, long long surveyTimeRequirementSec);
                ~SurveyTimer();
                void Update();
            };
        }
    }
}