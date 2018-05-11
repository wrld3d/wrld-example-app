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


JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_SelectedDirectionIndexChanged(
        JNIEnv *jenv, jobject obj,
        jlong nativeObjectPtr,
        jint directionIndex)
{
    ASSERT_UI_THREAD

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleSelectedDirectionIndexChanged(directionIndex);
}

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_CurrentNavModeChanged(
        JNIEnv *jenv, jclass type,
        jlong nativeObjectPtr,
        jobject currentNavMode)
{
    ASSERT_UI_THREAD

    jclass navModeClass = jenv->FindClass("com/wrld/widgets/navigation/model/WrldNavMode");

    jfieldID readyFieldId = jenv->GetStaticFieldID(navModeClass, "Ready", "Lcom/wrld/widgets/navigation/model/WrldNavMode;");
    jfieldID activeFieldId = jenv->GetStaticFieldID(navModeClass, "Active", "Lcom/wrld/widgets/navigation/model/WrldNavMode;");

    jobject readyObject = jenv->GetStaticObjectField(navModeClass, readyFieldId);
    jobject activeObject = jenv->GetStaticObjectField(navModeClass, activeFieldId);

    ExampleApp::NavRouting::View::NavRoutingMode navRoutingMode;

    if (jenv->IsSameObject(currentNavMode, readyObject))
    {
        navRoutingMode = ExampleApp::NavRouting::View::NavRoutingMode::Ready;
    }
    else if (jenv->IsSameObject(currentNavMode, activeObject))
    {
        navRoutingMode = ExampleApp::NavRouting::View::NavRoutingMode::Active;
    }
    else
    {
        navRoutingMode = ExampleApp::NavRouting::View::NavRoutingMode::NotReady;
    }

    auto* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleCurrentNavModeChanged(navRoutingMode);
}
