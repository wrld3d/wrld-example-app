// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroView.h"
#include "WindowsAppThreadAssertionMacros.h"

using namespace ExampleApp::Helpers::ReflectionHelpers;

using namespace System;
using namespace System::Reflection;

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            InitialExperienceIntroView::InitialExperienceIntroView(WindowsNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus)
            : m_nativeState(nativeState)
            , m_messageBus(messageBus)
            {
                ASSERT_UI_THREAD

                m_uiViewClass = GetTypeFromEntryAssembly("ExampleAppWPF.InitialExperienceView");
                ConstructorInfo^ ctor = m_uiViewClass->GetConstructor(CreateTypes(IntPtr::typeid));
                m_uiView = ctor->Invoke(CreateObjects(gcnew IntPtr(this)));

                mDestroy.SetupMethod(m_uiViewClass, m_uiView, "Destroy");
                mShowExitIUX.SetupMethod(m_uiViewClass, m_uiView, "ShowExitIUX");
                mDismissExitIUX.SetupMethod(m_uiViewClass, m_uiView, "DismissExitIUX");
            }

            InitialExperienceIntroView::~InitialExperienceIntroView()
            {
                ASSERT_UI_THREAD

                mDestroy();
            }

            void InitialExperienceIntroView::Show()
            {
                ASSERT_UI_THREAD

                /*AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID showDialogMethod = env->GetMethodID(m_uiViewClass, "show", "()V");
                env->CallVoidMethod(m_uiView, showDialogMethod);*/

                m_messageBus.Publish(Modality::UpdateNativeModalBackgroundMessage(1.0f, true));
            }

            void InitialExperienceIntroView::Dismiss()
            {
                ASSERT_UI_THREAD

                /*AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissDialogMethod = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
                env->CallVoidMethod(m_uiView, dismissDialogMethod);*/

                m_messageBus.Publish(Modality::UpdateNativeModalBackgroundMessage(0.0f, false));
            }

            void InitialExperienceIntroView::OnDismiss()
            {
                Dismiss();
                m_dismissedCallbacks.ExecuteCallbacks();
            }

            void InitialExperienceIntroView::InsertDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.AddCallback(callback);
            }

            void InitialExperienceIntroView::RemoveDismissedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_dismissedCallbacks.RemoveCallback(callback);
            }

            void InitialExperienceIntroView::ShowExitIUX()
            {
                mShowExitIUX();
            }

            void InitialExperienceIntroView::DismissExitIUX()
            {
                mDismissExitIUX();
            }
        }
    }
}
