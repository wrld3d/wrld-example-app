// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "JniHelper.h"
#include "MenuItemModel.h"


namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
			SearchWidgetView::SearchWidgetView(AndroidNativeState& nativeState,
											   SearchProviders::MyTestSearchProvider& searchProvider)
			: m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv *env = attached.envForThread;

                m_uiViewClass = Helpers::JniHelper::LoadClassGlobalRef(
                        m_nativeState, env,
                        "com/eegeo/searchmenu/SearchWidgetView");
                m_uiView = Helpers::JniHelper::LoadInstanceGlobalRef(
                        env,
                        "(Lcom/eegeo/entrypointinfrastructure/MainActivity;"
                                "J"
                                "Lcom/eegeo/searchproviders/MyTestSearchProvider;)V",
                        m_uiViewClass,
                        m_nativeState.activity,
                        (jlong) this,
                        searchProvider.GetJavaInstance());

                m_onSearchPerformed = env->GetMethodID(m_uiViewClass,
                                                       "onSearchPerformed",
                                                       "(Ljava/lang/String;ZZLjava/lang/String;ZZDDDZF)V");

                m_clearSearchResults = env->GetMethodID(m_uiViewClass, "clearSearchResults", "()V");
            }

            void SearchWidgetView::UpdateMenuSectionViews(Menu::View::TSections& sections)
            {
                ASSERT_UI_THREAD

                const size_t numSections = sections.size();
                size_t numItems = 0;
                for(size_t i = 0; i < numSections; ++ i)
                {
                    const Menu::View::IMenuSectionViewModel& section = *(sections.at(i));
                    numItems += section.GetTotalItemCount() + 1;
                }

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("java/lang/String");
                jclass strClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                jobjectArray groupNamesArray = env->NewObjectArray(numSections, strClass, 0);
                jintArray groupSizesArray = env->NewIntArray(numSections);
                jobjectArray childNamesArray = env->NewObjectArray(numItems, strClass, 0);
                env->DeleteLocalRef(strClass);

                size_t currentChildIndex = 0;
                for(size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    const Menu::View::IMenuSectionViewModel& section = *(sections.at(groupIndex));
                    int totalItems = section.GetTotalItemCount();

                    if (section.IsExpandable())
                    {
                        totalItems++;
                    }

                    for(size_t childIndex = 0; childIndex < totalItems; childIndex++)
                    {
                        int itemIndex = section.IsExpandable() ? childIndex-1 : childIndex;

                        std::string jsonData = section.IsExpandable() && childIndex == 0
                                               ? section.SerializeJson()
                                               : section.GetItemAtIndex(itemIndex).SerializeJson();

                        jstring jsonDataStr = env->NewStringUTF(jsonData.c_str());
                        env->SetObjectArrayElement(childNamesArray, currentChildIndex, jsonDataStr);
                        env->DeleteLocalRef(jsonDataStr);
                        currentChildIndex++;
                    }

                    jstring groupNameJni = env->NewStringUTF(section.SerializeJson().c_str());
                    env->SetObjectArrayElement(groupNamesArray, groupIndex, groupNameJni);
                    env->DeleteLocalRef(groupNameJni);

                    jint groupSize = (jint)(totalItems);
                    env->SetIntArrayRegion(groupSizesArray, groupIndex, 1, &groupSize);
                }

                jmethodID populateData = env->GetMethodID(m_uiViewClass, "populateData", "(J[Ljava/lang/String;[I[Ljava/lang/String;)V");

                env->CallVoidMethod(
                        m_uiView,
                        populateData,
                        (jlong)(this),
                        groupNamesArray,
                        groupSizesArray,
                        childNamesArray
                );

                env->DeleteLocalRef(groupNamesArray);
                env->DeleteLocalRef(groupSizesArray);
                env->DeleteLocalRef(childNamesArray);
            }

            void SearchWidgetView::HandleItemSelected(const std::string& menuText, int sectionIndex, int itemIndex){
                ASSERT_UI_THREAD
                m_onItemSelectedCallbacks.ExecuteCallbacks(menuText, sectionIndex, itemIndex);
            }

            void SearchWidgetView::InsertOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback){
                ASSERT_UI_THREAD
                m_onItemSelectedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnItemSelected(Eegeo::Helpers::ICallback3<const std::string&, int, int>& callback){
                ASSERT_UI_THREAD
                m_onItemSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::PerformSearch(const std::string& query, const QueryContext& context)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring queryText = env->NewStringUTF(query.c_str());
                jstring tagText   = env->NewStringUTF(context.TagText().c_str());

                env->CallVoidMethod(m_uiView,
                                    m_onSearchPerformed,
                                    queryText,
                                    (jboolean)context.ClearPreviousResults(),
                                    (jboolean)context.IsTag(),
                                    tagText,
                                    (jboolean)context.ShouldTryInterior(),
                                    (jboolean)context.UsesLocation(),
                                    (jdouble)context.Location().GetLatitude(),
                                    (jdouble)context.Location().GetLongitude(),
                                    (jdouble)context.Location().GetAltitude(),
                                    (jboolean)context.UsesRadius(),
                                    (jfloat)context.Radius());

                env->DeleteLocalRef(tagText);
                env->DeleteLocalRef(queryText);
            }

            void SearchWidgetView::ClearSearchResults()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                env->CallVoidMethod(m_uiView, m_clearSearchResults);
            }

            void SearchWidgetView::CallVoidVoidFunction(const char* func)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID jmethod = env->GetMethodID(m_uiViewClass, func, "()V");
                env->CallVoidMethod(m_uiView, jmethod);
            }

            void SearchWidgetView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
                env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, value);
            }

            void SearchWidgetView::SetOnScreen()
            {
                ASSERT_UI_THREAD

                CallVoidVoidFunction("animateOnScreen");
            }

            void SearchWidgetView::SetOffScreen()
            {
                ASSERT_UI_THREAD

                CallVoidVoidFunction("animateOffScreen");
            }

            void SearchWidgetView::CloseMenu()
            {
                ASSERT_UI_THREAD

                CallVoidVoidFunction("closeMenu");
            }

            void SearchWidgetView::HandleViewOpenCompleted()
            {
                ASSERT_UI_THREAD

                m_onViewOpenedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::HandleViewCloseCompleted()
            {
                ASSERT_UI_THREAD

                m_onViewClosedCallbacks.ExecuteCallbacks();
            }


            void SearchWidgetView::OnSearchResultsCleared()
            {
                m_searchClearedCallbacks.ExecuteCallbacks();
            }

            void SearchWidgetView::OnSearchResultSelected(int index)
            {
                m_resultSelectedCallbacks.ExecuteCallbacks(index);
            }

            void SearchWidgetView::InsertSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveSearchClearedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_searchClearedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveResultSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                m_resultSelectedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::OnSearchbarTextChanged(const std::string& newText)
            {
                m_onSearchbarTextChangedCallbacks.ExecuteCallbacks(newText);
            }
            void SearchWidgetView::InsertSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_onSearchbarTextChangedCallbacks.AddCallback(callback);
            }
            void SearchWidgetView::RemoveSearchbarTextChangedCallback(Eegeo::Helpers::ICallback1<const std::string&>& callback)
            {
                m_onSearchbarTextChangedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::OnNavigationRequest(int index)
            {
                m_navigationRequestedCallbacks.ExecuteCallbacks(index);
            }

            void SearchWidgetView::InsertOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationRequestedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnNavigationRequestedCallback(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationRequestedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewOpenedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewOpenedCallbacks.RemoveCallback(callback);
            }

            void SearchWidgetView::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewClosedCallbacks.AddCallback(callback);
            }

            void SearchWidgetView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewClosedCallbacks.RemoveCallback(callback);
            }

        }
    }
}
