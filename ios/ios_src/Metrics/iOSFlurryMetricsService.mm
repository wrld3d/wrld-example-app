// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSFlurryMetricsService.h"
#include "Flurry.h"

#include <string>

namespace ExampleApp
{
    namespace Metrics
    {
        iOSFlurryMetricsService::iOSFlurryMetricsService()
        : m_enabled(false)
        {
            
        }
        
        void iOSFlurryMetricsService::BeginSession(const std::string& string, const std::string& appVersion)
        {
            NSString* pAppVersionString = [NSString stringWithUTF8String:appVersion.c_str()];
            [Flurry setAppVersion:pAppVersionString];
            
            NSString* pString = [NSString stringWithUTF8String:string.c_str()];
            [Flurry startSession:pString];
            
            m_enabled = true;
        }
        
        void iOSFlurryMetricsService::SetPosition(const double latitude, const double longitude, const double horizontalAccuracy, const double verticalAccuracy)
        {
            [Flurry setLatitude: latitude
                      longitude: longitude
             horizontalAccuracy: static_cast<float>(horizontalAccuracy)
               verticalAccuracy: static_cast<float>(verticalAccuracy)];
        }
        
        void iOSFlurryMetricsService::SetEvent(const std::string& eventString)
        {
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            
            [Flurry logEvent:pString];
        }
        
        void iOSFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key, const std::string& value)
        {
            NSString* pKey1 = [NSString stringWithUTF8String: key.c_str()];
            NSString* pValue1 = [NSString stringWithUTF8String: value.c_str()];
            
            NSArray* pKeyArray = [NSArray arrayWithObject: pKey1];
            NSArray* pValueArray = [NSArray arrayWithObject: pValue1];
            
            NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            
            [Flurry logEvent:pString withParameters:pDict];
        }
        
        void iOSFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2)
        {
            NSString* pKey1 = [NSString stringWithUTF8String: key1.c_str()];
            NSString* pValue1 = [NSString stringWithUTF8String: value1.c_str()];
            
            NSString* pKey2 = [NSString stringWithUTF8String: key2.c_str()];
            NSString* pValue2 = [NSString stringWithUTF8String: value2.c_str()];
            
            NSArray* pKeyArray = [NSArray arrayWithObjects: pKey1,pKey2,nil];
            NSArray* pValueArray = [NSArray arrayWithObjects: pValue1,pValue2,nil];
            
            NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            [Flurry logEvent:pString withParameters:pDict];
        }
        
        void iOSFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2, const std::string& key3, const std::string& value3)
        {
            NSString* pKey1 = [NSString stringWithUTF8String: key1.c_str()];
            NSString* pValue1 = [NSString stringWithUTF8String: value1.c_str()];
            
            NSString* pKey2 = [NSString stringWithUTF8String: key2.c_str()];
            NSString* pValue2 = [NSString stringWithUTF8String: value2.c_str()];
            
            NSString* pKey3 = [NSString stringWithUTF8String: key3.c_str()];
            NSString* pValue3 = [NSString stringWithUTF8String: value3.c_str()];
            
            NSArray* pKeyArray = [NSArray arrayWithObjects: pKey1,pKey2,pKey3,nil];
            NSArray* pValueArray = [NSArray arrayWithObjects: pValue1,pValue2,pValue3,nil];
            
            NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            [Flurry logEvent:pString withParameters:pDict];
        }
        
        void iOSFlurryMetricsService::BeginTimedEvent(const std::string& eventString)
        {
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            [Flurry logEvent:pString timed:true];
        }
        
        void iOSFlurryMetricsService::BeginTimedEvent(const std::string& eventString, const std::string& key, const std::string& value)
        {
            NSString* pKey1 = [NSString stringWithUTF8String: key.c_str()];
            NSString* pValue1 = [NSString stringWithUTF8String: value.c_str()];
            
            NSArray* pKeyArray = [NSArray arrayWithObject: pKey1];
            NSArray* pValueArray = [NSArray arrayWithObject: pValue1];
            
            NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
            
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            [Flurry logEvent:pString withParameters:pDict timed:true];
        }
        
        void iOSFlurryMetricsService::EndTimedEvent(const std::string& eventString)
        {
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            [Flurry endTimedEvent:pString withParameters:nil];
        }
        
        void iOSFlurryMetricsService::EndTimedEvent(const std::string& eventString, const std::string& key, const std::string& value)
        {
            NSString* pKey1 = [NSString stringWithUTF8String: key.c_str()];
            NSString* pValue1 = [NSString stringWithUTF8String: value.c_str()];
            
            NSArray* pKeyArray = [NSArray arrayWithObject: pKey1];
            NSArray* pValueArray = [NSArray arrayWithObject: pValue1];
            
            NSDictionary* pDict = [NSDictionary dictionaryWithObjects:pValueArray forKeys:pKeyArray];
            
            NSString* pString = [NSString stringWithUTF8String: eventString.c_str()];
            [Flurry endTimedEvent:pString withParameters:pDict];
        }
        
        bool iOSFlurryMetricsService::IsEnabled() const
        {
            return m_enabled;
        }
    }
}