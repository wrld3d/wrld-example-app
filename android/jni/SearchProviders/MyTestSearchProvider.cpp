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
					"([Lcom/eegeo/searchproviders/MyTestSearchProvider$SearchResultInfo;)V");
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

		void MyTestSearchProvider::CancelSearch()
		{
			ASSERT_UI_THREAD

			m_searchCancelledCallbacks.ExecuteCallbacks();
		}

		void MyTestSearchProvider::OnSearchResponseReceived(const TSearchResults& searchResults)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jclass javaClass = Helpers::JniHelper::LoadClassLocalRef(
					m_nativeState, env,
					"com/eegeo/searchproviders/MyTestSearchProvider$SearchResultInfo");

			jfieldID fidName = env->GetFieldID(javaClass, "name",        "Ljava/lang/String;");
			jfieldID fidDesc = env->GetFieldID(javaClass, "description", "Ljava/lang/String;");

			jobjectArray javaArray = Helpers::JniHelper::LoadArrayLocalRef(
					env,
					javaClass,
					"(Lcom/eegeo/searchproviders/MyTestSearchProvider;)V",
					searchResults.size(),
					m_javaInstance);

			for (int i = 0; i < searchResults.size(); i++)
			{
				jobject arrayElement = env->GetObjectArrayElement(javaArray, i);

				jobject name = env->NewStringUTF(searchResults[i].GetTitle()   .c_str());
				jobject desc = env->NewStringUTF(searchResults[i].GetSubtitle().c_str());

				env->SetObjectField(arrayElement, fidName, name);
				env->SetObjectField(arrayElement, fidDesc, desc);

				env->DeleteLocalRef(desc);
				env->DeleteLocalRef(name);
			}

			env->CallVoidMethod(
					m_javaInstance,
					m_onSearchCompleted,
					javaArray);

			env->DeleteLocalRef(javaArray);
			env->DeleteLocalRef(javaClass);
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

		void MyTestSearchProvider::InsertSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
		{
			ASSERT_UI_THREAD

			m_searchCancelledCallbacks.AddCallback(callback);
		}

		void MyTestSearchProvider::RemoveSearchCancelledCallback(Eegeo::Helpers::ICallback0& callback)
		{
			ASSERT_UI_THREAD

			m_searchCancelledCallbacks.RemoveCallback(callback);
		}
	}
}
