// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Metrics
    {
        class IMetricsService
        {
        public:
            virtual ~IMetricsService() {}
            
            virtual void BeginSession(const std::string& apiKey, const std::string& appVersion) = 0;
            
            virtual void SetEvent(const std::string& eventString) = 0;
            
            virtual void SetEvent(const std::string& eventString,
                                  const std::string& key, const std::string& value) = 0;
            
            virtual void SetEvent(const std::string& eventString,
                                  const std::string& key1, const std::string& value1,
                                  const std::string& key2, const std::string& value2) = 0;
            
            virtual void SetEvent(const std::string& eventString,
                                  const std::string& key1, const std::string& value1,
                                  const std::string& key2, const std::string& value2,
                                  const std::string& key3, const std::string& value3) = 0;
            
            virtual void BeginTimedEvent(const std::string& eventString) = 0;
            virtual void BeginTimedEvent(const std::string& eventString, const std::string& key, const std::string& value) = 0;
            
            virtual void EndTimedEvent(const std::string& eventString) = 0;
            virtual void EndTimedEvent(const std::string& eventString, const std::string& key, const std::string& value) = 0;
            
            virtual void SetPosition(const double latitude, const double longitude, const double horizontalAccuracy, const double verticalAccuracy) = 0;
            
            virtual bool IsEnabled() const = 0;
        };
    }
}