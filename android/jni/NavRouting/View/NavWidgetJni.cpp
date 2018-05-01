// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "NavWidgetJni.h"
#include "NavWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_navwidget_NavWidgetViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::NavRouting::View::NavWidgetView* pView = reinterpret_cast<ExampleApp::NavRouting::View::NavWidgetView*>(nativeObjectPtr);
    pView->HandleCloseClicked();
}
