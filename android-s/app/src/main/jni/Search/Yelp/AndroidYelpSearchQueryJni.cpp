// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidYelpSearchQueryJni.h"
#include "AndroidYelpSearchQuery.h"
#include "AndroidYelpBusinessQuery.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_search_yelp_AndroidYelpSearchQueryJni_SearchQueryComplete(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jboolean success,
    jstring result)
{
	ASSERT_NATIVE_THREAD

    const char* chars = jenv->GetStringUTFChars(result, 0);
    std::string resultString = chars;
    jenv->ReleaseStringUTFChars(result, chars);

    ExampleApp::Search::Yelp::AndroidYelpSearchQuery* pYelpQuery = reinterpret_cast<ExampleApp::Search::Yelp::AndroidYelpSearchQuery*>(nativeObjectPtr);
	pYelpQuery->HandleQueryCompleted(success, resultString);
}


JNIEXPORT void JNICALL Java_com_eegeo_search_yelp_AndroidYelpSearchQueryJni_BusinessQueryComplete(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr,
    jboolean success,
    jstring result)
{
	ASSERT_NATIVE_THREAD

    const char* chars = jenv->GetStringUTFChars(result, 0);
    std::string resultString = chars;
    jenv->ReleaseStringUTFChars(result, chars);

    ExampleApp::Search::Yelp::AndroidYelpBusinessQuery* pYelpQuery = reinterpret_cast<ExampleApp::Search::Yelp::AndroidYelpBusinessQuery*>(nativeObjectPtr);
	pYelpQuery->HandleQueryCompleted(success, resultString);
}
