// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "MyTestSearchProvider.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "JniHelper.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
		MyTestSearchProvider::MyTestSearchProvider(AndroidNativeState& nativeState)
		: m_nativeState(nativeState)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			m_javaClass = Helpers::JniHelper::LoadClassGlobalRef(
					m_nativeState, env,
					"com/eegeo/searchproviders/MyTestSearchProvider");
			m_javaInstance = Helpers::JniHelper::LoadInstanceGlobalRef(
					env,
					"(J)V",
					m_javaClass,
					(jlong)this);

			m_onSearchCompleted = env->GetMethodID(
					m_javaClass,
					"onSearchCompleted",
					"([Ljava/lang/String;)V");
		}

		MyTestSearchProvider::~MyTestSearchProvider()
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			m_onSearchCompleted = 0;
			env->DeleteGlobalRef(m_javaInstance);
			env->DeleteGlobalRef(m_javaClass);
		}

		jobject MyTestSearchProvider::GetJavaInstance()
		{
			return m_javaInstance;
		}

		void MyTestSearchProvider::PerformSearch(const std::string& searchQuery)
		{
			ASSERT_UI_THREAD

			m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
		}

		void MyTestSearchProvider::OnSearchResponseReceived(const TSearchResults& searchResults)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jobjectArray javaResults = Helpers::JniHelper::LoadStringArrayLocalRef(
					m_nativeState,
					env,
					searchResults);

			env->CallVoidMethod(
					m_javaInstance,
					m_onSearchCompleted,
					javaResults);

			env->DeleteLocalRef(javaResults);
		}

		void MyTestSearchProvider::InsertSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
		{
			ASSERT_UI_THREAD

			m_searchPerformedCallbacks.AddCallback(callback);
		}

		void MyTestSearchProvider::RemoveSearchPerformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
		{
			ASSERT_UI_THREAD

			m_searchPerformedCallbacks.RemoveCallback(callback);
		}
	}
}
