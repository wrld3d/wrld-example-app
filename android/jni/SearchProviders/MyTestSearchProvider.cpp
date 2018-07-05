// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "MyTestSearchProvider.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "JniHelper.h"

namespace ExampleApp
{
    namespace SearchProviders
    {
		MyTestSearchProvider::MyTestSearchProvider(AndroidNativeState& nativeState, bool showNavigationButtons)
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
					"(JLandroid/app/Activity;Z)V",
					m_javaClass,
					(jlong)this,
					m_nativeState.activity,
					showNavigationButtons);

			m_onSearchCompleted = env->GetMethodID(
					m_javaClass,
					"onSearchCompleted",
					"([Lcom/eegeo/searchproviders/MyTestSearchProvider$SearchResultInfo;Z)V");

			m_onAutocompleteSuggestionsCompleted = env->GetMethodID(
					m_javaClass,
					"onSuggestionCompleted",
					"([Lcom/eegeo/searchproviders/MyTestSearchProvider$SearchResultInfo;Z)V");
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

		void MyTestSearchProvider::PerformSearchWithContext(const std::string& searchQuery,
															const SearchMenu::View::QueryContext& queryContext)
		{
			m_searchWithContextCallbacks.ExecuteCallbacks(searchQuery, queryContext);
		}

		void MyTestSearchProvider::PerformAutocompleteSuggestions(const std::string& searchQuery){
			m_autocompleteSuggestionsCallbacks.ExecuteCallbacks(searchQuery);
		}

		void MyTestSearchProvider::CancelSearch()
		{
			ASSERT_UI_THREAD

			m_searchCancelledCallbacks.ExecuteCallbacks();
		}

		void MyTestSearchProvider::CancelSuggestions()
		{
			ASSERT_UI_THREAD

			m_suggestionsCancelledCallbacks.ExecuteCallbacks();
		}

		void MyTestSearchProvider::OnAutocompleteSuggestionsResponseReceived(const bool success, const TSearchResults& searchResults)
		{
            ResponseReceived(success, searchResults, m_onAutocompleteSuggestionsCompleted);
		}

		void MyTestSearchProvider::OnSearchResponseReceived(const bool success, const TSearchResults& searchResults)
		{
            ResponseReceived(success, searchResults, m_onSearchCompleted);
		}


		void MyTestSearchProvider::ResponseReceived(const bool success, const TSearchResults& searchResults, jmethodID methodId)
		{
			ASSERT_UI_THREAD

			AndroidSafeNativeThreadAttachment attached(m_nativeState);
			JNIEnv* env = attached.envForThread;

			jclass javaClass = Helpers::JniHelper::LoadClassLocalRef(
					m_nativeState, env,
					"com/eegeo/searchproviders/MyTestSearchProvider$SearchResultInfo");

			jfieldID fidName = env->GetFieldID(javaClass, "name",        "Ljava/lang/String;");
			jfieldID fidDesc = env->GetFieldID(javaClass, "description", "Ljava/lang/String;");
			jfieldID fidIcon = env->GetFieldID(javaClass, "iconName",    "Ljava/lang/String;");

			jobjectArray javaArray = Helpers::JniHelper::LoadArrayLocalRef(
					env,
					javaClass,
					"(Lcom/eegeo/searchproviders/MyTestSearchProvider;)V",
					searchResults.size(),
					m_javaInstance);

			for (int i = 0; i < searchResults.size(); i++)
			{
				jobject arrayElement = env->GetObjectArrayElement(javaArray, i);

				jobject name = env->NewStringUTF(searchResults[i].GetName       ().c_str());
				jobject desc = env->NewStringUTF(searchResults[i].GetDescription().c_str());
				jobject icon = env->NewStringUTF(searchResults[i].GetIconName   ().c_str());

				env->SetObjectField(arrayElement, fidName, name);
				env->SetObjectField(arrayElement, fidDesc, desc);
				env->SetObjectField(arrayElement, fidIcon, icon);

				env->DeleteLocalRef(icon);
				env->DeleteLocalRef(desc);
				env->DeleteLocalRef(name);
			}

			env->CallVoidMethod(
					m_javaInstance,
					methodId,
					javaArray,
                    success);

			env->DeleteLocalRef(javaArray);
			env->DeleteLocalRef(javaClass);
		}


		void MyTestSearchProvider::InsertAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
		{
			ASSERT_UI_THREAD

			m_autocompleteSuggestionsCallbacks.AddCallback(callback);
		}

		void MyTestSearchProvider::RemoveAutocompleteSuggestionsCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
		{
			ASSERT_UI_THREAD

			m_autocompleteSuggestionsCallbacks.RemoveCallback(callback);
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

		void MyTestSearchProvider::InsertSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&,
																							  const SearchMenu::View::QueryContext&>& callback)
		{
			ASSERT_UI_THREAD

			m_searchWithContextCallbacks.AddCallback(callback);
		}

		void MyTestSearchProvider::RemoveSearchWithContextCallback(Eegeo::Helpers::ICallback2<const std::string&,
																							  const SearchMenu::View::QueryContext&>& callback)
		{
			ASSERT_UI_THREAD

			m_searchWithContextCallbacks.RemoveCallback(callback);
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

		void MyTestSearchProvider::InsertSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback)
		{
			ASSERT_UI_THREAD

			m_suggestionsCancelledCallbacks.AddCallback(callback);
		}

		void MyTestSearchProvider::RemoveSuggestionsCancelledCallback(Eegeo::Helpers::ICallback0& callback)
		{
			ASSERT_UI_THREAD

			m_suggestionsCancelledCallbacks.RemoveCallback(callback);
		}
	}
}
