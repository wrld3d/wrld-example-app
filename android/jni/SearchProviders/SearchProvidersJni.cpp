// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchProvidersJni.h"
#include "MyTestSearchProvider.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_search(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jstring searchQuery)
{
    ASSERT_UI_THREAD

    const char* chars = jenv->GetStringUTFChars(searchQuery, 0);
    std::string queryString = chars;
    jenv->ReleaseStringUTFChars(searchQuery, chars);

    ExampleApp::SearchProviders::MyTestSearchProvider* pSearch = reinterpret_cast<ExampleApp::SearchProviders::MyTestSearchProvider*>(nativeObjectPtr);
    pSearch->PerformSearch(queryString);
}

JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_cancel(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchProviders::MyTestSearchProvider* pSearch = reinterpret_cast<ExampleApp::SearchProviders::MyTestSearchProvider*>(nativeObjectPtr);
    pSearch->CancelSearch();
}
