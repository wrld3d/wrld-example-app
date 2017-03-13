// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "Helpers.h"
#include "SurveyView.h"
#include "ISurveyViewModule.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            class SurveyViewModule: public ISurveyViewModule, private Eegeo::NonCopyable
            {
            private:
            	SurveyView* m_pView;

            public:
                SurveyViewModule(
                    AndroidNativeState& nativeState,
					ExampleAppMessaging::TMessageBus& messageBus,
					const std::string& timerSurveyUrl
                );

                ~SurveyViewModule();

                SurveyView& GetSurveyView() const;
            };
        }
    }
}
