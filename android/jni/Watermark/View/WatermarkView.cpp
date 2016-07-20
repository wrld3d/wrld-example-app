// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WatermarkView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "WatermarkData.h"

namespace ExampleApp
{
    namespace Watermark
    {
        namespace View
        {
            WatermarkView::WatermarkView(AndroidNativeState& nativeState, const WatermarkData& watermarkData)
                : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com.eegeo.watermark.WatermarkView");
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;JLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");

                jstring jniImageAssetNameString = env->NewStringUTF(watermarkData.ImageAssetName().c_str());
                jstring jniPopupTitleString = env->NewStringUTF(watermarkData.PopupTitle().c_str());
                jstring jniPopupBodyString = env->NewStringUTF(watermarkData.PopupBody().c_str());
                jstring jniWebUrlString = env->NewStringUTF(watermarkData.WebUrl().c_str());
                jboolean jniShouldShowShadow = watermarkData.ShouldShowShadow();

                jobject instance = env->NewObject(
                                       m_uiViewClass,
                                       uiViewCtor,
                                       m_nativeState.activity,
                                       (jlong)(this),
									   jniImageAssetNameString,
									   jniPopupTitleString,
									   jniPopupBodyString,
									   jniWebUrlString,
									   jniShouldShowShadow
                                   );

                env->DeleteLocalRef(jniImageAssetNameString);
                env->DeleteLocalRef(jniPopupTitleString);
                env->DeleteLocalRef(jniPopupBodyString);
                env->DeleteLocalRef(jniWebUrlString);

                m_uiView = env->NewGlobalRef(instance);
            }

            WatermarkView::~WatermarkView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void WatermarkView::OnSelected()
            {
                ASSERT_UI_THREAD

                m_callbacks.ExecuteCallbacks();
            }

            void WatermarkView::SetOnScreenStateToIntermediateValue(float value)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToIntermediateOpenStateOnScreen = env->GetMethodID(m_uiViewClass, "animateToIntermediateOnScreenState", "(F)V");
                env->CallVoidMethod(m_uiView, animateToIntermediateOpenStateOnScreen, value);
            }

            void WatermarkView::SetFullyOnScreen()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToActive", "()V");
                env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
            }

            void WatermarkView::SetFullyOffScreen()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID animateToClosedOnScreen = env->GetMethodID(m_uiViewClass, "animateToInactive", "()V");
                env->CallVoidMethod(m_uiView, animateToClosedOnScreen);
            }

            void WatermarkView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.AddCallback(callback);
            }

            void WatermarkView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.RemoveCallback(callback);
            }

            void WatermarkView::UpdateWatermarkData(const WatermarkData& watermarkData)
            {
            	ASSERT_UI_THREAD

            	AndroidSafeNativeThreadAttachment attached(m_nativeState);
            	JNIEnv* env = attached.envForThread;

                jstring jniImageAssetNameString = env->NewStringUTF(watermarkData.ImageAssetName().c_str());
                jstring jniPopupTitleString = env->NewStringUTF(watermarkData.PopupTitle().c_str());
                jstring jniPopupBodyString = env->NewStringUTF(watermarkData.PopupBody().c_str());
                jstring jniWebUrlString = env->NewStringUTF(watermarkData.WebUrl().c_str());
                jboolean jniShouldShowShadow = watermarkData.ShouldShowShadow();

            	jmethodID updateWatermarkData = env->GetMethodID(m_uiViewClass, "updateWatermarkData", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
            	env->CallVoidMethod(m_uiView,
            						updateWatermarkData,
									jniImageAssetNameString,
									jniPopupTitleString,
									jniPopupBodyString,
									jniWebUrlString,
									jniShouldShowShadow);

                env->DeleteLocalRef(jniImageAssetNameString);
                env->DeleteLocalRef(jniPopupTitleString);
                env->DeleteLocalRef(jniPopupBodyString);
                env->DeleteLocalRef(jniWebUrlString);
            }

            void  WatermarkView::SetWatermarkAlignmentState(bool alignAlongBottom, bool alignBelowFloorDisplay)
            {
            	ASSERT_UI_THREAD

				AndroidSafeNativeThreadAttachment attached(m_nativeState);
				JNIEnv* env = attached.envForThread;

				jboolean jniAlignAlongBottom = alignAlongBottom;
				jboolean jniAlignBelowFloorDisplay = alignBelowFloorDisplay;
				jmethodID setAlignmentMethod = env->GetMethodID(m_uiViewClass, "setAlignmentState", "(ZZ)V");
				env->CallVoidMethod(m_uiView, setAlignmentMethod, jniAlignAlongBottom, jniAlignBelowFloorDisplay);
            }
        }
    }
}
