// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

#include <string>

#include "Metrics.h"
#include "PersistentSettings.h"

namespace ExampleApp
{
    namespace LinkOutObserver
    {
        class LinkOutObserver : private Eegeo::NonCopyable
        {
        private:
            Metrics::IMetricsService& m_metricsService;
            PersistentSettings::IPersistentSettingsModel& m_persistentSettingsModel;
            
            void CheckResumeFromLink() const;
            
        public:
            LinkOutObserver(Metrics::IMetricsService& metricsService,
                            PersistentSettings::IPersistentSettingsModel& persistentSettingsModel);
            
            ~LinkOutObserver();
            
            void OnAppStart() const;
            
            void OnAppResume() const;
            
            void OnLinkOut(const std::string& linkHost) const;
        };
    }
}