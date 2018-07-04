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

JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_searchWithContext(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jstring searchQuery,
        jboolean clearPreviousResults,
        jboolean isTag,
        jstring tagText,
        jboolean tryInterior,
        jboolean usesLocation,
        jdouble latitude,
        jdouble longitude,
        jdouble altitude,
        jboolean usesRadius,
        jfloat radius)
{
    ASSERT_UI_THREAD

    const char* chars = jenv->GetStringUTFChars(searchQuery, 0);
    std::string queryString = chars;
    jenv->ReleaseStringUTFChars(searchQuery, chars);

    chars = jenv->GetStringUTFChars(tagText, 0);
    std::string tagString = chars;
    jenv->ReleaseStringUTFChars(tagText, chars);

    ExampleApp::SearchProviders::MyTestSearchProvider* pSearch = reinterpret_cast<ExampleApp::SearchProviders::MyTestSearchProvider*>(nativeObjectPtr);

    if (usesLocation)
    {
        pSearch->PerformSearchWithContext(queryString,
                                          ExampleApp::SearchMenu::View::QueryContext(
                                            clearPreviousResults,
                                            isTag, tagString, tryInterior,
                                            Eegeo::Space::LatLongAltitude(latitude, longitude, altitude),
                                            radius));
    }
    else if (usesRadius)
    {
        pSearch->PerformSearchWithContext(queryString,
                                          ExampleApp::SearchMenu::View::QueryContext(
                                            clearPreviousResults,
                                            isTag, tagString, tryInterior,
                                            radius));
    }
    else
    {
        pSearch->PerformSearchWithContext(queryString,
                                          ExampleApp::SearchMenu::View::QueryContext(
                                                  clearPreviousResults,
                                                  isTag, tagString, tryInterior));
    }
}

JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_cancel(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchProviders::MyTestSearchProvider* pSearch = reinterpret_cast<ExampleApp::SearchProviders::MyTestSearchProvider*>(nativeObjectPtr);
    pSearch->CancelSearch();
}

JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_cancelSuggestions(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::SearchProviders::MyTestSearchProvider* pSearch = reinterpret_cast<ExampleApp::SearchProviders::MyTestSearchProvider*>(nativeObjectPtr);
    pSearch->CancelSuggestions();
}

JNIEXPORT void JNICALL Java_com_eegeo_searchproviders_SearchProvidersJniMethods_autocompleteSuggestions(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr,
        jstring searchQuery)
{
    ASSERT_UI_THREAD

    const char* chars = jenv->GetStringUTFChars(searchQuery, 0);
    std::string queryString = chars;
    jenv->ReleaseStringUTFChars(searchQuery, chars);

    ExampleApp::SearchProviders::MyTestSearchProvider* pSearch = reinterpret_cast<ExampleApp::SearchProviders::MyTestSearchProvider*>(nativeObjectPtr);
    pSearch->PerformAutocompleteSuggestions(queryString);
}
