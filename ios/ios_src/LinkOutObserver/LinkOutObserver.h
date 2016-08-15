// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

#include <string>

#include "Metrics.h"
#include "PersistentSettings.h"
#include <memory>

namespace ExampleApp
{
    namespace LinkOutObserver
    {
        class LinkOutObserver : private Eegeo::NonCopyable
        {
        private:
            const std::shared_ptr<Metrics::IMetricsService> m_metricsService;
            const std::shared_ptr<PersistentSettings::IPersistentSettingsModel> m_persistentSettingsModel;
            
            void CheckResumeFromLink() const;
            
        public:
            LinkOutObserver(const std::shared_ptr<Metrics::IMetricsService>& metricsService,
                            const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettingsModel);
            
            ~LinkOutObserver();
            
            void OnAppStart() const;
            
            void OnAppResume() const;
            
            void OnLinkOut(const std::string& linkHost) const;
        };
    }
}