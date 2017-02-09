// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "CallbackCollection.h"
#include "BidirectionalBus.h"

#include <string>

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
            class SurveyView
            {
            public:
            	SurveyView(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus, const std::string& timerSurveyUrl);
            	~SurveyView();

            private:
            	void StartUxSurveyCallback(const StartUxSurveyMessage& message);
            	Eegeo::Helpers::TCallback1<SurveyView, const StartUxSurveyMessage&> m_startUxSurveyCallback;

            	ExampleAppMessaging::TMessageBus& m_messageBus;
            	AndroidNativeState& m_nativeState;
            	jclass m_uiViewClass;
            	jobject m_uiView;
            	std::string m_timerSurveyUrl;
            };
        }
    }
}
