// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerViewJni.h"
#include "InteriorsExplorerView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include <string>

#include <jni.h>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
        InteriorsExplorerView::InteriorsExplorerView(AndroidNativeState &state)
				: m_nativeState(state)
				, m_uiViewClass(NULL)
				, m_uiView(NULL)
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jstring strClassName = env->NewStringUTF("com.eegeo.interiorsexplorer.InteriorsExplorerView");
				jclass uiClass = m_nativeState.LoadClass(env, strClassName);
				env->DeleteLocalRef(strClassName);

				m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
				jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

				jobject instance = env->NewObject(
									   m_uiViewClass,
									   uiViewCtor,
									   m_nativeState.activity,
									   (jlong)(this)
								   );

				m_uiView = env->NewGlobalRef(instance);
			}

			InteriorsExplorerView::~InteriorsExplorerView()
			{
				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID destroy = env->GetMethodID(m_uiViewClass, "destroy", "()V");
				env->CallVoidMethod(m_uiView, destroy);
			}

            void InteriorsExplorerView::Dismiss()
            {
                ASSERT_UI_THREAD
            	m_dismissedCallbacks.ExecuteCallbacks();
            }

            void InteriorsExplorerView::SelectFloor(int floor)
            {
                ASSERT_UI_THREAD
            	m_selectedFloorCallbacks.ExecuteCallbacks(floor);
            }

            void InteriorsExplorerView::SetFloorSelectionDrag(float dragParam)
            {
            	ASSERT_UI_THREAD
				m_floorSelectionDraggedCallbacks.ExecuteCallbacks(dragParam);
            }

            void InteriorsExplorerView::OnDismissed()
            {
            }

            void InteriorsExplorerView::UpdateFloors(const std::vector<std::string>& floorShortNames, int currentlySelectedFloorIndex)
            {
                ASSERT_UI_THREAD
            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jobjectArray floorNamesArray = env->NewObjectArray(floorShortNames.size(), env->FindClass("java/lang/String"), 0);

				for(size_t i = 0; i < floorShortNames.size(); ++i)
				{
					const std::string& nameString(floorShortNames[i]);
					jstring jniString = env->NewStringUTF(nameString.c_str());
					env->SetObjectArrayElement(floorNamesArray, i, jniString);
					env->DeleteLocalRef(jniString);
				}

				jmethodID updateFloors = env->GetMethodID(m_uiViewClass, "updateFloors", "([Ljava/lang/String;I)V");
				env->CallVoidMethod(m_uiView, updateFloors, floorNamesArray, currentlySelectedFloorIndex);

				env->DeleteLocalRef(floorNamesArray);
            }

            void InteriorsExplorerView::SetFloorName(const std::string& name)
            {
                ASSERT_UI_THREAD

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
            	JNIEnv* env = attached.envForThread;

            	jstring nameStr = env->NewStringUTF(name.c_str());

            	jmethodID setFloorName = env->GetMethodID(m_uiViewClass, "setFloorName", "(Ljava/lang/String;)V");
            	env->CallVoidMethod(m_uiView, setFloorName, nameStr);

            	env->DeleteLocalRef(nameStr);
            }

            void InteriorsExplorerView::SetSelectedFloorIndex(int index)
            {
                ASSERT_UI_THREAD

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID setSelectedFloorIndex = env->GetMethodID(m_uiViewClass, "setSelectedFloorIndex", "(I)V");
				env->CallVoidMethod(m_uiView, setSelectedFloorIndex, index);
            }

            void InteriorsExplorerView::AddTutorialDialogs(bool showExitDialog, bool showChangeFloorDialog)
            {
            	ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID addTutorialDialogs = env->GetMethodID(m_uiViewClass, "addTutorialDialogs", "(ZZ)V");
				env->CallVoidMethod(m_uiView, addTutorialDialogs, showExitDialog, showChangeFloorDialog);
            }

            void InteriorsExplorerView::RemoveTutorialDialogs()
            {
            	ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID removeTutorialDialogs = env->GetMethodID(m_uiViewClass, "removeTutorialDialogs", "()V");
				env->CallVoidMethod(m_uiView, removeTutorialDialogs);
            }

            bool InteriorsExplorerView::GetCanShowChangeFloorTutorialDialog()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID getCanShowChangeFloorTutorialDialog = env->GetMethodID(m_uiViewClass, "getCanShowChangeFloorTutorialDialog", "()Z");
				return env->CallBooleanMethod(m_uiView, getCanShowChangeFloorTutorialDialog);
			}

            void InteriorsExplorerView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

            	m_dismissedCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

            	m_dismissedCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerView::InsertFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                ASSERT_UI_THREAD

            	m_selectedFloorCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerView::RemoveFloorSelectedCallback(Eegeo::Helpers::ICallback1<int>& callback)
            {
                ASSERT_UI_THREAD

            	m_selectedFloorCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerView::InsertFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
            	ASSERT_UI_THREAD

				m_floorSelectionDraggedCallbacks.AddCallback(callback);
            }

            void InteriorsExplorerView::RemoveFloorSelectionDraggedCallback(Eegeo::Helpers::ICallback1<float>& callback)
            {
            	ASSERT_UI_THREAD

				m_floorSelectionDraggedCallbacks.RemoveCallback(callback);
            }

            void InteriorsExplorerView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID animateToIntermediateOnScreenState = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
				env->CallVoidMethod(m_uiView, animateToIntermediateOnScreenState, value);
            }

            void InteriorsExplorerView::SetFullyOnScreen()
            {
                ASSERT_UI_THREAD

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID animateToActive = env->GetMethodID(m_uiViewClass, "animateToActive", "()V");
				env->CallVoidMethod(m_uiView, animateToActive);
            }

            void InteriorsExplorerView::SetFullyOffScreen()
            {
                ASSERT_UI_THREAD

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID animateToInactive = env->GetMethodID(m_uiViewClass, "animateToInactive", "()V");
				env->CallVoidMethod(m_uiView, animateToInactive);
            }

            void InteriorsExplorerView::SetTouchEnabled(bool enabled)
            {
                ASSERT_UI_THREAD

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID setTouchEnabled = env->GetMethodID(m_uiViewClass, "setTouchEnabled", "(Z)V");
				env->CallVoidMethod(m_uiView, setTouchEnabled, enabled);
            }

            void InteriorsExplorerView::PlaySliderAnim()
			{
				ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jmethodID playSliderAnim = env->GetMethodID(m_uiViewClass, "playShakeSliderAnim", "()V");
				env->CallVoidMethod(m_uiView, playSliderAnim);
			}
        }
    }
}
