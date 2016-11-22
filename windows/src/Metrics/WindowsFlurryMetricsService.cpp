// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsFlurryMetricsService.h"

namespace ExampleApp
{
    namespace Metrics
    {
        WindowsFlurryMetricsService::WindowsFlurryMetricsService(const std::shared_ptr<WindowsNativeState>& nativeState)
        : m_nativeState(nativeState)
        , m_enabled(false)
        {
        }

        WindowsFlurryMetricsService::~WindowsFlurryMetricsService()
        {
        }

        void WindowsFlurryMetricsService::BeginSession(const std::string& apiKey, const std::string& appVersion)
        {
            m_enabled = true;
        }

        void WindowsFlurryMetricsService::SetPosition(double latitude, double longitude, double horizAccuracy, double vertAccuracy)
        {
        }

        void WindowsFlurryMetricsService::SetEvent(const std::string& eventString)
        {
        }

        void WindowsFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key, const std::string& value)
        {
        }

        void WindowsFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2)
        {
        }

        void WindowsFlurryMetricsService::SetEvent(const std::string& eventString, const std::string& key1, const std::string& value1, const std::string& key2, const std::string& value2, const std::string& key3, const std::string& value3)
        {
        }

        void WindowsFlurryMetricsService::BeginTimedEvent(const std::string& eventString)
        {
        }

        void WindowsFlurryMetricsService::BeginTimedEvent(const std::string& eventString, const std::string& key1, const std::string& value1)
        {
        }

        void WindowsFlurryMetricsService::EndTimedEvent(const std::string& eventString)
        {
        }

        void WindowsFlurryMetricsService::EndTimedEvent(const std::string& eventString, const std::string& key1, const std::string& value1)
        {
        }

        bool WindowsFlurryMetricsService::IsEnabled() const
        {
            return m_enabled;
        }
    }
}
