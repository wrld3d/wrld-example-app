// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchMenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchMenuView::SearchMenuView(AndroidNativeState& nativeState,
                                           const std::string& viewClassName)
                : Menu::View::MenuView(nativeState, viewClassName)
            {
            }

            void SearchMenuView::SetHeader(const std::string& header, bool queryPending, size_t numResult)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID updateHeaderMethod = env->GetMethodID(m_uiViewClass, "updateHeader", "(Ljava/lang/String;ZI)V");
                jstring queryString = env->NewStringUTF(header.c_str());

                env->CallVoidMethod(m_uiView, updateHeaderMethod, queryString, queryPending, numResult);
                env->DeleteLocalRef(queryString);
            }

            void SearchMenuView::HandleSearchClosed()
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.ExecuteCallbacks();
            }

            void SearchMenuView::InsertSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.AddCallback(callback);
            }

            void SearchMenuView::RemoveSearchClosed(Eegeo::Helpers::ICallback0& callback)
            {
                m_closedCallbacks.RemoveCallback(callback);
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
				m_searchItemSelectedCallbacks.ExecuteCallbacks(index);
			}
        }
    }
}
