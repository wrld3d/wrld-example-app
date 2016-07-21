// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "ImagePathHelpers.h"
#include "IWorldPinsInFocusModel.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinOnMapView::WorldPinOnMapView(AndroidNativeState& nativeState, float pinDiameter)
                : m_nativeState(nativeState)
                , m_pinOffset((pinDiameter * Helpers::ImageHelpers::GetPixelScale()))
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/worldpinonmapview/WorldPinOnMapView");
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

            WorldPinOnMapView::~WorldPinOnMapView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void WorldPinOnMapView::Open(const WorldPins::SdkModel::IWorldPinsInFocusModel& worldPinsInFocusModel,
            		float modality)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring titleStr = env->NewStringUTF(worldPinsInFocusModel.GetTitle().c_str());
                jstring detailsStr = env->NewStringUTF(worldPinsInFocusModel.GetSubtitle().c_str());
                jstring ratingsImgStr = env->NewStringUTF(worldPinsInFocusModel.GetRatingsImage().c_str());
                const int reviewCount = worldPinsInFocusModel.GetReviewCount();

                jmethodID showAtScreenLocation = env->GetMethodID(m_uiViewClass, "show", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;IF)V");
                env->CallVoidMethod(m_uiView, showAtScreenLocation, titleStr, detailsStr, ratingsImgStr, reviewCount, modality);

                env->DeleteLocalRef(titleStr);
                env->DeleteLocalRef(detailsStr);
                env->DeleteLocalRef(ratingsImgStr);
            }

            void WorldPinOnMapView::Close()
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismiss = env->GetMethodID(m_uiViewClass, "dismiss", "()V");
                env->CallVoidMethod(m_uiView, dismiss);
            }

            void WorldPinOnMapView::UpdateScreenLocation(float posX, float posY)
            {
                ASSERT_UI_THREAD
                float offsetY = posY - m_pinOffset;

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID updateScreenLocation = env->GetMethodID(m_uiViewClass, "updateScreenLocation", "(FF)V");
                env->CallVoidMethod(m_uiView, updateScreenLocation, posX, offsetY);
            }

            void WorldPinOnMapView::UpdateScreenState(float screenState)
            {
                ASSERT_UI_THREAD
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID updateScreenVisibility = env->GetMethodID(m_uiViewClass, "updateScreenVisibility", "(F)V");
                env->CallVoidMethod(m_uiView, updateScreenVisibility, screenState);
            }

            void WorldPinOnMapView::OnSelected()
            {
                ASSERT_UI_THREAD
                m_selectedCallbacks.ExecuteCallbacks();
            }

            void WorldPinOnMapView::InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_selectedCallbacks.AddCallback(callback);
            }

            void WorldPinOnMapView::RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_selectedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
