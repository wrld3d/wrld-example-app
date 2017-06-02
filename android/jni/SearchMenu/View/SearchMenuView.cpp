// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
        	void SearchMenuView::CallVoidVoidMethod(const char* func)
			{
				ASSERT_UI_THREAD
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID jmethod = env->GetMethodID(m_uiViewClass, func, "()V");
				env->CallVoidMethod(m_uiView, jmethod);
			}

            SearchMenuView::SearchMenuView(AndroidNativeState& nativeState,
                                           const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {
            }

            void SearchMenuView::SetSearchSection(Menu::View::IMenuSectionViewModel& searchSection)
            {
            	ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring strClassName = env->NewStringUTF("java/lang/String");
				jclass strClass = m_nativeState.LoadClass(env, strClassName);
				env->DeleteLocalRef(strClassName);

				int searchResultCount = searchSection.Size();
				jobjectArray searchResultArray = env->NewObjectArray(searchResultCount, strClass, 0);
				env->DeleteLocalRef(strClass);

				for(int i = 0; i < searchResultCount; ++i)
				{
					jstring searchResultJni = env->NewStringUTF(searchSection.GetItemAtIndex(i).SerializeJson().c_str());
					env->SetObjectArrayElement(searchResultArray, i, searchResultJni);
					env->DeleteLocalRef(searchResultJni);
				}

				jmethodID setSearchSection = env->GetMethodID(m_uiViewClass, "setSearchSection", "(I[Ljava/lang/String;)V");

				env->CallVoidMethod(
						m_uiView,
						setSearchSection,
						searchResultCount,
						searchResultArray);

				env->DeleteLocalRef(searchResultArray);
            }

            void SearchMenuView::RemoveSeachKeyboard()
			{
				ASSERT_UI_THREAD
				CallVoidVoidMethod("removeSearchKeyboard");
			}

			void SearchMenuView::SetSearchInProgress(bool inProgress)
			{
				ASSERT_UI_THREAD
				if(inProgress)
				{

					CallVoidVoidMethod("setSearchInProgress");
				}
				else
				{
					CallVoidVoidMethod("setSearchEnded");
				}
			}

			void SearchMenuView::SetEditText(const std::string& searchText, bool isTag)
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID setEditTextMethod = env->GetMethodID(m_uiViewClass, "setEditText", "(Ljava/lang/String;Z)V");
				jstring searchTextString = env->NewStringUTF(searchText.c_str());

				env->CallVoidMethod(m_uiView, setEditTextMethod, searchTextString, isTag);
				env->DeleteLocalRef(searchTextString);
			}

			std::string SearchMenuView::GetEditText()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID getEditTextMethod = env->GetMethodID(m_uiViewClass, "getEditText", "()Ljava/lang/String;");
				jstring editText = static_cast<jstring>(env->CallObjectMethod(m_uiView, getEditTextMethod));

				const char* chars = env->GetStringUTFChars(editText, 0);
				std::string editString = chars;
				env->ReleaseStringUTFChars(editText, chars);

				return editString;
			}

			bool SearchMenuView::HasTagSearch()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID hasTagSearchMethod = env->GetMethodID(m_uiViewClass, "hasTagSearch", "()Z");
				jboolean hasTagSearch = env->CallBooleanMethod(m_uiView, hasTagSearchMethod);

				return hasTagSearch;
			}

			void SearchMenuView::SetSearchResultCount(int searchResultCount)
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID setSearchResultCountMethod = env->GetMethodID(m_uiViewClass, "setSearchResultCount", "(I)V");

				env->CallVoidMethod(m_uiView, setSearchResultCountMethod, searchResultCount);
			}

			void SearchMenuView::HideSearchResultCount()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID hideSearchResultCountMethod = env->GetMethodID(m_uiViewClass, "hideSearchResultCount", "()V");

				env->CallVoidMethod(m_uiView, hideSearchResultCountMethod);
			}

			void SearchMenuView::RemoveSearchQueryResults()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID setSearchResultCountMethod = env->GetMethodID(m_uiViewClass, "removeSearchQueryResults", "()V");

				env->CallVoidMethod(m_uiView, setSearchResultCountMethod);
			}

			void SearchMenuView::CollapseAll()
			{
				for(Menu::View::TSections::iterator it = m_currentSections.begin(); it != m_currentSections.end(); ++it)
				{
					(*it)->Contract();
				}

				UpdateMenuSectionViews(m_currentSections, false);
			}

            void SearchMenuView::InsertSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
			{
				m_searchPerformedCallbacks.AddCallback(callback);
			}

			void SearchMenuView::RemoveSearchPeformedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
			{
				m_searchPerformedCallbacks.RemoveCallback(callback);
			}

			void SearchMenuView::SearchPerformed(const std::string& searchQuery)
			{
				ASSERT_UI_THREAD

				m_searchPerformedCallbacks.ExecuteCallbacks(searchQuery);
			}

			void SearchMenuView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
			{
				m_searchClearedCallbacks.AddCallback(callback);
			}

			void SearchMenuView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
			{
				m_searchClearedCallbacks.RemoveCallback(callback);
			}

			void SearchMenuView::OnSearchCleared()
			{
				ASSERT_UI_THREAD

				m_searchClearedCallbacks.ExecuteCallbacks();
			}

            void SearchMenuView::InsertSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
            	m_searchItemSelectedCallbacks.AddCallback(callback);
            }

			void SearchMenuView::RemoveSearchItemSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
			{
				m_searchItemSelectedCallbacks.RemoveCallback(callback);
			}

			void SearchMenuView::HandleSearchItemSelected(int index)
			{
				ASSERT_UI_THREAD

				m_searchItemSelectedCallbacks.ExecuteCallbacks(index);
			}

			void SearchMenuView::HandleItemSelected(int sectionIndex, int itemIndex)
			{
				RemoveSeachKeyboard();
				OnSearchCleared();
				MenuView::HandleItemSelected(sectionIndex, itemIndex);
			}

			void SearchMenuView::SetMenuSections(const std::vector<Menu::View::IMenuSectionViewModel*>& sections)
			{

			}
        }
    }
}
