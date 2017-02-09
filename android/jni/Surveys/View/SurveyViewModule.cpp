// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SurveyViewModule.h"
#include "Surveys.h"
#include "SurveyView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
        	SurveyViewModule::SurveyViewModule(
                AndroidNativeState& nativeState,
				ExampleAppMessaging::TMessageBus& messageBus,
				const std::string& timerSurveyUrl
            )
            {
                ASSERT_UI_THREAD

                m_pView = Eegeo_NEW(SurveyView)(nativeState, messageBus, timerSurveyUrl);
            }

        	SurveyViewModule::~SurveyViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE(m_pView);
            }

        	SurveyView& SurveyViewModule::GetSurveyView() const
            {
                ASSERT_UI_THREAD

                return *m_pView;
            }
        }
    }
}
