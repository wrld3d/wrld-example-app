// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FlurryWrapper.h"
#include "Flurry.h"

#if (FLURRY_ENABLED)

namespace ExampleApp
{
    void UncaughtExceptionHandler(NSException *exception)
    {
        NSLog(@"In custom Exception Handler!\n");
        [Flurry logError:@"Uncaught" message:@"Crash!" exception:exception];
    }

    void FlurryWrapper::Begin(const char* string, const char* appVersion)
    {
        NSString* pAppVersionString = [NSString stringWithUTF8String:appVersion];
        [Flurry setAppVersion:pAppVersionString];
        
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry startSession:pString];
        
        NSSetUncaughtExceptionHandler(&UncaughtExceptionHandler);  // For Objective-C
    }

    void FlurryWrapper::SetPosition(double latitude, double longitude, double horizAccuracy, double vertAccuracy)
    {
        // Temp
        NSLog(@"Flurry Setting position: %f, %f\n", latitude, longitude);
        [Flurry setLatitude: latitude
                  longitude: longitude
         horizontalAccuracy: static_cast<float>(horizAccuracy)
           verticalAccuracy: static_cast<float>(vertAccuracy)];
    }

    void FlurryWrapper::SetEvent(const char* string)
    {
        NSString* pString = [NSString stringWithUTF8String:string];
        
        // Temp logging for debugging
        NSLog(@"Flurry event: %s\n", string);
        [Flurry logEvent:pString];
    }

    void FlurryWrapper::SetEvent(const char* string, const char* key1, const char* value1)
    {
        NSLog(@"Flurry event: %s, key: %s, value: %s\n", string, key1, value1);
        NSString* pKey1 = [NSString stringWithUTF8String:key1];
        NSString* pValue1 = [NSString stringWithUTF8String:value1];
        
        NSArray* pKeyArray = [NSArray arrayWithObject: pKey1];
        NSArray* pValueArray = [NSArray arrayWithObject: pValue1];
        
        NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry logEvent:pString withParameters:pDict];
    }

    void FlurryWrapper::SetEvent(const char* string, const char* key1, const char* value1, const char* key2, const char* value2)
    {
        NSLog(@"Flurry event: %s\nkey\t\t value:\n%s\t\t%s\n%s\t\t%s\n", string, key1, value1, key2, value2);
        NSString* pKey1 = [NSString stringWithUTF8String:key1];
        NSString* pValue1 = [NSString stringWithUTF8String:value1];
        
        NSString* pKey2 = [NSString stringWithUTF8String:key2];
        NSString* pValue2 = [NSString stringWithUTF8String:value2];
        
        NSArray* pKeyArray = [NSArray arrayWithObjects: pKey1,pKey2,nil];
        NSArray* pValueArray = [NSArray arrayWithObjects: pValue1,pValue2,nil];
        
        NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry logEvent:pString withParameters:pDict];
    }

    void FlurryWrapper::SetEvent(const char* string, const char* key1, const char* value1, const char* key2, const char* value2, const char* key3, const char* value3)
    {
        NSLog(@"Flurry event: %s\nkey\t\t value:\n%s\t\t%s\n%s\t\t%s\n%s\t\t%s\n", string, key1, value1, key2, value2, key3, value3);
        NSString* pKey1 = [NSString stringWithUTF8String:key1];
        NSString* pValue1 = [NSString stringWithUTF8String:value1];
        
        NSString* pKey2 = [NSString stringWithUTF8String:key2];
        NSString* pValue2 = [NSString stringWithUTF8String:value2];
        
        NSString* pKey3 = [NSString stringWithUTF8String:key3];
        NSString* pValue3 = [NSString stringWithUTF8String:value3];
        
        NSArray* pKeyArray = [NSArray arrayWithObjects: pKey1,pKey2,pKey3,nil];
        NSArray* pValueArray = [NSArray arrayWithObjects: pValue1,pValue2,pValue3,nil];
        
        NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry logEvent:pString withParameters:pDict];
    }

    void FlurryWrapper::BeginTimedEvent(const char* string)
    {
        NSLog(@"Beginning Flurry timed event: %s\n", string);
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry logEvent:pString timed:true];
    }

    void FlurryWrapper::BeginTimedEvent(const char* string, const char* key1, const char* value1)
    {
        NSLog(@"Beginning Flurry timed event: %s, key:%s, value:%s\n", string, key1, value1);
        NSString* pKey1 = [NSString stringWithUTF8String:key1];
        NSString* pValue1 = [NSString stringWithUTF8String:value1];
        
        NSArray* pKeyArray = [NSArray arrayWithObject: pKey1];
        NSArray* pValueArray = [NSArray arrayWithObject: pValue1];
        
        NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
        
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry logEvent:pString withParameters:pDict timed:true];
        
    }

    void FlurryWrapper::EndTimedEvent(const char* string)
    {
        NSLog(@"Ending Flurry timed event: %s\n", string);
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry endTimedEvent:pString withParameters:nil];
    }

    void FlurryWrapper::EndTimedEvent(const char* string, const char* key1, const char* value1)
    {
        NSLog(@"Ending Flurry timed event: %s, key: %s, value: %s\n", string, key1, value1);
        NSString* pKey1 = [NSString stringWithUTF8String:key1];
        NSString* pValue1 = [NSString stringWithUTF8String:value1];
        
        NSArray* pKeyArray = [NSArray arrayWithObject: pKey1];
        NSArray* pValueArray = [NSArray arrayWithObject: pValue1];
        
        NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
        
        NSString* pString = [NSString stringWithUTF8String:string];
        [Flurry endTimedEvent:pString withParameters:pDict];
    }
}

#endif