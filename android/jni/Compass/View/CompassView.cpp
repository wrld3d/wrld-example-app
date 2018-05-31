// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassView::CompassView(AndroidNativeState& nativeState,
                                     Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& navViewBottomHeightChangedCallbacks)
                : m_nativeState(nativeState)
                , m_navWidgetBottomHeightChangedCallback(this, &CompassView::SetNavigationModeOffset)
                , m_navWidgetBottomHeightChangedCallbacks(navViewBottomHeightChangedCallbacks)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com.eegeo.compass.CompassView");
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

                m_navWidgetBottomHeightChangedCallbacks.AddCallback(m_navWidgetBottomHeightChangedCallback);
            }

            CompassView::~CompassView()
            {
                ASSERT_UI_THREAD

                m_navWidgetBottomHeightChangedCallbacks.RemoveCallback(m_navWidgetBottomHeightChangedCallback);
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void CompassView::OnCycle()
            {
                m_callbacks.ExecuteCallbacks();
            }

            void CompassView::CallVoidMethod(const std::string& methodName)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, methodName.c_str(), "()V");
                env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
            }

            void CompassView::ShowGpsDisabledView()
            {
                CallVoidMethod("showGpsDisabledView");
            }

            void CompassView::ShowGpsFollowView()
            {
                CallVoidMethod("showGpsFollowView");
            }

            void CompassView::ShowGpsCompassModeView()
            {
                CallVoidMethod("showGpsCompassModeView");
            }

            void CompassView::NotifyGpsUnauthorized()
            {
            	CallVoidMethod("notifyGpsUnauthorized");
            }

            void CompassView::SetHeadingRadians(float heading)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID updateHeading = env->GetMethodID(m_uiViewClass, "updateHeading", "(F)V");
                env->CallVoidMethod(m_uiView, updateHeading, heading);
            }

            void CompassView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
                env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, value);
            }

            void CompassView::SetOnScreen()
            {
                CallVoidMethod("animateToActive");
            }

            void CompassView::SetOffScreen()
            {
                CallVoidMethod("animateToInactive");;
            }

            void CompassView::SetRotationHighlight(bool shouldShowRotationHighlight)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID setRotationHighlight = env->GetMethodID(m_uiViewClass, "setRotationHighlight", "(Z)V");
                env->CallVoidMethod(m_uiView, setRotationHighlight, shouldShowRotationHighlight);
            }

            void CompassView::InsertCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void CompassView::RemoveCycledCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }

            void CompassView::SetState(
                    ScreenControl::View::TScreenControlViewState state)
			{
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv *env = attached.envForThread;

                jmethodID setState = env->GetMethodID(m_uiViewClass, "setState", "(I)V");
                env->CallVoidMethod(m_uiView, setState, state);
            }

            void CompassView::SetNavigationModeOffset(NavRouting::View::INavWidgetView::THeight& offset)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv *env = attached.envForThread;

                jmethodID setNavigationModeOffset = env->GetMethodID(m_uiViewClass, "setNavigationModeOffset", "(I)V");
                env->CallVoidMethod(m_uiView, setNavigationModeOffset, offset);
            }
        }
    }
}
