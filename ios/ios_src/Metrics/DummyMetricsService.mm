// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DummyMetricsService.h"

#include <string>

namespace ExampleApp
{
    namespace Metrics
    {
        DummyMetricsService::DummyMetricsService()
        : m_enabled(false)
        {
        }
        
        void DummyMetricsService::BeginSession(const std::string& string, const std::string& appVersion)
        {
            m_enabled = true;
        }
        
        void DummyMetricsService::SetPosition(const double latitude, const double longitude, const double horizontalAccuracy, const double verticalAccuracy)
        {
        }
        
        void DummyMetricsService::SetEvent(const std::string& eventString)
        {
        }
        
        void DummyMetricsService::SetEvent(const std::string& eventString, const std::string& key, const std::string& value)
        {
        }
        
        void DummyMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2)
        {
        }
        
        void DummyMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2, const std::string& key3, const std::string& value3)
        {
        }
        
        void DummyMetricsService::BeginTimedEvent(const std::string& eventString)
        {
        }
        
        void DummyMetricsService::BeginTimedEvent(const std::string& eventString, const std::string& key, const std::string& value)
        {
        }
        
        void DummyMetricsService::EndTimedEvent(const std::string& eventString)
        {
        }
        
        void DummyMetricsService::EndTimedEvent(const std::string& eventString, const std::string& key, const std::string& value)
        {
        }
        
        bool DummyMetricsService::IsEnabled() const
        {
            return m_enabled;
        }
    }
}
