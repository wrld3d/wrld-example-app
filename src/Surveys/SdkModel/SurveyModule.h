// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ISurveyModule.h"
#include "Types.h"

#include "BidirectionalBus.h"
#include "PersistentSettings.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace SdkModel
        {
            class SurveyModule : public ISurveyModule, private Eegeo::NonCopyable
            {
            private:
                SurveyObserver* m_pSurveyObserver;
                
            public:
                SurveyModule(ExampleAppMessaging::TMessageBus& messageBus,
                             PersistentSettings::IPersistentSettingsModel& persistentSettingsModel);
                
                ~SurveyModule();
                
                SurveyObserver& GetSurveyObserver() const;
                
            };
        }
    }
}
