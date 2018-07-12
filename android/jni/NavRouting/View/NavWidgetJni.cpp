// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "NavWidgetJni.h"
#include "NavWidgetView.h"
#include "NavRouting.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleCloseClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SelectStartLocationClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleStartLocationClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SelectEndLocationClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleEndLocationClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_StartLocationClearButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleStartLocationClearButtonClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_EndLocationClearButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleEndLocationClearButtonClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_StartEndLocationsSwapped(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleStartEndLocationsSwapped();
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_StartEndButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleStartEndRoutingButtonClicked();
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SelectedDirectionIndexChanged(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jint directionIndex)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleSelectedDirectionIndexChanged(directionIndex);
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetTopViewHeight(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jint height)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->SetTopViewHeight(height);
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetBottomViewHeight(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jint height)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->SetBottomViewHeight(height);
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_RerouteDialogClosed(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jboolean shouldReroute)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleRerouteDialogClosed(shouldReroute);
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetNavigationStartPointFromSuggestion(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jint searchResultIndex)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->SetStartPointFromResultIndex(searchResultIndex);
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetNavigationEndPointFromSuggestion(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jint searchResultIndex)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->SetEndPointFromResultIndex(searchResultIndex);
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SetSearchingForLocation(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jboolean isSearching,
        jboolean isStartLocation)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->SetSearchingForLocation(isSearching, isStartLocation);
}