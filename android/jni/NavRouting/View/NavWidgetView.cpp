// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchVendorNames.h"
#include "YelpSearchResultModel.h"
#include "YelpParsingHelpers.h"
#include "EegeoJsonParser.h"
#include "EegeoSearchResultModel.h"
#include "ICompassView.h"
#include "MyTestSearchProvider.h"
#include "SearchServicesResult.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            NavWidgetView::NavWidgetView(AndroidNativeState& nativeState,
                                         SearchProviders::MyTestSearchProvider& navSearchProvider,
                                         Eegeo::Helpers::CallbackCollection1<THeight>& navWidgetViewTopHeightChangedCallbacks,
                                         Eegeo::Helpers::CallbackCollection1<THeight>& navWidgetViewBottomHeightChangedCallbacks)
                    : m_nativeState(nativeState)
                    , m_uiViewClass(NULL)
                    , m_navSearchProvider(navSearchProvider)
                    , m_uiView(NULL)
                    , m_navWidgetViewTopHeightChangedCallbacks(navWidgetViewTopHeightChangedCallbacks)
                    , m_navWidgetViewBottomHeightChangedCallbacks(navWidgetViewBottomHeightChangedCallbacks)
            {
                ASSERT_UI_THREAD

                const std::string viewClass = "com/eegeo/navwidget/NavWidgetView";
                m_uiViewClass = CreateJavaClass(viewClass);
                Eegeo_ASSERT(m_uiViewClass != NULL, "failed to create viewClass NavWidgetView");
                m_uiView = CreateJavaObject(m_uiViewClass);
                Eegeo_ASSERT(m_uiView != NULL, "failed to create view NavWidgetView");

                AddSuggestionProvider(m_navSearchProvider);
            }

            NavWidgetView::~NavWidgetView()
            {
                ASSERT_UI_THREAD
                RemoveSuggestionProvider(m_navSearchProvider);

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);

                m_uiViewClass = NULL;
                m_uiView = NULL;
            }

            void NavWidgetView::AddSuggestionProvider(SearchProviders::MyTestSearchProvider& navSearchProvider)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID methodID = env->GetMethodID(m_uiViewClass, "addLocationSuggestionProvider", "(Lcom/wrld/widgets/search/model/SuggestionProvider;)V");
                env->CallVoidMethod(m_uiView, methodID, navSearchProvider.GetJavaInstance());

                jmethodID searchMethodID = env->GetMethodID(m_uiViewClass, "setLocationSearchProvider", "(Lcom/eegeo/searchproviders/MyTestSearchProvider;)V");
                env->CallVoidMethod(m_uiView, searchMethodID, navSearchProvider.GetJavaInstance());
            }

            void NavWidgetView::RemoveSuggestionProvider(SearchProviders::MyTestSearchProvider& navSearchProvider)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID methodID = env->GetMethodID(m_uiViewClass, "removeLocationSuggestionProvider", "(Lcom/wrld/widgets/search/model/SuggestionProvider;)V");
                env->CallVoidMethod(m_uiView, methodID, navSearchProvider.GetJavaInstance());

                jmethodID searchMethodID = env->GetMethodID(m_uiViewClass, "removeLocationSearchProvider", "(Lcom/wrld/widgets/search/model/SearchProvider;)V");
                env->CallVoidMethod(m_uiView, searchMethodID, navSearchProvider.GetJavaInstance());
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

            void NavWidgetView::SetRoute(const SdkModel::NavRoutingRouteModel& routeModel, bool isNewRoute)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jclass arrayListClass = env->FindClass("java/util/ArrayList");
                jmethodID arrayListCtor = env->GetMethodID(arrayListClass, "<init>", "()V");
                jmethodID arrayListAddMethod = env->GetMethodID(arrayListClass, "add", "(Ljava/lang/Object;)Z");

                jclass navDirectionClass = env->FindClass("com/wrld/widgets/navigation/model/WrldNavDirection");
                jmethodID navDirectionsCtor = env->GetMethodID(navDirectionClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/util/List;Ljava/lang/String;IZ)V");

                jobject directionsArrayListObject = env->NewObject(arrayListClass, arrayListCtor);

                for (auto &direction: routeModel.GetDirections())
                {
                    jstring name = env->NewStringUTF(direction.GetName().c_str());
                    jstring icon = env->NewStringUTF(direction.GetIcon().c_str());
                    jstring instruction = env->NewStringUTF(direction.GetInstruction().c_str());
                    jstring thenInstruction = env->NewStringUTF(direction.GetNextInstruction().c_str());
                    jstring indoorMapId = env->NewStringUTF(direction.GetIndoorMapId().Value().c_str());

                    jobject navDirectionObject = env->NewObject(navDirectionClass,
                                                                navDirectionsCtor,
                                                                name,
                                                                icon,
                                                                instruction,
                                                                thenInstruction,
                                                                NULL,
                                                                direction.GetIsIndoors() ? indoorMapId : NULL,
                                                                direction.GetIndoorMapFloorId(),
                                                                direction.GetIsMultiFloor());

                    env->CallBooleanMethod(directionsArrayListObject, arrayListAddMethod, navDirectionObject);

                    env->DeleteLocalRef(name);
                    env->DeleteLocalRef(icon);
                    env->DeleteLocalRef(instruction);
                    env->DeleteLocalRef(thenInstruction);
                    env->DeleteLocalRef(indoorMapId);
                }

                jclass navRouteClass = env->FindClass("com/wrld/widgets/navigation/model/WrldNavRoute");
                jmethodID navRouteCtor = env->GetMethodID(navRouteClass, "<init>", "(DLjava/util/List;)V");

                jobject navRouteObject = env->NewObject(navRouteClass, navRouteCtor, routeModel.GetDuration(), directionsArrayListObject);

                jmethodID setRouteMethod = env->GetMethodID(m_uiViewClass, "setRoute", "(Lcom/wrld/widgets/navigation/model/WrldNavRoute;Z)V");
                env->CallVoidMethod(m_uiView, setRouteMethod, navRouteObject, isNewRoute);
            }

            void NavWidgetView::ClearRoute()
            {
                ASSERT_UI_THREAD

                CallVoidMethod("clearRoute");
            }

            void NavWidgetView::SetCurrentDirection(int directionIndex)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID methodID = env->GetMethodID(m_uiViewClass, "setCurrentDirectionIndex", "(I)V");
                env->CallVoidMethod(m_uiView, methodID, directionIndex);
            }

            void NavWidgetView::UpdateCurrentDirection(const SdkModel::NavRoutingDirectionModel& directionModel)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jclass navDirectionClass = env->FindClass("com/wrld/widgets/navigation/model/WrldNavDirection");
                jmethodID navDirectionsCtor = env->GetMethodID(navDirectionClass, "<init>", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/util/List;Ljava/lang/String;IZ)V");

                jstring name = env->NewStringUTF(directionModel.GetName().c_str());
                jstring icon = env->NewStringUTF(directionModel.GetIcon().c_str());
                jstring instruction = env->NewStringUTF(directionModel.GetInstruction().c_str());
                jstring thenInstruction = env->NewStringUTF(directionModel.GetNextInstruction().c_str());
                jstring indoorMapId = env->NewStringUTF(directionModel.GetIndoorMapId().Value().c_str());

                jobject navDirectionObject = env->NewObject(navDirectionClass,
                                                            navDirectionsCtor,
                                                            name,
                                                            icon,
                                                            instruction,
                                                            thenInstruction,
                                                            NULL,
                                                            directionModel.GetIsIndoors() ? indoorMapId : NULL,
                                                            directionModel.GetIndoorMapFloorId(),
                                                            directionModel.GetIsMultiFloor());

                jmethodID setCurrentDirectionMethod = env->GetMethodID(m_uiViewClass, "setCurrentDirection", "(Lcom/wrld/widgets/navigation/model/WrldNavDirection;)V");
                env->CallVoidMethod(m_uiView, setCurrentDirectionMethod, navDirectionObject);

                env->DeleteLocalRef(name);
                env->DeleteLocalRef(icon);
                env->DeleteLocalRef(instruction);
                env->DeleteLocalRef(thenInstruction);
                env->DeleteLocalRef(indoorMapId);
            }

            void NavWidgetView::SetSelectedDirection(int directionIndex)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID methodID = env->GetMethodID(m_uiViewClass, "setSelectedDirectionIndex", "(I)V");
                env->CallVoidMethod(m_uiView, methodID, directionIndex);
            }

            void NavWidgetView::SetRemainingRouteDuration(double seconds)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID methodID = env->GetMethodID(m_uiViewClass, "setRemainingRouteDurationSeconds", "(D)V");
                env->CallVoidMethod(m_uiView, methodID, seconds);
            }

            void NavWidgetView::SetNavMode(SdkModel::NavRoutingMode mode)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jclass navModeClass = env->FindClass("com/wrld/widgets/navigation/model/WrldNavMode");

                jfieldID readyFieldId = env->GetStaticFieldID(navModeClass, "Ready", "Lcom/wrld/widgets/navigation/model/WrldNavMode;");
                jfieldID activeFieldId = env->GetStaticFieldID(navModeClass, "Active", "Lcom/wrld/widgets/navigation/model/WrldNavMode;");
                jfieldID notReadyFieldId = env->GetStaticFieldID(navModeClass, "NotReady", "Lcom/wrld/widgets/navigation/model/WrldNavMode;");

                jobject modeObject;

                switch (mode)
                {
                    case SdkModel::NavRoutingMode::Ready:
                        modeObject = env->GetStaticObjectField(navModeClass, readyFieldId);
                        break;
                    case SdkModel::NavRoutingMode::Active:
                        modeObject = env->GetStaticObjectField(navModeClass, activeFieldId);
                        break;
                    default:
                        modeObject = env->GetStaticObjectField(navModeClass, notReadyFieldId);
                        break;
                }

                jmethodID methodID = env->GetMethodID(m_uiViewClass, "setCurrentNavMode", "(Lcom/wrld/widgets/navigation/model/WrldNavMode;)V");
                env->CallVoidMethod(m_uiView, methodID, modeObject);
            }

            void NavWidgetView::ShowRerouteDialog(const std::string message)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring messageStr = env->NewStringUTF(message.c_str());

                jmethodID showRerouteDialogMethod = env->GetMethodID(m_uiViewClass, "showRerouteDialog", "(Ljava/lang/String;)V");
                env->CallVoidMethod(m_uiView, showRerouteDialogMethod, messageStr);

                env->DeleteLocalRef(messageStr);
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

                env->DeleteLocalRef(nameStr);
                env->DeleteLocalRef(indoorMapIdStr);
            }

            void NavWidgetView::ShowCalculatingRouteSpinner()
            {
                CallVoidMethod("showCalculatingRouteSpinner");
            }

            void NavWidgetView::HideCalculatingRouteSpinner()
            {
                CallVoidMethod("hideCalculatingRouteSpinner");
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

            void NavWidgetView::InsertStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startEndRoutingButtonClicked.AddCallback(callback);
            }

            void NavWidgetView::RemoveStartEndRoutingButtonClickedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD

                m_startEndRoutingButtonClicked.RemoveCallback(callback);
            }

            void NavWidgetView::HandleStartEndRoutingButtonClicked()
            {
                ASSERT_UI_THREAD

                m_startEndRoutingButtonClicked.ExecuteCallbacks();
            }

            void NavWidgetView::InsertSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback)
            {
                ASSERT_UI_THREAD

                m_selectedDirectionIndexChangedCallbacks.AddCallback(selectedDirectionIndexChangedCallback);
            }

            void NavWidgetView::RemoveSelectedDirectionIndexChangedCallback(Eegeo::Helpers::ICallback1<const int>& selectedDirectionIndexChangedCallback)
            {
                ASSERT_UI_THREAD

                m_selectedDirectionIndexChangedCallbacks.RemoveCallback(selectedDirectionIndexChangedCallback);
            }

            void NavWidgetView::HandleSelectedDirectionIndexChanged(int selectedDirectionIndex)
            {
                ASSERT_UI_THREAD

                m_selectedDirectionIndexChangedCallbacks.ExecuteCallbacks(selectedDirectionIndex);
            }

            void NavWidgetView::InsertRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback)
            {
                ASSERT_UI_THREAD

                m_rerouteDialogClosedCallbacks.AddCallback(rerouteDialogClosedCallback);
            }

            void NavWidgetView::RemoveRerouteDialogClosedCallback(Eegeo::Helpers::ICallback1<const bool>& rerouteDialogClosedCallback)
            {
                ASSERT_UI_THREAD

                m_rerouteDialogClosedCallbacks.RemoveCallback(rerouteDialogClosedCallback);
            }

            void NavWidgetView::HandleRerouteDialogClosed(bool shouldReroute)
            {
                ASSERT_UI_THREAD

                m_rerouteDialogClosedCallbacks.ExecuteCallbacks(shouldReroute);
            }

            void NavWidgetView::SetTopViewHeight(THeight topViewHeight){
                ASSERT_UI_THREAD

                m_topViewHeight = topViewHeight;
                m_navWidgetViewTopHeightChangedCallbacks.ExecuteCallbacks(topViewHeight);
            }

            void NavWidgetView::SetBottomViewHeight(THeight bottomViewHeight){
                ASSERT_UI_THREAD
                m_bottomViewHeight = bottomViewHeight;
                m_navWidgetViewBottomHeightChangedCallbacks.ExecuteCallbacks(bottomViewHeight);
            }

            INavWidgetView::THeight NavWidgetView::GetTopViewHeight()
            {
                ASSERT_UI_THREAD
                return m_topViewHeight;
            }

            INavWidgetView::THeight NavWidgetView::GetBottomViewHeight()
            {
                ASSERT_UI_THREAD
                return m_bottomViewHeight;
            }

            void NavWidgetView::SetStartPointFromResultIndex(int index)
            {
                m_navigationStartPointFromResultCallbacks.ExecuteCallbacks(index);
            }

            void NavWidgetView::SetEndPointFromResultIndex(int index)
            {
                m_navigationEndPointFromResultCallbacks.ExecuteCallbacks(index);
            }

            void NavWidgetView::SetSearchingForLocation(bool isSearching, bool isStartLocation)
            {
                m_searchingForLocationCallbacks.ExecuteCallbacks(isSearching, isStartLocation);
            }

            void NavWidgetView::InsertOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool> &callback)
            {
                m_searchingForLocationCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveOnSearchForLocationChanged(Eegeo::Helpers::ICallback2<const bool, const bool> &callback)
            {
                m_searchingForLocationCallbacks.RemoveCallback(callback);
            }

            void NavWidgetView::InsertOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationStartPointFromResultCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveOnNavigationStartPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationStartPointFromResultCallbacks.AddCallback(callback);
            }

            void NavWidgetView::InsertOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationEndPointFromResultCallbacks.AddCallback(callback);
            }

            void NavWidgetView::RemoveOnNavigationEndPointSetFromResult(Eegeo::Helpers::ICallback1<const int>& callback)
            {
                m_navigationEndPointFromResultCallbacks.RemoveCallback(callback);
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
