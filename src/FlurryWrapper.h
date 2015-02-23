// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#ifndef FLURRY_ENABLED
    #define FLURRY_ENABLED 0
#endif

#ifdef ANDROID
#include "AndroidNativeState.h"
#endif

namespace ExampleApp
{
#if (FLURRY_ENABLED)
	class FlurryWrapper
	{
    public:
		static void Begin(const char* apiKey, const char* appVersion);

		static void SetPosition(double latitude, double longitude, double horizAccuracy, double vertAccuracy);

		static void SetEvent(const char* string);
		static void SetEvent(const char* string, const char* key1, const char* value1);
		static void SetEvent(const char* string, const char* key1, const char* value1, const char* key2, const char*  value2);
		static void SetEvent(const char* string, const char* key1, const char* value1, const char* key2, const char*  value2, const char* key3, const char* value3);

		static void BeginTimedEvent(const char* string);
		static void BeginTimedEvent(const char* string, const char* key1, const char* value1);
		static void EndTimedEvent(const char* string);
		static void EndTimedEvent(const char* string, const char* key1, const char* value1);
        
        #ifdef ANDROID
        static void InitialiseJavaInterface(AndroidNativeState* pNativeState);
        
    private:
        
        static AndroidNativeState* m_pNativeState;
        #endif
        
    };
    
	#define FLURRY_BEGIN(x, y)                      ExampleApp::FlurryWrapper::Begin(x, y)
	#define FLURRY_SET_POSITION(a, b, c, d)         ExampleApp::FlurryWrapper::SetPosition(a, b, c, d)
	#define FLURRY_SET_EVENT(x, ...)				ExampleApp::FlurryWrapper::SetEvent(x, ##__VA_ARGS__)
	#define FLURRY_BEGIN_TIMED_EVENT(x, ...)		ExampleApp::FlurryWrapper::BeginTimedEvent(x, ##__VA_ARGS__)
	#define FLURRY_END_TIMED_EVENT(x, ...)			ExampleApp::FlurryWrapper::EndTimedEvent(x, ##__VA_ARGS__)
    
	#else
    
	#define FLURRY_BEGIN(x, y)
	#define FLURRY_SET_POSITION(a, b, c, d)
	#define FLURRY_SET_EVENT(x, ...)
	#define FLURRY_BEGIN_TIMED_EVENT(x, ...)
	#define FLURRY_END_TIMED_EVENT(x, ...)
    
	#endif
}
