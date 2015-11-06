// Copyright eeGeo Ltd (2012-2015), All Rights Reserved
//
//#include "WindowsYelpSearchQueryJni.h"
//#include "WindowsYelpSearchQuery.h"
//#include "WindowsYelpBusinessQuery.h"
//#include "WindowsAppThreadAssertionMacros.h"

//JNIEXPORT void JNICALL Java_com_eegeo_search_yelp_WindowsYelpSearchQueryJni_SearchQueryComplete(
//    JNIEnv* jenv, jobject obj,
//    jlong nativeObjectPtr,
//    jboolean success,
//    jstring result)
//{
//	ASSERT_NATIVE_THREAD
//
//    const char* chars = jenv->GetStringUTFChars(result, 0);
//    std::string resultString = chars;
//    jenv->ReleaseStringUTFChars(result, chars);
//
//    ExampleApp::Search::Yelp::WindowsYelpSearchQuery* pYelpQuery = reinterpret_cast<ExampleApp::Search::Yelp::WindowsYelpSearchQuery*>(nativeObjectPtr);
//	pYelpQuery->HandleQueryCompleted(success, resultString);
//}
//
//
//JNIEXPORT void JNICALL Java_com_eegeo_search_yelp_WindowsYelpSearchQueryJni_BusinessQueryComplete(
//    JNIEnv* jenv, jobject obj,
//    jlong nativeObjectPtr,
//    jboolean success,
//    jstring result)
//{
//	ASSERT_NATIVE_THREAD
//
//    const char* chars = jenv->GetStringUTFChars(result, 0);
//    std::string resultString = chars;
//    jenv->ReleaseStringUTFChars(result, chars);
//
//    ExampleApp::Search::Yelp::WindowsYelpBusinessQuery* pYelpQuery = reinterpret_cast<ExampleApp::Search::Yelp::WindowsYelpBusinessQuery*>(nativeObjectPtr);
//	pYelpQuery->HandleQueryCompleted(success, resultString);
//}
