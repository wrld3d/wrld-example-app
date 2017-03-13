// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidAppThreadAssertionMacros.h"
#include "SurveyView.h"

namespace ExampleApp
{
    namespace Surveys
    {
        namespace View
        {
        	SurveyView::SurveyView(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus, const std::string& timerSurveyUrl)
                : m_nativeState(nativeState)
        		, m_startUxSurveyCallback(this, &SurveyView::StartUxSurveyCallback)
        		, m_messageBus(messageBus)
        		, m_timerSurveyUrl(timerSurveyUrl)
            {
        		ASSERT_UI_THREAD

    			AndroidSafeNativeThreadAttachment attached(m_nativeState);
    			JNIEnv* env = attached.envForThread;

    			jstring strClassName = env->NewStringUTF("com/eegeo/surveys/SurveyView");
    			jclass surveyClass = m_nativeState.LoadClass(env, strClassName);

    			env->DeleteLocalRef(strClassName);

    			m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(surveyClass));

    			jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;)V");

    			jobject instance = env->NewObject(
    			                                       m_uiViewClass,
    			                                       uiViewCtor,
    			                                       m_nativeState.activity,
    			                                       (jlong)(this)
    			                                   );

    			m_uiView = env->NewGlobalRef(instance);

    			m_messageBus.SubscribeUi(m_startUxSurveyCallback);
            }

        	SurveyView::~SurveyView()
    		{
        		ASSERT_UI_THREAD

    			AndroidSafeNativeThreadAttachment attached(m_nativeState);
    			JNIEnv* env = attached.envForThread;

    			env->DeleteGlobalRef(m_uiViewClass);

    			m_messageBus.UnsubscribeUi(m_startUxSurveyCallback);
    		}

        	void SurveyView::StartUxSurveyCallback(const StartUxSurveyMessage& message )
        	{
        		ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring eventStr = env->NewStringUTF(m_timerSurveyUrl.c_str());

				jmethodID startUxCallback = env->GetMethodID(m_uiViewClass, "startUxCallback", "(Ljava/lang/String;)V");
				env->CallVoidMethod(m_uiView, startUxCallback, eventStr);

				env->DeleteLocalRef(eventStr);
        	}
        }
    }
}
