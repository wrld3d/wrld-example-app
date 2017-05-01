// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MenuView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Menu
    {
        namespace View
        {
            void MenuView::CallVoidVoidFunction(const char* func)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID jmethod = env->GetMethodID(m_uiViewClass, func, "()V");
                env->CallVoidMethod(m_uiView, jmethod);
            }

            MenuView::MenuView(AndroidNativeState& nativeState,
                               const std::string& viewClassName)
                    : m_nativeState(nativeState)
                    , m_pTryDragFunc(NULL)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF(viewClassName.c_str());
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                env->DeleteLocalRef(uiClass);
                jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                        m_uiViewClass,
                        uiViewCtor,
                        m_nativeState.activity,
                        (jlong)(this)
                );

                m_uiView = env->NewGlobalRef(instance);
                env->DeleteLocalRef(instance);
            }

            MenuView::~MenuView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void MenuView::SetTryDragFunc(Eegeo::Helpers::IFunc0<bool>& function)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::ClearTryDragFunc()
            {
                ASSERT_UI_THREAD
            }

            float MenuView::GetAnimationProgress() const
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                static jmethodID normalisedAnimationProgressMethod = env->GetMethodID(m_uiViewClass, "normalisedAnimationProgress", "()F");
                const float normalisedAnimationProgress = env->CallFloatMethod(m_uiView, normalisedAnimationProgressMethod);
                return normalisedAnimationProgress;
            }

            bool MenuView::IsAnimating() const
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                static jmethodID isAnimatingMethod = env->GetMethodID(m_uiViewClass, "isAnimating", "()Z");
                const bool isAnimating = env->CallBooleanMethod(m_uiView, isAnimatingMethod);
                return isAnimating;
            }

            void MenuView::UpdateAnimation(float dt)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                static jmethodID updateAnimationMethod = env->GetMethodID(m_uiViewClass, "updateAnimation", "(F)V");
                env->CallVoidMethod(m_uiView, updateAnimationMethod, dt);
            }

            void MenuView::UpdateMenuSectionViews(TSections& sections, bool contentsChanged)
            {
                ASSERT_UI_THREAD

                if (!contentsChanged)
                {
                    return;
                }

                m_currentSections = sections;

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("java/lang/String");
                jclass strClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                const size_t numSections = sections.size();
                size_t numItems = 0;
                for(size_t i = 0; i < numSections; ++ i)
                {
                    const IMenuSectionViewModel& section = *(sections.at(i));
                    numItems += section.GetTotalItemCount() + 1;
                }

                jobjectArray groupNamesArray = env->NewObjectArray(numSections, strClass, 0);
                jintArray groupSizesArray = env->NewIntArray(numSections);
                jobjectArray childNamesArray = env->NewObjectArray(numItems, strClass, 0);
                env->DeleteLocalRef(strClass);

                size_t currentChildIndex = 0;
                for(size_t groupIndex = 0; groupIndex < numSections; groupIndex++)
                {
                    const IMenuSectionViewModel& section = *(sections.at(groupIndex));
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

            void MenuView::SetFullyOnScreenOpen()
            {
                ASSERT_UI_THREAD
                        CallVoidVoidFunction("animateToOpenOnScreen");
            }

            void MenuView::SetFullyOnScreenClosed()
            {
                ASSERT_UI_THREAD

                        CallVoidVoidFunction("animateToClosedOnScreen");
            }

            void MenuView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
                env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, value);
            }

            void MenuView::SetFullyOnScreen()
            {
                ASSERT_UI_THREAD

                        CallVoidVoidFunction("animateToClosedOnScreen");
            }

            void MenuView::SetFullyOffScreen()
            {
                ASSERT_UI_THREAD

                        CallVoidVoidFunction("animateOffScreen");
            }

            void MenuView::InsertOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewClickedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewClicked(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewClickedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewOpenedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewOpened(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewOpenedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewOpenStartedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewOpenStarted(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewOpenedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewClosedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnViewClosed(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_onViewClosedCallbacks.RemoveCallback(callback);
            }

            void MenuView::InsertOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::RemoveOnDragStarted(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::InsertOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::RemoveOnDrag(Eegeo::Helpers::ICallback1<float>& callback)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::InsertOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::RemoveOnDragCompleted(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::InsertOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                ASSERT_UI_THREAD

                m_onItemSelectedCallbacks.AddCallback(callback);
            }

            void MenuView::RemoveOnItemSelected(Eegeo::Helpers::ICallback2<int, int>& callback)
            {
                ASSERT_UI_THREAD

                m_onItemSelectedCallbacks.RemoveCallback(callback);
            }

            void MenuView::HandleViewClicked()
            {
                ASSERT_UI_THREAD

                m_onViewClickedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleViewOpenCompleted()
            {
                ASSERT_UI_THREAD

                m_onViewOpenedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleViewOpenStarted()
            {
                ASSERT_UI_THREAD

                m_onViewOpenStartedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleViewCloseCompleted()
            {
                ASSERT_UI_THREAD

                m_onViewClosedCallbacks.ExecuteCallbacks();
            }

            void MenuView::HandleDraggingViewStarted()
            {
                ASSERT_UI_THREAD
            }

            void MenuView::HandleDraggingViewInProgress(float progress)
            {
                ASSERT_UI_THREAD
            }

            void MenuView::HandleDraggingViewCompleted()
            {
                ASSERT_UI_THREAD
            }

            void MenuView::HandleItemSelected(int sectionIndex, int itemIndex)
            {
                ASSERT_UI_THREAD
                m_onItemSelectedCallbacks.ExecuteCallbacks(sectionIndex, itemIndex);
            }

            bool MenuView::CallBeginDrag()
            {
                ASSERT_UI_THREAD
                return false;
            }

            void MenuView::SetCanInteract(bool canInteract)
            {
                // This is already handled in the Java-side View on Android
            }

            void MenuView::ToggleSection(int sectionIndex)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID toggleSection = env->GetMethodID(m_uiViewClass, "toggleSection", "(I)V");
                env->CallVoidMethod(m_uiView, toggleSection, sectionIndex);
            }
        }
    }
}