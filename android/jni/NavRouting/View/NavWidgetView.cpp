// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchVendorNames.h"
#include "YelpSearchResultModel.h"
#include "YelpParsingHelpers.h"
#include "EegeoJsonParser.h"
#include "EegeoSearchResultModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetView::NavWidgetView(AndroidNativeState& nativeState)
                    : m_nativeState(nativeState)
                    , m_uiViewClass(NULL)
                    , m_uiView(NULL)
            {
                ASSERT_UI_THREAD

                const std::string viewClass = "com/eegeo/navwidget/NavWidgetView";
                m_uiViewClass = CreateJavaClass(viewClass);
                Eegeo_ASSERT(m_uiViewClass != NULL, "failed to create viewClass NavWidgetView");
                m_uiView = CreateJavaObject(m_uiViewClass);
                Eegeo_ASSERT(m_uiView != NULL, "failed to create view NavWidgetView");
            }

            NavWidgetView::~NavWidgetView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);

                m_uiViewClass = NULL;
                m_uiView = NULL;
            }

            void NavWidgetView::Show()
            {
                ASSERT_UI_THREAD

                CallVoidMethod("showNavWidgetView");
            }

            void NavWidgetView::Hide()
            {
                ASSERT_UI_THREAD

                CallVoidMethod("dismissNavWidgetView");
            }

            void NavWidgetView::SetStartLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                ASSERT_UI_THREAD

                SetLocation(locationModel, true);
            }

            void NavWidgetView::ClearStartLocation()
            {
                ASSERT_UI_THREAD

                CallVoidMethod("clearStartLocation");
            }

            void NavWidgetView::SetEndLocation(const SdkModel::NavRoutingLocationModel& locationModel)
            {
                ASSERT_UI_THREAD

                SetLocation(locationModel, false);
            }

            void NavWidgetView::ClearEndLocation()
            {
                ASSERT_UI_THREAD

                CallVoidMethod("clearEndLocation");
            }

            void NavWidgetView::SetLocation(const SdkModel::NavRoutingLocationModel& locationModel, bool isStartLocation)
            {
                ASSERT_UI_THREAD

                Eegeo::Space::LatLong latLong = locationModel.GetLatLon();

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring nameStr = env->NewStringUTF(locationModel.GetName().c_str());
                jstring indoorMapIdStr = env->NewStringUTF(locationModel.GetIndoorMapId().Value().c_str());

                jmethodID setLocationMethod = env->GetMethodID(m_uiViewClass, isStartLocation ? "setStartLocation" : "setEndLocation", "(Ljava/lang/String;DDZLjava/lang/String;I)V");
                env->CallVoidMethod(m_uiView,
                                    setLocationMethod,
                                    nameStr,
                                    latLong.GetLatitudeInDegrees(),
                                    latLong.GetLongitudeInDegrees(),
                                    locationModel.GetIsIndoors(),
                                    indoorMapIdStr,
                                    locationModel.GetIndoorMapFloorId());
            }

            void NavWidgetView::CallVoidMethod(const std::string& methodName)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID methodID = env->GetMethodID(m_uiViewClass, methodName.c_str(), "()V");
                env->CallVoidMethod(m_uiView, methodID);
            }

            void NavWidgetView::InsertClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::HandleCloseClicked()
            {
                ASSERT_UI_THREAD

                m_closedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetView::InsertStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startLocationClickedCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveStartLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startLocationClickedCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::HandleStartLocationClicked()
            {
                ASSERT_UI_THREAD

                m_startLocationClickedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetView::InsertEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_endLocationClickedCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveEndLocationClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_endLocationClickedCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::HandleEndLocationClicked()
            {
                ASSERT_UI_THREAD

                m_endLocationClickedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetView::InsertStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startLocationClearButtonClickedCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveStartLocationClearButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startLocationClearButtonClickedCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::HandleStartLocationClearButtonClicked()
            {
                ASSERT_UI_THREAD

                m_startLocationClearButtonClickedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetView::InsertEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_endLocationClearButtonClickedCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveEndLocationClearButtonCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_endLocationClearButtonClickedCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::HandleEndLocationClearButtonClicked()
            {
                ASSERT_UI_THREAD

                m_endLocationClearButtonClickedCallbacks.ExecuteCallbacks();
            }

            void NavWidgetView::InsertStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startEndLocationsSwappedCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveStartEndLocationsSwappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startEndLocationsSwappedCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::HandleStartEndLocationsSwapped()
            {
                ASSERT_UI_THREAD

                m_startEndLocationsSwappedCallbacks.ExecuteCallbacks();
            }

            jclass NavWidgetView::CreateJavaClass(const std::string& viewClass)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF(viewClass.c_str());
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                return static_cast<jclass>(env->NewGlobalRef(uiClass));
            }

            jobject NavWidgetView::CreateJavaObject(jclass uiViewClass)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID uiViewCtor = env->GetMethodID(uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                        uiViewClass,
                        uiViewCtor,
                        m_nativeState.activity,
                        (jlong)(this)
                );

                return env->NewGlobalRef(instance);
            }

            jobjectArray NavWidgetView::CreateJavaArray(const std::vector<std::string>& stringVector)
            {
                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jobjectArray jniStringArray = env->NewObjectArray(
                        stringVector.size(),
                        env->FindClass("java/lang/String"),
                        0
                );

                for(size_t i = 0; i < stringVector.size(); ++ i)
                {
                    jstring jniString = env->NewStringUTF(stringVector[i].c_str());
                    env->SetObjectArrayElement(jniStringArray, i, jniString);
                    env->DeleteLocalRef(jniString);
                }

                return jniStringArray;
            }
        }
    }
}
